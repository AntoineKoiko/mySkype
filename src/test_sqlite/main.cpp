/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Main
*/

#include "Database.hpp"

int main(int argc, char *argv[])
{
    std::vector<std::pair<const std::string, const std::string>> tableDescription
    = {{"value", "int"}, {"string", "text"}};
    std::vector<std::tuple<const std::string, const std::string>> entry1
    = {{"int", "1"}, {"int", "12"}, {"text", "plouf"}};
    std::vector<std::tuple<const std::string, const std::string>> entry2
    = {{"int", "2"}, {"int", "14"}, {"text", "hey"}};
    std::vector<std::tuple<const std::string, const std::string, const std::string>> entry2_1
    = {{"id", "int", "2"}, {"value", "int", "14"}, {"string", "text", "hey"}};

    if (argc != 2 && argc != 3) {
        std::cout << "Wrong number of arguments -- ./??? databaseName" << std::endl;
        return 84;
    }
    
    try {
        Database database(argv[1]);

        if (argc == 2)
            database.createTable("tableTest0", "id", tableDescription);
        database.addEntryIntoTable("tableTest0", entry1);
        database.addEntryIntoTable("tableTest0", entry2);
        std::cout << "Does entry 2 exist ? " << (database.checkIfEntryExist("tableTest0", entry2_1) ? "TRUE" : "FALSE") << std::endl;
        database.deleteEntryIntoTable("tableTest0", entry2_1);
        std::cout << "Does entry 2 exist ? " << (database.checkIfEntryExist("tableTest0", entry2_1) ? "TRUE" : "FALSE") << std::endl;
        database.printTable("tableTest0");
        database.deleteTable("tableTest0");
    } catch (DatabaseError &e) {
        std::cout << "DATABASE ERROR -> " << e.what() << std::endl;
    }
    return 0;
}
