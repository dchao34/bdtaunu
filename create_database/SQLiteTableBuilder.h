#ifndef __SQLITETABLEBUILDER_H__
#define __SQLITETABLEBUILDER_H__

#include <string>
#include <sqlite3.h>

//! Abstract base class for creating/filling SQLite table.
/*! This is the basic template for building SQLite tables. 
 *  Implement a specific realization of this base class for 
 *  every SQLite table that is to be created into the database. 
 *  This class handles the task of accessing SQLite's API 
 *  for the user. 
 *
 *  You must explicitly provide the creation query with the 
 *  method ConstructInsertStatement(), the query for
 *  inserting new records through ConstructInsertStatement(), 
 *  and also how each variables get binded to columns through
 *  function BindColumns(). */
class SQLiteTableBuilder {

  protected:
    sqlite3 *db;
    sqlite3_stmt *create_stmt;
    sqlite3_stmt *insert_stmt;
    int db_status;

    //! SQL table creation statement. This determines the schema. 
    virtual std::string ConstructCreateStatement() const = 0;

    //! SQL table insertion statement. 
    virtual std::string ConstructInsertStatement() const = 0;

    //! Controls how variables bind to specific columns.
    virtual void BindColumns() = 0;

  public:
    SQLiteTableBuilder() {};
    SQLiteTableBuilder(sqlite3 *db);
    virtual ~SQLiteTableBuilder();

    //! Create the table.
    void CreateTable();

    //! Construct and insert a record using currently binded column values.
    void InsertTable();

};

#endif
