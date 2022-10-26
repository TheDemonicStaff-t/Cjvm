#pragma once
#include "nums.h"

const char* opcode_names[256] = 
    {"nop (00)","aconst_null (01)", "iconst_m1 (02)", "iconst_0 (03)", "iconst_1 (04)", "iconst_2 (05)", "iconst_3 (06)", "iconst_4 (07)", "iconst_5 (08)", "lconst_0 (09)", "lconst_1(0a)", 
    "fconst_0 (0b)", "fconst_1 (0c)", "fconst_2 (0d)", "dconst_0 (0e)", "dconst_1 (0f)", "bipush (10)", "sipush (11)", "ldc (12)", "ldc_w (13)","ldc2_w (14)", "iload (15)", "lload (16)", "fload (17)",
    "dloat (18)", "aload (19)", "iload_0 (1a)", "iload_1 (1b)", "iload_2 (1c)", "iload_3 (1d)", "lload_0 (1e)", "lload_1 (1f)", "lload_2 (20)", "lload_3 (21)", "fload_0 (22)", "fload_1 (23)", 
    "fload_2 (24)", "fload_3 (25)", "dload_0 (26)", "dload_1 (27)", "dload_2 (28)", "dload_3 (29)", "aload_0 (2a)", "aload_1 (2b)", "aload_2 (2c)", "aload_3 (2d)", "iaload (2e)", "laload (2f)",
    "faload (30)", "daload (31)", "aaload (32)", "baload (33)", "caload (34)", "saload (35)", "istore (36)", "lstore (37)", "fstore (38)", "dstore (39)", "astore (3a)", "istore_0(3b)", "istore_1(3c)",
    "istore_2 (3d)", "istore_3 (3e)", "lstore_0 (3f)", "lstore_1 (40)", "lstore_2 (41)", "lstore_3 (42)", "fstore_0 (43)", "fstore_1 (44)", "fstore_2 (45)", "fstore_3 (46)", "dstore_0 (47)", "dstore_1 (48)", 
    "dstore_2 (49)", "dstore_3 (4a)", "astore_0 (4b)", "astore_1 (4c)", "astore_2 (4d)", "astore_3 (4e)", "iastore (4f)", "lastore (50)", "fastore (51)", "dastore (52)", "aastore (53)", "bastore (54)", 
    "castore (55)", "sastore (56)", "pop (57)", "pop2 (58)", "dup (59)", "dup_x1 (5a)", "dup_x2 (5b)", "dup2 (5c)", "dup2_x1 (5d)", "dup2_x2 (5e)", "swap (5f)", "iadd (60)", "ladd (61)", "fadd (62)", 
    "dadd (63)", "isub (64)", "lsub (65)", "fsub (66)", "dsub (67)", "imul (68)", "lmul (69)", "fmul (6a)", "dmul (6b)", "idiv (6c)", "ldiv (6d)", "fdiv (6e)", "ddiv (6f)", "irem (70)", "lrem (71)",
    "frem (72)", "drem (73)", "ineg (74)", "lneg (75)", "fneg (76)", "dneg (77)", "ishl (78)", "lshl (79)", "ishr (7a)", "lshr (7b)", "iushr (7c)", "lushr (7d", "iand (7e)", "land (7f)", "ior (80)", 
    "lor (81)", "ixor (82)", "lxor (83)", "iinc (84)", "i2l (85)", "i2f (86)", "i2d (87)", "l2i (88)", "l2f (89)", "l2d (8a)", "f2i (8b)", "f2l (8c)", "f2d (8d)", "d2i (8e)", "d2l (8f)", "d2f (90)",
    "i2b (91)", "i2c (92)", "i2s (93)", "lcmp (94)", "fcmpl (95)", "fcmpg (96)", "dcmpl (97)", "dcmgg (98)","ifeq (99)", "ifne (9a)", "iflt (9b)", "ifge (9c)", "ifgt (9d)", "ifle (9e)", "if_icmpeq (9f)", 
    "if_icmpne (a0)", "if_icmplt (a1)", "if_icmpge (a2)", "if_icmpgt (a3)", "if_icmple (a4)", "if_acmpeq (a5)", "if_acmpne (a6)", "goto (a7)", "jsr !DEP (a8)", "ret !DEP (a9)", "tableswitch (aa)", "lookupswitch (ab)",
    "ireturn (ac)", "lreturn (ad)", "freturn (ae)", "dreturn (af)", "areturn (b0)", "return (b1)", "getstatic (b2)", "putstatic (b3)", "getfield (b4)", "putfield (b5)", "invokevirtual (b6)", "invokespecial (b7)",
    "invokestatic (b8)", "invokeinterface (b9)", "invokedynamic (ba)", "new (bb)", "newarray (bc)", "anewarray (bd)", "arraylength (be)", "athrow (bf)", "checkcast (c0)", "instanceof (c1)", "monitorenter (c2)", 
    "monitorexit (c3)", "wide (c4)", "multianewarray (c5)", "ifnull (c6)", "ifnonnull (c7)", "goto_w (c8)", "jsr_w !DEP (c9)", "breakpoint (ca)", "udef (cb)", "udef (cc)", "udef (cd)", "udef (ce)", "udef (cf)",
    "udef (d0)", "udef (d1)", "udef (d2)", "udef (d3)", "udef (d4)", "udef (d5)", "udef (d6)", "udef (d7)", "udef (d8)", "udef (d9)", "udef (da)", "udef (db)", "udef (dc)", "udef (dd)", "udef (de)", "udef (df)",
    "udef (e0)", "udef (e1)", "udef (e2)", "udef (e3)", "udef (e4)", "udef (e5)", "udef (e6)", "udef (e7)", "udef (e8)", "udef (e9)", "udef (ea)", "udef (eb)", "udef (ec)", "udef (ed)", "udef (ee)", "udef (ef)",
    "udef (f0)", "udef (f1)", "udef (f2)", "udef (f3)", "udef (f4)", "udef (f5)", "udef (f6)", "udef (f7)", "udef (f8)", "udef (f9)", "udef (fa)", "udef (fb)", "udef (fc)", "udef (fd)", "impdep1 (fe)", "impdep2 (fe)"};