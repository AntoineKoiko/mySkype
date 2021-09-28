/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Database
*/

#include "Database.hpp"

Database::Database(const std::string name) : _name(name)
{
    int rc = 0;
    char *errMsg = NULL;

    rc = sqlite3_open(name.data(), &_db);
    if (rc) {
        sqlite3_close(_db);
        sprintf(errMsg, "Can't open the database : %s\n", sqlite3_errmsg(_db));
        throw DatabaseError(errMsg);
    }
}

Database::~Database()
{
    sqlite3_close(_db);
}

void Database::createTable(const std::string tableName,
const std::string tableKeyName,
std::vector<std::pair<const std::string /*NAME*/, const std::string /*TYPE*/>> tableDescription) const
{
    sqlite3_stmt *stmt;
    std::string sql = "CREATE TABLE \"";
    int rc = 0;

    sql += tableName + "\" (";
    sql += "\"" + tableKeyName + "\" INTEGER PRIMARY KEY NOT NULL";
    for (size_t i = 0; i < tableDescription.size(); i++) {
        if (tableDescription[i].second.compare(INTEGER_IN_TABLE) == 0)
            sql += ", \"" + tableDescription[i].first + "\" INTEGER NOT NULL";
        if (tableDescription[i].second.compare(TEXT_IN_TABLE) == 0)
            sql += ", \"" + tableDescription[i].first + "\" TEXT NOT NULL";
    }
    sql += ")";
    rc = sqlite3_prepare_v2(_db, sql.data(), -1, &stmt, NULL);
    if (rc != SQLITE_OK)
        throw DatabaseError("Create table - Prepare fail !");
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw DatabaseError(sqlite3_errmsg(_db));
    }
    sqlite3_finalize(stmt);
}

void Database::deleteTable(const std::string tableName) const
{
    sqlite3_stmt *stmt;
    std::string sql = "DROP TABLE " + tableName;
    int rc = 0;

    rc = sqlite3_prepare_v2(_db, sql.data(), -1, &stmt, NULL);
    if (rc != SQLITE_OK)
        throw DatabaseError("Delete table - Prepare fail !");
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw DatabaseError(sqlite3_errmsg(_db));
    }
    sqlite3_finalize(stmt);
}

static int callback(void *notUsed, int argc, char **argv, char **colName)
{
    (void) notUsed;
    for(size_t i = 0; i < (size_t) argc; i++)
        std::cout << colName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    std::cout << std::endl;
    return 0;
}

void Database::printTable(const std::string tableName) const
{
    int rc = 0;
    char *sqlErrMsg = NULL;
    std::string sql = "SELECT * FROM " + tableName;
    std::string errMsg = "Print Table - ";

    rc = sqlite3_exec(_db, sql.data(), callback, 0, &sqlErrMsg);

    if(rc != SQLITE_OK) {
      errMsg += sqlErrMsg;
      sqlite3_free(sqlErrMsg);
      throw DatabaseError(errMsg);
    }
}

bool Database::checkIfEntryExist(const std::string tableName,
std::vector<std::tuple<const std::string /*NAME*/,
                       const std::string /*TYPE*/,
                       const std::string /*VALUE*/>> entryDescription) const
{
    sqlite3_stmt *stmt;
    std::string sql = "SELECT * FROM " + tableName + " WHERE ";
    int rc = 0;

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
        throw DatabaseError("Check if entry exist - Prepare fail !");
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW && rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw DatabaseError(sqlite3_errmsg(_db));
    }
    if (rc == SQLITE_DONE) {
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}

void Database::addEntryIntoTable(const std::string tableName,
std::vector<std::tuple<const std::string /*TYPE*/,
                       const std::string /*VALUE*/>> entryDescription) const
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
        throw DatabaseError("Add entry - Prepare fail !");
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw DatabaseError(sqlite3_errmsg(_db));
    }
    sqlite3_finalize(stmt);
}

void Database::deleteEntryIntoTable(const std::string tableName,
std::vector<std::tuple<const std::string /*NAME*/,
                       const std::string /*TYPE*/,
                       const std::string /*VALUE*/>> entryDescription) const
{
    sqlite3_stmt *stmt;
    std::string sql = "DELETE FROM " + tableName + " WHERE ";
    int rc = 0;

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
        throw DatabaseError("Delete entry - Prepare fail !");
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw DatabaseError(sqlite3_errmsg(_db));
    }
    sqlite3_finalize(stmt);
}