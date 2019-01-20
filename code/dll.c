/**************************************
 * Generic Doubly Linked List library *
 * author: Sydney Ann Mason           *
 * version: 20190119                  *
 **************************************/

/***********
 * Imports *
 ***********/
#include<stdio.h>
#include<stdbool.h>

#include"dll.h"

/*************
 * Functions *
 *************/
//is list empty
bool isEmpty(){
    return head == NULL:
}

//length of the linked list
int length(){
    int length = 0;
    Node *current;

    //Counts the elements of the linked list
    for(current = head; current != NULL; current = current->next){
        length++;
    }

    return length;
}
