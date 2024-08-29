#pragma once
#include <std/string.pat>

namespace DC {

    using StringId64 = u64;

    enum ScriptId : StringId64 {
        modules = 0x0B4B7080C994E5B8, // *modules*
        persistent_command_list = 0x0D4214F3AB9F95C3, // *persistent-command-list*
        mouse_default_settings = 0x153A061C977AB3B4, // *mouse-default-settings*
    };
    
    enum Type : StringId64 {
        Array = 0x4F9E14B634C6B026, // @ Array
        map = 0x080F5919176D2D91, // @ map
        _float = 0xA00A62A942B20165, // @ float
        symbol_array = 0xC8F749F92779D489, // @ symbol-array
        module_info_array = 0xE442DCB00300FB28, // @ module-info-array
        action_scheme = 0x9FF30B9A5C83CB5D, // @ action-scheme
        command_list = 0xB18C294ADE7B782B, // @ B18C294ADE7B782B
        mouse_settings = 0xD6BCF8E23269E80E // @ D6BCF8E23269E80E
    };

    // @ Array
    struct Array<T> {
        T *m_value : u64;
    };

    // @ map
    struct map<_Kty,_Ty> {
        u64 m_size;
        _Kty *m_key[m_size] : _Kty;
        _Ty *m_value[m_size] : u64;
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