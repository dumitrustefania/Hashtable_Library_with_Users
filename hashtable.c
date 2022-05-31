// Copyright 2022 Dumitru Bianca Stefania 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "macros.h"
#include "structs.h"
#include "linked_list.h"
#include "hashtable.h"

hashtable_t * ht_create(unsigned int hmax,
						unsigned int (*hash_function)(void *),
						int (*compare_function)(void *, void *))
{
	//  check if the parameter functions are valid
	if (!hash_function || !compare_function)
		return NULL;

	//  allocate memory for the hashtable
	hashtable_t *ht = malloc(sizeof(hashtable_t));
	DIE(!ht, "malloc failed");


	//  initialize parameters for the hashtable
	ht->size = 0;
	ht->hmax = hmax;
	ht->hash_function = hash_function;
	ht->compare_function = compare_function;


	//  allocate memory for the hmax buckets of the hashtable
	//  each bucket is represented as a linked list
	ht->buckets = malloc(ht->hmax * sizeof(linked_list_t *));
	DIE(!ht->buckets, "malloc failed");


	//  alocate memory for each bucket by creating a new linked list
	for (unsigned int i = 0; i < ht->hmax; ++i)
		ht->buckets[i] = ll_create(sizeof(info));

	return ht;
}

void ht_put(hashtable_t **ht_, void *key, unsigned int key_size,
			void *value, unsigned int value_size, char *type)
{
	hashtable_t *ht = *ht_;

	//  check if the parameters are valid
	if (!ht || !key || !value)
		return;

	//  compute the hash of the key
	unsigned int hash = ht->hash_function(key) % ht->hmax;


	//  check if the given key is already in the hashtable
	ll_node_t *aux = ht->buckets[hash]->head;
	while (aux != NULL)  //  traverse the bucket
	{
		info *entry = (info *)aux->data;
		if (!ht->compare_function(entry->key, key))
		{
			//  if the given key is already in the hashtable
			//  free the previously allocated memory for its value and
			//  allocate the new amount of necessary memory
			free(entry->value);
			entry->value = malloc(value_size);
			DIE(entry->value == NULL, "malloc failed");

			//  copy the new value corresponding to the key
			entry->value_size = value_size;
			memcpy(entry->value, value, value_size);
			return;
		}
		aux = aux->next;
	}
	//  if we got here, it means that the key is not in the hashtable

	//  if there are too many elements in the hashtable, resize it in order
	//  to have as little colosions as possible
	double load_factor = ht->size / ht->hmax;
	if (load_factor > 1)
		ht = ht_resize(&ht, type);

	//  add the new pair key-value inside the hashtable
	info new_entry;

	//  allocate memory for the key and value and copy them in a data structure
	new_entry.key = malloc(key_size);
	DIE(new_entry.key == NULL, "malloc failed");
	memcpy(new_entry.key, key, key_size);

	new_entry.value = malloc(value_size);
	DIE(new_entry.value == NULL, "malloc failed");
	memcpy(new_entry.value, value, value_size);

	new_entry.key_size = key_size;
	new_entry.value_size = value_size;

	//  recompute the hash for the key because we might have changed the hmax
	hash = ht->hash_function(key) % ht->hmax;
	//  add the new pair into the hashtable
	ll_add_nth_node(ht->buckets[hash], 0, &new_entry);
	//  increase the size of the hashtable
	ht->size++;
	*ht_ = ht;
}

hashtable_t *ht_resize(hashtable_t **ht_, char *type)
{
	hashtable_t *ht = *ht_;
	//  create an array containg all the key-value pairs
	//  that were stored in the hashtable
	info *ht_array = make_ht_to_array(ht);

	int size = ht->size;
	int hmax = ht->hmax * 2;
	//  create a new hashtable with double the no of buckets from the old one
	hashtable_t *new_ht = ht_create(hmax, ht->hash_function, ht->compare_function);

	//  insert each key-value pair from the old hashtable to the new one
	for (int i = 0; i < size; i++)
		ht_put(&new_ht, ht_array[i].key, ht_array[i].key_size,
			   ht_array[i].value, ht_array[i].value_size, type);

	//  free memory for the old hashtable
	ht_free(ht, type);
	//  free memory for the array that saved the key-value pairs
	free(ht_array);

	*ht_ = ht;
	return new_ht;
}

