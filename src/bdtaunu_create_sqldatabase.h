#include <sqlite3.h>

int create_event_table(
    sqlite3 *db, 
    const char *root_fname, 
    const char *root_trname = "ntp1", 
    int run = 0
    );

int create_event_weight_table(
    sqlite3 *db, 
    const char *event_weights_fname 
    );

int create_machine_learning_sample_assignment_table(
    sqlite3 *db, 
    const char *ml_assignment_fname
    );

int create_candidate_table(sqlite3 *db, 
    const char *root_fname, 
    const char *root_trname);
