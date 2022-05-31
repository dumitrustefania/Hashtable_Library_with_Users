// Copyright 2022 Dumitru Bianca Stefania 312CA
#ifndef UTILS_H_
#define UTILS_H_

//  create tokens array
void read_tokens(char[TOKENS_MAX][COMMAND_MAX]);

//  add k definitions to the book
void add_definitions(hashtable_t **, int k);

//  create book with given name
book_t *create_book(char *);

//  create user with given name
user_t *create_user(char *);

//  eliminate " " from a book name
char *get_book_name(char[COMMAND_MAX]);

//  swap 2 elements in array
void swap_elem(info **, int , int);

//  arrange books, putting the best rated ones on top
void arrange_books(info **, int , int);

//  arrange users, putting the ones with the highest points on top
void arrange_users(info **, int , int);

//  print users & books rankings
void print_ranking(hashtable_t *, char *);

#endif  // UTILS_H_