int ht_has_key(hashtable_t *ht, void *key)
{
	//  check if parameters are valid
	if (!ht || !key)
		return -1;

	//  compute the hash for the key
	unsigned int hash = ht->hash_function(key) % ht->hmax;

	//  check the bucket corresponding to the calculated hash
	//  to see if the key is present
	ll_node_t *aux = ht->buckets[hash]->head;
	while (aux != NULL)
	{
		info *node = (info *)aux->data;
		if (!ht->compare_function(node->key, key))
			return 1;  //  we found the key
		aux = aux->next;
	}

	return 0;  //  key is not in the hashtable
}

void *ht_get(hashtable_t *ht, void *key)
{
	//  check if parameters are valid and key is inside of hahstable
	if (!ht || !key || ht_has_key(ht, key) != 1)
		return NULL;

	//  compute the hash for the key
	unsigned int hash = ht->hash_function(key) % ht->hmax;

	//  traverse the bucket corresponding to the calculated hash
	//  to find the value associated to the key
	ll_node_t *aux = ht->buckets[hash]->head;
	while (aux != NULL)
	{
		info *data = (info *)aux->data;
		if (!ht->compare_function(data->key, key))
			return data->value;  //  return value associated with key
		aux = aux->next;
	}

	return NULL;
}

int compare_function_strings(void *a, void *b)
{
	//  cast void* to char*
	char *str_a = (char *)a;
	char *str_b = (char *)b;

	return strcmp(str_a, str_b);
}

unsigned int
hash_function_string(void *a)
{
	unsigned char *puchar_a = (unsigned char *)a;
	int64_t hash = 5381;
	int c;

	while ((c = *puchar_a++))
		hash = ((hash << 5u) + hash) + c;

	return hash;
}

info *make_ht_to_array(hashtable_t *ht)
{
	//  allocate memory for the array that will contain the key-value pairs
	info *ht_array = malloc(ht->size * sizeof(info));
	DIE(ht_array == NULL, "malloc failed");

	int counter = 0;
	//  for each bucket
	for (unsigned int i = 0; i < ht->hmax; i++)
	{
		linked_list_t *list = ht->buckets[i];
		ll_node_t *aux = list->head;
		//  traverse each element in the bucket
		for (unsigned int j = 0; j < list->size; j++)
		{
			//  add the pair key-value to the array
			ht_array[counter] = *(info *)aux->data;
			aux = aux->next;
			counter++;
		}
	}
	return ht_array;
}


int ht_remove_entry(hashtable_t *ht, void *key)
{
	//  check if the key is present in the hashtable
	if(!ht_has_key(ht, key))
		return 0;

	//  compute the hash for the given key
	unsigned int hash = ht->hash_function(key) % ht->hmax;

	ll_node_t *aux = ht->buckets[hash]->head;

	int count = 0;
	//  traverse the bucket corresponding to the
	//  calculated hash to find the key
	while (aux != NULL)
	{
		info *node = (info *)aux->data;
		if (!ht->compare_function(node->key, key))
		{
			//  remove key-value entry from the bucket
			ll_remove_nth_node(ht->buckets[hash], count);
			//  free memory for the node in the bucket containing the key-value pair
			free_node(aux);
			//  decrease hashtable size
			ht->size--;
			return 1;
		}
		count++;
		aux = aux->next;
	}
	return 0;
}

void ht_free(hashtable_t *ht, char *type)
{
	//  for each bucket
	for (unsigned int i = 0; i < ht->hmax; i++)
	{
		linked_list_t *list = ht->buckets[i];
		ll_node_t *aux = list->head;

		for (unsigned int i = 0; i < list->size; i++)
		{
			//  traverse each element in the bucket
			ll_node_t *to_free = aux;
			aux = aux->next;

			//  if we are currently freeing a library, we should be aware
			//  that the value associated with the key is a book data structure, which
			//  also contains a hashtable that has to be freed
			if (!strcmp(type, "library"))
			{
				info *infor = (info *)to_free->data;
				book_t *book = (book_t *)infor->value;
				//  free memory for the book hashtable
				ht_free(book->book_ht, "book");
			}
			//  free memory for the key-value pair
			free_node(to_free);
		}
		//  free memory for the bucket
		free(list);
	}
	//  free the hashtable
	free(ht->buckets);
	free(ht);
}

void free_node(ll_node_t *node)
{
	//  free memory for the key, value and node
	info *data = (info *)node->data;
	free(data->key);
	free(data->value);
	free(node->data);
	free(node);
}
