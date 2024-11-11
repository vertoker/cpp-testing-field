// Collection for utility defines, taken from many sources
// https://github.com/gustavo-tomas/Magnolia (types.hpp)
// https://github.com/TheCherno/Hazel (Base.h)
// collected by vertoker

// Start copy here

#pragma once

#include <cstdint>
#include <memory>
#include <string>

// Types shorthands
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

typedef char c8;
typedef unsigned char uc8;

typedef bool b8;

typedef std::string str;

// std pointers shorthands (Cherno, Hazel)

template <typename T>
using unique = std::unique_ptr<T>;

template <typename T>
using ref = std::shared_ptr<T>;

template <typename T, typename... Args>
constexpr unique<T> create_unique(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
constexpr ref<T> create_ref(Args&&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

// Common macros

// Vector size in bytes
#define VEC_SIZE_BYTES(vec) (vec.empty() ? 0 : vec.size() * sizeof(vec[0]))
// 1 second in nanoseconds
#define MAG_TIMEOUT 1'000'000'000

// Shortcuts to bind methods
#define BIND_FN(x) std::bind(&x, this, std::placeholders::_1)
#define BIND_FN2(x) std::bind(&x, this, std::placeholders::_1, std::placeholders::_2)

#define MAX_U32 static_cast<u32>(0xFFFFFFFF)
#define MAX_I32 static_cast<i32>(0xFFFFFFFF)

// End copy here

int main() {

}