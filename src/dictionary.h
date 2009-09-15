#include <db.h>
#include <glib.h>
#include <stdlib.h>

#define DICTDB             "dictdata.db"

static DB *dictionary;
static DBC *cursor;

int dictionary_open (void);
int dictionary_close (void); 
const char * dictionary_search_exact (const char *);
const char * dictionary_search (const char *);
const char * dictionary_get_current_word (void);
const char * dictionary_get_next_word (void);
const char * dictionary_get_first_matched_word (void);
 
