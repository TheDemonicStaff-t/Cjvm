#pragma once

#include "../nums.h"
#include "verification_types.h"

typedef struct _SameLocals1StackItemFrame {u8 frame_type; jvm_verification_type_info stack;} SameLocals1StackItemFrame;
typedef struct _SameLocals1StackItemFrameExtended {u8 frame_type; u16 offset_delta; jvm_verification_type_info stack;} SameLocals1StackItemFrameExtended;
typedef struct _ChopFrame {u8 frame_type; u16 offset_delta;} ChopFrame;
typedef struct _SameFrameExtended {u8 frame_type; u16 offset_delta;} SameFrameExtended;
typedef struct _AppendFrame {u8 frame_type; u16 offset_delta; jvm_verification_type_info locals;} AppendFrame;
typedef struct _FullFrame {u8 frame_type; u16 offset_delta; u16 number_of_locals; jvm_verification_type_info* locals; u16 number_of_stack_items; jvm_verification_type_info* stack;} FullFrame;

typedef union _stack_map_frame {
    u8 _same_frame;
    SameLocals1StackItemFrame _same_local_stack_item_frame;
    SameLocals1StackItemFrameExtended _same_local_stack_item_frame_extended;
    ChopFrame _chop_frame;
    SameFrameExtended _same_frame_extended;
    AppendFrame _append_frame;
    FullFrame _full_frame;
} stack_map_frame;

typedef struct _jvm_stack_map_frame {
    u8 frame_type;
    stack_map_frame frame;
} jvm_stack_map_frame;