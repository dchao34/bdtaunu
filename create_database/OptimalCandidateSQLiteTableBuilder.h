#ifndef __OPTIMALCANDIDATESQLITETABLEBUILDER_H__
#define __OPTIMALCANDIDATESQLITETABLEBUILDER_H__

#include <string>
#include <vector>
#include <map>
#include <utility>

#include <sqlite3.h>

#include "SQLiteTableBuilder.h"

class OptimalCandidateSQLiteTableBuilder : public SQLiteTableBuilder {

  protected:
    std::string table_name;
    std::vector<std::pair<std::string, std::string> > id_colnames;
    std::vector<std::pair<std::string, std::string> > algo_colnames;

    std::string babar_event_id;
    int svm_optcand_idx;
    int min_eextra_optcand_idx;

    std::string ConstructCreateStatement() const;
    std::string ConstructInsertStatement() const;

    virtual void BindColumns();

  public:
    OptimalCandidateSQLiteTableBuilder() {};
    OptimalCandidateSQLiteTableBuilder(sqlite3 *db);
    virtual ~OptimalCandidateSQLiteTableBuilder();

    void set_babar_event_id(std::string id) { babar_event_id = id; }
    void set_svm_optcand_idx(int value) { svm_optcand_idx = value; }
    void set_min_eextra_optcand_idx(int value) { min_eextra_optcand_idx = value; }

};

#endif
