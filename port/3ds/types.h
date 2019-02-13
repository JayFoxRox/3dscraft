#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h> // size_t

typedef uint8_t u8;
typedef uint16_t u16;
//typedef uint32_t u32;
typedef uintptr_t u32; // Fuck it, smea keeps casting back and forth
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

#define U64_MAX UINT64_MAX
