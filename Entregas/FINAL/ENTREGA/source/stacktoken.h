//
//  stack.h
//  Compilador
//
//  Created by Renan Mendes on 10/30/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*  
 *          File: stack.h
 *        Author: Robert I. Pitts <rip@cs.bu.edu>
 * Last Modified: March 7, 2000
 *         Topic: Stack - Array Implementation
 * ----------------------------------------------------------------
 *
 * This is the interface for a stack of characters.
 */

#ifndef _STACK_TOKEN_H
#define _STACK_TOKEN_H

#include <stdio.h>
#include <stdlib.h>  /* for dynamic allocation */
#include "Token.h"


/*
 * Type: stackElementT
 * -------------------
 * This is the type of the objects entered in the stack.
 * Edit it to change the type of things to be placed in
 * the stack.
 */



typedef Token* stackElementToken;
typedef struct { 
    stackElementToken *contents; 
    int maxSize; 
    int top; 
} stackToken; 

void StackTokenInit(stackToken *stackP, int maxSize);
void StackTokenDestroy(stackToken *stackP);
void StackTokenPush(stackToken *stackP, stackElementToken element);
stackElementToken StackTokenPop(stackToken *stackP);
int StackTokenIsEmpty(stackToken *stackP);
int StackTokenIsFull(stackToken *stackP);

#endif  /* not defined _STACK_H */