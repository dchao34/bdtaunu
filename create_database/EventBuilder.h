#ifndef __EVENTBUILDER_H__
#define __EVENTBUILDER_H__

#include <string>

#include <sqlite3.h>

class EventBuilder {
  private:
    static const std::string creation_statement;
    static const std::string insertion_statement;

    static std::string define_creation_statement();
    static std::string define_insertion_statement();

  private:
    sqlite3 *db;
    sqlite3_stmt *create_stmt;
    sqlite3_stmt *insert_stmt;
    int db_status;

    std::string babar_event_id;
    int run;
    int nTrk;
    double R2;
    int nY;

    void CreateTable();

  public:
    EventBuilder(sqlite3* db);
    ~EventBuilder();

    void InsertEntry();

    void set_babar_event_id(std::string id) { babar_event_id = id; }
    void set_run(int run_number) { run = run_number; }
    void set_nTrk(int ntrk) { nTrk = ntrk; }
    void set_R2(double r2) { R2 = r2; }
    void set_nY(int nUps) { nY = nUps; }
};

#endif
