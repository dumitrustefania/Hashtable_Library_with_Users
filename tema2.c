// Copyright 2022 Dumitru Bianca Stefania 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"
#include "structs.h"
#include "linked_list.h"
#include "hashtable.h"
#include "utils.h"
#include "functions.h"

int main()
{
	//  create the 2 hashtables: for the library and for the users
	hashtable_t *library = ht_create(HMAX, hash_function_string,
									compare_function_strings);
	hashtable_t *users = ht_create(HMAX, hash_function_string,
								   compare_function_strings);

	while (1)
	{
		char command[COMMAND_MAX], tokens[TOKENS_MAX][COMMAND_MAX];

		scanf("%s", command);  //  read the given command
		if (!strcmp(command, "EXIT"))
		{
			print_and_free(library, users);
			break;
		}

		read_tokens(tokens);  // read tokens after the command

		if (!strcmp(command, "ADD_BOOK"))
		{
			char *book_name = get_book_name(tokens[0]);
			int no_def = atoi(tokens[1]);

			add_book(&library, book_name, no_def);
		}
		else if (!strcmp(command, "GET_BOOK"))
		{
			char *book_name = get_book_name(tokens[0]);

			get_book(library, book_name);
		}
		else if (!strcmp(command, "GET_DEF"))
		{
			char *book_name = get_book_name(tokens[0]);
			char *def_name = malloc(strlen(tokens[1]) + 1);
			strcpy(def_name, tokens[1]);

			get_def(library, book_name, def_name);
		}
		else if (!strcmp(command, "RMV_BOOK"))
		{
			char *book_name = get_book_name(tokens[0]);

			rmv_book(library, book_name);
		}
		else if (!strcmp(command, "ADD_DEF") )
		{
			char *book_name = get_book_name(tokens[0]);
			char *key = malloc(MAX_STRING_SIZE);
			char *val = malloc(MAX_STRING_SIZE);
			strcpy(key, tokens[1]);
			strcpy(val, tokens[2]);

			add_def(library, book_name, key, val);
		}
		else if (!strcmp(command, "RMV_DEF"))
		{
			char *book_name = get_book_name(tokens[0]);

			rmv_def(library, book_name, tokens[1]);
		}
		else if (!strcmp(command, "ADD_USER"))
		{
			char *user_name = malloc(strlen(tokens[0]) + 1);
			strcpy(user_name, tokens[0]);

			add_user(&users, user_name);
		}
		else if (!strcmp(command, "BORROW"))
		{
			char *user_name = malloc(strlen(tokens[0]) + 1);
			strcpy(user_name, tokens[0]);
			char *book_name = get_book_name(tokens[1]);
			int borrowed_days = atoi(tokens[2]);

			borrow(users, user_name, library, book_name, borrowed_days);
		}
		else if (!strcmp(command, "RETURN"))
		{
			char *user_name = malloc(strlen(tokens[0]) + 1);
			strcpy(user_name, tokens[0]);
			char *book_name = get_book_name(tokens[1]);
			int actual_days = atoi(tokens[2]);
			int rating = atoi(tokens[3]);

			return_book(users, user_name, library, book_name, actual_days, rating);
		}
		else if (!strcmp(command, "LOST"))
		{
			char *user_name = malloc(strlen(tokens[0]) + 1);
			strcpy(user_name, tokens[0]);
			char *book_name = get_book_name(tokens[1]);

			lost_book(users, user_name, library, book_name);
		}
	}
	return 0;
}
