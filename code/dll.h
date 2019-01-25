/*************************************
 * Generic Doubly Linked List header *
 * author: Sydney Ann Mason          *
 * version: 20190125                 *
 *************************************/

#ifndef _DLL_H_
#define _DLL_H_

/*
 * A single node in a linked list
 *
 * data, void pointer that holds the value
 * of the node
 *
 * next, struct node pointer to the next node 
 * (null by default)
 *
 * prev, struct node pointer to the previous
 * node (null by default)
 */
typedef struct node{
    void *data;
    struct node *next;
    struct node *prev;
}Node;

/*
 * Contains information about the
 * linked list as a whole
 *
 * head, the first node in the list
 *
 * tail, the last node in the list
 *
 * current, the node being pointed to
 * currently in the list
 *
 * size, number of nodes in the list
 */
typedef struct dllist{
    struct node *head;
    struct node *tail;
    struct node *current;
    int size;
}Dllist;

/*
 * Creates a new linked list
 *
 * Returns the new list
 */
struct dllist* dllist_create(void);

/*
 * Deletes a linked list
 */
void dllist_destroy(struct dllist *dllist);

/*
 * Puts a new node at the head of the list
 *
 * Returns -1 if it fails; 0 if it succeeds
 */
int dllist_push_front(struct dllist *dllist, void *data);

/*
 * Puts a new node at the tail of the list
 *
 * Returns -1 if it fails; 0 if it succeeds
 */
int dllist_push_back(struct dllist *dllist, void *data);

/*
 * Grabs the head node and frees the space
 *
 * Returns NULL if it fails; data if it
 * succeeds
 */
void* dllist_pop_front(struct dllist *dllist);

/*
 * Grabs the tail node and frees the space
 *
 * Returns NULL if it fails; data if it
 * succeeds
 */
void* dllist_pop_back(struct dllist *dllist);

/*
 * Moves current node to next node
 *
 * Returns 1 if next is NULL
 * Returns 0 otherwise
 */
int dllist_step_forward(struct dllist *dllist);

/*
 * Moves current node to the previous node
 *
 * Returns 1 if next is NULL
 * Returns 0 otherwise
 */
int dllist_step_backward(struct dllist *dllist);

/*
 * Reads value at specified index
 *
 * Returns NULL if nothing can be read
 * Returns target->data otherwise
 */
void* dllist_read_index(struct dllist *dllist, int index);
#endif
