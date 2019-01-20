#ifdef _DLL_H_
#define _DLL_H_

/***********
 * Structs *
 ***********/
typedef struct node{
    void *data;
    int key;
    struct *next;
    struct *prev;
} Node;

/********************
 * Global Variables *
 ********************/
extern Node *head;
extern Node *last;
extern Node *current;

/*************
 * Functions *
 *************/
extern void push(Node* link, void* val);
extern void pop(Node* link);
extern void* get(int key);
extern Node* remove(int key);
extern bool isEmpty();
extern int length();
#endif
