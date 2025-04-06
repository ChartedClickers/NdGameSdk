#include "DevSandboxMod.hpp"
#include <codecvt>
namespace ExampleMod
{
	void DevSandboxMod::OnNdModinitialize()
	{
		auto SomeComponent1 = GetSharedSdkComponent<ndlib::EngineComponents>().get();

	#if defined(T2R)
		auto module = Utility::memory::get_executable();

		std::wstring_convert<std::codecvt_utf8<wchar_t>> wstring_converter{};

		const unsigned char IsTestTasksAvailableTrue[] = { 0x40, 0xb6, 0x01 };

		static Patch::Ptr TestTasksMenu = Utility::WritePatchPattern(module, L"48 89 5c 24 08 48 89 74 24 10 48 89 7c 24 18 55 41 54 41 55 41 56 41 57 48 8b ec 48 83 ec 70 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 45 f8 b9 e0 00 00 00", IsTestTasksAvailableTrue, sizeof(IsTestTasksAvailableTrue),
			wstr(TestTasksMenu), +0x92);

		if (TestTasksMenu) {
			spdlog::info("{} patch applied", wstring_converter.to_bytes(TestTasksMenu->GetName()));
		}
		else {
			spdlog::error("{} patch failed", wstring_converter.to_bytes(TestTasksMenu->GetName()));
		}
	#endif

	}

}