#include "error.hpp"

namespace NdGameSdk::corelib::util {

    static constexpr const char* kSuccess = "Success";

    static constexpr const char* kAuxDefaultErr[] = {
        "General error",
        "Wrong state",
        "Bad data",                 
        "Abort",                    
        "Out of memory",            
        "Not found",                
        "Not initialized",          
        "Already initialized",      
        "Invalid argument",         
        "Out of Fios2 File Handles",
        "Out of Fios2 Op Handles",  
    };
    static constexpr const char* kAuxDefaultSucc[] = {
        "Success with warning",
        "Success code, aux default",
        "In progress", 
        "Unknown default subsystem success",
    };

    static constexpr const char* kEnvSucc[] = { "Success" };
    static constexpr const char* kEnvErr[] = { "Unknown environment subsystem error" };

    static constexpr const char* kDBSucc[] = { "Success code, aux database" };
    static constexpr const char* kDBErr[] = {
        "Generic SQL failure", 
        "Cannot connect to SQL server",
        "Result contains too many records",
        "Unknown database subsystem error",
    };

    static constexpr const char* kMsgIPCSucc[] = {
        "A response was received for the message specified",
    };
    static constexpr const char* kMsgIPCErr[] = {
        "The socket returned an unspecified error",          
        "There is no message available at this time",        
        "No more messages can be sent until a reply...",     
        "A special character in the message is unrecognized",
        "Reply timeout exceeded",                            
        "Outgoing message buffer is full",                   
        "Incoming message buffer underrun",                  
        "Read-string buffer too small",                      
        "Attempted double response",                         
        "Invalid message id",                                
        "Response received for different message",           
        "All responses already sent",                        
    };

    static constexpr const char* kCgfxSucc[] = { "Success code, cgfx compiler" };
    static constexpr const char* kCgfxErr[] = { "Generic cgfx compiler error" };

    static constexpr const char* kGameSucc[] = { "Success" };
    static constexpr const char* kGameErr[] = {
        "Missing level/package",      
        "Anim Actor Symbol Not Found",
        "Anim Actor Login Failed",    
        "Art Group Not Found",        
        "Script Id Not Found",           
        "Physics Failed to Init (no collision?)",
        "Missing Spawner",      
        "Missing State Script", 
        "Mesh Not Loaded",      
        "Skeleton Not Loaded",  
        "Spawning Suppressed",  
    };

    static constexpr const char* kAudioSucc[] = { "Unknown success" };
    static constexpr const char* kAudioErr[] = {
        "Unknown error",             
        "Audio not enabled",         
        "System not initialized",    
        "System already initialized",
        "Audio system not started",  
        "Out of synths",             
        "Out of voices",             
        "Invalid vibration handle",  
        "Invalid voice handle",      
        "Invalid plugin",            
        "Invalid oscillator",        
        "Invalid argument",          
    };

    static constexpr std::string_view pick(const char* const* tbl, size_t count, 
        uint16_t idx, std::string_view fallback) noexcept {
        return (idx < count && tbl[idx]) ? std::string_view(tbl[idx]) : fallback;
    }

    static std::string_view crt_or_posix_str(int err, std::string_view unknown) {
        thread_local char buf[128];
    #if defined(_WIN32)
        if (strerror_s(buf, sizeof(buf), err) == 0)
            return buf;
    #else
        if (std::strlen(std::strerror(err)) < sizeof(buf)) {
            std::strncpy(buf, std::strerror(err), sizeof(buf));
            buf[sizeof(buf) - 1] = '\0';
            return buf;
        }
    #endif
        return unknown;
    }

    uint32_t Err::code() const { return this->Get()->m_code; }
    uint32_t Err::winCode() const { return this->Get()->m_winCode; }
    uint16_t Err::domain() const { return GetDomain(this->Get()->m_code); }
    uint16_t Err::sub() const { return GetSub(this->Get()->m_code); }
    bool Err::isError() const { return IsError(this->Get()->m_code); }
    bool Err::isOK() const { return this->Get()->m_code == kOK; }

    std::string_view Err::Describe() {
		if (NdSystem_Err_Describe) {
			return NdSystem_Err_Describe(this);
		}
		
        const Raw* e = this->Get();

        if (e->m_payload)
            return static_cast<const char*>(e->m_payload);

        if (e->m_code == kOK)
            return kSuccess;

        const Domain  dom = GetDomain(code());
        const uint16_t sub = GetSub(code());

        switch (dom) {
        case Domain::CRT:
            return crt_or_posix_str(static_cast<int>(sub), "Unknown C runtime error");

        case Domain::PosixSocket:
            return crt_or_posix_str(static_cast<int>(sub), "Unknown POSIX/socket error");

        case Domain::CgfxCompiler:
            return isError() ? kCgfxErr[0] : kCgfxSucc[0];

        case Domain::AuxDefault:
            return isError()
                ? pick(kAuxDefaultErr, std::size(kAuxDefaultErr), sub, "Unknown default subsystem error")
                : pick(kAuxDefaultSucc, std::size(kAuxDefaultSucc), sub, "Unknown default subsystem success");

        case Domain::AuxEnvironment:
            return isError()
                ? kEnvErr[0]
                : kEnvSucc[0];

        case Domain::AuxDatabase:
            return isError()
                ? pick(kDBErr, std::size(kDBErr), sub, "Unknown database subsystem error")
                : kDBSucc[0];

        case Domain::AuxMessageIPC:
            return isError()
                ? pick(kMsgIPCErr, std::size(kMsgIPCErr), sub, "Error from unknown subsystem")
                : pick(kMsgIPCSucc, std::size(kMsgIPCSucc), sub, "Unknown success");

        case Domain::AuxGameContent:
            return isError()
                ? pick(kGameErr, std::size(kGameErr), sub, "Unknown game content error")
                : kGameSucc[0];

        case Domain::AuxAudio:
            return isError()
                ? pick(kAudioErr, std::size(kAudioErr), sub, "Unknown audio error")
                : kAudioSucc[0];

        case Domain::AuxReserved:
        case Domain::AuxUnknown:
        default:
            return isError() ? "Unknown error" : "Unknown success";
        }

    }

#if defined(_WIN32)
    Err* Err::FromWinError(Err* pOutErr, uint32_t winErr) {
        always_assert(((winErr & ERROR_CODE_MASK) == winErr), "(nErr & ERROR_CODE_MASK) == nErr");

        constexpr uint32_t kWinDomainTag = 0x0F030000u;

        pOutErr->Get()->m_payload = nullptr;
        pOutErr->Get()->m_winCode = winErr;
        pOutErr->Get()->m_code = (winErr == 0) ? 0u : (kWinDomainTag | (winErr & ERROR_CODE_MASK));

        return pOutErr;

    }
#endif

    INIT_FUNCTION_PTR(Err::NdSystem_Err_Describe);

}