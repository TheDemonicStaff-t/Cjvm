#pragma once
#include "nums.h"
#include "jvm_structs/constants.h"
#include "jvm_structs/miscellaneous.h"

typedef struct _jvm_class {
    u8 valid;
    char* version;
    u16 constpool_c;
    jvm_constant* constpool;
    u16 access_flags;
    u16 this_class;
    u16 super_class;
    u16 interface_c;
    u16* interfaces;
    u16 field_c;
} jvm_class;

jvm_class gen_class();