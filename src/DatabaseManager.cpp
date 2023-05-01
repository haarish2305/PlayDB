#include "../includes/DatabaseManager.h"

int DatabaseManager::execute_create_query(CreateQuery *query) {
    if (name_db_map.find(query->database_name) != name_db_map.end()) return DATABASE_EXISTS_ERROR;
    std::vector<Attribute*> attributes;

    for (int i = 0; i < query->attributes.size(); i++) {
        attributes.push_back(new Attribute(query->attributes[i].first, query->attributes[i].second));
    }

    int tuple_size = commons::get_tuple_size(attributes);

    Database *db = new Database(query->database_name, attributes, query->primary_key, query->foreign_key, query->foreign_database_name, new RamBasedStorage(tuple_size));

    for (int i = 0; i < attributes.size(); i++) delete attributes[i];
    name_db_map[query->database_name] = db;
    return QUERY_EXECUTED;
}

int DatabaseManager::execute_drop_query(DropQuery *query) {
    return QUERY_EXECUTED;
}

int DatabaseManager::execute_insert_query(InsertQuery *query) {
    std::cout << "execute_insert_query" << std::endl;
    std::cout << "db_name: " << query->db_name << std::endl;
    std::cout << "values: ";
    for (std::string value: query->values) std::cout << value << " ";
    std::cout << std::endl;
    if (name_db_map.find(query->db_name) == name_db_map.end()) return DATABASE_NOT_FOUND;
    return QUERY_EXECUTED;
}

bool DatabaseManager::execute_query(std::string query) {
    Query* parsed_query = QueryParser::get_query(query);
    switch (parsed_query->type)
    {
    case CREATE_QUERY:
        execute_create_query((CreateQuery*)parsed_query);
        break;
    case DROP_QUERY:
        execute_drop_query((DropQuery*)parsed_query);
        break;
    case INSERT_QUERY:
    execute_insert_query((InsertQuery*)parsed_query);
        break;
    default:
        break;
    }
    delete parsed_query;
    // Parse query using QueryParser
}