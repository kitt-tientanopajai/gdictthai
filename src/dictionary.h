#include <glib.h>
#include <stdlib.h>
#include <sqlite3.h>

#define DICTDB             "en-th.sq3"

static sqlite3 *db;
static sqlite3_stmt *stmt;

int dictionary_open (void);
int dictionary_close (void); 
const char * dictionary_search_exact (const char *);
const char * dictionary_search (const char *);
const char * dictionary_get_current_word (void);
const char * dictionary_get_next_word (void);
const char * dictionary_get_first_matched_word (void);
