/*
 *  TabelaSimbolos.c
 *  Compilador
 *
 *  Created by Tiago Schelp Lopes on 03/12/11.
 *  Copyright 2011 USP. All rights reserved.
 *
 */

#include "TabelaSimbolos.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

void insereConstante(int c, TabelaConstantes* t) {
    // Cria uma constante a partir de um inteiro
    Constante* k = (Constante*)malloc(sizeof(Constante));
    k->valor = c;
    char* label = (char*)malloc(10*sizeof(char));
    
    int i;
    for(i = 0; i < 50; ++i) {
        label[i] = '\0';
    }
    
    strcat(label, "K");
    char n[5];
    n[0] = n[1] = n[2] = n[3] = n[4] = '\0';
    sprintf(n, "%d", c);
    strcat(label, n);
    k->label = label;
    t->constantes[t->tamanho] = k;
    t->tamanho++;
}

int existeConstante(int c, TabelaConstantes* t) {
    // Verifica se já existe uma constante de mesmo valor
    int i;
    for(i = 0; i < t->tamanho; ++i) {
        if(t->constantes[i]->valor == c) {
            return 1;
        }
    }
    
    return 0;
}

char* recuperaLabelConstante(int c, TabelaConstantes* t) {
    int i;
    for(i = 0; i < t->tamanho; ++i) {
        if(c == t->constantes[i]->valor) {
            return t->constantes[i]->label;
        }
    }
    
    return 0;
}

void initEscopo(Escopo* e){
	e->numInternos = 0;
	e->numSimbolos = 0;
}

void insereEscopoInterno(Escopo* e, Escopo* interno){
	e->internos[e->numInternos] = interno;
    e->numInternos++;
}

//
//
///Escopo com no m√°ximo MAX_SIMBOLOS
//typedef struct {
//	Simbolo s[MAX_SIMBOLOS];
//	struct Escopo* anterior;
//	struct Escopo* internos[MAX_ESCOPOS];
//	int numSimbolos;
//	int numInternos
//



void adicionarSimbolo(Tipo t, char* nome, char* label, Escopo* e){
	e->simbolos[e->numSimbolos].tipo = t;
	e->simbolos[e->numSimbolos].nome = nome;
	e->simbolos[e->numSimbolos].label = label;
    e->numSimbolos++;	
}

void adicionarVarTemp(char* label, TabelaVarTemp* t) {
    t->vars[t->tamanho] = label;
    t->tamanho++;
}

int existeSimbolo(char* nome, Escopo* e){
	for (int i = 0; i < e->numSimbolos; i++) {
		if (!strcmp(e->simbolos[i].nome, nome)) {
			return 1;
		}
	}
	return 0;
}

char* recuperaLabelSimbolo(char* nome, Escopo* e) {
    int i;
    for(i = 0; i < e->numSimbolos; ++i) {
        if(!strcmp(e->simbolos[i].nome, nome)) {
            return e->simbolos[i].label;
        }
    }
    
    if(e->anterior == 0) {
        return 0;
    }
        
    return recuperaLabelSimbolo(nome, e->anterior);
}
