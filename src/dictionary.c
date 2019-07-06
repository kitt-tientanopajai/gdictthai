#include <stdio.h>
#include <string.h>
#include <glib.h>

#include <config.h>
#include "dictionary.h"

static char *current_keyword = NULL;
static char *first_matched_word = NULL;

/* dictionary_open
 * args: none
 * return: 0 if success, otherwise non-zero error of DB3 */
int 
dictionary_open (void) 
{
	int result = sqlite3_open_v2 (PACKAGE_DATA_DIR "/" PACKAGE "/dictionary/" DICTDB, &db, SQLITE_OPEN_READONLY, NULL);
	if (result != SQLITE_OK) 
		sqlite3_close (db);

	return result;
}

/* dictionary_close
 * args: none
 * return: 0 if success, otherwise -1 */

int
dictionary_close (void) 
{
	sqlite3_finalize (stmt);

	if (db != NULL) 
	{
		sqlite3_close (db);
	} else {
		return -1;
	}
}
/* dictionary_search_exact
 * args: keyword to search exact match
 * return: meaning string or NULL 
 * note: this function returns a pointer to newly-allocated memory, 
 *       it should later be freed */

const char *
dictionary_search_exact (const char *keyword)
{
	if (keyword == NULL || strlen (keyword) == 0)
		return NULL;
	
	char *sql;
	const char *tail;
	char *meaning = NULL;

	sql = sqlite3_mprintf ("select keyword,meaning from dictionary where keyword = '%q';", keyword);

	int result = sqlite3_prepare_v2 (db, sql, strlen (sql), &stmt, &tail);

	if (result != SQLITE_OK) 
	{
		fprintf (stderr, "SQL error: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize (stmt);
		sqlite3_free (sql);
		return NULL;
	}

	result = sqlite3_step (stmt);
	if (result == SQLITE_ROW)
	{
		meaning = strdup (sqlite3_column_text (stmt, 1));
		free (first_matched_word);
		first_matched_word = strdup (keyword);
		free (current_keyword);
		current_keyword = strdup (keyword);
	}

	sqlite3_free (sql);

	return meaning; 
}

/* dictionary_search
 * args: keyword to search
 * return: meaning or NULL 
 * note: this function returns a pointer to newly-allocated memory, 
 *       it should later be freed */

const char *
dictionary_search (const char *keyword)
{
	if (keyword == NULL || strlen (keyword) == 0)
		return NULL;
	
	char *sql;
	const char *tail;
	char *meaning = NULL;

	sql = sqlite3_mprintf ("select keyword,meaning from dictionary where keyword like '%q%%';", keyword);

	int result = sqlite3_prepare_v2 (db, sql, strlen (sql), &stmt, &tail);

	if (result != SQLITE_OK) 
	{
		fprintf (stderr, "SQL error: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize (stmt);
		sqlite3_free (sql);
		return NULL;
	}

	result = sqlite3_step (stmt);
	if (result == SQLITE_ROW)
	{
		meaning = strdup (sqlite3_column_text (stmt, 1));
		free (first_matched_word);
		first_matched_word = strdup (sqlite3_column_text (stmt, 0));
		free (current_keyword);
		current_keyword = strdup (sqlite3_column_text (stmt, 0));
	}

	sqlite3_free (sql);

	return meaning;
}

/* dictionary_get_current_word
 * args: none
 * return: current keyword */

const char *
dictionary_get_current_word () 
{
	if (current_keyword == NULL || strlen (current_keyword) == 0)
		return NULL;

	return current_keyword;
}

/* dictionary_get_next_word
 * arg: keyword to search
 * return: next keyword 
 * note: this function returns a pointer to newly-allocated memory, 
 *       it should later be freed */

const char *
dictionary_get_next_word ()
{
	if (current_keyword == NULL || strlen (current_keyword) == 0)
		return NULL;

	int result = sqlite3_step (stmt);
	
	if (result != SQLITE_ROW) 
		return NULL;	

	int len = strlen (current_keyword);
	if (strncmp (current_keyword, sqlite3_column_text (stmt, 0), len))
		return NULL;
	else
		return sqlite3_column_text (stmt, 0);
}

/* dictionary_get_first_matched_word
 * args: none
 * return: first matched word */

const char *
dictionary_get_first_matched_word ()
{
	if (first_matched_word == NULL || strlen (first_matched_word) == 0)
		return NULL;

	return first_matched_word;
}
