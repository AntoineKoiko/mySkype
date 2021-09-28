/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Databse
*/

#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <iostream>
#include <vector>
#include <tuple>

#include <stdio.h>
#include <sqlite3.h>

#include "DatabaseError.hpp"

#define INTEGER_IN_TABLE "int"
#define TEXT_IN_TABLE "text"

class Database
{
    public :
        Database(const std::string name);
        ~Database();

        void createTable(const std::string tableName,
        const std::string tableKeyName,
        std::vector<std::pair<const std::string /*NAME*/, const std::string /*TYPE*/>> tableDescription) const;
        void deleteTable(const std::string tableName) const;

        void printTable(const std::string tableName) const;

        bool checkIfEntryExist(const std::string tableName,
        std::vector<std::tuple<const std::string /*NAME*/,
                               const std::string /*TYPE*/,
                               const std::string /*VALUE*/>> entryDescription) const;

        void addEntryIntoTable(const std::string tableName,
        std::vector<std::tuple<const std::string /*TYPE*/,
                               const std::string /*VALUE*/>> entryDescription) const;
        void deleteEntryIntoTable(const std::string tableName,
        std::vector<std::tuple<const std::string /*NAME*/,
                               const std::string /*TYPE*/,
                               const std::string /*VALUE*/>> entryDescription) const;

    protected :

    private :
        sqlite3 *_db;
        const std::string _name;
};

/*
NAMESPACE
RECUP UNE ENTREE
RECUP LES TYPES D'UNE TABLE ?
*/

#endif /* !DATABASE_HPP */
