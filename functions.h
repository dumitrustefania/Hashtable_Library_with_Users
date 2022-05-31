// Copyright 2022 Dumitru Bianca Stefania 312CA
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

//  add book with given name into the library
void add_book(hashtable_t **, char *, int);

//  print book with given name into the library
void get_book(hashtable_t *, char *);

//  get definition with given key from a book in the library
void get_def(hashtable_t *, char *, char *);

//  remove book with given name from the library
void rmv_book(hashtable_t *, char *);

//  add given key-value definition in a book
void add_def(hashtable_t *, char *, char *, char *);

//  remove given key-value definition in a book
void rmv_def(hashtable_t *, char *, char[MAX_STRING_SIZE]);

//  add user with given name into the users hashtable
void add_user(hashtable_t **, char *);

//  make user borrow a book from the library, specifying
//  the number of days he expects to keep it
void borrow(hashtable_t *, char *, hashtable_t *, char *, int);

//  make user return a book to the library, specifying a rating for the book
//  update his points based on the number of days he kept the book
void return_book(hashtable_t *, char *, hashtable_t *, char *, int , int);

//  make user lose a book => eliminating the book from the library
//  and user losing 50 points
void lost_book(hashtable_t *, char *, hashtable_t *, char *);

//  print the final rankings and free memory for the library and users
void print_and_free(hashtable_t *, hashtable_t *);

#endif  // FUNCTIONS_H_
