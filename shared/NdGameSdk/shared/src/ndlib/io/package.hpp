#pragma once

#include "NdGameSdk/sdk.hpp"

#include <NdGameSdk/shared/src/gamelib/level/level.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/io/Package.hpp>
#include <NdGameSdk/regenny/t2r/shared/ndlib/io/PakLoginTableEntry.hpp>
#endif

#include <Utility/helper.hpp>
#include <Utility/function_ptr.hpp>

using namespace NdGameSdk::gamelib::level;

namespace NdGameSdk::ndlib::io {
#if defined(T2R)
	class NdGameSdk_API Package : public ISdkRegenny<regenny::shared::ndlib::io::Package> 
	{
	public:
		using PakItem = regenny::shared::ndlib::io::Package::PakItem;
        using Status = regenny::shared::ndlib::io::Package::Status;
		using LoginStage = regenny::shared::ndlib::io::Package::LoginStage;

        enum ItemId : StringId64 {
			PAK_LOGIN_TABLE = SID("PAK_LOGIN_TABLE"),
            INTERACTIVE_BG_1 = SID("INTERACTIVE_BG_1"),
            NAV_MESH_1 = SID("NAV_MESH_1"),
            PATH_TRACING_1 = SID("PATH_TRACING_1"),
            NURBS_TABLE_1 = SID("NURBS_TABLE_1"),
            MOTION_MATCH_SET_1 = SID("MOTION_MATCH_SET_1"),
            VOXELIZATION_1 = SID("VOXELIZATION_1"),
            TEXTURE_TABLE = SID("TEXTURE_TABLE"),
            CAMERA_TABLE_1 = SID("CAMERA_TABLE_1"),
            PM_FG_PROTOTYPES = SID("PM_FG_PROTOTYPES"),
            LEVEL_FLOOR_PATS_1 = SID("LEVEL_FLOOR_PATS_1"),
            LEVEL_FLOOR_PATS_2 = SID("LEVEL_FLOOR_PATS_2"),
            TEXTURE_BLOB_TABLE_1 = SID("TEXTURE_BLOB_TABLE_1"),
            CIN_SEQUENCE_1 = SID("CIN_SEQUENCE_1"),
            SPHERE_TREE_NODE_1 = SID("SPHERE_TREE_NODE_1"),
            COLLISION_DATA_BACKGROUND = SID("COLLISION_DATA_BACKGROUND"),
            JSON_GEOMETRY = SID("JSON_GEOMETRY"),
            SPLINE_TABLE = SID("SPLINE_TABLE"),
            GRAPH_TABLE = SID("GRAPH_TABLE"),
            VIS_CHEAT = SID("VIS_CHEAT"),
            CUTSCENE_DATA = SID("CUTSCENE_DATA"),
            LEVEL_PATS_1 = SID("LEVEL_PATS_1"),
            LEVEL_PATS_2 = SID("LEVEL_PATS_2"),
            COLLISION_DATA_HAVOK_BG = SID("COLLISION_DATA_HAVOK_BG"),
            PACKAGE_ITEM_LOOKUP = SID("PACKAGE_ITEM_LOOKUP"),
            INSTANCE_TAGS_1 = SID("INSTANCE_TAGS_1"),
            VERTEX_SHADER_TABLE = SID("VERTEX_SHADER_TABLE"),
            ANIMATED_LIGHTS = SID("ANIMATED_LIGHTS"),
            SPECULAR_CUBEMAPSET = SID("SPECULAR_CUBEMAPSET"),
            LIGHT_TABLE_1 = SID("LIGHT_TABLE_1"),
            SOUND_BANK_TABLE = SID("SOUND_BANK_TABLE"),
            PM_COLLECTION_1 = SID("PM_COLLECTION_1"),
            PM_COLLECTION_2 = SID("PM_COLLECTION_2"),
            LEVEL_OFFSET_1 = SID("LEVEL_OFFSET_1"),
            DEBUG_INFO_1 = SID("DEBUG_INFO_1"),
            AMBSHADOWS_OCCLUDER_INFO = SID("AMBSHADOWS_OCCLUDER_INFO"),
            JSON_DOC = SID("JSON_DOC"),
            TAG_INT = SID("TAG_INT"),
            COLLISION_DATA_CLOTH = SID("COLLISION_DATA_CLOTH"),
            LEVEL_BOUNDING_BOX_DATA = SID("LEVEL_BOUNDING_BOX_DATA"),
            REGION_TREE = SID("REGION_TREE"),
            ACTOR_FLAGS = SID("ACTOR_FLAGS"),
            RES_ITEM_ART_ITEM = SID("RES_ITEM_ART_ITEM"),
            POPULATOR_1 = SID("POPULATOR_1"),
            CINEMATIC_1 = SID("CINEMATIC_1"),
            FEATURE_DB_2 = SID("FEATURE_DB_2"),
            ANIM = SID("ANIM"),
            NAV_MESH_HEIGHT_MAP_TEX_1 = SID("NAV_MESH_HEIGHT_MAP_TEX_1"),
            FT_SVG = SID("FT_SVG"),
            RIVER_SECTION = SID("RIVER_SECTION"),
            GEOMETRY_1 = SID("GEOMETRY_1"),
            TAG_FLOAT = SID("TAG_FLOAT"),
            TEXTURE_DICTIONARY = SID("TEXTURE_DICTIONARY"),
            UI_TEXTURES_METADATA = SID("UI_TEXTURES_METADATA"),
            FOREGROUND_SECTION_2 = SID("FOREGROUND_SECTION_2"),
            WATER_DATA = SID("WATER_DATA"),
            TAG_VEC4 = SID("TAG_VEC4"),
            VIS_INFO_1 = SID("VIS_INFO_1"),
            BG_COLLISION_DEBUG_INFO = SID("BG_COLLISION_DEBUG_INFO"),
            SPAWNER_GROUP = SID("SPAWNER_GROUP"),
            TAG_STRING = SID("TAG_STRING"),
            NAV_LEDGE_GRAPH_1 = SID("NAV_LEDGE_GRAPH_1"),
            JOINT_HIERARCHY = SID("JOINT_HIERARCHY"),
            KD_TREE_1 = SID("KD_TREE_1"),
            KD_TREE_2 = SID("KD_TREE_2"),
            ANIM_GROUP = SID("ANIM_GROUP"),
            ATTACHED_FG_MAPPING = SID("ATTACHED_FG_MAPPING"),
            ANIM_STREAM = SID("ANIM_STREAM"),
            EFFECT_TABLE = SID("EFFECT_TABLE"),
            BACKGROUND_SECTION = SID("BACKGROUND_SECTION"),
            LEVEL_INFO_3 = SID("LEVEL_INFO_3"),
            LEVEL_INFO_2 = SID("LEVEL_INFO_2"),
            LEVEL_INFO_1 = SID("LEVEL_INFO_1"),
            LEVEL_INFO_4 = SID("LEVEL_INFO_4"),
            FOREGROUND_SECTION = SID("FOREGROUND_SECTION"),
            NAME_TABLE_1 = SID("NAME_TABLE_1"),
            PIXEL_SHADER_TABLE = SID("PIXEL_SHADER_TABLE"),
            MATERIAL_TABLE_1 = SID("MATERIAL_TABLE_1"),
            SHRUB_COLLECTION_2 = SID("SHRUB_COLLECTION_2"),
            COLLISION_DATA_FOREGROUND = SID("COLLISION_DATA_FOREGROUND")
        };

