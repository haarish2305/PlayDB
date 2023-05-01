#ifndef QUERY_PARSER 

#define QUERY_PARSER 1

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "commons.h"

/*
create database database_name (name1 type1, name2 type2, . . . . . ) primary_key (namex, namey, . . . ) foreign_key (...) references database_name1
drop database database_name
insert into database_name (value1, value2, value3, . . . . .)
delete from database_name where name1 = value1, name2 = value2, . . . . . 
update database_name set name1 = value1, name2 = value2 where name1 = value1, . . . . . . 
*/

class QueryParser {
private:
    static std::unordered_set<char> delimiters;
    static std::string get_next(const std::string &query, unsigned int &index);
    static std::vector<std::pair<std::string, std::string>> extract_key_value_pairs(const std::string &query, unsigned int &index);
    static std::vector<std::string> extract_keys(const std::string &query, unsigned int &index);
    static Query* get_drop_query(const std::string &query);
    static Query* get_create_query(const std::string &query);
    static unsigned int get_query_type(const std::string &query);
    static Query* get_insert_query(const std::string &query);
public:
    static Query* get_query(const std::string &query);
};

#endif