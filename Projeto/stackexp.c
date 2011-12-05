/*
 *          File: stack.c
 *        Author: Robert I. Pitts <rip@cs.bu.edu>
 * Last Modified: March 7, 2000
 *         Topic: Stack - Array Implementation
 * ----------------------------------------------------------------
 *
 * This is an array implementation of a character stack.
 */

#include <stdio.h>
#include <stdlib.h>  /* for dynamic allocation */
#include "stackexp.h"       

void insereTokenNaExpressao(Token* t, Expressao* e) {
    e->tokens[e->tamanho] = t;
    e->tamanho++;
}


/************************ Function Definitions **********************/

void StackExpInit(stackExp *stackP, int maxSize)
{
    stackElementExp *newContents;
    
    /* Allocate a new array to hold the contents. */
    
    newContents = (stackElementExp *)malloc(sizeof(stackElementExp) * maxSize);
    
    if (newContents == NULL) {
        fprintf(stderr, "Insufficient memory to initialize stack.\n");
        exit(1);  /* Exit, returning error code. */
    }
    
    stackP->contents = newContents;
    stackP->maxSize = maxSize;
    stackP->top = -1;  /* I.e., empty */
}

void StackExpDestroy(stackExp *stackP)
{
    /* Get rid of array. */
    free(stackP->contents);
    
    stackP->contents = NULL;
    stackP->maxSize = 0;
    stackP->top = -1;  /* I.e., empty */
}

void StackExpPush(stackExp *stackP, stackElementExp element)
{
    if (StackExpIsFull(stackP)) {
        fprintf(stderr, "Can't push element on stack: stack is full.\n");
        exit(1);  /* Exit, returning error code. */
    }
    
    /* Put information in array; update top. */
    
    stackP->contents[++stackP->top] = element;
}

stackElementExp StackExpPop(stackExp *stackP)
{
    if (StackExpIsEmpty(stackP)) {
        fprintf(stderr, "Can't pop element from stack: stack is empty.\n");
        exit(1);  /* Exit, returning error code. */
    }
    
    return stackP->contents[stackP->top--];
}

int StackExpIsEmpty(stackExp *stackP)
{
    return stackP->top < 0;
}

int StackExpIsFull(stackExp *stackP)
{
    return stackP->top >= stackP->maxSize - 1;
}