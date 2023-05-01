#ifndef COMMONS

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <math.h>

#define COMMONS 1

#define UNKNOWN_QUERY -1
#define CREATE_QUERY 1
#define DROP_QUERY   2
#define INSERT_QUERY 3
#define DELETE_QUERY 4
#define UPDATE_QUERY 5

#define STRING 6
#define CHAR 7
#define INT 8
#define LONG_LONG 9
#define DOUBLE 10
#define BOOLEAN 11

#define STRING_SIZE 32
#define INT_SIZE 4
#define CHAR_SIZE 1
#define LONG_LONG_SIZE 8
#define DOUBLE_SIZE 8
#define BOOLEAN_SIZE 1

struct Query {
    unsigned int type;
};

struct CreateQuery : public Query {
    std::vector<std::pair<std::string, unsigned int>> attributes;
    std::unordered_set<unsigned int> primary_key;
    std::unordered_set<std::string> foreign_key;
    std::string foreign_database_name;
    std::string database_name;
};

struct InsertQuery : public Query {
    std::string db_name;
    std::vector<std::string> values;
};

struct DropQuery : public Query {
    std::string db_name;
    DropQuery(std::string db_name) { this-> db_name = db_name; }
};

struct Tuple {
    unsigned int size;
    std::string values;
};

struct Attribute {
    std::string name;
    unsigned int type;
    Attribute(std::string name, unsigned int type) {
        this->name = name;
        this->type = type;
    }
};

struct Schema {
    std::string meta_data;
    std::string db_name;
    unsigned int size;
    std::vector<Attribute*> attributes;
    std::unordered_set<unsigned int> primary_keys;
    std::unordered_set<std::string> foreign_keys;
    std::string foreign_db_name;
};

class commons {
public:
    static unsigned int get_tuple_size(std::vector<Attribute*> attributes);
    static void pad_extra_bytes(std::string &str, char pad_ch, int bytes);
    static inline std::string trim(std::string &str) {
        str.erase(str.find_last_not_of(' ')+1);         //suffixing spaces
        str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
        return str;
    }
};

#endif