/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** DatabaseManager
*/

#include "DatabaseManager.hpp"

using namespace Babel;

DatabaseManager::DatabaseManager(const std::string &name) : _name(name)
{
    int rc = 0;
    char *errMsg = NULL;

    rc = sqlite3_open(name.data(), &_db);
    if (rc) {
        sqlite3_close(_db);
        sprintf(errMsg, "Can't open the database : %s\n", sqlite3_errmsg(_db));
        throw DatabaseManagerError(errMsg);
    }
}

DatabaseManager::~DatabaseManager()
{
    sqlite3_close(_db);
}

void DatabaseManager::createTable(const std::string &tableName,
const std::string &tableKeyName,
std::vector<std::pair<const std::string /*NAME*/, const std::string /*TYPE*/>> &tableDescription) const
{
    sqlite3_stmt *stmt;
    std::string sql = "CREATE TABLE \"";
    int rc = 0;

    sql += tableName + "\" (";
    sql += "\"" + tableKeyName + "\" INTEGER PRIMARY KEY NOT NULL";
    for (auto &element : tableDescription) {
        if (element.second.compare(INTEGER_IN_TABLE) == 0)
            sql += ", \"" + element.first + "\" INTEGER NOT NULL";
        if (element.second.compare(TEXT_IN_TABLE) == 0)
            sql += ", \"" + element.first + "\" TEXT NOT NULL";
    }
    sql += ")";
    rc = sqlite3_prepare_v2(_db, sql.data(), -1, &stmt, NULL);
    if (rc != SQLITE_OK)
        throw DatabaseManagerError("Create table - Prepare fail !");
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw DatabaseManagerError(sqlite3_errmsg(_db));
    }
    sqlite3_finalize(stmt);
}

void DatabaseManager::deleteTable(const std::string &tableName) const
{
    sqlite3_stmt *stmt;
    std::string sql = "DROP TABLE " + tableName;
    int rc = 0;

    rc = sqlite3_prepare_v2(_db, sql.data(), -1, &stmt, NULL);
    if (rc != SQLITE_OK)
        throw DatabaseManagerError("Delete table - Prepare fail !");
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw DatabaseManagerError(sqlite3_errmsg(_db));
    }
    sqlite3_finalize(stmt);
}

size_t DatabaseManager::getTableSize(const std::string &tableName) const
{
    sqlite3_stmt *stmt;
    std::string sql = "SELECT * FROM " + tableName;
    int rc = 0;
    size_t tableSize = 0;

    rc = sqlite3_prepare_v2(_db, sql.data(), -1, &stmt, NULL);
    if (rc != SQLITE_OK)
        throw DatabaseManagerError("Get table size - Prepare fail !");
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW && rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw DatabaseManagerError(sqlite3_errmsg(_db));
    }
    while (rc != SQLITE_DONE) {
        tableSize += 1;
        rc = sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);
    return tableSize;
}

static int callback(void *notUsed, int argc, char **argv, char **colName)
{
    (void) notUsed;
    for(size_t i = 0; i < (size_t) argc; i++)
        std::cout << colName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    std::cout << std::endl;
    return 0;
}

void DatabaseManager::printTable(const std::string &tableName) const
{
    int rc = 0;
    char *sqlErrMsg = NULL;
    std::string sql = "SELECT * FROM " + tableName;
    std::string errMsg = "Print Table - ";

    rc = sqlite3_exec(_db, sql.data(), callback, 0, &sqlErrMsg);

    if(rc != SQLITE_OK) {
      errMsg += sqlErrMsg;
      sqlite3_free(sqlErrMsg);
      throw DatabaseManagerError(errMsg);
    }
}

bool DatabaseManager::checkIfEntryExist(const std::string &tableName,
std::vector<std::tuple<const std::string /*NAME*/,
                       const std::string /*TYPE*/,
                       const std::string /*VALUE*/>> &entryDescription) const
{
    sqlite3_stmt *stmt;
    std::string sql = "SELECT * FROM " + tableName;
    int rc = 0;

    if (entryDescription.size() != 0)
        sql += " WHERE ";
    for (size_t i = 0; i < entryDescription.size(); i++) {
        if (i != 0)
            sql += " AND ";
        sql += std::get<0>(entryDescription[i]) + " = ";
        if (std::get<1>(entryDescription[i]).compare(INTEGER_IN_TABLE) == 0)
            sql += std::get<2>(entryDescription[i]);
        if (std::get<1>(entryDescription[i]).compare(TEXT_IN_TABLE) == 0)
            sql += "\'" + std::get<2>(entryDescription[i]) + "\'";
    }
    rc = sqlite3_prepare_v2(_db, sql.data(), -1, &stmt, NULL);
    if (rc != SQLITE_OK)
        throw DatabaseManagerError("Check if entry exist - Prepare fail !");
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW && rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw DatabaseManagerError(sqlite3_errmsg(_db));
    }
    if (rc == SQLITE_DONE) {
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}

