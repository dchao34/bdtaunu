#ifndef __MCEVENTSQLITETABLEBUILDER_H__
#define __MCEVENTSQLITETABLEBUILDER_H__

#include <string>
#include <map>
#include <utility>

#include <sqlite3.h>

#include "EventSQLiteTableBuilder.h"

class McEventSQLiteTableBuilder : public EventSQLiteTableBuilder {

  private:
    int b1mctype, b2mctype;
    int sp_mode;
    double event_weight;

    std::map<std::string, std::pair<std::string, std::string> > sample_assignment_map;
    std::map<std::string, int> truthB_idx_map;
    void BuildCachedDataMap(const char *assignment_fname);

    void BindColumns();

    int DetermineMcEventTypeDefA() const;
    int DetermineMcEventTypeDefB() const;

  public:
    McEventSQLiteTableBuilder() {};
    McEventSQLiteTableBuilder(sqlite3 *db, const char *assignment_fname);
    virtual ~McEventSQLiteTableBuilder();

    void set_b1mctype(int value) { b1mctype = value; }
    void set_b2mctype(int value) { b2mctype = value; }
    void set_sp_mode(int spmode) { sp_mode = spmode; }
    void set_event_weight(double evt_wgt) { event_weight = evt_wgt; }
};

#endif
