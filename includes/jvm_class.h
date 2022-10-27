#pragma once
#include "nums.h"

#include "jvm_structs/attributes.h"
#include "jvm_structs/constants.h"
#include "jvm_structs/miscellaneous.h"

typedef struct _jvm_class_file {
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
    field* fields;
    u16 method_c;
    method* methods;
    u16 attribute_c;
    jvm_attribute* attributes;
} jvm_class_file;

jvm_class_file gen_class();