#ifndef __SQLITEREADER_H__
#define __SQLITEREADER_H__

#include <string>
#include <map>

#include <sqlite3.h>

#include "SQLiteAccessor.h"

class SQLiteReader : public SQLiteAccessor{

  protected: 
    sqlite3_stmt *stmt;
    std::map<std::string, int> column_idx_map;

    void Initialize();

    virtual std::string ConstructSelectStatement() const = 0;
    virtual void BuildColumnIndexMap() = 0;
    virtual void UpdateColumns() = 0;
    virtual void ClearColumns() = 0;

  public:
    SQLiteReader();
    SQLiteReader(const char *dbname);
    virtual ~SQLiteReader();

    int next_record();
};

#endif
