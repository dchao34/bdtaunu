#ifndef __SQLITEACCESSOR_H__
#define __SQLITEACCESSOR_H__

#include <vector>
#include <string>
#include <map>

#include <sqlite3.h>

class SQLiteAccessor {

  protected:
    sqlite3 *db;
    int db_status;
    char *errmsg;

  public:
    SQLiteAccessor();
    SQLiteAccessor(const char *dbname, const char *mode="");
    virtual ~SQLiteAccessor();
};

#endif
