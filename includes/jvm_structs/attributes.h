#pragma once

#include "../nums.h"
#include "miscellaneous.h"
#include "stack_map_frames.h"

typedef enum _attr_type {
    attrConstantValue,
    attrCode,
    attrStackMapTable,
    attrExceptions,
    attrInnerClasses,
    attrEnclosingMethod,
    attrSynthetic,
    attrSignature,
    attrSourcefile,
    attrSourceDebugExtension,
    attrLineNumberTable,
    attrLocalVariableTable,
    attrLocalVariableTypeTable,
    attrDeprecated,
    attrRuntimeVisibleAnnotations,
    attrRuntimeInvisibleAnnotations,
    attrRuntimeVisibleParameterAnnotations,
    attrRuntimeInvisibleParameterAnnotations,
    attrAnnotationDefault,
    attrBootstrapMethods
} attr_type;

typedef struct _ConstantValue {u16 constantvalue_index;} ConstantValue;
typedef struct _Code {
    u16 max_stack;
    u16 max_locals;
    u32 code_length;
    u8* code;
    u16 exception_c;
    exception* exceptions;
    u16 attribute_c;
    jvm_attribute* attribute;
} Code;
typedef struct _StackMapTable {u16 number_of_entries; jvm_stack_map_frame* entries;} StackMapTable;
typedef struct _Exceptions {u16 number_fo_exceptions; u16* exception_index_table;} Exceptions;
typedef struct _InnerClasses {u16 number_of_classes; jvm_class* classes;} InnerClasses;
typedef struct _EnclosingMethod {u16 class_index; u16 method_index;} EnclosingMethod;
typedef struct _Signature {u16 signature_address;} Signature;
typedef struct _Sourcefile {u16 sourcefile_index;} Sourcefile;
typedef struct _SourceDebugExtension {u8* debug_estension;} SourceDebugExtension;
typedef struct _LineNumberTable {u16 line_number_table_length; line_number_table* line_numbers;} LineNumberTable;
typedef struct _LocalVariableTable {u16 local_variables_table_length; local_variable_table* local_variables;} LocalVariableTable;
typedef struct _LocalVariableTypeTable {u16 local_variable_type_table_length; local_variable_type_table* local_variable_types;} LocalVariableTypeTable;
typedef struct _RuntimeAnnotations {u16 num_annotations; annotation* annotations;} RuntimeAnnotations;
typedef struct _RuntimeParameterAnnotations {u8 num_parameters; parameter_annotation* annotations;} RuntimeParameterAnnotations;
typedef struct _AnnotationDefault {element_value default_value;} AnnotationDefault;
typedef struct _BootstrapMethods {u16 num_bootstrap_methods;} BootstrapMethods;

typedef union _attribute {
    ConstantValue* const_val_attr;
    Code* code_attr;
    StackMapTable* stack_map_table_attr;
    Exceptions* exception_attr;
    InnerClasses* inner_class_attr;
    EnclosingMethod* enclosing_method_attr;
    u64 synthetic_attr;
    Signature* signature_attr;
    Sourcefile* source_file_attr;
    SourceDebugExtension* source_debug_extension_attr;
    LineNumberTable* line_number_table_attr;
    LocalVariableTable* local_variable_table_attr;
    LocalVariableTypeTable* local_variable_type_table_attr;
    u64 deprecated_attr;
    RuntimeAnnotations* runtime_visible_annotations_attr;
    RuntimeAnnotations* runtime_invisible_annotations_attr;
    RuntimeParameterAnnotations* runtime_visible_parameter_annotations_attr;
    RuntimeParameterAnnotations* runtime_invisible_parameter_annotations_attr;
    AnnotationDefault* annotation_default_attr;
    BootstrapMethods* bootstrap_method_attr;
} attribute;

typedef struct _jvm_attribute {
    attribute attr;
    u32 attribute_length;
    u16 attribute_name_index;
    u8 attribute_type;
} jvm_attribute;