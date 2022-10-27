#include "../includes/jvm_structs/constants.h"
#include <stdio.h>
#include <stdlib.h>

int pprint_cpool(u8* data, int idx)
{
    u16 csize = jvm_u16(data[idx++], data[idx++])-1;
    int ssize = 0;
    int cpidx = 0;

    for (int i = 0; i < csize; i++){
        u32 tag = (u32) 0x00000000|data[idx++];

        switch (tag){
            case CONSTANT_Methodref:
                printf("%d:methodref{%d, %d}\n",cpidx++, jvm_u16(data[idx++], data[idx++])-1, jvm_u16(data[idx++], data[idx++])-1);
                break;
            case CONSTANT_Class:
                printf("%d:class{%d}\n", cpidx++, jvm_u16(data[idx++], data[idx++])-1);
                break;
            case CONSTANT_NameAndType:
                printf("%d:nameandtype{%d, %d}\n", cpidx++,jvm_u16(data[idx++], data[idx++])-1, jvm_u16(data[idx++], data[idx++])-1);
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
                printf("%d:fieldref{%d, %d}\n",cpidx++,jvm_u16(data[idx++], data[idx++])-1,jvm_u16(data[idx++], data[idx++])-1);
                break;
            case CONSTANT_String:
                printf("%d:string{%d}\n", cpidx++, jvm_u16(data[idx++], data[idx++])-1);
                break;
            case CONSTANT_Integer:
                printf("%d:int{%d}", cpidx++, jvm_i32(data[idx++], data[idx++], data[idx++], data[idx++]));
                break;
            case CONSTANT_InterfaceMethodref:
                printf("%d:interfacemethodref{%d, %d}", cpidx++, jvm_u16(data[idx++], data[idx++])-1, jvm_u16(data[idx++], data[idx++])-1);
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
                printf("%d:methodhandle{%d, %d}", cpidx++, data[idx++], jvm_u16(data[idx++], data[idx++])-1);
                break;
            case CONSTANT_MethodType:
                printf("%d:methodtype{%d}", cpidx++,jvm_u16(data[idx++], data[idx++])-1);
                break;
            case CONSTANT_InvokeDynamic:
                printf("%d:invokedynamic{%d, %d}", cpidx++, jvm_u16(data[idx++], data[idx++])-1, jvm_u16(data[idx++], data[idx++])-1);
                break;
            default:
                printf("parsing_error\n", cpidx++, tag);
                exit(3);
        }
    }

    return idx;
}

