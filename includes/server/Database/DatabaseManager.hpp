/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Database Manager
*/

#ifndef DATABASE_MANAGER_HPP
#define DATABASE_MANAGER_HPP

#include <iostream>
#include <vector>
#include <tuple>

#include <stdio.h>
#include <sqlite3.h>

#include "DatabaseManagerError.hpp"

#define INTEGER_IN_TABLE "int"
#define TEXT_IN_TABLE "text"

namespace Babel::Server::Db {

    class DatabaseManager
    {
        public :
            DatabaseManager(const std::string &name);
            ~DatabaseManager();

            void createTable(const std::string &tableName,
            const std::string &tableKeyName,
            std::vector<std::pair<const std::string /*NAME*/, const std::string /*TYPE*/>> &tableDescription) const;
            void deleteTable(const std::string &tableName) const;

            bool checkIfTableExist(const std::string &table_name) const;

            std::size_t getTableSize(const std::string &tableName) const;

            void printTable(const std::string &tableName) const;

            void addEntry(const std::string &tableName,
            std::vector<std::tuple<const std::string /*TYPE*/,
                                const std::string /*VALUE*/>> &entryDescription) const;
            void deleteEntry(const std::string &tableName,
            std::vector<std::tuple<const std::string /*NAME*/,
                                const std::string /*TYPE*/,
                                const std::string /*VALUE*/>> &entryDescription) const;

            bool checkIfEntryExist(const std::string &tableName,
            std::vector<std::tuple<const std::string /*NAME*/,
                                   const std::string /*TYPE*/,
                                   const std::string /*VALUE*/>> &entryDescription) const;

            std::vector<std::vector<std::string>> getEntry(const std::string &tableName,
            std::vector<std::tuple<const std::string /*NAME*/,
                                const std::string /*TYPE*/,
                                const std::string /*VALUE*/>> &entryDescription) const;

            std::size_t getNextFreePrimaryKey(const std::string &tableName, const std::string &tableKeyName) const;

        protected :
        private :
            sqlite3 *_db;
            const std::string _name;
    };
}

#endif /* !DATABASE_MANAGER_HPP */
