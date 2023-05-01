#include "../includes/commons.h"

unsigned int commons::get_tuple_size(std::vector<Attribute*> attributes) {
    unsigned int tuple_size = 0;
    for (int i = 0; i < attributes.size(); i++) {
        switch (attributes[i]->type)
        {
        case STRING:
            tuple_size += STRING_SIZE;
            break;
        case INT:
            tuple_size += INT_SIZE;
            break;
        case CHAR:
            tuple_size += CHAR_SIZE;
            break;
        case LONG_LONG:
            tuple_size += LONG_LONG_SIZE;
            break;
        case DOUBLE:
            tuple_size += DOUBLE_SIZE;
            break;
        case BOOLEAN:
            tuple_size += BOOLEAN_SIZE;
            break;
        default:
            break;
        }
    }
    return tuple_size;
}

void commons::pad_extra_bytes(std::string &str, char pad_ch, int bytes) {
    if (bytes < 0) return;
    for (int i = 0; i < bytes; i++) str += pad_ch;
}