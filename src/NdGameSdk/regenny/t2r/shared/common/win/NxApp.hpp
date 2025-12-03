#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::common::win {
#pragma pack(push, 1)
struct NxApp {
    struct NixxesLogger {
        struct VTable {
            private: char pad_8[0x60]; public:
            virtual ~VTable() = default;
            virtual uint64_t Startup() = 0;
            virtual bool OpenAndRedirectStdIO() = 0;
            private: virtual void virtual_function_3() = 0; public:
            private: virtual void virtual_function_4() = 0; public:
            private: virtual void virtual_function_5() = 0; public:
            private: virtual void virtual_function_6() = 0; public:
            private: virtual void virtual_function_7() = 0; public:
            virtual void WriteRawLine(char* src) = 0;
            virtual void LogF(char* arg2, char* arg3, uint64_t arg4) = 0;
        }; // Size: 0x68

        VTable* vftable; // 0x0
        bool m_initialized; // 0x8
        private: char pad_9[0x7]; public:
        void* m_StdOutputHandle; // 0x10
        uint32_t stdout_fd; // 0x18
        uint32_t stderr_fd; // 0x1c
        uint64_t m_field20; // 0x20
        private: char pad_28[0x100228]; public:
    }; // Size: 0x100250

    void* m_field0; // 0x0
    void* m_field8; // 0x8
    void* m_field10; // 0x10
    void* m_field18; // 0x18
    void* m_field20; // 0x20
    NixxesLogger* m_logger; // 0x28
    private: char pad_30[0xe8]; public:
}; // Size: 0x118
#pragma pack(pop)
}
