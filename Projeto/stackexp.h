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

#ifndef _STACK_EXPRESSOES_H
#define _STACK_EXPRESSOES_H

#include <stdio.h>
#include <stdlib.h>  /* for dynamic allocation */
#include "Token.h"

#define MAX_EXPRESSOES
/*
 * Type: stackElementT
 * -------------------
 * This is the type of the objects entered in the stack.
 * Edit it to change the type of things to be placed in
 * the stack.
 */


typedef struct {
    int tamanho;
    Token* tokens[MAX_EXPRESSOES];
} Expressao;

void insereTokenNaExpressao(Token* t, Expressao* e);


typedef Expressao* stackElementExp;
typedef struct { 
    stackElementExp *contents; 
    int maxSize; 
    int top; 
} stackExp; 

void StackExpInit(stackExp *stackP, int maxSize);
void StackExpDestroy(stackExp *stackP);
void StackExpPush(stackExp *stackP, stackElementExp element);
stackElementExp StackExpPop(stackExp *stackP);
int StackExpIsEmpty(stackExp *stackP);
int StackExpIsFull(stackExp *stackP);

#endif  /* not defined _STACK_H */