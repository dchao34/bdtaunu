#include <sqlite3.h>

int make_event_weight_table(
    sqlite3 *db, 
    const char *event_weights_fname 
    );

int make_machine_learning_sample_assignment_table(
    sqlite3 *db, 
    const char *ml_assignment_fname
    );

int create_event_table(sqlite3 *db); 
int create_monte_carlo_table(sqlite3 *db);
int create_candidate_table(sqlite3 *db); 

int insert_table(sqlite3 *db, 
    const char *root_fname, 
    const char *root_trname, 
    int run);
