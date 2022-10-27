#pragma once

#include "../nums.h"

typedef enum _verification_type {
    TopVariableVerification = 0,
    IntergerVariableVerification = 1,
    FloatVariableVerification = 2,
    LongVariableVerification = 4,
    DoubleVariableVerification = 3,
    NullVariableVerification = 5,
    UninitializedThisVariableVerification = 6,
    ObjectVariableVerification = 7,
    UninitializedVariableVerification = 8
} verification_type;

typedef struct _TopVariableInfo {u8 tag;} TopVariableInfo;
typedef struct _IntergerVariableInfo {u8 tag;} IntergerVariableInfo;
typedef struct _float_variable_info {u8 tag;} FloatVariableInfo;
typedef struct _long_variable_info {u8 tag;} LongVariableInfo;
typedef struct _double_variable_info{u8 tag;} DoubleVariableInfo;
typedef struct _null_variable_info {u8 tag;} NullVariableInfo;
typedef struct _uninitialized_this_variable_info {u8 tag;} UninitializedThisVariableInfo;
typedef struct _object_variable_info {u8 tag; u16 cpool_index;} ObjectVariableInfo;
typedef struct _uninitialized_variable_info{u8 tag; u16 offset;} UninitializedVariableInfo;

typedef union _verification_type_info {
    TopVariableInfo* _top_variable_info;
    IntergerVariableInfo* _interger_variable_info;
    FloatVariableInfo* _float_variable_info;
    LongVariableInfo* _long_variable_info;
    DoubleVariableInfo* _double_variable_info;
    NullVariableInfo* _null_variable_info;
    UninitializedThisVariableInfo* _uninitialized_this_variable_info;
    ObjectVariableInfo* _object_variable_info;
    UninitializedVariableInfo* _uninitialized_variable_info;
} verification_type_info;

typedef struct _jvm_verification_type_info {
    u8 tag;
    verification_type_info verification_type;
} jvm_verification_type_info;