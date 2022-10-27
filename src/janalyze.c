#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/jvm_class.h"

int main(int argc, char** argv){
    if (argc != 2){
        printf("no file provided\n");
        return 1;
    }

    FILE* f = fopen(argv[1], "rb");

    fseek(f, 0, SEEK_END);
    int f_size = ftell(f);
    fseek(f, 0, SEEK_SET);

    u8* data = (u8*) malloc(f_size);
    fread(data, 1, f_size, f);

    fclose(f);

    i32 idx = 0;
    if (!((data[idx++] == 0xCA)&(data[idx++] == 0xFE)&(data[idx++] == 0xBA)&(data[idx++] == 0xBE))){
        printf("non-.class file provided\n");
        return 2;
    }

    jvm_class_file file;

    file.valid = 1;

    // gen version
    f32 tmp = ((f32)jvm_u16(data[idx++], data[idx++])/100)+((f32)jvm_u16(data[idx++], data[idx++]));
    file.version = (char*) malloc(sizeof(char)*9);
    sprintf(file.version, "%f", tmp);

    file.constpool_c = jvm_u16(data[idx++], data[idx++]) - 1;

    file.constpool = (jvm_constant *) malloc(sizeof(jvm_constant)*file.constpool_c);

    for(int i = 0; i < file.constpool_c; i++){
        file.constpool[i].tag = data[idx++];

        switch (file.constpool[i].tag){
            case CONSTANT_Class:
                file.constpool[i].jconst._class = (constant_class*) malloc(sizeof(constant_class));
                file.constpool[i].jconst._class->name_index = jvm_u16(data[idx++], data[idx++]);
                break;
            case CONSTANT_Fieldref:
                file.constpool[i].jconst._fieldref = (constant_fieldref*) malloc(sizeof(constant_fieldref));
                file.constpool[i].jconst._fieldref->class_index = jvm_u16(data[idx++], data[idx++]);
                file.constpool[i].jconst._fieldref->name_and_type_index = jvm_u16(data[idx++], data[idx++]);
                break;
            case CONSTANT_Methodref:
                break;
            case CONSTANT_InterfaceMethodref:
                break;
            case CONSTANT_String:
                break;
            case CONSTANT_Integer:
                break;
            case CONSTANT_Float:
                break;
            case CONSTANT_Long:
                break;
            case CONSTANT_Double:
                break;
            case CONSTANT_NameAndType:
                break;
            case CONSTANT_Utf8:
                break;
            case CONSTANT_MethodHandle:
                break;
            case CONSTANT_MethodType:
                break;
            case CONSTANT_InvokeDynamic:
                break;
            default:
                printf("unknown constant");
                return 3;
        }
    }

    for(int i = 0; i < file.constpool_c; i++){

        switch (file.constpool[i].tag){
            case CONSTANT_Class:
                free(file.constpool[i].jconst._class);
                break;
            case CONSTANT_Fieldref:
                free(file.constpool[i].jconst._fieldref);
                break;
            case CONSTANT_Methodref:
                free(file.constpool[i].jconst._methodref);
                break;
            case CONSTANT_InterfaceMethodref:
                free(file.constpool[i].jconst._interfacemethodref);
                break;
            case CONSTANT_String:
                free(file.constpool[i].jconst._string);
                break;
            case CONSTANT_Integer:
                free(file.constpool[i].jconst._int);
                break;
            case CONSTANT_Float:
                break;
            case CONSTANT_Long:
                break;
            case CONSTANT_Double:
                break;
            case CONSTANT_NameAndType:
                break;
            case CONSTANT_Utf8:
                break;
            case CONSTANT_MethodHandle:
                break;
            case CONSTANT_MethodType:
                break;
            case CONSTANT_InvokeDynamic:
                break;
            default:
                printf("unknown constant");
                return 3;
        }
    }

    free(file.constpool);

    free(data);

    return 0;
}