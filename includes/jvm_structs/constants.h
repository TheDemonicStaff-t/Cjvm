#pragma once

#include "../nums.h"

typedef enum _const_tag{ // 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 15, 16, 18
    CONSTANT_Utf8 = 1,                  //
    CONSTANT_Long = 5,                  //
    CONSTANT_Float = 4,                 //
    CONSTANT_Class = 7,                 //
    CONSTANT_String = 8,                //
    CONSTANT_Double = 6,                //
    CONSTANT_Integer = 3,               //
    CONSTANT_Fieldref = 9,              //
    CONSTANT_Methodref = 10,            //
    CONSTANT_MethodType = 16,           //
    CONSTANT_NameAndType = 12,          //
    CONSTANT_MethodHandle = 15,         //
    CONSTANT_InvokeDynamic = 18,        //
    CONSTANT_InterfaceMethodref = 11,   //
} const_tag;

typedef struct _constant_class {u16 name_index;} constant_class;
typedef struct _constant_fieldref {u16 class_index; u16 name_and_type_index;} constant_fieldref;
typedef struct _constant_methodref {u16 class_index; u16 name_and_type_index;} constant_methodref;
typedef struct _constant_interfacemethodref {u16 class_index; u16 name_and_type_index;} constant_interfacemethodref;
typedef struct _constant_string {u16 string_index;} constant_string;
typedef struct _constant_int {i32 num;} constant_int;
typedef struct _constant_float {f32 num;} constant_float;
typedef struct _constant_long {i64 num;} constant_long;
typedef struct _constant_double {f64 num;} constant_double;
typedef struct _constant_nameandtype {u16 name_index; u16 descriptor_index;} constant_nameandtype;
typedef struct _constant_utf8 {u16 length; char* bytes;} constant_utf8;
typedef struct _constant_methodhandle {u8 reference_kind; u16 reference_index;} constant_methodhandle;
typedef struct _constant_methodtype {u16 descriptor_index;} constant_methodtype;
typedef struct _constant_invokedynamic {u16 bootstrap_method_attr_index; u16 name_and_type_index;} constant_invokedynamic;

typedef union _constant {
    constant_class* _class;
    constant_fieldref* _fieldref;
    constant_methodref* _methodref;
    constant_interfacemethodref* _interfacemethodref;
    constant_string* _string;
    constant_int* _int;
    constant_float* _float;
    constant_long* _long;
    constant_double* _double;
    constant_nameandtype* _nameandtype;
    constant_utf8* _utf8;
    constant_methodhandle* _methodhandle;
    constant_methodtype* _methodtype;
    constant_invokedynamic* _invokedynamic;
} constant;

typedef struct _jvm_constant{
    constant jconst;
    u8 tag;
} jvm_constant;

int pprint_cpool(u8* data, int idx);
int parse_cpool(u8* data, int idx, jvm_constant* consts, u16 csize, u8 debug);
void free_cpool(jvm_constant* consts, u16 csize);
