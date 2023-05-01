#include "../includes/QueryParser.h"

std::unordered_set<char> QueryParser::delimiters = {
    ' ', '(', ')', ','
};

unsigned int QueryParser::get_query_type(const std::string &query) {
    std::string first_word = query.substr(0, query.find(' '));
    if(first_word == "create") return CREATE_QUERY;
    else if(first_word == "drop") return DROP_QUERY;
    else if(first_word == "insert") return INSERT_QUERY;
    else if(first_word == "delete") return DELETE_QUERY;
    else if(first_word == "update") return UPDATE_QUERY;
    else return UNKNOWN_QUERY;
}

std::string QueryParser::get_next(const std::string &query, unsigned int &index) {
    std::string next = "";
    while(index < (unsigned int)query.size()) {
        if(delimiters.find(query[index]) != delimiters.end()) break;
        next += query[index++];
    }
    return next;
}

std::vector<std::pair<std::string, std::string>> QueryParser::extract_key_value_pairs(const std::string &query, unsigned int &index) {
    if(query[index] != '('){
        std::cout << "Cannot extract key value pairs. First character != \'(\'" << std::endl;
        return {};
    }
    index++;
    std::string key, value;
    std::vector<std::pair<std::string, std::string>> res;
    while(1) {
        key = get_next(query, index);
        index++;
        value = get_next(query, index);
        res.push_back({ key, value });
        if(query[index] == ',') {
            index += 2;
            continue;
        }
        else if(query[index] == ')') break;
        else {
            std::cout << "Cannot extract key value pairs. Unexpected character." << std::endl;
            return {};
        }
    }
    return res;
}

std::vector<std::string> QueryParser::extract_keys(const std::string &query, unsigned int &index) {
    if(query[index] != '('){
        std::cout << "Cannot extract keys, First character != \'(\'" << std::endl;
        return {};
    }
    index++;
    std::string key;
    std::vector<std::string> res;
    while(1) {
        key = get_next(query, index);
        res.push_back(key);
        if(query[index] == ',') {
            index += 2;
            continue;
        }
        else if(query[index] == ')') break;
        else {
            std::cout << "Cannot extract keys. Unexpected character." << std::endl;
            return {};
        }
    }
    return res;
}

Query* QueryParser::get_create_query(const std::string &query) {
    CreateQuery *create_query = new CreateQuery();
    unsigned int index = 0;
    std::string keyword = get_next(query, index);
    if(keyword != "create") {
        std::cout << "First word != \"create\"" << std::endl;
        delete create_query;
        return NULL;
    }
    index++;
    keyword = get_next(query, index);
    if(keyword != "database") {
        std::cout << "Second word != \"database\"" << std::endl;
        delete create_query;
        return NULL;
    }
    index++;
    keyword = get_next(query, index);
    if(keyword.empty()) {
        std::cout << "Database name cannot be empty" << std::endl;
        delete create_query;
        return NULL;
    }
    create_query->database_name = keyword;
    index++;
    std::vector<std::pair<std::string, std::string>> attributes = extract_key_value_pairs(query, index);
    if(attributes.empty()) {
        std::cout << "Attributes cannot be empty" << std::endl;
        delete create_query;
        return NULL;
    }
    index += 2;
    keyword = get_next(query, index);
    if(keyword != "primary_key") {
        std::cout << "Cannot find \"primary_key\"" << std::endl;
        delete create_query;
        return NULL;
    }
    index++;
    std::vector<std::string> primary_keys = extract_keys(query, index);
    if(primary_keys.empty()) {
        std::cout << "Primary keys cannot be empty" << std::endl;
        delete create_query;
        return NULL;
    }
    
    if(index < (int)query.size() - 1) {
        index += 2;
        keyword = get_next(query, index);
        if(keyword != "foreign_key") {
            std::cout << "Cannot find \"foreign_key\"" << std::endl;
            delete create_query;
            return NULL;
        }
        index++;
        std::vector<std::string> foreign_keys = extract_keys(query, index);
        if(foreign_keys.empty()) {
            std::cout << "Foreign key cannot be empty." << std::endl;
            delete create_query;
            return NULL;
        }
        index += 2;
        keyword = get_next(query, index);
        if(keyword != "references") {
            std::cout << "Cannot find \"references\"" << std::endl;
            delete create_query;
            return NULL;
        }
        index++;
        keyword = get_next(query, index);
        if(keyword.empty()) {
            std::cout << "Referenced database name cannot be empty." << std::endl;
            delete create_query;
            return NULL;
        }
        create_query->foreign_database_name = keyword;

        for(std::string str: foreign_keys) {
        create_query->foreign_key.insert(str);
    }
    }

    std::unordered_set<std::string> temp;
    for(std::pair<std::string, std::string> p: attributes) {
        unsigned int data_type = -1;
        if(p.second == "char") data_type = CHAR;
        else if(p.second == "string") data_type = STRING;
        else if(p.second == "int") data_type = INT;
        else if(p.second == "long long") data_type = LONG_LONG;
        else if(p.second == "double") data_type = DOUBLE;
        else if(p.second == "boolean") data_type = BOOLEAN;
        
        if(data_type == -1 && temp.find(p.first) != temp.end()) {
            std::cout << "not a create query" << std::endl;
            delete create_query;
            return NULL;
        }
        create_query->attributes.push_back({ p.first, data_type });
        temp.insert(p.first);
    }
    temp.clear();

    for(std::string str: primary_keys) {
        unsigned int attr_index = -1;
        for (unsigned int i = 0; i < attributes.size(); i++) {
            if(attributes[i].first == str) {
                attr_index = i;
                break;
            }
        }
        if(attr_index == -1 && create_query->primary_key.find(attr_index) != create_query->primary_key.end()) {
            std::cout << "not a create query" << std::endl;
            delete create_query;
            return NULL;
        }
        create_query->primary_key.insert(attr_index);
    }

    return create_query;
}

