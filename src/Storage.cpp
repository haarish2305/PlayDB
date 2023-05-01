#include "../includes/Storage.h"

Storage::Storage() {}

void Storage::write_schema(std::shared_ptr<Schema> schema) {
    std::string schema_str = schema->meta_data;
    schema_str += schema->db_name;
    commons::pad_extra_bytes(schema_str, ' ', 32 - (int)schema->db_name.size());
    unsigned int num_of_tuples = schema->size;
    schema_str += std::to_string(num_of_tuples);
    commons::pad_extra_bytes(schema_str, ' ', 4 - std::to_string(num_of_tuples).size());
    for (Attribute* attr: schema->attributes) {
        schema_str += attr->name;
        commons::pad_extra_bytes(schema_str, ' ', 16 - attr->name.size());
        schema_str += std::to_string(attr->type);
    }
    schema_str += schema->foreign_db_name;
    commons::pad_extra_bytes(schema_str, ' ', 32 - schema->foreign_db_name.size());
    schema_str += std::to_string(schema->primary_keys.size());
    commons::pad_extra_bytes(schema_str, ' ', 4 - std::to_string(schema->primary_keys.size()).size());
    for (int i: schema->primary_keys) {
        schema_str += std::to_string(i);
        commons::pad_extra_bytes(schema_str, ' ', 4 - std::to_string(i).size());
    }
    schema_str += std::to_string(schema->foreign_keys.size());
    commons::pad_extra_bytes(schema_str, ' ', 4 - std::to_string(schema->foreign_keys.size()).size());
    for (std::string str: schema->foreign_keys) schema_str += str + '\0';
    this->schema_file = schema_str;
    std::cout << "schema_file: " << this->schema_file << std::endl;
}

void Storage::read_schema(Schema *schema) {
    schema->meta_data = this->schema_file.substr(0, 8);   // 8 bytes  -> meta data
    schema->db_name = this->schema_file.substr(8, 32);    // 32 bytes -> db name
    std::string temp = this->schema_file.substr(40, 4);   // 4 bytes  -> num of tuples
    commons::trim(temp);
    schema->size = stoi(temp);
    unsigned int offset = 44;
    for (int i = 0; i < schema->size; i++) {
        std::string attr_name = this->schema_file.substr(offset, 16); // 16 bytes -> attribute name
        offset += 16;
        temp = this->schema_file.substr(offset, 1);                   // 1 byte   -> attribute type
        offset += 1;
        commons::trim(temp);
        unsigned int attr_type = stoi(temp);
        Attribute *attr = new Attribute(attr_name, attr_type);
        schema->attributes.push_back(attr);
    }
    schema->foreign_db_name = this->schema_file.substr(offset, 32);   // 32 bytes -> foreign db name
    offset += 32;
    temp = this->schema_file.substr(offset, 4);                       // 4 bytes  -> num of primary keys
    offset += 4;
    commons::trim(temp);
    unsigned int num_of_primary_keys = stoi(temp);
    for (int i = 0; i < num_of_primary_keys; i++) {
        temp = this->schema_file.substr(offset, 4);                   // 4 bytes -> primary key
        offset += 4;
        commons::trim(temp);
        schema->primary_keys.insert(stoi(temp));
    }

    temp = this->schema_file.substr(offset, 4);                       // 4 bytes -> num of foreign key
    offset += 4;
    commons::trim(temp);
    unsigned int num_of_foreign_keys = stoi(temp);
    for (int i = 0; i < num_of_foreign_keys; i++) {
        temp = this->schema_file.substr(offset, 4);                   // 4 bytes -> foreign key
        offset += 4;
        commons::trim(temp);
        schema->foreign_keys.insert(temp);
    }

    //////// Print schema /////////
    std::cout << "Meta data: " << schema->meta_data << std::endl;
    std::cout << "DB name: " << schema->db_name << std::endl;
    std::cout << "Schema size: " << schema->size << std::endl;
    std::cout << "Attributes: " << std::endl;
    for (int i = 0; i < schema->attributes.size(); i++) {
        std::cout << schema->attributes[i]->name << " " << schema->attributes[i]->type << std::endl;
    }
    std::cout << "Foreign DB name: " << schema->foreign_db_name << std::endl;
    std::cout << "Primary keys: " << std::endl;
    for (int i: schema->primary_keys) std::cout << i << std::endl;
    std::cout << "Foreign keys: " << std::endl;
    for (std::string i: schema->foreign_keys) std::cout << i << std::endl;
}

RamBasedStorage::RamBasedStorage(unsigned int tuple_size) {
    this->tuple_size = tuple_size;
    this->read_tuple_pointer = this->write_tuple_pointer = 0;
}

void RamBasedStorage::read_tuples(std::vector<std::string> &values, unsigned int num_tuples) {
    values.clear();
    unsigned int temp = read_tuple_pointer;
    for(int i = 0; i < num_tuples; i++) {
        values[i] = file.substr(temp, tuple_size);
        temp += tuple_size;
    }
}

void RamBasedStorage::write_tuples(std::vector<std::string> &values, unsigned int num_tuples) {
    if((int)values.size() != num_tuples) {
        std::cout << "Cannot write tuples" << std::endl;
        return;
    }
    for(int i = 0; i < num_tuples; i++) file += values[i];
    this->write_tuple_pointer += this->tuple_size * num_tuples;
}

void RamBasedStorage::remove_tuple(int tuple_num) {
}