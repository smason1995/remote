#ifdef _DLL_H_
#define _DLL_H_

/***********
 * Structs *
 ***********/
typedef struct node{
    void *data;
    struct *next;
    struct *prev;
} Node;

typedef struct dllist{
    Node *head;
    Node *tail;
    Node *current;
    int size;
} Dllist;

/*************
 * Functions *
 *************/
Dllist* dllist_create(void);

void dllist_destroy(Dllist *dllist);

int dllist_push_front(Dllist *dllist, void *data);

int dllist_push_back(Dllist *dllist, void *data);

void* dllist_pop_front(Dllist *dllist);

void* dllist_pop_back(Dllist *dllist);

int dllist_step_forward(Dllist *dllist);

int dllist_step_backward(Dllist *dllist);

void* dllist_read_index(Dllist *dllist, int index);

int dllist_insert_after(Dllist *dllist, int index, void *data);

void* dllist_extract_after(Dllist *dllist, int index);
#endif
