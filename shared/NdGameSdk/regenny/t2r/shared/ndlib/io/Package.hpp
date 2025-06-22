#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "LoadingHeapMgr.hpp"
namespace regenny::shared::gamelib::level {
struct Level;
}
namespace regenny::shared::ndlib::io {
#pragma pack(push, 1)
struct Package {
    enum PakItem : uint32_t {
        INTERACTIVE_BG_1 = 79,
        NAV_MESH_1 = 33,
        PATH_TRACING_1 = 73,
        NURBS_TABLE_1 = 29,
        MOTION_MATCH_SET_1 = 72,
        VOXELIZATION_1 = 70,
        TEXTURE_TABLE = 1,
        CAMERA_TABLE_1 = 30,
        PM_FG_PROTOTYPES = 50,
        LEVEL_FLOOR_PATS_1 = 48,
        LEVEL_FLOOR_PATS_2 = 63,
        TEXTURE_BLOB_TABLE_1 = 81,
        CIN_SEQUENCE_1 = 68,
        SPHERE_TREE_NODE_1 = 21,
        COLLISION_DATA_BACKGROUND = 7,
        JSON_GEOMETRY = 24,
        SPLINE_TABLE = 16,
        GRAPH_TABLE = 13,
        VIS_CHEAT = 54,
        CUTSCENE_DATA = 15,
        LEVEL_PATS_1 = 47,
        LEVEL_PATS_2 = 62,
        COLLISION_DATA_HAVOK_BG = 44,
        PACKAGE_ITEM_LOOKUP = 10,
        INSTANCE_TAGS_1 = 53,
        VERTEX_SHADER_TABLE = 2,
        ANIMATED_LIGHTS = 77,
        SPECULAR_CUBEMAPSET = 61,
        LIGHT_TABLE_1 = 18,
        SOUND_BANK_TABLE = 49,
        PM_COLLECTION_1 = 22,
        PM_COLLECTION_2 = 23,
        LEVEL_OFFSET_1 = 31,
        DEBUG_INFO_1 = 28,
        AMBSHADOWS_OCCLUDER_INFO = 55,
        JSON_DOC = 57,
        TAG_INT = 38,
        COLLISION_DATA_CLOTH = 9,
        LEVEL_BOUNDING_BOX_DATA = 66,
        REGION_TREE = 14,
        ACTOR_FLAGS = 74,
        RES_ITEM_ART_ITEM = 11,
        POPULATOR_1 = 71,
        CINEMATIC_1 = 67,
        FEATURE_DB_2 = 35,
        ANIM = 41,
        NAV_MESH_HEIGHT_MAP_TEX_1 = 76,
        FT_SVG = 80,
        RIVER_SECTION = 17,
        GEOMETRY_1 = 25,
        TAG_FLOAT = 39,
        TEXTURE_DICTIONARY = 64,
        UI_TEXTURES_METADATA = 75,
        FOREGROUND_SECTION_2 = 6,
        WATER_DATA = 36,
        TAG_VEC4 = 40,
        VIS_INFO_1 = 32,
        BG_COLLISION_DEBUG_INFO = 78,
        SPAWNER_GROUP = 12,
        TAG_STRING = 37,
        NAV_LEDGE_GRAPH_1 = 34,
        JOINT_HIERARCHY = 43,
        KD_TREE_1 = 65,
        KD_TREE_2 = 69,
        ANIM_GROUP = 42,
        ATTACHED_FG_MAPPING = 26,
        ANIM_STREAM = 51,
        EFFECT_TABLE = 20,
        BACKGROUND_SECTION = 4,
        LEVEL_INFO_3 = 59,
        LEVEL_INFO_2 = 58,
        LEVEL_INFO_1 = 46,
        LEVEL_INFO_4 = 60,
        FOREGROUND_SECTION = 5,
        NAME_TABLE_1 = 52,
        PIXEL_SHADER_TABLE = 3,
        MATERIAL_TABLE_1 = 19,
        SHRUB_COLLECTION_2 = 27,
        COLLISION_DATA_FOREGROUND = 8,
    };

