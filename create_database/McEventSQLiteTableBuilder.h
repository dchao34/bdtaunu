#ifndef __MCEVENTSQLITETABLEBUILDER_H__
#define __MCEVENTSQLITETABLEBUILDER_H__

#include <string>
#include <map>
#include <utility>

#include <sqlite3.h>

#include "EventSQLiteTableBuilder.h"

class McEventSQLiteTableBuilder : public EventSQLiteTableBuilder {

  private:
    int mc_evttype;
    int sp_mode;
    double event_weight;

    std::map<std::string, std::pair<std::string, std::string> > sample_assignment_map;
    void BuildSampleAssignmentMap(const char *assignment_fname);

    void BindColumns();

  public:
    McEventSQLiteTableBuilder() {};
    McEventSQLiteTableBuilder(sqlite3 *db, const char *assignment_fname);
    virtual ~McEventSQLiteTableBuilder();

    void set_mc_evttype(int evttype) { mc_evttype = evttype; }
    void set_sp_mode(int spmode) { sp_mode = spmode; }
    void set_event_weight(double evt_wgt) { event_weight = evt_wgt; }
};

#endif
