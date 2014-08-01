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
    int b1_taumctype, b2_taumctype;
    double b1_dtau_max_photon_energy, b2_dtau_max_photon_energy;
    int sp_mode;
    double event_weight;

    std::map<std::string, std::pair<std::string, std::string> > sample_assignment_map;
    std::map<std::string, int> truthB_idx_map;
    void BuildCachedDataMap(const char *assignment_fname);

    void BindColumns();

    int DetermineMcEventTypeDefA() const;

  public:
    McEventSQLiteTableBuilder() {};
    McEventSQLiteTableBuilder(sqlite3 *db, const char *assignment_fname);
    virtual ~McEventSQLiteTableBuilder();

    void set_b1mctype(int value) { b1mctype = value; }
    void set_b2mctype(int value) { b2mctype = value; }
    void set_b1_taumctype(int value) { b1_taumctype = value; }
    void set_b2_taumctype(int value) { b2_taumctype = value; }
    void set_b1_dtau_max_photon_energy(double value) { b1_dtau_max_photon_energy = value; }
    void set_b2_dtau_max_photon_energy(double value) { b2_dtau_max_photon_energy = value; }
    void set_sp_mode(int spmode) { sp_mode = spmode; }
    void set_event_weight(double evt_wgt) { event_weight = evt_wgt; }
};

#endif
