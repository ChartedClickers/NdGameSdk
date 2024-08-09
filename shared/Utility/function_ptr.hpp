#pragma once

#include "assertion/assert.hpp"

#define FUNCTION_PTR(return_type, func_name, func_addr, ...) \
    always_assert(func_addr == 0, "Unable to resolve " #return_type " " #func_name "(" #__VA_ARGS__ ")" "!"); \
    typedef return_type (*func_name##_t)(__VA_ARGS__); \
    func_name##_t func_name = (func_name##_t)(void*)(func_addr)

#define TYPEDEF_FUNCTION_PTR(ret_type, func_name, ...) \
    typedef ret_type (*func_name##_ptr)(__VA_ARGS__); \
    extern func_name##_ptr func_name

#define MEMBER_FUNCTION_PTR(ret_type, func_name, ...) \
    typedef ret_type (*func_name##_ptr)(__VA_ARGS__); \
    func_name##_ptr func_name = nullptr;

#define INIT_FUNCTION_PTR(func_name) \
    func_name##_ptr func_name = nullptr