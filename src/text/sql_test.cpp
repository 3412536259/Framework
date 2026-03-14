#include <stdio.h>
#include "common/sqlite/sqlite3.h"

// 回调函数：处理查询结果
static int callback(void *data, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main() {
    sqlite3 *db;
    char *errMsg;
    int rc;

    // 1. 打开/创建数据库
    rc = sqlite3_open("/home/lin/Desktop/Framework/include/common/database/test.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "无法打开数据库: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // 2. 创建表
    const char *createSql = "CREATE TABLE IF NOT EXISTS user (id INT, name TEXT);";
    rc = sqlite3_exec(db, createSql, NULL, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "创建表失败: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    // 3. 插入数据
    const char *insertSql = "INSERT INTO user (id, name) VALUES (1, 'test');";
    rc = sqlite3_exec(db, insertSql, NULL, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "插入数据失败: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    // 4. 查询数据
    const char *selectSql = "SELECT * FROM user;";
    printf("查询结果：\n");
    rc = sqlite3_exec(db, selectSql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "查询失败: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    // 5. 关闭数据库
    sqlite3_close(db);
    return 0;
}