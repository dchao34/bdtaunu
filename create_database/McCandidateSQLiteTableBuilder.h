#ifndef __MCCANDIDATESQLITETABLEBUILDER_H__
#define __MCCANDIDATESQLITETABLEBUILDER_H__

#include <string>
#include <map>
#include <utility>

#include <sqlite3.h>

#include "CandidateSQLiteTableBuilder.h"

class McCandidateSQLiteTableBuilder : public CandidateSQLiteTableBuilder {

  private:
    int truth_match;

    void BindColumns();

  public:
    McCandidateSQLiteTableBuilder() {};
    McCandidateSQLiteTableBuilder(sqlite3 *db);
    virtual ~McCandidateSQLiteTableBuilder();

    void set_truth_match(int value) { truth_match = value; }
};

#endif
