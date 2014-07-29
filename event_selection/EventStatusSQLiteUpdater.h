#ifndef __EVENTSTATUSSQLITEUPDATER_H__
#define __EVENTSTATUSSQLITEUPDATER_H__

#include <vector>
#include <string>

#include <sqlite3.h>

#include "SQLiteUpdater.h"

class EventStatusSQLiteUpdater : public SQLiteUpdater{

  protected: 
    std::string table_name;

    int failed_event_precuts;
    double signal_score;
    double continuum_score;
    double sig_sl_score;
    double sig_had_score;
    double sig_cont_score;
    double sig_all_score;
    std::string babar_event_id;

    std::vector<std::string> target_colnames;
    std::vector<std::string> constraint_colnames;

    std::string ConstructUpdateStatement() const;
    void BindColumns();

  public:
    EventStatusSQLiteUpdater();
    EventStatusSQLiteUpdater(const char *dbname);
    ~EventStatusSQLiteUpdater() {};

    void set_failed_event_precuts(int value) { failed_event_precuts = value; }
    void set_signal_score(double value) { signal_score = value; }
    void set_continuum_score(double value) { continuum_score = value; }
    void set_sig_sl_score(double value) { sig_sl_score = value; }
    void set_sig_had_score(double value) { sig_had_score = value; }
    void set_sig_cont_score(double value) { sig_cont_score = value; }
    void set_sig_all_score(double value) { sig_all_score = value; }
    void set_babar_event_id(std::string value) { babar_event_id = value; }

};

#endif
