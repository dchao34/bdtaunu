#ifndef __EVENTSTATUSSQLITETABLEBUILDER_H__
#define __EVENTSTATUSSQLITETABLEBUILDER_H__

#include <string>
#include <vector>
#include <map>
#include <utility>

#include <sqlite3.h>

#include "SQLiteTableBuilder.h"

class EventStatusSQLiteTableBuilder : public SQLiteTableBuilder {

  protected:
    std::string table_name;
    std::vector<std::pair<std::string, std::string> > id_colnames;
    std::vector<std::pair<std::string, std::string> > code_colnames;
    std::vector<std::pair<std::string, std::string> > score_colnames;

    std::string babar_event_id;
    int failed_event_precuts;
    double signal_score;
    double continuum_score;

    std::string ConstructCreateStatement() const;
    std::string ConstructInsertStatement() const;

    virtual void BindColumns();

  public:
    EventStatusSQLiteTableBuilder() {};
    EventStatusSQLiteTableBuilder(sqlite3 *db);
    virtual ~EventStatusSQLiteTableBuilder();

    void set_babar_event_id(std::string id) { babar_event_id = id; }
    void set_failed_event_precuts(int value) { failed_event_precuts = value; }
    void set_signal_score(double value) { signal_score = value; }
    void set_continuum_score(double value) { continuum_score = value; }

};

#endif
