#include "../includes/jvm_structs/attributes.h"
#include "../includes/jvm_structs/constants.h"
#include <stdlib.h>
#include <string.h>

void parse_attr(u8* data, i32* idx, jvm_attribute* attrs, i32 attr_c, jvm_constant* consts){
    for (int i = 0; i < attr_c; i++){
        attrs[i].attribute_name_index = jvm_u16(data[*idx++], data[*idx++]);
        attrs[i].attribute_length = jvm_i32(data[*idx++], data[*idx++],data[*idx++], data[*idx++]);
        if (strcmp("ConstantValue", consts[attrs[i].attribute_name_index].jconst._utf8->bytes) == 0){
            attrs[i].attr.const_val_index = jvm_u16(data[*idx++], data[*idx++]);
        } else if (strcmp("Code", consts[attrs[i].attribute_name_index].jconst._utf8->bytes) == 0){
            attrs[i].attr.code_attr = (Code*) malloc(sizeof(Code));
            attrs[i].attr.code_attr->max_stack = jvm_u16(data[*idx++], data[*idx++]);
            attrs[i].attr.code_attr->max_locals = jvm_u16(data[*idx++], data[*idx++]);
            attrs[i].attr.code_attr->code_length = jvm_u32(data[*idx++], data[*idx++], data[*idx++], data[*idx++]);
            attrs[i].attr.code_attr->code = (u8*) malloc(sizeof(u8) * attrs[i].attr.code_attr->code_length);
            for (int x = 0; x < attrs[i].attr.code_attr->code_length; x++){
                attrs[i].attr.code_attr->code[x] = data[*idx++];
            }
            attrs[i].attr.code_attr->exception_c = jvm_u16(data[*idx++], data[*idx++]);
            attrs[i].attr.code_attr->exceptions = (exception*) malloc(sizeof(exception));
            for (int x = 0; x < attrs[i].attr.code_attr->exception_c; x++){
                attrs[i].attr.code_attr->exceptions[x].start_pc = jvm_u16(data[*idx++], data[*idx++]);
                attrs[i].attr.code_attr->exceptions[x].end_pc = jvm_u16(data[*idx++], data[*idx++]);
                attrs[i].attr.code_attr->exceptions[x].handler_pc = jvm_u16(data[*idx++], data[*idx++]);
                attrs[i].attr.code_attr->exceptions[x].catch_type = jvm_u16(data[*idx++], data[*idx++]);
            }
            attrs[i].attr.code_attr->attribute_c = jvm_u16(data[*idx++], data[*idx++]);
            attrs[i].attr.code_attr->attributes = (jvm_attribute*) malloc(sizeof(jvm_attribute));
            parse_attr(data, idx, attrs[i].attr.code_attr->attributes, attrs[i].attr.code_attr->attribute_c, consts);
        } else if (strcmp("StackMapTable", consts[attrs[i].attribute_name_index].jconst._utf8->bytes) == 0){
            attrs[i].attr.stack_map_table_attr = (StackMapTable*) malloc(sizeof(StackMapTable));
            attrs[i].attr.stack_map_table_attr->number_of_entries = jvm_u16(data[*idx++], data[*idx++]);
            attrs[i].attr.stack_map_table_attr->entries = (jvm_stack_map_frame*) malloc(sizeof(jvm_stack_map_frame)*attrs[i].attr.stack_map_table_attr->number_of_entries);
        }
    }
}

void free_attr(jvm_attribute* attrs, i32 attr_c, jvm_constant* consts){
    for (int i = 0; i < attr_c; i++){
        if (strcmp("Code", consts[attrs[i].attribute_name_index].jconst._utf8->bytes) == 0){
            free(attrs[i].attr.code_attr->code);
            free(attrs[i].attr.code_attr->exceptions);
            free_attr(attrs[i].attr.code_attr->attributes, attrs[i].attr.code_attr->attribute_c, consts);
        }
    }
    free(attrs);
}