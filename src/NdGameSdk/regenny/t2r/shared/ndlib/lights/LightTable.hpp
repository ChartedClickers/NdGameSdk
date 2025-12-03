#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::lights {
#pragma pack(push, 1)
struct LightTable {
    struct PointLight {
        vec3 m_color; // 0x0
        vec3 m_pos; // 0xc
        vec3 m_dir; // 0x18
        vec3 m_center; // 0x24
        uint32_t m_flags; // 0x30
        float m_radius; // 0x34
        float m_shapeRadius; // 0x38
        float m_startDistance; // 0x3c
        float m_startRange; // 0x40
        float m_intensity; // 0x44
        float m_minRoughness; // 0x48
        float m_specScale; // 0x4c
        float m_shapeRadiusEyeScale; // 0x50
    }; // Size: 0x54

    struct AreaLight : public PointLight {
        float m_width; // 0x54
        float m_height; // 0x58
    }; // Size: 0x5c

    struct SpotLight : public PointLight {
        float m_coneAngle; // 0x54
        float m_penumbraAngle; // 0x58
        float m_dropOff; // 0x5c
        private: char pad_60[0x4]; public:
    }; // Size: 0x64

    struct DirLight : public PointLight {
    }; // Size: 0x54

    uint32_t m_version; // 0x0
    private: char pad_4[0x4]; public:
    // Metadata: utf8*
    char* m_name; // 0x8
    uint32_t m_pointCount; // 0x10
    uint32_t m_areaCount; // 0x14
    uint32_t m_spotCount; // 0x18
    uint32_t m_dirCount; // 0x1c
    uint32_t m_projectorCount; // 0x20
    private: char pad_24[0x4]; public:
    PointLight* m_pointArray; // 0x28
    AreaLight* m_areaArray; // 0x30
    SpotLight* m_spotArray; // 0x38
    DirLight* m_dirArray; // 0x40
    void* m_projArray; // 0x48
    private: char pad_50[0x20]; public:
}; // Size: 0x70
#pragma pack(pop)
}
