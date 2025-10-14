#pragma once
#include "NdGameSdk/sdk.hpp"

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/corelib/util/Err.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/corelib/util/Err.hpp>
#endif

#include "..\system\NdSystem.hpp"

#include <Utility/assertion/assert.hpp>
#include <Utility/function_ptr.hpp>

namespace NdGameSdk::corelib::util {

    #define ERROR_CODE_MASK 0x0000FFFFu

	class NdGameSdk_API Err : public ISdkRegenny<regenny::shared::corelib::util::Err> {
	public:
		using Raw = regenny::shared::corelib::util::Err;

        // Domains
        using Domain = Raw::ErrDomain;

        // Subcodes per domain
        using AuxDefaultError = Raw::ErrAuxDefaultError;
        using AuxDefaultSuccess = Raw::ErrAuxDefaultSuccess;
        using EnvSuccess = Raw::ErrEnvSuccess;
        using EnvError = Raw::ErrEnvError;
        using DBSuccess = Raw::ErrDBSuccess;
        using DBError = Raw::ErrDBError;
        using MsgIPCSuccess = Raw::ErrMsgIPCSuccess;
        using MsgIPCError = Raw::ErrMsgIPCError;
        using CgfxSuccess = Raw::ErrCgfxSuccess;
        using CgfxError = Raw::ErrCgfxError;
        using GameSuccess = Raw::ErrGameSuccess;
        using GameError = Raw::ErrGameError;
        using AudioSuccess = Raw::ErrAudioSuccess;
        using AudioError = Raw::ErrAudioError;

        Err() {
            auto* self = this->Get();
            self->m_code = 0;
        }

        uint32_t code() const;
        uint32_t winCode() const;
        uint16_t domain() const;
        uint16_t sub() const;
        bool isError() const;
        bool isOK() const;

        std::string_view Describe();

        static constexpr uint32_t Make(uint16_t domain, uint16_t sub) {
            return (uint32_t(sub) | (uint32_t(domain & 0x07FFu) << 16));
        }

        static constexpr Domain GetDomain(uint32_t code) {
            return Domain((code >> 16) & 0x07FFu);
        }

        static constexpr uint16_t GetSub(uint32_t code) {
            return static_cast<uint16_t>(code & 0xFFFFu);
        }

        template <class SubEnum>
        static constexpr SubEnum GetSubAs(uint32_t code) {
            return static_cast<SubEnum>(GetSub(code));
        }

        static constexpr bool IsError(uint32_t code) {
            return static_cast<int32_t>(code) > 0;
        }

#if defined(_WIN32)
        static Err* FromWinError(Err* pOutErr, uint32_t winErr);
#endif

        static constexpr uint32_t kOK = 0u;
	private:
        TYPEDEF_FUNCTION_PTR(const char*, NdSystem_Err_Describe, Err* pError);
		friend class corelib::system::NdSystem;
	};

	static_assert(sizeof(Err) == 0x10, "Size of Err is not correct.");

}