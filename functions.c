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

void add_book(hashtable_t **library, char *book_name, int no_def)
{
    //  check if the book is already in the library
    //  if it is, eliminate it to create a new one with the same name
	if (ht_has_key(*library, book_name))
	{
		book_t *book = (book_t *)ht_get(*library, book_name);
        //  free memory for the definitions hashtable
		ht_free(book->book_ht, "book");
        //  eliminate book from library
		ht_remove_entry(*library, book_name);
	}

    //  create a new book with given name
	book_t *book = create_book(book_name);
	free(book_name);

    //  add the given definitions inside the book
	add_definitions(&book->book_ht, no_def);
    //  add the book to the library
	ht_put(&*library, book->book_name, strlen(book->book_name) + 1,
		   book, sizeof(book_t), "book");

	free(book);
}

void get_book(hashtable_t *library, char *book_name)
{
    //  get book with given name from the library
	book_t *book = (book_t *)ht_get(library, book_name);
	free(book_name);

    //  if book was found, print it
	if (book)
		printf("Name:%s Rating:%0.3f Purchases:%d\n",
			   book->book_name, book->score, book->purchases);
	else
		printf("The book is not in the library.\n");
}

void get_def(hashtable_t *library, char *book_name, char *def_name)
{
    //  get book with given name from the library
	book_t *book = (book_t *)ht_get(library, book_name);
	free(book_name);

    //  if book with given name does not exist
	if (!book)
	{
		printf("The book is not in the library.\n");
		free(def_name);
		return;
	}
    //  get definition with given key
	char *def = (char *)ht_get(book->book_ht, def_name);
	free(def_name);

    //  if definition is present in the book, print it
	if (def)
		printf("%s\n", def);
	else
		printf("The definition is not in the book.\n");
}

void rmv_book(hashtable_t *library, char *book_name)
{
    //  get book with given name from the library
	book_t *book = (book_t *)ht_get(library, book_name);

    //  if book with given name does not exist
	if (!book)
	{
		printf("The book is not in the library.\n");
		free(book_name);
		return;
	}
    //  free the definitions hashtable from the book
	ht_free(book->book_ht, "book");
    //  remove book from the library
	ht_remove_entry(library, book_name);
	free(book_name);
}

void add_def(hashtable_t *library, char *book_name, char *key, char *val)
{   //  get book with given name from the library
	book_t *book = (book_t *)ht_get(library, book_name);
	free(book_name);

    //  if book with given name does not exist
	if (!book)
	{
		printf("The book is not in the library.\n");
		free(key);
		free(val);
		return;
	}

    //  add the key-value pair to the definitions hashtable in the book
	ht_put(&book->book_ht, key, strlen(key) + 1, val, strlen(val) + 1, "def");
	free(key);
	free(val);
}

void rmv_def(hashtable_t *library, char *book_name,
			 char def_name[MAX_STRING_SIZE])
{   //  get book with given name from the library
	book_t *book = (book_t *)ht_get(library, book_name);
	free(book_name);

    //  if book with given name does not exist
	if (!book)
	{
		printf("The book is not in the library.\n");
		return;
	}

    //  remove definition with given key from the definitions hashtable
	if (!ht_remove_entry(book->book_ht, def_name))
		printf("The definition is not in the book.\n");
}

void add_user(hashtable_t **users, char *user_name)
{   //  check if user already exists
	if (ht_has_key(*users, user_name))
	{
		printf("User is already registered.\n");
		free(user_name);
		return;
	}

    //  create user with given user name
	user_t *user = create_user(user_name);
    //  add user to the users hashtable
	ht_put(&*users, user->user_name, strlen(user->user_name) + 1,
		   user, sizeof(user_t), "user");

	free(user);
	free(user_name);
}

