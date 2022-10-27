#pragma once

#include <stdint.h>

#define u8      uint8_t
#define u16     uint16_t
#define u32     uint32_t
#define u64     uint64_t

#define i8      int8_t
#define i16     int16_t
#define i32     int32_t
#define i64     int64_t

#define f32     float
#define f64     double
#define f128    long double

u16 jvm_u16(u8 v1, u8 v2){return (((u16)v1)<<8)|(((u16)v2));}
u32 jvm_u32(u8 v1, u8 v2, u8 v3, u8 v4){return (((u32)v1)<<24)|(((u32)v2)<<16)|(((u32)v3)<<8)|((u32)v4);}
u64 jvm_u64(u8 v1, u8 v2, u8 v3, u8 v4, u8 v5, u8 v6, u8 v7, u8 v8){return (((u64)v1)<<56)|(((u64)v2)<<48)|(((u64)v3)<<40)|(((u64)v4)<<32)|(((u64)v5)<<24)|(((u64)v6)<<16)|(((u64)v7)<<8)|((u64)v8);}

i16 jvm_i16(u8 v1, u8 v2){return (i16)(((u16)v1)<<8)|(((u16)v2));}
i32 jvm_i32(u8 v1, u8 v2, u8 v3, u8 v4){return (i32)(((u32)v1)<<24)|(((u32)v2)<<16)|(((u32)v3)<<8)|(((u32)v4));}
i64 jvm_i64(u8 v1, u8 v2, u8 v3, u8 v4, u8 v5, u8 v6, u8 v7, u8 v8){return (i64)((((u64)v1)<<56)|(((u64)v2)<<48)|(((u64)v3)<<40)|(((u64)v4)<<32)|(((u64)v5)<<24)|(((u64)v6)<<16)|(((u64)v7)<<8)|((u64)v8));}

f32 jvm_f32(u8 v1, u8 v2, u8 v3, u8 v4){return (f32)((((u32)v1)<<24)|(((u32)v2)<<16)|(((u32)v3)<<8)|(((u32)v4)));}
f64 jvm_f64(u8 v1, u8 v2, u8 v3, u8 v4, u8 v5, u8 v6, u8 v7, u8 v8){return (f64)((((u64)v1)<<56)|(((u64)v2)<<48)|(((u64)v3)<<40)|(((u64)v4)<<32)|(((u64)v5)<<24)|(((u64)v6)<<16)|(((u64)v7)<<8)|((u64)v8));}

u16 nm_u16(u8 v1, u8 v2){return (u16)(((u16)v1)<<8)|(((u16)v2));}
u32 nm_u32(u8 v1, u8 v2, u8 v3, u8 v4){return (((u32)v1)<<24)|(((u32)v2)<<16)|(((u32)v3)<<8)|(((u32)v4));}
u64 nm_u64(u8 v1, u8 v2, u8 v3, u8 v4, u8 v5, u8 v6, u8 v7, u8 v8){return (u64)(((u64)v1)<<56)|(((u64)v2)<<48)|(((u64)v3)<<40)|(((u64)v4)<<32)|(((u64)v5)<<24)|(((u64)v6)<<16)|(((u64)v7)<<8)|((u64)v8);}

i16 nm_i16(u8 v1, u8 v2){return (i16)((((u16)v1)<<8)|(((u16)v2)));}
i32 nm_i32(u8 v1, u8 v2, u8 v3, u8 v4){return (i32)((((u32)v1)<<24)|(((u32)v2)<<16)|(((u32)v3)<<8)|(((u32)v4)));}
i64 nm_i64(u8 v1, u8 v2, u8 v3, u8 v4, u8 v5, u8 v6, u8 v7, u8 v8){return (i64)((((u64)v1)<<56)|(((u64)v2)<<48)|(((u64)v3)<<40)|(((u64)v4)<<32)|(((u64)v5)<<24)|(((u64)v6)<<16)|(((u64)v7)<<8)|((u64)v8));}

f32 nm_f32(u8 v1, u8 v2, u8 v3, u8 v4){return (f32)((((u32)v1)<<24)|(((u32)v2)<<16)|(((u32)v3)<<8)|(((u32)v4)));}
f64 nm_f64(u8 v1, u8 v2, u8 v3, u8 v4, u8 v5, u8 v6, u8 v7, u8 v8){return (f64)((((u64)v1)<<56)|(((u64)v2)<<48)|(((u64)v3)<<40)|(((u64)v4)<<32)|(((u64)v5)<<24)|(((u64)v6)<<16)|(((u64)v7)<<8)|((u64)v8));}
