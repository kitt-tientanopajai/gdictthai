#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "dictionary.h"

int
main (int argc, char *argv[]) 
{
	if (argc < 2) 
	{
		printf ("Usage: tdictthai [-n] keyword\n");
		exit (EXIT_FAILURE);
	} else {
		if (dictionary_open ())
		{
			exit (EXIT_FAILURE);
		} else {
			int keyword_index = 1;
			int print_keyword = 1;
			if (strcmp (argv[1], "-n") == 0) {
				keyword_index = 2;
				print_keyword = 0;
			}
			const char *meaning = dictionary_search (argv[keyword_index]);
			if (meaning == NULL)
			{
				printf ("%s not found.\n", argv[keyword_index]);
			} else {
				if (print_keyword)
					printf ("%s:\n", dictionary_get_first_matched_word ());
				printf ("%s\n", meaning);
			}
			dictionary_close ();
			return 0;
		}
	}
}
