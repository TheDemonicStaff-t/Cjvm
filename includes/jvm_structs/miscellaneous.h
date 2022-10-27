#pragma once

#include "../nums.h"
#include "attributes.h"

typedef struct _jvm_attribute jvm_attribute;
typedef struct _annotation annotation;

typedef struct _exception {u16 start_pc; u16 end_pc; u16 handler_pc; u16 catch_type;} exception;

typedef struct _jvm_class {u16 inner_class_info_index; u16 outer_class_info_index; u16 inner_name_index; u16 inner_name_access_flags;} jvm_class;

typedef struct _line_number_table {u16 start_pc; u16 line_number;} line_number_table;

typedef struct _local_variable_table {u16 start_pc; u16 length; u16 name_index; u16 descriptor_index; u16 index;} local_variable_table;

typedef struct _local_variable_type_table {u16 start_pc; u16 length; u16 name_index; u16 signature_index; u16 index;} local_variable_type_table;

typedef struct _element_value {
    u8 tag;
    union {
        u16 const_value_index;
        struct enum_const_value_info {u16 num_values; element_value* values;} enum_value;
        u16 class_info_index;
        annotation anotation_value;
        struct array_value_info {u16 num_values; element_value* values;} array_value;
    } value;
} element_value;

typedef struct _element_value_pair {u16 element_name_index; element_value value;} element_value_pair;

typedef struct _annotation {u16 type_index; u16 num_element_value_pairs; element_value_pair* element_value_pairs;} annotation;

typedef struct _parameter_annotation {u16 num_annotations; annotation* annotations;} parameter_annotation;

typedef struct _bootstrap_method {u16 bootstrap_method_ref; u16 num_bootstrap_arguments; u16* bootstrap_arguments;} bootstrap_method;

typedef struct _field {
    u16 access_flags;
    u16 name_index;
    u16 descriptor_index;
    u16 attribute_c;
    jvm_attribute* attributes;
} field;

typedef struct _method {
    u16 access_flags;
    u16 name_index;
    u16 descriptor_index;
    u16 attribute_c;
    jvm_attribute* attributes;
} method;