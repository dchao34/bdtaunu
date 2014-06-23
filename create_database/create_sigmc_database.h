#include <sqlite3.h>

int make_mlsample_assignment_table(
    sqlite3 *db, 
    const char *ml_assignment_fname
    );

int create_sigmc_candidate_table(sqlite3 *db); 

int insert_sigmc_table(sqlite3 *db, 
    const char *root_fname, 
    const char *root_trname);
