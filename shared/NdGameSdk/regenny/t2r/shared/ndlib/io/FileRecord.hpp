#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "PathString.hpp"
namespace regenny::shared::ndlib::io {
#pragma pack(push, 1)
struct FileRecord {
    enum HandleObjType : uint32_t {
        kHandleInvalid = 0,
        kHandleWin32 = 1,
        kHandleDSFile = 2,
    };

    enum FileState : uint32_t {
        kStateRaw = 0,
        kStateArchive = 1,
    };

    struct RBTreeHeader {
        regenny::shared::ndlib::io::FileRecord** m_Parent; // 0x0
        regenny::shared::ndlib::io::FileRecord** m_Left; // 0x8
        regenny::shared::ndlib::io::FileRecord** m_Right; // 0x10
    }; // Size: 0x18

    struct HandleObj {
        void* m_obj; // 0x0
        regenny::shared::ndlib::io::FileRecord::HandleObjType m_type; // 0x8
        private: char pad_c[0x4]; public:
    }; // Size: 0x10

    regenny::shared::ndlib::io::FileRecord* m_left; // 0x0
    regenny::shared::ndlib::io::FileRecord* m_parent; // 0x8
    regenny::shared::ndlib::io::FileRecord* m_right; // 0x10
    bool m_isBlack; // 0x18
    bool m_isHeader; // 0x19
    private: char pad_1a[0x6]; public:
    regenny::shared::ndlib::io::PathString m_pathStr; // 0x20
    FileState m_state; // 0x40
    private: char pad_44[0x4]; public:
    uint64_t m_fileSize; // 0x48
    HandleObj m_handleObj; // 0x50
    uint32_t m_refCount; // 0x60
    uint32_t m_openIndex; // 0x64
    wchar_t m_path[260]; // 0x68
}; // Size: 0x270
#pragma pack(pop)
}
