#ifndef DATABASE_MANAGER

#define DATABASE_MANAGER 1

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "QueryParser.h"
#include "Database.h"

#define DATABASE_EXISTS_ERROR -1
#define QUERY_EXECUTED         1
#define DATABASE_NOT_FOUND    -2

// Take database queries and executes
class DatabaseManager {
private:
    std::unordered_map<std::string, Database*> name_db_map;
    int execute_create_query(CreateQuery* query);
    int execute_drop_query(DropQuery* query);
    int execute_insert_query(InsertQuery* query);
public:
    bool execute_query(std::string query);
};

#endif