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
    std::vector<std::tuple<const std::string, const std::string>> entry3
    = {{"int", "3"}, {"int", "12"}, {"text", "yo"}};
    std::vector<std::tuple<const std::string, const std::string, const std::string>> entry2_1
    = {{"string", "text", "hey"}};
    std::vector<std::tuple<const std::string, const std::string, const std::string>> searched1
    = {{"value", "int", "12"}};
    std::vector<std::tuple<const std::string, const std::string, const std::string>> searched2
    = {{"string", "text", "yo"}};
    std::vector<std::vector<std::string>> returnEntries = {{}};

    if (argc != 2 && argc != 3) {
        std::cout << "Wrong number of arguments -- ./??? databaseName" << std::endl;
        return 84;
    }
    
    try {
        Babel::Database database(argv[1]);

        if (argc == 2)
            database.createTable("tableTest0", "id", tableDescription);
        database.addEntry("tableTest0", entry1);
        database.addEntry("tableTest0", entry2);
        database.addEntry("tableTest0", entry3);
        std::cout << "Does entry 2 exist ? " << (database.checkIfEntryExist("tableTest0", entry2_1) ? "TRUE" : "FALSE") << std::endl;
        database.deleteEntry("tableTest0", entry2_1);
        std::cout << "Does entry 2 exist ? " << (database.checkIfEntryExist("tableTest0", entry2_1) ? "TRUE" : "FALSE") << std::endl;
        database.printTable("tableTest0");
        returnEntries = database.getEntry("tableTest0", searched1);
        std::cout << "SEARCHED 1 : " << std::endl;
        for (auto &i : returnEntries) {
            for (auto &j : i)
                std::cout << "Value = " << j << std::endl;                
            std::cout << std::endl;
        }
        std::cout << "END SEARCHED 1" << std::endl;
        returnEntries = database.getEntry("tableTest0", searched2);
        std::cout << "SEARCHED 2 :" << std::endl;
        for (auto &i : returnEntries) {
            for (auto &j : i)
                std::cout << "Value = " << j << std::endl;                
            std::cout << std::endl;
        }
        std::cout << "END SEARCHED 2" << std::endl;
        std::cout << "Does table 1 exist ? " << (database.checkIfTableExist("tableTest0") ? "TRUE" : "FALSE") << std::endl;
        std::cout << "Does table 0 exist ? " << (database.checkIfTableExist("tableTest1") ? "TRUE" : "FALSE") << std::endl;
        database.deleteTable("tableTest0");
    } catch (DatabaseError &e) {
        std::cout << "DATABASE ERROR -> " << e.what() << std::endl;
    }
    return 0;
}
