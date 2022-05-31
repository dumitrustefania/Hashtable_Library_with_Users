// Copyright 2022 Dumitru Bianca Stefania 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"
#include "structs.h"
#include "linked_list.h"
#include "hashtable.h"
#include "functions.h"
#include "utils.h"

void read_tokens(char tokens[TOKENS_MAX][COMMAND_MAX])
{
    //  read the line containing the tokens
	char str[COMMAND_MAX];
	fgets(str, COMMAND_MAX, stdin);

    //  remove trailing newline
	if (str[strlen(str) - 1] == '\n')
		str[strlen(str) - 1] = '\0';

    //  tokenize string
	char *p = strtok(str, " ");
	int count = 0;
	while (p)
	{
		if (p[0] == '"') //  concatenate book name separated by " "
		{
			strcpy(tokens[count], p);
			while (p[strlen(p) - 1] != '"')
			{
				p = strtok(NULL, " ");
				strcat(tokens[count], " ");
				strcat(tokens[count], p);
			}
			p = strtok(NULL, " ");
			count++;
		}
		else
		{   //  add each token to the array
			strcpy(tokens[count], p);
			p = strtok(NULL, " ");
			count++;
		}
	}
}

void add_definitions(hashtable_t **book, int no_def)
{
	for (int i = 0; i < no_def; i++)
	{   //  aloocate memory for key-value strings and read them
		char *key = malloc(MAX_STRING_SIZE);
		char *val = malloc(MAX_STRING_SIZE);
		scanf("%s %s", key, val);

        //  add each key-value pair to the definitions hashtable in the book
		ht_put(&*book, key, strlen(key) + 1, val, strlen(val) + 1, "def");

        //  free memory for the strings
		free(key);
		free(val);
	}
}

book_t *create_book(char *book_name)
{
    //  allocate memory for the book
	book_t *book = malloc(sizeof(book_t));
    //  allocate the memory for creating the definitions hashtable
	book->book_ht = ht_create(HMAX, hash_function_string,
							  compare_function_strings);

    //  initialize book parameters
	strcpy(book->book_name, book_name);
	book->borrowed = 0;
	book->purchases = 0;
	book->rating = 0;
	book->score = 0;

	return book;
}

user_t *create_user(char *user_name)
{
    //  allocate memory for the user
	user_t *user = malloc(sizeof(user_t));

    //  initialize user parameters
	strcpy(user->borrowed_book, "-");
	user->borrowed_days = -1;
	user->points = 100;
	strcpy(user->user_name, user_name);

	return user;
}

char *get_book_name(char token[COMMAND_MAX])
{   //  allocate memory for the string and eliminate the " "
    //  from the beginning and end
	char *book_name = malloc(strlen(token));
	strcpy(book_name, token + 1);
	book_name[strlen(book_name) - 1] = '\0';

	return book_name;
}

void swap_elem(info **v, int i, int j)
{
	info aux = (*v)[i];
	(*v)[i] = (*v)[j];
	(*v)[j] = aux;
}

void arrange_books(info **list, int i, int j)
{
	info *list_p = *list;
	book_t book1 = *(book_t *)list_p[i].value;
	book_t book2 = *(book_t *)list_p[j].value;

    //  compare scores
	if (book1.score > book2.score)
		swap_elem(&*list, i, j);

	else if (book1.score == book2.score)
	{   //  compare no of purchases
		if (book1.purchases > book2.purchases)
			swap_elem(&*list, i, j);
            //  compare names lexicographically
		else if ((book1.purchases == book2.purchases) &&
				 (strcmp(book1.book_name, book2.book_name) < 0))
			swap_elem(&*list, i, j);
	}
}

void arrange_users(info **list, int i, int j)
{
	info *list_p = *list;
	user_t user1 = *(user_t *)list_p[i].value;
	user_t user2 = *(user_t *)list_p[j].value;

    // compare no of points
	if (user1.points > user2.points)
		swap_elem(&*list, i, j);
    //  compare names lexicographically
	else if (user1.points == user2.points)
		if (strcmp(user1.user_name, user2.user_name) < 0)
			swap_elem(&*list, i, j);
}

void print_ranking(hashtable_t *ht, char *type)
{
	printf("%s ranking:\n", type);

    //  create an array containg all the key-value pairs in the hashtable
	info *ht_array = make_ht_to_array(ht);

    //  arrange the books / users based on different aspects
	for (unsigned int i = 0; i < ht->size; i++)
		for (unsigned int j = 0; j < i; j++)
		{
			if (!strcmp(type, "Books"))
				arrange_books(&ht_array, i, j);
			else
				arrange_users(&ht_array, i, j);
		}

    //  print the rankings
	for (unsigned int i = 0; i < ht->size; i++)
	{
		if (!strcmp(type, "Books"))
		{
			printf("%d. ", i + 1);
			book_t book = *(book_t *)ht_array[i].value;
			printf("Name:%s Rating:%0.3f Purchases:%d\n",
				   book.book_name, book.score, book.purchases);
		}
		else
		{
			user_t user = *(user_t *)ht_array[i].value;
			if (user.points < 0)
				break;
			printf("%d. Name:%s Points:%d\n", i + 1, user.user_name, user.points);
		}
	}
	free(ht_array);
}
