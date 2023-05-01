#ifndef DATABASE

#define DATABASE 1
#define SCHEMA_METADATA_SIZE 8

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include "Storage.h"
#include "commons.h"

class Database {
private:
    std::shared_ptr<Schema> schema;
    std::unique_ptr<Storage> storage;
public:
    Database(std::string name, std::vector<Attribute*> attributes, std::unordered_set<unsigned int> primary_key, std::unordered_set<std::string> foreign_key, std::string foreign_db_name, Storage *storage);
    bool insert(Tuple *tuple);
    bool remove_tuples(std::unordered_map<Attribute*, std::string> values);
    bool update(Tuple *tuple, std::unordered_map<Attribute*, std::string> where);
};

#endif