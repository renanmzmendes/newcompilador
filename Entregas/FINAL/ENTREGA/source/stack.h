/*  
 *          File: stack.h
 *        Author: Robert I. Pitts <rip@cs.bu.edu>
 * Last Modified: March 7, 2000
 *         Topic: Stack - Array Implementation
 * ----------------------------------------------------------------
 *
 * This is the interface for a stack of characters.
 */

#ifndef _STACK_H
#define _STACK_H

#include <stdio.h>
#include <stdlib.h>  /* for dynamic allocation */


/*
 * Type: stackElementT
 * -------------------
 * This is the type of the objects entered in the stack.
 * Edit it to change the type of things to be placed in
 * the stack.
 */



typedef int stackElementT;
typedef struct { 
    stackElementT *contents; 
    int maxSize; 
    int top; 
} stackT; 

void StackInit(stackT *stackP, int maxSize);
void StackDestroy(stackT *stackP);
void StackPush(stackT *stackP, stackElementT element);
stackElementT StackPop(stackT *stackP);
int StackIsEmpty(stackT *stackP);
int StackIsFull(stackT *stackP);

#endif  /* not defined _STACK_H */