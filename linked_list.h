// Copyright 2022 Dumitru Bianca Stefania 312CA
#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

//  allocate memory for a new linked list
linked_list_t * ll_create(unsigned int);

//  add a new node at given position in a list
void ll_add_nth_node(linked_list_t *, unsigned int , const void *);

//  remove a node from given position from a list
void ll_remove_nth_node(linked_list_t *, unsigned int);

#endif  // LINKED_LIST_H_
