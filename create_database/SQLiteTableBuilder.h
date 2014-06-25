#ifndef __SQLITETABLEBUILDER_H__
#define __SQLITETABLEBUILDER_H__

#include <string>
#include <sqlite3.h>

class SQLiteTableBuilder {

  protected:
    sqlite3 *db;
    sqlite3_stmt *create_stmt;
    sqlite3_stmt *insert_stmt;
    int db_status;

    virtual std::string ConstructCreateStatement() const = 0;
    virtual std::string ConstructInsertStatement() const = 0;

    virtual void BindColumns() = 0;

  public:
    SQLiteTableBuilder() {};
    SQLiteTableBuilder(sqlite3 *db);
    virtual ~SQLiteTableBuilder();

    void CreateTable();
    void InsertTable();

};

#endif
