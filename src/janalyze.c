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

    printf("VERSION: %s\n", file.version);
    file.constpool_c = (jvm_u16(data[idx++], data[idx++])-1);
    printf("constants[%d]=\n", file.constpool_c);
    file.constpool = (jvm_constant*) malloc(sizeof(jvm_constant)*file.constpool_c);
 
    idx = parse_cpool(data, idx, file.constpool, file.constpool_c, 1);

    file.access_flags = jvm_u16(data[idx++], data[idx++]);
    printf("access_flags: %d\n", file.access_flags);

    file.this_class = jvm_u16(data[idx++], data[idx++])-1;
    printf("this_class: %s\n", file.constpool[file.constpool[file.this_class].jconst._class->name_index].jconst._utf8->bytes);

    file.super_class = jvm_u16(data[idx++], data[idx++])-1;
    if (file.super_class != 0)
        printf("super_clas: %s\n", file.constpool[file.constpool[file.super_class].jconst._class->name_index].jconst._utf8->bytes);
    file.interface_c = jvm_u16(data[idx++], data[idx++]);
    printf("interfaces[%d]=\n", file.interface_c);

    u16 interfaces[file.interface_c];

    for (int i = 0; i < file.interface_c; i++){
        interfaces[i] = jvm_u16(data[idx++], data[idx++]);
        printf("interface[%d]\n", interfaces[i]);
    }
    file.interfaces = interfaces;

    file.field_c = jvm_u16(data[idx++], data[idx++]);
    printf("fields[%d]=\n", file.field_c);

    field fields[file.field_c];

    for (int i = 0; i < file.field_c; i++){
        fields[i].access_flags = jvm_u16(data[idx++], data[idx++]);
        fields[i].name_index = jvm_u16(data[idx++], data[idx++]);
        fields[i].descriptor_index = jvm_u16(data[idx++], data[idx++]);
        fields[i].attribute_c = jvm_u16(data[idx++], data[idx++]);
        fields[i].attributes = (jvm_attribute*) malloc(sizeof(jvm_attribute)*fields[i].attribute_c);
        parse_attr(data, &idx, fields[i].attributes, fields[i].attribute_c, file.constpool);
    }

    file.fields = fields;

    free(data);
    for (int i = 0; i < file.field_c; i++){
        free_attr(file.fields->attributes, file.fields->attribute_c, file.constpool);
    }
    free_cpool(file.constpool, file.constpool_c);

    return 0;
}