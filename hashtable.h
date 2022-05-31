// Copyright 2022 Dumitru Bianca Stefania 312CA
#ifndef HASHTABLE_H_
#define HASHTABLE_H_

//  allocate memory to create a hashtable with given hash and compare functions
hashtable_t * ht_create(unsigned int , unsigned int (*)(void *),
		  int (*)(void *, void *));

//  insert a key-value pair into the hashtable
void ht_put(hashtable_t **, void *, unsigned int ,
			void *, unsigned int , char *);

//  resize the hashtable by doubling its size
//  and rehashing all the elements inside of it
hashtable_t *ht_resize(hashtable_t **, char *);

//  check if given key is presend in the hahstable
int ht_has_key(hashtable_t *, void *);

//  return the value associated with a given key from the hashtable
void *ht_get(hashtable_t *, void *);

//  compare 2 strings
int compare_function_strings(void *, void *);

//  hash a string
unsigned int hash_function_string(void *);

//  create an array containg all the key-value pairs in a hashtable
info *make_ht_to_array(hashtable_t *);

//  remove a key-value pair from a hashtable
int ht_remove_entry(hashtable_t *, void *);

//  free memory for a hashtable
void ht_free(hashtable_t *, char *);

//  free a node(structure containg key-value pair)
//  from a bucket inside the hashtable
void free_node(ll_node_t *);

#endif  // HASHTABLE_H_
