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
                file.constpool[i].jconst._methodref = (constant_methodref*) malloc(sizeof(constant_methodref));
                file.constpool[i].jconst._methodref->class_index = jvm_u16(data[idx++], data[idx++]);
                file.constpool[i].jconst._methodref->name_and_type_index = jvm_u16(data[idx++], data[idx++]);
                break;
            case CONSTANT_InterfaceMethodref:
                file.constpool[i].jconst._interfacemethodref = (constant_interfacemethodref*) malloc(sizeof(constant_interfacemethodref));
                file.constpool[i].jconst._interfacemethodref->class_index = jvm_u16(data[idx++], data[idx++]);
                file.constpool[i].jconst._interfacemethodref->name_and_type_index = jvm_u16(data[idx++], data[idx++]);
                break;
            case CONSTANT_String:
                file.constpool[i].jconst._string = (constant_string*) malloc(sizeof(constant_string));
                file.constpool[i].jconst._string->string_index = jvm_u16(data[idx++], data[idx++]);
                break;
            case CONSTANT_Integer:
                file.constpool[i].jconst._int = (constant_int*) malloc(sizeof(constant_int));
                file.constpool[i].jconst._int->num = jvm_i32(data[idx++],data[idx++],data[idx++],data[idx++]);
                break;
            case CONSTANT_Float:
                file.constpool[i].jconst._float = (constant_float*) malloc(sizeof(constant_float));
                file.constpool[i].jconst._float->num = jvm_f32(data[idx++],data[idx++],data[idx++],data[idx++]);
                break;
            case CONSTANT_Long:
                file.constpool[i].jconst._long = (constant_long*) malloc(sizeof(constant_long));
                file.constpool[i].jconst._long->num = jvm_i64(data[idx++],data[idx++],data[idx++],data[idx++],data[idx++],data[idx++],data[idx++],data[idx++]);
                break;
            case CONSTANT_Double:
                file.constpool[i].jconst._double = (constant_double*) malloc(sizeof(constant_double));
                file.constpool[i].jconst._double->num = jvm_f64(data[idx++],data[idx++],data[idx++],data[idx++],data[idx++],data[idx++],data[idx++],data[idx++]);
                break;
            case CONSTANT_NameAndType:
                file.constpool[i].jconst._nameandtype = (constant_nameandtype*) malloc(sizeof(constant_nameandtype));
                file.constpool[i].jconst._nameandtype->name_index = jvm_u16(data[idx++], data[idx++]);
                file.constpool[i].jconst._nameandtype->descriptor_index = jvm_u16(data[idx++], data[idx++]);
                break;
            case CONSTANT_Utf8:
                file.constpool[i].jconst._utf8 = (constant_utf8*) malloc(sizeof(constant_utf8));
                file.constpool[i].jconst._utf8->length = jvm_u16(data[idx++], data[idx++]);
                file.constpool[i].jconst._utf8->bytes = (char*) malloc(sizeof(char)*(file.constpool[i].jconst._utf8->length+1));
                for (int x = 0; i < file.constpool[i].jconst._utf8->length; x++){
                    file.constpool[i].jconst._utf8->bytes[x] = data[idx++];
                } file.constpool[i].jconst._utf8->bytes[file.constpool[i].jconst._utf8->length+1] = '\0';
                break;
            case CONSTANT_MethodHandle:
                file.constpool[i].jconst._methodhandle = (constant_methodhandle*) malloc(sizeof(constant_methodhandle));
                file.constpool[i].jconst._methodhandle->reference_kind = data[idx++];
                file.constpool[i].jconst._methodhandle->reference_index = jvm_u16(data[idx++], data[idx++]);;
                break;
            case CONSTANT_MethodType:
                file.constpool[i].jconst._methodtype = (constant_methodtype*) malloc(sizeof(constant_methodtype));
                file.constpool[i].jconst._methodtype->descriptor_index = jvm_u16(data[idx++], data[idx++]);
                break;
            case CONSTANT_InvokeDynamic:
                file.constpool[i].jconst._invokedynamic = (constant_invokedynamic*) malloc(sizeof(constant_invokedynamic));
                file.constpool[i].jconst._invokedynamic->bootstrap_method_attr_index = jvm_u16(data[idx++], data[idx++]);
                file.constpool[i].jconst._invokedynamic->name_and_type_index = jvm_u16(data[idx++], data[idx++]);
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
                free(file.constpool[i].jconst._float);
                break;
            case CONSTANT_Long:
                free(file.constpool[i].jconst._long);
                break;
            case CONSTANT_Double:
                free(file.constpool[i].jconst._double);
                break;
            case CONSTANT_NameAndType:
                free(file.constpool[i].jconst._nameandtype);
                break;
            case CONSTANT_Utf8:
                free(file.constpool[i].jconst._utf8->bytes);
                free(file.constpool[i].jconst._utf8);
                break;
            case CONSTANT_MethodHandle:
                free(file.constpool[i].jconst._methodhandle);
                break;
            case CONSTANT_MethodType:
                free(file.constpool[i].jconst._methodtype);
                break;
            case CONSTANT_InvokeDynamic:
                free(file.constpool[i].jconst._invokedynamic);
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