void borrow(hashtable_t *users, char *user_name,
			hashtable_t *library, char *book_name, int borrowed_days)
{
    //  get user with given name from the users hashtable
	user_t *user = ht_get(users, user_name);
	free(user_name);

    //  if user with given name does not exist
	if (!user)
	{
		printf("You are not registered yet.\n");
		free(book_name);
		return;
	}
    //  if user has no more points
	if (user->points < 0)
	{
		printf("You are banned from this library.\n");
		free(book_name);
		return;
	}

    //  get book with given name from the library
	book_t *book = (book_t *)ht_get(library, book_name);
	free(book_name);

    //  if user already has a book borrowed
	if (strcmp(user->borrowed_book, "-"))
	{
		printf("You have already borrowed a book.\n");
		return;
	}
    //  if book with given name does not exist
	if (!book)
	{
		printf("The book is not in the library.\n");
		return;
	}
    //  if book is already borrowed by someone else
	if (book->borrowed)
	{
		printf("The book is borrowed.\n");
		return;
	}

    //  memorize which book the user has borrowed
	strcpy(user->borrowed_book, book->book_name);
    //  memorize how many days he said he will keep it
	user->borrowed_days = borrowed_days;
    // mark the book as borrowed
	book->borrowed = 1;
}

void return_book(hashtable_t *users, char *user_name,
				 hashtable_t *library, char *book_name, int actual_days, int rating)
{
    //  get user with given name from the users hashtable
	user_t *user = ht_get(users, user_name);
	free(user_name);

    //  if user has no more points
	if (user->points < 0)
	{
		printf("You are banned from this library.\n");
		free(book_name);
		return;
	}

    //  get book with given name from the library
	book_t *book = (book_t *)ht_get(library, book_name);
	free(book_name);

    //  if user did not borrow any book or the
	//  returned book is not the borrowed book
	if (user->borrowed_book == NULL ||
		strcmp(book->book_name, user->borrowed_book))
	{
		printf("You didn't borrow this book.\n");
		return;
	}

    //  compute how many points the user wins/loses
	int promised_days = user->borrowed_days;

	if (promised_days > actual_days)
		user->points += promised_days - actual_days;
	else
		user->points -= (actual_days - promised_days) * 2;

    //  mark the user with currently having no book borrowed
	strcpy(user->borrowed_book, "-");
	user->borrowed_days = -1;

    //  mark the book as not borrowed and update its rating
	book->borrowed = 0;
	book->purchases++;
	book->rating += rating;
	book->score = book->rating / book->purchases;

    //  if user lost all its points because of this return
	if (user->points < 0)
		printf("The user %s has been banned from this library.\n", user->user_name);
}

void lost_book(hashtable_t *users, char *user_name,
				 hashtable_t *library, char *book_name)
{
    //  get user with given name from the users hashtable
	user_t *user = ht_get(users, user_name);
	free(user_name);

    //  if user with given name does not exist
	if (!user)
	{
		printf("You are not registered yet.\n");
		free(book_name);
		return;
	}
    //  if user has no more points
	if (user->points < 0)
	{
		printf("You are banned from this library.\n");
		free(book_name);
		return;
	}

    //  get book with given name from the library
	book_t *book = (book_t *)ht_get(library, book_name);

    //  update user's points and
    //  mark the user with currently having no book borrowed
	user->points -= 50;
	strcpy(user->borrowed_book, "-");
	user->borrowed_days = -1;

    //  free memory for the definitions hashtable in the lost book
	ht_free(book->book_ht, "book");
    //  eliminate lost book from library
	ht_remove_entry(library, book_name);
	free(book_name);

    //  if user lost all its points because of this loss
	if (user->points < 0)
		printf("The user %s has been banned from this library.\n", user->user_name);
}

void print_and_free(hashtable_t *library, hashtable_t *users)
{   //  print books&users ranking
	print_ranking(library, "Books");
	print_ranking(users, "Users");

    //  free memory for library and users hashtables
	ht_free(library, "library");
	ht_free(users, "users");
}
