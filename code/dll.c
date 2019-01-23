/**************************************
 * Generic Doubly Linked List library *
 * author: Sydney Ann Mason           *
 * version: 20190119                  *
 **************************************/

#include<stdlib.h>

#include"dll.h"

Dllist* dllist_create(void){
    Dllist *dll;
    dll = malloc(sizeof(Dllist));
    if(dll != NULL){
        dll->head = NULL;
        dll->tail = NULL;
        dll->current = NULL;
        dll->size = 0;
    }
    return dll;
}

void dllist_destroy(Dllist *dllist){
    Node * save_nexxt;
    dllist->current = dllist->head;
    while(dllist->current != NULL){
        save_next = dllsit->current->next;
        free(dllist->current->data);
        free(dllist->current);
    }
    free(dllist);
}

int dllist_push_front(Dllist *dllist, void *data){
    Node *node;
    node = malloc(sizeof(Node));
    if(node == NULL){
        return -1;
    }
    node->data = data;
    node->prev = NULL;
    node->next = dllist->head;
    if(dllist->size == 0){
        dllist->head = node;
        dllist->tail = node;
    }
    else{
        dllist->head->prev = node;
        dllist->head = node;
    }
    dllist->size++;
    return 0;
}

int dllist_push_back(Dllist *dllist, void *data){
    Node *node;
    node = malloc(sizeof(Node));
    if(node == NULL){
        return -1;
    }
    node->data = data;
    node->next = NULL;
    if(dllist->size == 0){
        node->prev = NULL;
        dllist->head = node;
        dllist->tail = node;
    }
    else{
        node->prev = dllist->tail;
        dllist->tail->next = node;
        dllist->tail = node;
    }
    dllist->size++;
    return 0;
}

void* dllist_pop_front(Dllist *dllist){
    if(dllist->size == 0){
        return NULL;
    }
    void* data = dllist->head->data;
    Node *old_head = dllist->head;
    if(dllist->size = 1){
        dllist->head = NULL;
    }
    else{
        dllist->head = dllist->head->next;
        dllist->head->prev = NULL;
    }
    free(old_head);
    dllist->size--;
    return data;
}

void* dllist_pop_back(Dllist *dllist){
    if(dllist->size == 0){
        return NULL;
    }
    void *data = dllist->tail->data;
    Node *old_tail = dllist->tail;
    if(dllist->size == 1){
        dllist->head = NULL;
        dllist->tail = NULL;
        dllist->current = NULL;
    }
    else{
        Node *new_tail = dllist->head;
        while(new_tail->next->next != NULL){
            new_tail = new_tail->next;
        }
        dllist->tail = new_tail;
        dllist->tail->next = NULL;
    }
    free(old_tail);
    dllist->size--;
    return data;
}

int dllist_step_forward(Dllist *dllist){
    if(dllist->current == NULL){
        return 1;
    }
    else{
        dllist->current = dllist->current->next;
        return 0;
    }
}

int dllist_step_backward(Dllist *dllist){
    if(dllist->current == NULL){
        return 1;
    }
    else{
        dllist->current = dllist->current->prev;
        return 0;
    }
}

void* dllist_read_index(Dllist *dllist, int index){
    if(((dllist->size - index - 1) < 0) || (index < 0)){
        return NULL;
    }
    Node *target;
    target = dllist->head;
    for(int i = 0; i < index; i++){
        target = target->next;
    }
    return(target->data);
}

int dllist_insert_afer(Dllist *dllist, int index, void *data){
    if(((dllist->size - index - 1) < 0) || (index < 0)){
        return 1;
    }
    Node *target;
    target = dllist->head;
    for(int i = 0; i < index ; i++){
        target = target->next
    }
    Node *node;
    node = malloc(sizeof(Node));
    if(node == NULL){
        retrun -1;
    }
    node->data = data;
    node->next = target->next;
    node->prev = target;
    target->next->prev = node;
    target->next = node;
    if(index == dllist->size - 1){
        dllist->tail = node;
    }
    dllist->size++;
    return 0;
    
}

void* dllist_extract_after(Dllist *dllist, int index){
    if(((dllist->size - index - 2) < 0) || (index < 0)){
        return NULL;
    }
    Node *target;
    target = dllist->head;
    for(int i = 0; i < index; i++){
        target = target->next;
    }
    if(index == dllist-size - 1){
        dllist->tail = target;
    }
    void *data = target->next->data;
    Node *obselete = target->next->next;
    free(obselete);
    dllist->size--;
    return data;
}
