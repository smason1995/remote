/**************************************
 * Generic Doubly Linked List library *
 * author: Sydney Ann Mason           *
 * version: 20190119                  *
 **************************************/

/***********
 * Imports *
 ***********/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

/***************************
 * Linked List Data Struct *
 ***************************/
struct node{
    void *data;
    int key;

    struct node *next;
    struct node *prev;
};

//this link always point to first Link
struct node *head = NULL;

//this link always point to last Link
struct node *last = NULL;

struct node *current = NULL;

//is list empty
bool isEmpty(){
    return head == NULL:
}

int length(){
    int length = 0;
    struct node *current;

    for(current = head; current != NULL; current = current->next){
        length++;
    }

    return length;
}


