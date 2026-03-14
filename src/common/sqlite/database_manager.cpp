#include "common/sqlite/database_manager.h"

bool DatabaseManager::init(const std::string& dbFile)
{   
    if(m_db != nullptr) return true;

    if(sqlite3_open(dbFile.c_str(), &m_db) != SQLITE_OK)
        return false;

    return true;
}

sqlite3* DatabaseManager::getDB()
{
    return m_db;
}


DatabaseManager:: ~DatabaseManager()
{
    if(m_db)
        sqlite3_close(m_db);
}