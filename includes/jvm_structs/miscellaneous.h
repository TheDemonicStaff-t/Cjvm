#pragma once

#include "../nums.h"
#include "attributes.h"

typedef struct _field {
    u16 access_flags;
    u16 name_index;
    u16 descriptor_index;
    u16 attribute_c;
    jvm_attribute* attributes;
} field;