//
//  stack.c
//  Compilador
//
//  Created by Renan Mendes on 10/30/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "stacktoken.h"

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

/************************ Function Definitions **********************/

void StackTokenInit(stackToken *stackP, int maxSize)
{
    stackElementToken *newContents;
    
    /* Allocate a new array to hold the contents. */
    
    newContents = (stackElementToken *)malloc(sizeof(stackElementToken) * maxSize);
    
    if (newContents == NULL) {
        fprintf(stderr, "Insufficient memory to initialize stack.\n");
        exit(1);  /* Exit, returning error code. */
    }
    
    stackP->contents = newContents;
    stackP->maxSize = maxSize;
    stackP->top = -1;  /* I.e., empty */
}

void StackTokenDestroy(stackToken *stackP)
{
    /* Get rid of array. */
    free(stackP->contents);
    
    stackP->contents = NULL;
    stackP->maxSize = 0;
    stackP->top = -1;  /* I.e., empty */
}

void StackTokenPush(stackToken *stackP, stackElementToken element)
{
    if (StackTokenIsFull(stackP)) {
        fprintf(stderr, "Can't push element on stack: stack is full.\n");
        exit(1);  /* Exit, returning error code. */
    }
    
    /* Put information in array; update top. */
    
    stackP->contents[++stackP->top] = element;
}

stackElementToken StackTokenPop(stackToken *stackP)
{
    if (StackTokenIsEmpty(stackP)) {
        fprintf(stderr, "Can't pop element from stack: stack is empty.\n");
        exit(1);  /* Exit, returning error code. */
    }
    
    return stackP->contents[stackP->top--];
}

int StackTokenIsEmpty(stackToken *stackP)
{
    return stackP->top < 0;
}

int StackTokenIsFull(stackToken *stackP)
{
    return stackP->top >= stackP->maxSize - 1;
}