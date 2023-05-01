#include "../includes/Database.h"

Database::Database(std::string name, std::vector<Attribute*> attributes, std::unordered_set<unsigned int> primary_key, std::unordered_set<std::string> foreign_key, std::string foreign_db_name, Storage *storage) {
    this->storage = std::unique_ptr<Storage>(storage);
    this->schema = std::unique_ptr<Schema>(new Schema());
    for (int i = 0; i < (unsigned int)attributes.size(); i++) {
        this->schema->attributes.push_back(attributes[i]);
    }
    this->schema->meta_data = "        ";
    this->schema->size = (unsigned int) attributes.size();
    this->schema->db_name = name;
    this->schema->foreign_db_name = foreign_db_name;
    this->schema->primary_keys = primary_key;
    this->schema->foreign_keys = foreign_key;
    this->storage->write_schema(this->schema);

    Schema *temp = new Schema();
    this->storage->read_schema(temp);
}

bool Database::insert(Tuple *tuple) {
    std::vector<std::string> values(1);
    values[0] = tuple->values;
    this->storage->write_tuples(values, 1);
}

bool Database::remove_tuples(std::unordered_map<Attribute*, std::string> values) {
}