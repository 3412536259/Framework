#pragma once
#include <string>
#include "common/sqlite/sqlite3.h"
class DatabaseManager {
public:
    static DatabaseManager& instance();

    bool init(const std::string& dbFile);

    sqlite3* getDB();

private:
    sqlite3* m_db = nullptr;

    DatabaseManager() = default;

   

};