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
 
    idx = pprint_cpool(data, idx);

    free(data);

    return 0;
}