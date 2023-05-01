#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "includes/QueryParser.h"
#include "includes/DatabaseManager.h"
using namespace std;

int main(){
    DatabaseManager *db_man = new DatabaseManager();
    while(1){
        string str;
        getline(cin, str);
        string temp = str;
        cout << "input is: " << str << endl;
        // cout << QueryParser::get_query_type(str) << endl;
        // CreateQuery *create_query = (CreateQuery*)QueryParser::get_create_query(str);

        // cout << "Database name: " << create_query->database_name << endl;
        // cout << "Foreign database name: " << create_query->foreign_database_name << endl;
        // cout << "Attributes: " << endl;
        // for (std::pair<std::string, unsigned int> p: create_query->attributes) {
        //     cout << p.first << " " << p.second << endl;
        // }

        // cout << "Primary key: " << endl;
        // for(unsigned int key: create_query->primary_key) {
        //     cout << key << endl;
        // }

        // cout << "Foreign key: " << endl;
        // for(string key: create_query->foreign_key) {
        //     cout << key << endl;
        // }

        db_man->execute_query(temp);
    }
}