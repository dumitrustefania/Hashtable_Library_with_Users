// Copyright 2022 Dumitru Bianca Stefania 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"
#include "structs.h"
#include "linked_list.h"
#include "hashtable.h"

linked_list_t *
ll_create(unsigned int data_size)
{
	linked_list_t *ll;

	//  allocate memory for a linked list
	ll = malloc(sizeof(*ll));
	DIE(ll == NULL, "linked_list malloc");

	//  initialize list parameters
	ll->head = NULL;
	ll->data_size = data_size;
	ll->size = 0;

	return ll;
}

void ll_add_nth_node(linked_list_t *list, unsigned int n, const void *new_data)
{
	ll_node_t *prev, *curr;
	ll_node_t *new_node;

	//  check if parameter list is allocated
	if (!list)
		return;

	//  add on the last position if desired position > list size
	if (n > list->size)
		n = list->size;

	//  traverse the list until finding the right place to insert the node
	curr = list->head;
	prev = NULL;
	while (n > 0)
	{
		prev = curr;
		curr = curr->next;
		--n;
	}

	//  allocate memory for the new node and the data inside of it
	new_node = malloc(sizeof(*new_node));
	DIE(new_node == NULL, "new_node malloc");

	new_node->data = malloc(list->data_size);
	DIE(new_node->data == NULL, "new_node->data malloc");

	//  copy the data to the new node
	memcpy(new_node->data, new_data, list->data_size);

	//  insert the new node in the list at desired position
	new_node->next = curr;
	if (prev == NULL)  //  if desired position = 0
		list->head = new_node;
	else
		prev->next = new_node;

	//  increase list size
	list->size++;
}

void ll_remove_nth_node(linked_list_t *list, unsigned int n)
{
	//  check if parameter list is allocated and if it is not an empty list
	if (!list || !list->head)
		return;

	//  remove from the last position if desired position > list size
	if (n > list->size - 1)
		n = list->size - 1;

	//  traverse the list until finding the right place to insert the node
	ll_node_t *prev, *curr;
	curr = list->head;
	prev = NULL;
	while (n > 0)
	{
		prev = curr;
		curr = curr->next;
		--n;
	}

	//  remove the node in the list at desired position
	if (prev == NULL)  //  if desired position = 0
		list->head = curr->next;
	else
		prev->next = curr->next;

	//  decrease list size
	list->size--;
}
