#pragma once

#include "../nums.h"

typedef enum _attr_type {
    ConstantValue,
    Code,
    StackMapTable,
    Exceptions,
    InnerClasses,
    EnclosingMethod,
    Synthetic,
    Signature,
    Sourcefile,
    SourceDebugExtension,
    LineNumberTable,
    LocalVariableTable,
    LocalVariableTypeTable,
    Deprecated,
    RuntimeVisibleAnnotations,
    RuntimeInvisibleAnnotations,
    RuntimeVisibleParameterAnnotations,
    RuntimeInvisibleParameterAnnotations,
    AnnotationDefault,
    BootstrapMethods
} attr_type;

typedef struct _ConstantValue {u16 constantvalue_index;} ConstantValue;
typedef struct _Code {
    
} Code;
typedef struct _StackMapTable {} StackMapTable;
typedef struct _Exceptions {} Exceptions;
typedef struct _InnerClasses {} InnerClasses;
typedef struct _EnclosingMethod {} EnclosingMethod;
typedef struct _Synthetic {} Synthetic;
typedef struct _Signature {} Signature;
typedef struct _Sourcefile {} Sourcefile;
typedef struct _SourceDebugExtension {} SourceDebugExtension;
typedef struct _LineNumberTable {} LineNumberTable;
typedef struct _LocalVariableTable {} LocalVariableTable;
typedef struct _LocalVariableTypeTable {} LocalVariableTypeTable;
typedef struct _Deprecated {} Deprecated;
typedef struct _RuntimeVisibleAnnotations {} RuntimeVisibleAnnotations;
typedef struct _RuntimeInvisibleAnnotations {} RuntimeInvisibleAnnotations;
typedef struct _RuntimeVisibleParameterAnnotations {} RuntimeVisibleParameterAnnotations;
typedef struct _RuntimeInvisibleParameterAnnotations {} RuntimeInvisibleParameterAnnotations;
typedef struct _AnnotationDefault {} AnnotationDefault;
typedef struct _BootstrapMethods {} BootstrapMethods;

typedef union _attribute {
    ConstantValue* const_val_attr;
    Code* code_attr;
    StackMapTable* stack_map_table_attr;
    Exceptions* exception_attr;
    InnerClasses* inner_class_attr;
    EnclosingMethod* enclosing_method_attr;
    Synthetic* synthetic_attr;
    Signature* signature_attr;
    Sourcefile* source_file_attr;
    SourceDebugExtension* source_debug_extension_attr;
    LineNumberTable* line_number_table_attr;
    LocalVariableTable* local_variable_table_attr;
    LocalVariableTypeTable* local_variable_type_table_attr;
    Deprecated* deprecated_attr;
    RuntimeVisibleAnnotations* runtime_visible_annotations_attr;
    RuntimeInvisibleAnnotations* runtime_invisible_annotations_attr;
    RuntimeVisibleParameterAnnotations* runtime_visible_parameter_annotations_attr;
    RuntimeInvisibleParameterAnnotations* runtime_invisible_parameter_annotations_attr;
    AnnotationDefault* annotation_default_attr;
    BootstrapMethods* bootstrap_method_attr;
} attribute;

typedef struct _jvm_attribute {
    attribute attr;
    u16 attribute_type;
    u32 attribute_length;
} jvm_attribute;