int parse_cpool(u8* data, int idx, jvm_constant* consts, u16 csize, u8 debug){

    *consts;
    int ssize = 0;

    for (int i = 0; i < csize; i++){
        u8 tag = data[idx++];
        consts[i].tag = tag;

        switch (tag) {
            case CONSTANT_Methodref:
                consts[i].jconst._methodref = (constant_methodref*) malloc(sizeof(constant_methodref));
                consts[i].jconst._methodref->class_index = jvm_u16(data[idx++], data[idx++])-1;
                consts[i].jconst._methodref->name_and_type_index = jvm_u16(data[idx++], data[idx++])-1;

                if (debug == 1)
                    printf("%d:methodref{ci:%d, n+ti:%d}\n", i, consts[i].jconst._methodref->class_index, consts[i].jconst._methodref->name_and_type_index);
                break;
            case CONSTANT_Class:
                consts[i].jconst._class = (constant_class*) malloc(sizeof(constant_class));
                consts[i].jconst._class->name_index = jvm_u16(data[idx++], data[idx++]);

                if (debug == 1)
                    printf("%d:class{ni:%d}\n", i, consts[i].jconst._class->name_index);
                break;
            case CONSTANT_NameAndType:
                    consts[i].jconst._nameandtype = (constant_nameandtype*) malloc(sizeof(constant_nameandtype));
                    consts[i].jconst._nameandtype->name_index = jvm_u16(data[idx++], data[idx++]);
                    consts[i].jconst._nameandtype->descriptor_index = jvm_u16(data[idx++], data[idx++]);

                    if (debug == 1)
                        printf("%d:nameandtype{ni:%d, di:%d}\n", i, consts[i].jconst._nameandtype->name_index, consts[i].jconst._nameandtype->descriptor_index);
                break;
            case CONSTANT_Utf8:
                consts[i].jconst._utf8 = (constant_utf8*) malloc(sizeof(constant_utf8));
                consts[i].jconst._utf8->length = jvm_u16(data[idx++], data[idx++]);
                consts[i].jconst._utf8->bytes = (char*) malloc(sizeof(char)*(consts[i].jconst._utf8->length+1));
                for(int x = 0; x < consts[i].jconst._utf8->length; x++){
                    consts[i].jconst._utf8->bytes[x] = data[idx++];
                } consts[i].jconst._utf8->bytes[consts[i].jconst._utf8->length] = '/0';

                if (debug == 1)
                    printf("%d:utf8{l:%d, s:'%s'}\n",i ,consts[i].jconst._utf8->length, consts[i].jconst._utf8->bytes);
                break;
            case CONSTANT_Fieldref:
                consts[i].jconst._fieldref = (constant_fieldref*) malloc(sizeof(constant_fieldref));
                consts[i].jconst._fieldref->class_index = jvm_u16(data[idx++], data[idx++]);
                consts[i].jconst._fieldref->name_and_type_index = jvm_u16(data[idx++], data[idx++]);

                if (debug == 1)
                    printf("%d:fieldref:{ci:%d, n+ti:%d}\n", i, consts[i].jconst._fieldref->class_index, consts[i].jconst._fieldref->name_and_type_index);
                break;
            case CONSTANT_String:
                consts[i].jconst._string = (constant_string*) malloc(sizeof(constant_string));
                consts[i].jconst._string->string_index = jvm_u16(data[idx++], data[idx++]);

                if (debug == 1)
                    printf("%d:string{si:%d}\n", i, consts[i].jconst._string->string_index);
                break;
            default: // consts[i].jconst._ = (constant_*) malloc(sizeof(constant_));
                printf("unimplemented constant: %d\n", tag);
                free_cpool(consts, i);
                exit(3);
        }
    }

    return idx;
}

void free_cpool(jvm_constant* consts, u16 csize){
    for (int i = 0; i < csize; i++){
        int tag = consts[i].tag;
        switch (tag){
            case CONSTANT_Methodref:
                free(consts[i].jconst._methodref);
                break;
            case CONSTANT_Class:
                free(consts[i].jconst._class);
                break;
            case CONSTANT_NameAndType:
                free(consts[i].jconst._nameandtype);
                break;
            case CONSTANT_Utf8:
                free(consts[i].jconst._utf8->bytes);
                free(consts[i].jconst._utf8);
                break;
            case CONSTANT_Fieldref:
                free(consts[i].jconst._fieldref);
                break;
            case CONSTANT_String:
                free(consts[i].jconst._string);
                break;
            case CONSTANT_Integer:
                free(consts[i].jconst._int);
                break;
            case CONSTANT_InterfaceMethodref:
                free(consts[i].jconst._interfacemethodref);
                break;
            case CONSTANT_Float:
                free(consts[i].jconst._float);
                break;
            case CONSTANT_Long:
                free(consts[i].jconst._long);
                break;
            case CONSTANT_Double:
                free(consts[i].jconst._double);
                break;
            case CONSTANT_MethodHandle:
                free(consts[i].jconst._methodhandle);
                break;
            case CONSTANT_MethodType:
                free(consts[i].jconst._methodtype);
                break;
            case CONSTANT_InvokeDynamic:
                free(consts[i].jconst._invokedynamic);
                break;
        }
    }
    free(consts);
}

void p_cpool(jvm_constant* consts, u16 csize);