#ifndef STORAGE

#define STORAGE 1
#define MAXIMUM_BYTES_FOR_STORAGE 1024

#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <unordered_set>
#include "commons.h"

class Storage {
    // Provides some apis to store and retrieve data.
protected:
    std::string file;
    std::string schema_file;
    const static unsigned int MAX_STORAGE_SIZE = MAXIMUM_BYTES_FOR_STORAGE;
    unsigned int tuple_size;
    int read_tuple_pointer;
    int write_tuple_pointer;
public:
    Storage();
    virtual void read_tuples(std::vector<std::string> &values, unsigned int num_tuples) = 0;
    virtual void write_tuples(std::vector<std::string> &values, unsigned int num_tuples) = 0;
    virtual void remove_tuple(int tuple_pointer) = 0;
    virtual void write_schema(std::shared_ptr<Schema> schema);
    virtual void read_schema(Schema *schema);
    void set_read_tuple_pointer(unsigned int value) { this->read_tuple_pointer = value; }
};

class RamBasedStorage : public Storage {
private:
    virtual void read_tuples(std::vector<std::string> &values, unsigned int num_tuples);
    virtual void write_tuples(std::vector<std::string> &values, unsigned int num_tuples);
    virtual void remove_tuple(int tuple_pointer);
public:
    RamBasedStorage(unsigned int tuple_size);
};

#endif