Query* QueryParser::get_drop_query(const std::string &query) {
    unsigned int index = 0;
    std::string keyword = get_next(query, index);
    if (keyword != "drop") {
        std::cout << "Cannot find drop" << std::endl;
        return NULL;
    }
    index++;
    keyword = get_next(query, index);
    if (keyword != "database") {
        std::cout << "Cannot find database" << std::endl;
        return NULL;
    }
    index++;
    keyword = get_next(query, index);
    if (keyword == "" || keyword.empty()) {
        std::cout << "Cannot find database name" << std::endl;
        return NULL;
    }
    DropQuery *drop_query = new DropQuery(keyword);
    return drop_query;
}

Query* QueryParser::get_query(const std::string &query) {
    unsigned int type = QueryParser::get_query_type(query);
    Query* parsed_query;
    switch(type) {
        case CREATE_QUERY:
            parsed_query = QueryParser::get_create_query(query);
            parsed_query->type = CREATE_QUERY;
            break;
        case DROP_QUERY:
            parsed_query = QueryParser::get_drop_query(query);
            parsed_query->type = DROP_QUERY;
            break;
        case INSERT_QUERY:
            parsed_query = QueryParser::get_insert_query(query);
            parsed_query->type = INSERT_QUERY;
            break;
        default:
            std::cout << "Unknown query" << std::endl;
            break;
    }
    return parsed_query;
}

Query* QueryParser::get_insert_query(const std::string &query) {
    InsertQuery *insert_query = new InsertQuery();
    unsigned int index = 0;
    std::string keyword = get_next(query, index);
    if (keyword != "insert") {
        std::cout << "\"insert\" not found" << std::endl;
        return NULL;
    }
    index++;
    keyword = get_next(query, index);
    if (keyword != "into") {
        std::cout << "\"into\" not found" << std::endl;
        return NULL;
    }
    index++;
    keyword = get_next(query, index);
    if (keyword == "" || keyword.empty()) {
        std::cout << "database name cannot be empty" << std::endl;
        return NULL;
    }
    insert_query->db_name = keyword;
    index++;
    std::vector<std::string> values = extract_keys(query, index);
    if (values.empty()) {
        std::cout << "values cannot be empty" << std::endl;
        return NULL;
    }
    insert_query->values = values;
    return insert_query;
}