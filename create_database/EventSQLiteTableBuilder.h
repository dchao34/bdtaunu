#ifndef __EVENTSQLITETABLEBUILDER_H__
#define __EVENTSQLITETABLEBUILDER_H__

#include <string>
#include <vector>
#include <map>
#include <utility>

#include <sqlite3.h>

#include "SQLiteTableBuilder.h"

//! Creates the Event table. 
/*! Schema:
 *  Event(id INTEGER PRIMARY KEY, 
 *        babar_event_id TEXT UNIQUE, 
 *        nY INTEGER, 
 *        run_number INTEGER, 
 *        nTrk INTEGER, 
 *        R2 REAL)
 *  
 *  Use the public set functions to set the column values. These values 
 *  are then inserted into the table when InsertTable() is called. */
class EventSQLiteTableBuilder : public SQLiteTableBuilder {

  protected:
    std::string table_name;
    std::vector<std::pair<std::string, std::string> > id_colnames;
    std::vector<std::pair<std::string, std::string> > meta_colnames;
    std::vector<std::pair<std::string, std::string> > feature_colnames;

    std::string babar_event_id;
    int run;
    int nTrk;
    double R2;
    int nY;

    std::string ConstructCreateStatement() const;
    std::string ConstructInsertStatement() const;

    virtual void BindColumns();

  public:
    EventSQLiteTableBuilder() {};

    //! Create the table and put it in database db. 
    EventSQLiteTableBuilder(sqlite3 *db);
    virtual ~EventSQLiteTableBuilder();

    void set_babar_event_id(std::string id) { babar_event_id = id; }
    void set_run(int run_number) { run = run_number; }
    void set_nTrk(int ntrk) { nTrk = ntrk; }
    void set_R2(double r2) { R2 = r2; }
    void set_nY(int nUps) { nY = nUps; }
};

#endif
