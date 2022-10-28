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
            for (int x = 0; x < attrs[i].attr.stack_map_table_attr->number_of_entries; x++){
                attrs[i].attr.stack_map_table_attr->entries[x].frame_type = data[*idx++];
                if (0<=attrs[i].attr.stack_map_table_attr->entries[x].frame_type<=63){
                    attrs[i].attr.stack_map_table_attr->entries[x].frame._same_frame = attrs[i].attr.stack_map_table_attr->entries[x].frame_type;
                }else if (64<=attrs[i].attr.stack_map_table_attr->entries[x].frame_type<=127){
                    attrs[i].attr.stack_map_table_attr->entries[x].frame._same_local_stack_item_frame.frame_type = attrs[i].attr.stack_map_table_attr->entries[x].frame_type;
                    attrs[i].attr.stack_map_table_attr->entries[x].frame._same_local_stack_item_frame.stack.tag = data[*idx++];
                    switch(attrs[i].attr.stack_map_table_attr->entries[x].frame._same_local_stack_item_frame.stack.tag){
                        case ObjectVariableVerification:
                            attrs[i].attr.stack_map_table_attr->entries[x].frame._same_local_stack_item_frame.stack.verification_type._object_variable_info.cpool_index = jvm_u16(data[*idx++],data[*idx++]);
                            break;
                        case UninitializedVariableVerification:
                            attrs[i].attr.stack_map_table_attr->entries[x].frame._same_local_stack_item_frame.stack.verification_type._uninitialized_variable_info.offset = jvm_u16(data[*idx++],data[*idx++]);
                            break;
                        default:
                            break;
                    }

                } else if ((attrs[i].attr.stack_map_table_attr->entries[x].frame_type==247)){

                    attrs[i].attr.stack_map_table_attr->entries[x].frame._same_local_stack_item_frame_extended.frame_type = attrs[i].attr.stack_map_table_attr->entries[x].frame_type;
                    attrs[i].attr.stack_map_table_attr->entries[x].frame._same_local_stack_item_frame_extended.offset_delta = jvm_u16(data[*idx++], data[*idx++]);
                    switch(attrs[i].attr.stack_map_table_attr->entries[x].frame._same_local_stack_item_frame_extended.stack.tag){
                        case ObjectVariableVerification:
                            attrs[i].attr.stack_map_table_attr->entries[x].frame._same_local_stack_item_frame.stack.verification_type._object_variable_info.cpool_index = jvm_u16(data[*idx++],data[*idx++]);
                            break;
                        case UninitializedVariableVerification:
                            attrs[i].attr.stack_map_table_attr->entries[x].frame._same_local_stack_item_frame.stack.verification_type._uninitialized_variable_info.offset = jvm_u16(data[*idx++],data[*idx++]);
                            break;
                        default:
                            break;
                    }
                } else if (248<=attrs[i].attr.stack_map_table_attr->entries[x].frame_type<=250){

                    attrs[i].attr.stack_map_table_attr->entries[x].frame._chop_frame.frame_type = attrs[i].attr.stack_map_table_attr->entries[x].frame_type;
                    attrs[i].attr.stack_map_table_attr->entries[x].frame._chop_frame.offset_delta = jvm_u16(data[*idx++],data[*idx++]);
                } else if (attrs[i].attr.stack_map_table_attr->entries[x].frame_type == 251){

                    attrs[i].attr.stack_map_table_attr->entries[x].frame._same_frame_extended.frame_type = attrs[i].attr.stack_map_table_attr->entries[x].frame_type;
                    attrs[i].attr.stack_map_table_attr->entries[x].frame._same_frame_extended.offset_delta = jvm_u16(data[*idx++], data[*idx++]);
                } else if (252<=attrs[i].attr.stack_map_table_attr->entries[x].frame_type<=254){

                    attrs[i].attr.stack_map_table_attr->entries[x].frame._append_frame.frame_type = attrs[i].attr.stack_map_table_attr->entries[x].frame_type;
                    attrs[i].attr.stack_map_table_attr->entries[x].frame._append_frame.offset_delta = jvm_u16(data[*idx++], data[*idx++]);
                    attrs[i].attr.stack_map_table_attr->entries[x].frame._append_frame.locals.tag = data[*idx++];
                    switch(attrs[i].attr.stack_map_table_attr->entries[x].frame._append_frame.locals.tag){
                        case ObjectVariableVerification:
                            attrs[i].attr.stack_map_table_attr->entries[x].frame._append_frame.locals.verification_type._object_variable_info.cpool_index = jvm_u16(data[*idx++],data[*idx++]);
                            break;
                        case UninitializedVariableVerification:
                            attrs[i].attr.stack_map_table_attr->entries[x].frame._append_frame.locals.verification_type._uninitialized_variable_info.offset = jvm_u16(data[*idx++],data[*idx++]);
                            break;
                        default:
                            break;
                    }
                } else if (attrs[i].attr.stack_map_table_attr->entries[x].frame_type == 255){
                    attrs[i].attr.stack_map_table_attr->entries[x].frame._full_frame.frame_type = attrs[i].attr.stack_map_table_attr->entries[x].frame_type;
                    attrs[i].attr.stack_map_table_attr->entries[x].frame._full_frame.offset_delta = jvm_u16(data[*idx++], data[*idx++]);
                    attrs[i].attr.stack_map_table_attr->entries[x].frame._full_frame.number_of_locals = jvm_u16(data[*idx++],data[*idx++]);
                    attrs[i].attr.stack_map_table_attr->entries[x].frame._full_frame.locals = (verification_type_info*) malloc(sizeof(verification_type_info)*attrs[i].attr.stack_map_table_attr->entries[x].frame._full_frame.number_of_locals);
                    for (int y = 0; y < attrs[i].attr.stack_map_table_attr->entries[x].frame._full_frame.number_of_locals; y++){
                        attrs[i].attr.stack_map_table_attr->entries[x].frame._full_frame.locals[y].tag = data[*idx++];
                        switch(attrs[i].attr.stack_map_table_attr->entries[x].frame._full_frame.locals[y].tag){
                            case ObjectVariableVerification:
                                attrs[i].attr.stack_map_table_attr->entries[x].frame._full_frame.locals[y].verification_type._object_variable_info.cpool_index = jvm_u16(data[*idx++],data[*idx++]);
                                break;
                            case UninitializedVariableVerification:
                                attrs[i].attr.stack_map_table_attr->entries[x].frame._full_frame.locals[y].verification_type._uninitialized_variable_info.offset = jvm_u16(data[*idx++],data[*idx++]);
                                break;
                            default:
                                break;
                        }
                    }
                    attrs[i].attr.stack_map_table_attr->entries[x].frame._full_frame.number_of_stack_items = jvm_u16(data[*idx++],data[*idx++]);
                    attrs[i].attr.stack_map_table_attr->entries[x].frame._full_frame.stack = (verification_type_info*) malloc(sizeof(verification_type_info)*attrs[i].attr.stack_map_table_attr->entries[x].frame._full_frame.number_of_stack_items);
                    for (int y = 0; y < attrs[i].attr.stack_map_table_attr->entries[x].frame._full_frame.number_of_stack_items; y++){
                        attrs[i].attr.stack_map_table_attr->entries[x].frame._full_frame.stack[y].tag = data[*idx++];
                        switch(attrs[i].attr.stack_map_table_attr->entries[x].frame._full_frame.locals->tag){
                            case ObjectVariableVerification:
                                attrs[i].attr.stack_map_table_attr->entries[x].frame._full_frame.stack[y].verification_type._object_variable_info.cpool_index = jvm_u16(data[*idx++],data[*idx++]);
                                break;
                            case UninitializedVariableVerification:
                                attrs[i].attr.stack_map_table_attr->entries[x].frame._full_frame.stack[y].verification_type._uninitialized_variable_info.offset = jvm_u16(data[*idx++],data[*idx++]);
                                break;
                            default:
                                break;
                        }
                            
                    }
                    
                }
            }
        }  else if (strcmp("Exceptions", consts[attrs[i].attribute_name_index].jconst._utf8->bytes) == 0){
            attrs[i].attr.exception_attr = (Exceptions*) malloc(sizeof(Exceptions));
        }
    }
}

void free_attr(jvm_attribute* attrs, i32 attr_c, jvm_constant* consts){
    for (int i = 0; i < attr_c; i++){
        if (strcmp("Code", consts[attrs[i].attribute_name_index].jconst._utf8->bytes) == 0){
            free(attrs[i].attr.code_attr->code);
            free(attrs[i].attr.code_attr->exceptions);
            free_attr(attrs[i].attr.code_attr->attributes, attrs[i].attr.code_attr->attribute_c, consts);
            free(attrs[i].attr.code_attr);
        } else if (strcmp("StackMapTable", consts[attrs[i].attribute_name_index].jconst._utf8->bytes) == 0){
            for (int x = 0; x < attrs[i].attr.stack_map_table_attr->number_of_entries; x++) {
                if (attrs[i].attr.stack_map_table_attr->entries[x].frame_type == 255){
                    free(attrs[i].attr.stack_map_table_attr->entries[x].frame._full_frame.stack);
                    free(attrs[i].attr.stack_map_table_attr->entries[x].frame._full_frame.locals);
                }
            }
            free(attrs[i].attr.stack_map_table_attr->entries);
            free(attrs[i].attr.stack_map_table_attr);
        }
    }
    free(attrs);
}