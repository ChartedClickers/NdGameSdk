#pragma once
#include <std/sys.pat>
#include <std/core.pat>
#include <std/string.pat>
#include <hex/provider.pat>

using StringId64 = u64;

namespace DC {

    enum SymbolId : StringId64 {
        // reserved symbols
        top_level = 0x8666BEE87D00EAD3, // top-level
        _exclude_from_global_namespace_ = 0x1715E5AF53E3474E, // **exclude-from-global-namespace**
        _namespace_ = 0x253BB602E393A4CC, // **namespace**
        enable_struct_instancing = 0x837031DD7AF4B90B, // *enable-struct-instancing*
        _allow_rebind_ = 0x8A033868145A533F, // **allow-rebind**
        disable_relocation = 0xAD007EAC63692400, // disable-relocation
        
        modules = 0x0B4B7080C994E5B8, // *modules*
        namespace_capacities = 0x0A66B0FB2349C513, // *namespace-capacities*
        namespace_array = 0x158968AC18929F74, // *namespace-array*
        audio_module_array = 0x20FC10F914F3A8C6, // *audio-module-array*
        module_array_debug = 0x6F1C1C18825A62CF, // *module-array-debug*
        module_array_debug_sp = 0x9A22FEB66C570A95, // *module-array-debug-sp*
        all_vox_igc_levels = 0xC00B1626CBFCCBE6, // *all-vox-igc-levels*
        module_array = 0xF3267F82646520ED, // *module-array*
        module_array_sp = 0xF67FE941AA1605AB, // *module-array-sp*
        joypad_adrenaline_hold_square = 0x1EBF2A74C5A1B002, // *joypad-adrenaline-hold-square*
        persistent_command_list = 0x0D4214F3AB9F95C3, // *persistent-command-list*
        mouse_default_settings = 0x153A061C977AB3B4, // *mouse-default-settings*
        analog_stick_icon_paths = 0x6ECB9D5F76F9A2E7, // *analog-stick-icon-paths*
        melee_override_ids = 0x7E555F8321D35D11, // *melee-override-ids*
        weapon_cross_press_release_blacklist = 0xB8A76AAD46BA03C6, // *weapon-cross-press-release-blacklist*
        joypad_additional_presets = 0xF1F762C8F706097D, // *joypad-additional-presets*
        action_map = 0x939AA361BA96F916, // *action-map*
    };

    enum Type : StringId64 {
        Array = 0x4F9E14B634C6B026, // @ array
        _array = 0x104D3D9BAD9D2464, // @ array*
        map = 0x080F5919176D2D91, // @ map
        _float = 0xA00A62A942B20165, // @ float
        int32 = 0xF9E1C08F4291A8DF, // @ int32
        symbol = 0xE81B0096BC73F511, // @ symbol
        string = 0x704BE0D8FAAFFC58, // @ string
        symbol_array = 0xC8F749F92779D489, // @ symbol-array
        module_info_array = 0xE442DCB00300FB28, // @ module-info-array
        action_scheme = 0x9FF30B9A5C83CB5D, // @ action-scheme
        command_list = 0xB18C294ADE7B782B, // @ joypad-persistent-command-list
        mouse_default_settings = 0xD6BCF8E23269E80E, // @ mouse-default-settings
        action_collection = 0xAF5C458ED236456E, // @ action-collection
    };

    // @ Array
    struct Array<T> {
        T *m_value : u64;
    };

    // @ Array | @ array*
    struct FixedSizeArray<T> {
        $ += 0x8;
        u32 m_FixedSize;
        $ -= 0xc;
        T *m_value[m_FixedSize] : u64;
    };

    // @ map
    struct map<_Kty,_Ty> {
        u64 m_size;
        _Kty *m_key[m_size] : _Kty;
        _Ty *m_value[m_size] : u64;
    };

    // @ symbol-array
    struct SymbolArray {
        u64 m_Count;
        StringId64 *m_Symbols[m_Count] : StringId64;
     };

    // @ string
    struct String {
        char *string[] : u64;
    };

}


struct NullablePtr<T> {
    u64 pointerValue [[no_unique_address, hidden]];
    if (pointerValue == 0x0) {
        u64 m_nullptr;
    } else {
        T *m_dataptr : u64;
    }
};

struct NullableCharPtr {
    u64 pointerValue [[no_unique_address, hidden]];
    if (pointerValue == 0x0) {
        u64 m_nullptr;
    } else {
        char *m_charptr[] : u64;
    }
};