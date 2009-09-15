#include <db.h>
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
	int result = db_create (&dictionary, NULL, 0);
	if (result != 0)
		return result;

	/* open for read only */
	u_int32_t flags = DB_RDONLY;
	result = dictionary->open (dictionary, NULL, PACKAGE_DATA_DIR "/" PACKAGE "/dictionary/" DICTDB, NULL, DB_BTREE, flags, 0);
	
	/* open cursor */
	dictionary->cursor (dictionary, NULL, &cursor, 0);
	return result;
}

/* dictionary_close
 * args: none
 * return: 0 if success, otherwise -1 */

int
dictionary_close (void) 
{
	if (dictionary != NULL) 
	{
		if (cursor != NULL)
		{
			cursor->c_close (cursor);
		}
		dictionary->close(dictionary, 0);
	} else {
		return -1;
	}
}
/* dictionary_search_exact
 * args: keyword to search exact match
 * return: meaning or NULL 
 * note: this function returns a pointer to newly-allocated memory, 
 *       it should later be freed */

const char *
dictionary_search_exact (const char *keyword)
{
	if (keyword == NULL || strlen (keyword) == 0)
	{
		free ((void *) current_keyword);
		current_keyword = NULL;
		return NULL;
	}
	
	DBT key, data;
	int result;

	memset (&key, 0, sizeof (DBT));
	memset (&data, 0, sizeof (DBT));
	key.data = (char *) keyword;
	key.size = strlen (key.data) + 1;
	
	result = cursor->c_get (cursor, &key, &data, DB_SET);
	if (result == DB_NOTFOUND)
		return NULL;
	else
		return data.data;
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
	{
		free (current_keyword);
		current_keyword = NULL;
		return NULL;
	}

	DBT key, data;
	int result;
	char *meaning;

	memset (&key, 0, sizeof (DBT));
	memset (&data, 0, sizeof (DBT));
	key.data = (char *) keyword;
	key.size = strlen (key.data) + 1;
	
	result = cursor->c_get (cursor, &key, &data, DB_SET_RANGE);
	if (strncmp (keyword, key.data, strlen (keyword)))
	{
		meaning = NULL;
	} else {
		meaning = strdup (data.data);
		free (first_matched_word);
		first_matched_word = strdup (key.data);
	}

	result = cursor->c_get (cursor, &key, &data, DB_PREV);
	free (current_keyword);
	current_keyword = strdup (keyword);
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
	
	DBT key, data;
	int result;
	char *keyword;

	memset (&key, 0, sizeof (DBT));
	memset (&data, 0, sizeof (DBT));
	result = cursor->c_get (cursor, &key, &data, DB_NEXT);
	if (result == DB_NOTFOUND) {
		return NULL;
	} else {
		int len = strlen (current_keyword);
		if (strncmp (current_keyword, key.data, len))
			return NULL;
		else
			return key.data;
	}
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
