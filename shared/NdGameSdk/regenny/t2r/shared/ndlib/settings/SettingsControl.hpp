#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\corelib\containers\FixedSizeHashTable.hpp"
#include "..\..\corelib\containers\FixedSizeHeap.hpp"
#include "..\..\corelib\system\platform\ndsys.hpp"
namespace regenny::shared::ndlib::settings {
#pragma pack(push, 1)
struct SettingsControl {
    enum SettingFlags : uint8_t {
        Active = 1,
        Process = 2,
        Timed = 4,
        HasData = 8,
        ExternalData = 16,
    };

    struct Setting {
        void* m_ProcessPtr; // 0x0
        uint32_t m_ownerId; // 0x8
        uint64_t m_expireFrame; // 0xc
        uint32_t m_type; // 0x14
        private: char pad_18[0x8]; public:
        void* m_Callback; // 0x20
        void* m_valuePtr; // 0x28
        uint32_t m_bucketId; // 0x30
        uint32_t m_sequence; // 0x34
        private: char pad_38[0x8]; public:
        uint8_t m_data[68]; // 0x40
        private: char pad_84[0x4]; public:
        void* m_pData; // 0x88
        uint8_t m_cbByte; // 0x90
        regenny::shared::ndlib::settings::SettingsControl::SettingFlags m_flags; // 0x91
        private: char pad_92[0x6]; public:
        StringId64 m_key; // 0x98
    }; // Size: 0xa0

    struct HashNode : public regenny::shared::corelib::containers::FixedSizeHashTable::ListHead {
        regenny::shared::ndlib::settings::SettingsControl::Setting* m_pFirst; // 0x10
        regenny::shared::ndlib::settings::SettingsControl::Setting* m_pLast; // 0x18
    }; // Size: 0x20

    struct FixedSizeHashTable_corelib_containers_HashNode {
        regenny::shared::ndlib::settings::SettingsControl::HashNode** m_Buckets; // 0x0
        regenny::shared::corelib::containers::FixedSizeHeap m_Pool; // 0x8
        regenny::shared::ndlib::settings::SettingsControl::HashNode* m_Head; // 0x60
        uint64_t m_NodeSize; // 0x68
        uint64_t m_RequestedBuckets; // 0x70
        regenny::shared::ndlib::settings::SettingsControl::HashNode** m_Begin; // 0x78
        regenny::shared::ndlib::settings::SettingsControl::HashNode** m_End; // 0x80
        uint64_t m_Count; // 0x88
        uint32_t m_BucketCountAligned; // 0x90
        regenny::shared::corelib::containers::FixedSizeHashTable::Flags m_PeakAndFlags; // 0x94
    }; // Size: 0x98

    uint64_t m_usedMask[75][64]; // 0x0
    void* m_poolBase; // 0x9600
    void* m_bucketPtr[75]; // 0x9608
    uint32_t m_bucketTag[75]; // 0x9860
    uint32_t m_numUsedBuckets; // 0x998c
    uint32_t m_maxNumSettings; // 0x9990
    private: char pad_9994[0xc]; public:
    FixedSizeHashTable_corelib_containers_HashNode m_settingHashTable; // 0x99a0
    uint8_t m_rtFlag; // 0x9a38
    uint32_t m_rtCounter; // 0x9a39
    uint32_t m_nextSequence; // 0x9a3d
    private: char pad_9a41[0xf]; public:
    regenny::shared::corelib::system::platform::ndsys::WaitLock m_waitListLock; // 0x9a50
}; // Size: 0x9a70
#pragma pack(pop)
}
