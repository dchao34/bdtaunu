#ifndef __SQLITEUPDATER_H__
#define __SQLITEUPDATER_H__

#include <string>

#include <sqlite3.h>

#include "SQLiteAccessor.h"

class SQLiteUpdater : public SQLiteAccessor{

  protected: 
    sqlite3_stmt *stmt;
    
    void Initialize();

    virtual std::string ConstructUpdateStatement() const = 0;
    virtual void BindColumns() = 0;

  public:
    SQLiteUpdater();
    SQLiteUpdater(const char *dbname);
    virtual ~SQLiteUpdater();

    virtual void UpdateTable();
};

#endif