        class PakHeader : public ISdkRegenny<regenny::shared::ndlib::io::Package::PakHeader> {};
        class PakPageEntry : public ISdkRegenny<regenny::shared::ndlib::io::Package::PakPageEntry> {};

        class ResPage : public ISdkRegenny<regenny::shared::ndlib::io::Package::ResPage> {};

        class ResItem : public ISdkRegenny<regenny::shared::ndlib::io::Package::ResItem> {
        public:
			const char* GetResourceName() const;

            size_t GetPageSize() const;

			StringId64 GetResourceId() const;
			StringId64 GetResourceTypeId() const;

            ItemId GetResourceType() const;

        };

		size_t GetSize() const;
		size_t GetHdrSize() const;
        size_t GetDataSize() const;
		uint32_t GetNumAllocatedPages() const;
		uint32_t GetNumPages() const;
		uint32_t GetNumRequests() const;

		void* GetVirtualMemoryAddressRange() const;
		Level* GetLevel() const;

		const char* GetName() const;
		const char* GetPackPath() const;

		bool IsLoginFinalized() const;

		StringId64 GetPackId() const;
		StringId64 GetPackPathId() const;

		Status GetStatus() const;
        std::string GetStatusString();

		LoginStage GetLoginStage() const;

        static std::string GetStatusString(Status status);

        inline static constexpr uint32_t kMaxSubPagesPerPackage = 0x258;
        inline static constexpr uint32_t kMaxNameLength = 0x80;
	};

    class PakLoginTableEntry : public ISdkRegenny<regenny::shared::ndlib::io::PakLoginTableEntry, Package::ResItem> {
    public:
        class ResourcePair : public ISdkRegenny<regenny::shared::ndlib::io::PakLoginTableEntry::ResourcePair> {
        public:
            uint32_t GetPageIdx() const;
            uint32_t GetItemOfs() const;
        };

        uint32_t GetMaxResources() const;
        ResourcePair* GetPairs();
        const ResourcePair* GetPairs() const;
    };

    TYPEDEF_EXTERN_FUNCTION_PTR(Package::PakItem, PackageMgr_Package_ResolvePakItem, Package::ItemId ItemId);
    TYPEDEF_EXTERN_FUNCTION_PTR(const char*, PackageMgr_Package_GetStatusString, Package::Status status);

	static_assert(sizeof(Package) == 0x1b00, "Package size mismatch");
	static_assert(sizeof(Package::PakHeader) == 0x40, "Package::PakHeader size mismatch");
	static_assert(sizeof(Package::ResItem) == 0x30, "Package::ResItem size mismatch");
#endif
}