    enum Status : uint8_t {
        PackageStatusUnused = 0,
        PackageStatusInvalid = 1,
        PackageStatusFailedOptionalFile = 2,
        PackageStatusLoading = 3,
        PackageStatusLoaded = 4,
        PackageStatusUnloading = 5,
    };

    struct PakHeader {
        uint32_t m_magic; // 0x0
        uint32_t m_hdrSize; // 0x4
        uint32_t m_pakLoginTableIdx; // 0x8
        uint32_t m_pakLoginTableOffset; // 0xc
        uint32_t m_pageCt; // 0x10
        uint32_t m_pakPageEntryTableOffset; // 0x14
        uint32_t m_numPointerFixUpPages; // 0x18
        uint32_t m_pointerFixUpTableOffset; // 0x1c
        uint32_t m_dataSize; // 0x20
        uint32_t m_LoginTableIdx; // 0x24
        uint32_t m_VramTableOffset; // 0x28
        uint32_t m_field2c; // 0x2c
        uint32_t m_field30; // 0x30
        uint32_t m_field34; // 0x34
        uint32_t m_field38; // 0x38
        uint32_t m_hdrsizeleft; // 0x3c
    }; // Size: 0x40

    struct PakPageEntry {
        uint32_t m_resPageOffset; // 0x0
        uint32_t m_pageSize; // 0x4
        uint32_t m_owningPackageIndex; // 0x8
    }; // Size: 0xc

    struct ResPage {
    }; // Size: 0x0

    struct ResItem {
        uint64_t m_resNameStrOffset; // 0x0
        private: char pad_8[0x8]; public:
        uint32_t m_pageSize; // 0x10
        private: char pad_14[0x4]; public:
        StringId64 m_ResourceId; // 0x18
        StringId64 m_resourceTypeId; // 0x20
        uint32_t m_field28; // 0x28
        uint32_t m_field2c; // 0x2c
    }; // Size: 0x30

    struct PakVramItemTable {
        uint32_t m_nVramItems; // 0x0
        private: char pad_4[0x4]; public:
        regenny::shared::ndlib::io::Package::ResItem* m_items; // 0x8
    }; // Size: 0x10

    private: char pad_0[0x8]; public:
    uint64_t m_field8; // 0x8
    uint64_t m_size; // 0x10
    uint32_t m_numAllocatedPages; // 0x18
    uint32_t m_field1c; // 0x1c
    uint32_t m_LoginTableFlags[600]; // 0x20
    regenny::shared::ndlib::io::LoadingHeapMgr::LevelHeapType m_levelheaptype; // 0x980
    private: char pad_984[0x4]; public:
    uint64_t m_ChunkSize; // 0x988
    uint32_t m_hdrSize; // 0x990
    uint32_t m_pageCt; // 0x994
    uint32_t m_dataSize; // 0x998
    uint32_t m_field99c; // 0x99c
    uint32_t m_field9a0; // 0x9a0
    uint32_t m_field9a4; // 0x9a4
    uint64_t m_VirtualMemoryAddressRange; // 0x9a8
    regenny::shared::gamelib::level::Level* m_Level; // 0x9b0
    private: char pad_9b8[0x10]; public:
    // Metadata: utf8*
    char m_packname[128]; // 0x9c8
    StringId64 m_packid; // 0xa48
    private: char pad_a50[0x1]; public:
    // Metadata: utf8*
    char m_packfilepath[128]; // 0xa51
    private: char pad_ad1[0x7]; public:
    StringId64 m_packfilepathid; // 0xad8
    PakVramItemTable* m_VramItemTable; // 0xae0
    uint32_t m_fieldae8; // 0xae8
    Status m_status; // 0xaec
    private: char pad_aed[0x1013]; public:
}; // Size: 0x1b00
#pragma pack(pop)
}
