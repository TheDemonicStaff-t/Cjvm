#include "../includes/jvm_structs/constants.h"
#include <stdio.h>
#include <stdlib.h>

int pprint_cpool(u8* data, int idx)
{
    u16 csize = jvm_u16(data[idx++], data[idx++])-1;
    int ssize = 0;
    int cpidx = 1;

    for (int i = 0; i < csize; i++){
        u32 tag = (u32) 0x00000000|data[idx++];

        switch (tag){
            case CONSTANT_Methodref:
                printf("%d:methodref{%d, %d}\n",cpidx++, jvm_u16(data[idx++], data[idx++]), jvm_u16(data[idx++], data[idx++]));
                break;
            case CONSTANT_Class:
                printf("%d:class{%d}\n", cpidx++, jvm_u16(data[idx++], data[idx++]));
                break;
            case CONSTANT_NameAndType:
                printf("%d:nameandtype{%d, %d}\n", cpidx++,jvm_u16(data[idx++], data[idx++]), jvm_u16(data[idx++], data[idx++]));
                break;
            case CONSTANT_Utf8:
                ssize = jvm_u16(data[idx++], data[idx++]);
                char* tmp = (char*) malloc(sizeof(char) * (ssize+1));
                for (int i = 0; i < ssize; i++){
                    tmp[i] = (char) data[idx++];
                } tmp[ssize+1] = '\0';

                printf("%d:utf8{%d, %s}\n", cpidx++, ssize, tmp);
                break;
            case CONSTANT_Fieldref:
                printf("%d:fieldref{%d, %d}\n",cpidx++,jvm_u16(data[idx++], data[idx++]),jvm_u16(data[idx++], data[idx++]));
                break;
            case CONSTANT_String:
                printf("%d:string{%d}\n", cpidx++, jvm_u16(data[idx++], data[idx++]));
                break;
            case CONSTANT_Integer:
                printf("%d:int{%d}", cpidx++, jvm_i32(data[idx++], data[idx++], data[idx++], data[idx++]));
                break;
            case CONSTANT_InterfaceMethodref:
                printf("%d:interfacemethodref{%d, %d}", cpidx++, jvm_u16(data[idx++], data[idx++]), jvm_u16(data[idx++], data[idx++]));
                break;
            case CONSTANT_Float:
                printf("%d:float{%f}", cpidx++, jvm_f32(data[idx++], data[idx++], data[idx++], data[idx++]));
                break;
            case CONSTANT_Long:
                printf("%d:long{%lli}", cpidx++, jvm_i64(data[idx++], data[idx++], data[idx++], data[idx++],data[idx++], data[idx++], data[idx++], data[idx++]));
                break;
            case CONSTANT_Double:
                printf("%d:double{%lf}", cpidx++, jvm_f64(data[idx++], data[idx++], data[idx++], data[idx++],data[idx++], data[idx++], data[idx++], data[idx++]));
                break;
            case CONSTANT_MethodHandle:
                printf("%d:methodhandle{%d, %d}", cpidx++, data[idx++], jvm_u16(data[idx++], data[idx++]));
                break;
            case CONSTANT_MethodType:
                printf("%d:methodtype{%d}", cpidx++,jvm_u16(data[idx++], data[idx++]));
                break;
            case CONSTANT_InvokeDynamic:
                printf("%d:invokedynamic{%d, %d}", cpidx++, jvm_u16(data[idx++], data[idx++]), jvm_u16(data[idx++], data[idx++]));
                break;
            default:
                printf("parsing_error\n", cpidx++, tag);
                exit(3);
        }
    }

    return idx;
}

int parse_cpool(u8* data, int idx, jvm_constant* const, u16* csize){

    csize* = jvm_u16(data[idx++], data[idx++])-1;
    int ssize = 0;

    for (int i = 0; i < csize*; i++){
        u16 tag = jvm_u16(data[idx++], data[idx++]);

        switch (tag) {
            default:
                printf("unimplemented constant: %d\n", tag);
                exit(3);
        }
    }

    return idx;
}