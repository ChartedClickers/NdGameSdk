#include "particle.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

namespace NdGameSdk::gamelib::render::particle {

	ParticleManager::ParticleManager() : ISdkComponent(TOSTRING(ParticleManager)) {}

	uintptr_t OnExecuteRootDataSelector_ReturnAddr = NULL;
	void OnExecuteRootDataSelector_CC();

	void ParticleManager::Awake() {
		auto SharedComponents = ISdkComponent::GetSharedComponents();
		m_Memory = SharedComponents->GetComponent<Memory>();
	}

	void ParticleManager::Initialize() {
		static std::once_flag Initialized;

		std::call_once(Initialized, [this] {

			spdlog::info("Initializing {} patterns...", GetName());

			auto MissingDependencies = CheckSdkComponents<Memory>({ m_Memory.get()});

			if (MissingDependencies.has_value()) {
				throw SdkComponentEx
				{ std::format("Missing necessary dependencies: {:s}", MissingDependencies.value()),
					SdkComponentEx::ErrorCode::DependenciesFailed };
			}


			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

			findpattern = Patterns::Particle_ParticleInternal_ParticleDebug;
			const auto pParticleDebug = (uintptr_t*)Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::Particle_ParticleInternal_ParticleDebug), findpattern.offset, 3, 7);

			if (!pParticleDebug) {
				throw SdkComponentEx
				{ std::format("Failed to find {}", TOSTRING(Patterns::Particle_ParticleInternal_ParticleDebug)),
					SdkComponentEx::ErrorCode::PatternFailed };
			}

			
			m_ParticleDebug.g_pParticleDebug = pParticleDebug;

			findpattern = Patterns::Particle_ParticleInternal_ParticleDebug_Constructor;
			m_ParticleDebug.ParticleDebug_ParticleDebug = (ParticleInternal::ParticleDebug::ParticleDebug_ParticleDebug_ptr)
				Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::Particle_ParticleInternal_ParticleDebug_Constructor), findpattern.offset);

			findpattern = Patterns::Particle_ParticleInternal_ParticleDebug_Init;
			m_ParticleDebug.ParticleDebug_Init = (ParticleInternal::ParticleDebug::ParticleDebug_Init_ptr)
				Utility::FindAndPrintPattern(module,
					findpattern.pattern, wstr(Patterns::Particle_ParticleInternal_ParticleDebug_Init), findpattern.offset);

			findpattern = Patterns::Particle_ParticleManager_Init;
			auto ParticleDebugInitJMP = (void*)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::Particle_ParticleManager_Init), findpattern.offset + 0x3DB);

			if (!m_ParticleDebug.ParticleDebug_ParticleDebug ||
				!m_ParticleDebug.ParticleDebug_Init ||
				!ParticleDebugInitJMP) {
				throw SdkComponentEx{ "Failed to find ParticleInternal::ParticleDebug:: game functions!", SdkComponentEx::ErrorCode::PatternFailed };
			}

			if (m_Memory->IsDebugMemoryAvailable()) {
				
				m_Memory->IncreaseMemoryMap(MemoryMapId::ALLOCATION_PARTICLE_MGR, MemSize(6.5, SizeUnit::Megabytes));

				m_ParticleDebug_InitHook = Utility::MakeMidHook(ParticleDebugInitJMP,
					[](SafetyHookContext& ctx)
					{
						auto particlemanager = GetSharedComponents()->GetComponent<ParticleManager>();

						constexpr uint64_t heap_size = 0xb8; //TODO: Make struct for this
						void* pParticleDebug_mem = particlemanager->m_Memory->m_HeapArena.Allocate(heap_size, MemoryContextType::kAllocParticleManager, __FUNCSIG__, __LINE__, __FILE__);

						if (pParticleDebug_mem) {

							ParticleInternal::ParticleDebug* ParticleDebug = &particlemanager->m_ParticleDebug;

							memset(pParticleDebug_mem, 0, heap_size);
							auto pParticleDebug = ParticleDebug->Constructor(pParticleDebug_mem);
							*reinterpret_cast<uintptr_t*>(ParticleDebug->g_pParticleDebug) = (uint64_t)pParticleDebug;
							ParticleDebug->Init(pParticleDebug);
						}

					}, wstr(Patterns::Particle_ParticleManager_Init), wstr(m_ParticleDebug_InitHook));


				findpattern = Patterns::Particle_ParticleInternal_RenderUpdate;
				m_ParticleDebug_RenderUpdatePatch = Utility::WritePatchPattern(module, findpattern.pattern, { 0x48, 0x8b, 0x19 },
					wstr(Patterns::Particle_ParticleInternal_RenderUpdate), findpattern.offset + 0x24);

				findpattern = Patterns::Particle_ParticleInternal_OnExecuteRootDataSelector;
				m_ParticleDebug_OnExecuteRootDataSelectorHook = Utility::WritePatchPattern_Hook(module, findpattern.pattern, wstr(Patterns::Particle_ParticleInternal_OnExecuteRootDataSelector),
					findpattern.offset + 0x58, (void*)OnExecuteRootDataSelector_CC);

				if (!m_ParticleDebug_InitHook ||
					!m_ParticleDebug_RenderUpdatePatch ||
					!m_ParticleDebug_OnExecuteRootDataSelectorHook) {
					throw SdkComponentEx{ "Failed Patch ParticleDebug functions!",
						SdkComponentEx::ErrorCode::PatchFailed };
				}

				OnExecuteRootDataSelector_ReturnAddr = m_ParticleDebug_OnExecuteRootDataSelectorHook->get_original();
			}
		});
	}


	void __attribute__((naked)) OnExecuteRootDataSelector_CC() {
		__asm {
			mov rax, qword ptr[rax];
			jmp[rip + OnExecuteRootDataSelector_ReturnAddr];
		}
	}
}