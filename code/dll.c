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

/********************
 * Global Variables *
 ********************/
Node *head = NULL; //this link always point to first Link

Node *last = NULL; //this link always point to last Link

Node *current = NULL; //this link always points to the current link

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
