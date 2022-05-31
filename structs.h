// Copyright 2022 Dumitru Bianca Stefania 312CA
#ifndef STRUCTS_H_
#define STRUCTS_H_

//  node structure
typedef struct ll_node_t
{
	void *data;
	struct ll_node_t *next;
} ll_node_t;

//  linked list structure
typedef struct linked_list_t
{
	ll_node_t *head;
	unsigned int data_size;
	unsigned int size;
} linked_list_t;

//  info structure containg key-value pair and its sizes
typedef struct info info;
struct info
{
	void *key;
	void *value;
	int key_size, value_size;
};

//  hashtable structure
typedef struct hashtable_t hashtable_t;
struct hashtable_t
{
	linked_list_t **buckets;  //  array with linked list elements
	unsigned int size;  //  no of elements
	unsigned int hmax;  //  no of buckets
	//  pointer to hash function
	unsigned int (*hash_function)(void *);
	//  pointer to comparing function
	int (*compare_function)(void *, void *);
};

//  book structure
typedef struct book_t
{
	hashtable_t *book_ht;  //  hashtable containing the definitions
	char book_name[MAX_STRING_SIZE];
	int borrowed, purchases;
	double rating, score;
} book_t;

//  user structure
typedef struct user_t
{
	int points;
	char borrowed_book[MAX_STRING_SIZE];
	char user_name[MAX_STRING_SIZE];
	int borrowed_days;
} user_t;

#endif  // STRUCTS_H_