void DatabaseManager::addEntry(const std::string &tableName,
std::vector<std::tuple<const std::string /*TYPE*/,
                       const std::string /*VALUE*/>> &entryDescription) const
{
    sqlite3_stmt *stmt;
    std::string sql = "INSERT INTO " + tableName + " VALUES(";
    int rc = 0;

    for (size_t i = 0; i < entryDescription.size(); i++) {
        if (i != 0)
            sql += ", ";
        if (std::get<0>(entryDescription[i]).compare(INTEGER_IN_TABLE) == 0)
            sql += std::get<1>(entryDescription[i]);
        if (std::get<0>(entryDescription[i]).compare(TEXT_IN_TABLE) == 0)
            sql += "\'" + std::get<1>(entryDescription[i]) + "\'";
    }
    sql += ")";
    std::cerr << "ADD ENTRY SQL = " << sql << std::endl;
    rc = sqlite3_prepare_v2(_db, sql.data(), -1, &stmt, NULL);
    if (rc != SQLITE_OK)
        throw DatabaseManagerError("Add entry - Prepare fail !");
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw DatabaseManagerError(sqlite3_errmsg(_db));
    }
    sqlite3_finalize(stmt);
}

void DatabaseManager::deleteEntry(const std::string &tableName,
std::vector<std::tuple<const std::string /*NAME*/,
                       const std::string /*TYPE*/,
                       const std::string /*VALUE*/>> &entryDescription) const
{
    sqlite3_stmt *stmt;
    std::string sql = "DELETE FROM " + tableName;
    int rc = 0;

    if (entryDescription.size() != 0)
        sql += " WHERE ";
    for (size_t i = 0; i < entryDescription.size(); i++) {
        if (i != 0)
            sql += " AND ";
        sql += std::get<0>(entryDescription[i]) + " = ";
        if (std::get<1>(entryDescription[i]).compare(INTEGER_IN_TABLE) == 0)
            sql += std::get<2>(entryDescription[i]);
        if (std::get<1>(entryDescription[i]).compare(TEXT_IN_TABLE) == 0)
            sql += "\'" + std::get<2>(entryDescription[i]) + "\'";
    }
    rc = sqlite3_prepare_v2(_db, sql.data(), -1, &stmt, NULL);
    if (rc != SQLITE_OK)
        throw DatabaseManagerError("Delete entry - Prepare fail !");
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw DatabaseManagerError(sqlite3_errmsg(_db));
    }
    sqlite3_finalize(stmt);
}

std::vector<std::vector<std::string>> DatabaseManager::getEntry(const std::string &tableName,
std::vector<std::tuple<const std::string /*NAME*/,
                       const std::string /*TYPE*/,
                       const std::string /*VALUE*/>> &entryDescription) const
{
    sqlite3_stmt *stmt;
    std::string sql = "SELECT * FROM " + tableName;
    int rc = 0;
    std::vector<std::vector<std::string>> returnEntries = {{}};
    std::vector<std::string> returnEntry = {};
    std::string element = "";
    size_t entrySize = 0;

    if (entryDescription.size() != 0)
        sql += " WHERE ";
    for (size_t i = 0; i < entryDescription.size(); i++) {
        if (i != 0)
            sql += " AND ";
        sql += std::get<0>(entryDescription[i]) + " = ";
        if (std::get<1>(entryDescription[i]).compare(INTEGER_IN_TABLE) == 0)
            sql += std::get<2>(entryDescription[i]);
        if (std::get<1>(entryDescription[i]).compare(TEXT_IN_TABLE) == 0)
            sql += "\'" + std::get<2>(entryDescription[i]) + "\'";
    }
    rc = sqlite3_prepare_v2(_db, sql.data(), -1, &stmt, NULL);
    if (rc != SQLITE_OK)
        throw DatabaseManagerError("Get entry - Prepare fail !");
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW && rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw DatabaseManagerError(sqlite3_errmsg(_db));
    }
    entrySize = sqlite3_column_count(stmt);
    while (rc != SQLITE_DONE) {
        for (size_t i = 0; i < entrySize; i++) {
            element = reinterpret_cast<char const*>(sqlite3_column_text(stmt, i/* + entrySize * entryNum*/));
            returnEntry.push_back(element);
        }
        returnEntries.push_back(returnEntry);
        rc = sqlite3_step(stmt);
        returnEntry.clear();
    }
    sqlite3_finalize(stmt);
    return returnEntries;
}