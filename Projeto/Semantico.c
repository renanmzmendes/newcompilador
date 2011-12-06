//
//  Semantico.c
//  Compilador
//
//  Created by Renan Mendes on 12/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "stdio.h"
#include "Semantico.h"
#include "TabelaSimbolos.h"
#include "Token.h"
#include "stdlib.h"
#include "string.h"
#include "stacktoken.h"

#define MAX_LABEL 50

Escopo* escopoAtual;
Expressao* expressaoAtual;
Token* lvalue;

char* getEmptyString(int length) {
    char* s = (char*)malloc(length*sizeof(char));
    int i;
    for(i = 0; i < length; ++i) {
        s[i] = '\0';
    }
    
    return s;
}

char* criaVariavelTemporaria() {
    char* label = getEmptyString(MAX_LABEL);
    strcat(label, "TEMP");
    char* idx = getEmptyString(5);
    sprintf(idx, "%d", contaTemp);
    strcat(label, idx);
    adicionarSimbolo(ID, label, label, escopoAtual);
    free(idx);
    
    contaTemp++;
    
    // Retorna o número da variável temporária
    return label;
}

char* recuperaLabel(Token* t) {
    char* label;
    if(t->tipo == NUM) {
        int c = atoi(t->valor);
        label = recuperaLabelConstante(c, &constTab);
        if(label == 0) {
            printf("Constante %s nao presente na tabela de constantes", t->valor);
            exit(1);
        }
    } else if(t->tipo == ID) {
        label = recuperaLabelSimbolo(t->valor, escopoAtual);
        if(label == 0) {
            printf("Variavel '%s' nao declarada\n", t->valor);
            exit(1);
        }
    }
    
    return label;
}

// Gera código da operação e 
void geraCodigoOperacao(Token* topo, Token* abaixo, Token* operador) {
    // Cria variável temporária
    char* labelTemp = criaVariavelTemporaria();
    
    char* labelTopo = recuperaLabel(topo);
    char* labelAbaixo = recuperaLabel(abaixo);
    printf("LD %s\n", labelAbaixo);
    printf("%s %s\n", operador->valor, labelTopo);
    printf("MM %s\n", labelTemp);
    
    Token* t = (Token*) malloc(sizeof(Token));
    t->tipo = ID;
    strcpy(t->valor, labelTemp);
    
    StackTokenPush(&pilhaOperandos, t);
}

void geraCodigoLoad(Token* var) {
    char* labelOperando = recuperaLabel(var);
    printf("LD %s\n", labelOperando);
}

void executarAcaoSemantica(Estado anterior, Estado atual, Token* t) {
    AcaoSemantica a = decidirAcaoSemantica(anterior, atual);
    
    // Sempre que achar um número, não importa onde
    // adiciona-o à tabela de constantes
    if(t->tipo == NUM) {
        int c = atoi(t->valor);
        if(!existeConstante(c, &constTab)) {
            insereConstante(c, &constTab);
        }
    }
    
    if(a == 0) {
        return;
    }
    
    if(a == PROGRAM_MAIN) {
        // Leu a primeira linha do main
        Escopo* mainScope = (Escopo*) malloc(sizeof(Escopo));
        initEscopo(mainScope);
        mainScope->anterior = 0;
        mainScope->nome = "main";
        
        // Adiciona escopo de primeiro nível
        escopos.escopo[escopos.tamanho] = mainScope;
        escopos.tamanho++;
        
        escopoAtual = mainScope;
        printf("main OS /0\n");
        
    } else if(a == PROGRAM_END_MAIN) {
        // Terminou o main
        printf("HM /0\n");
        
    } else if(a == VARIAVEL_NA_TABELA) {
        
        if(!existeSimbolo(t->valor, escopoAtual)) {
            char* label = getEmptyString(MAX_LABEL);
            strcat(label, escopoAtual->nome);
            strcat(label, "_");
            strcat(label, t->valor);
            
            char* valor = getEmptyString(strlen(t->valor));
            strcpy(valor, t->valor);
            adicionarSimbolo(INT, valor, label, escopoAtual);
        } else {
            printf("Redeclaracao da variavel %s, linha %d", t->valor, t->linha);
            getchar();
            exit(1);
        }
    } else if(a == EMPILHA_IF) {
        // Empilha if
        StackPush(&pilhaIfs, contaIfs);
        char* label = getEmptyString(MAX_LABEL);
        strcat(label, "if_");
        char idx[4];
        sprintf(idx, "%d", contaIfs);
        strcat(label, idx);
        printf("%s OS /0\n", label);
                
        // Cria escopo interno
        Escopo* internoIf = (Escopo*)malloc(sizeof(Escopo));
        initEscopo(internoIf);
        internoIf->anterior = escopoAtual;
        char* nomeEscopo = getEmptyString(MAX_LABEL);
        strcat(nomeEscopo, escopoAtual->nome);
        strcat(nomeEscopo, "_");
        strcat(nomeEscopo, label);
        internoIf->nome = nomeEscopo;
        insereEscopoInterno(escopoAtual, internoIf);
        
        free(label);
        
        // Muda o escopo atual
        escopoAtual = internoIf;
                
        // Incrementa o contador de ifs
        ++contaIfs;

        
    } else if(a == APOS_CONDICAO_IF) {
        stackElementT idIf = StackPop(&pilhaIfs);
        StackPush(&pilhaIfs, idIf);
        
        char* label = getEmptyString(MAX_LABEL);
        strcat(label, "fim_if_");
        char idx[4];
        sprintf(idx, "%d", idIf);
        strcat(label, idx);
        printf("JZ %s\n", label);
        free(label);
    } else if(a == TERMINA_IF) {
        stackElementT idIf = StackPop(&pilhaIfs);
        
        char* label = getEmptyString(MAX_LABEL);
        strcat(label, "fim_if_");
        char idx[4];
        sprintf(idx, "%d", idIf);
        strcat(label, idx);
        printf("%s OS /0\n", label); // fim_if_<id>
        free(label);
        
        // Volta ao escopo anterior
        escopoAtual = escopoAtual->anterior;
        
    } else if(a == TERMINA_IF_EMPILHA_ELSE) {
        // Desempilha if
        stackElementT ifId = StackPop(&pilhaIfs);
        
        // Empilha else
        StackPush(&pilhaElses, ifId);
        
        char* label = getEmptyString(MAX_LABEL);
        strcat(label, "fim_else_");
        char idx[4];
        sprintf(idx, "%d", ifId);
        strcat(label, idx);
        printf("JP %s\n", label);
        free(label);
                
        
        label = getEmptyString(MAX_LABEL);
        idx[0] = idx[1] = idx[2] = idx[3] = '\0';
        strcat(label, "fim_if_");
        sprintf(idx, "%d", ifId);
        strcat(label, idx);
        printf("%s OS /0\n", label); // fim_if_<id>
        free(label);
        
        label = getEmptyString(MAX_LABEL);
        strcat(label, "else_");
        strcat(label, idx);
        
        // Volta ao escopo anterior e cria um escopo para o else
        escopoAtual = escopoAtual->anterior;
        Escopo* internoElse = (Escopo*)malloc(sizeof(Escopo));
        initEscopo(internoElse);
        char* nomeEscopo = (char*)malloc(MAX_LABEL*sizeof(char));
        strcat(nomeEscopo, escopoAtual->nome);
        strcat(nomeEscopo, "_");
        strcat(nomeEscopo, label);
        internoElse->nome = nomeEscopo;
        insereEscopoInterno(escopoAtual, internoElse);
        internoElse->anterior = escopoAtual;
        free(label);
        
        // Muda o escopo atual
        escopoAtual = internoElse;
    } else if(a == TERMINA_ELSE) {
        stackElementT elseId = StackPop(&pilhaElses);
        
        char* label = getEmptyString(MAX_LABEL);
        strcat(label, "fim_else_");
        char idx[4];
        sprintf(idx, "%d", elseId);
        strcat(label, idx);
        printf("%s OS /0\n", label);
        free(label);
        
        // Volta ao escopo anterior
        escopoAtual = escopoAtual->anterior;
    } else if(a == EMPILHA_WHILE) {
        // Empilha while
        StackPush(&pilhaWhiles, contaWhiles);
        char* label = getEmptyString(MAX_LABEL);
        strcat(label, "while_");
        char idx[4];
        sprintf(idx, "%d", contaWhiles);
        strcat(label, idx);
        printf("%s OS /0\n", label);
        
        // Cria escopo interno
        Escopo* internoWhile = (Escopo*)malloc(sizeof(Escopo));
        initEscopo(internoWhile);
        internoWhile->anterior = escopoAtual;
        char* nomeEscopo = getEmptyString(MAX_LABEL);
        strcat(nomeEscopo, escopoAtual->nome);
        strcat(nomeEscopo, "_");
        strcat(nomeEscopo, label);
        internoWhile->nome = nomeEscopo;
        insereEscopoInterno(escopoAtual, internoWhile);
        
        // Muda o escopo atual
        escopoAtual = internoWhile;
        
        // Incrementa o contador de whiles
        ++contaWhiles;
    } else if(a == APOS_CONDICAO_WHILE) {
        stackElementT idWhile = StackPop(&pilhaWhiles);
        StackPush(&pilhaWhiles, idWhile);
        
        char* label = getEmptyString(MAX_LABEL);
        strcat(label, "fim_while_");
        char idx[4];
        sprintf(idx, "%d", idWhile);
        strcat(label, idx);
        printf("JZ %s\n", label);
        free(label);

    } else if(a == TERMINA_WHILE) {
        stackElementT idWhile = StackPop(&pilhaWhiles);
        
        char* label = getEmptyString(MAX_LABEL);
        strcat(label, "while_");
        char idx[4];
        sprintf(idx, "%d", idWhile);
        strcat(label, idx);
        printf("JP %s\n", label);
        free(label);
        
        label = getEmptyString(MAX_LABEL);
        strcat(label, "fim_while_");
        idx[0] = idx[1] = idx[2] = idx[3] = '\0';
        sprintf(idx, "%d", idWhile);
        strcat(label, idx);
        printf("%s OS /0\n", label);
        free(label);
        
        // Volta ao escopo anterior
        escopoAtual = escopoAtual->anterior;
    } else if(a == EMPILHA_OPERANDO) {
        StackTokenPush(&pilhaOperandos, t);
        
    } else if(a == EMPILHA_OPERADOR) {
        // Verifica se o topo da pilha contém 
        // algum operador do tipo +, -, * ou /
        Token* operador = 0;
        if(!StackTokenIsEmpty(&pilhaOperadores)) {
            operador = StackTokenPop(&pilhaOperadores);
            StackTokenPush(&pilhaOperadores, operador);
        }
        
        if(operador != 0) {
            if(!strcmp(operador->valor, "*") || !strcmp(operador->valor, "/") ||
               !strcmp(operador->valor, "+") || !strcmp(operador->valor, "-")) {
                // Executa a operação determinada pelo operador do topo da pilha
                Token* topo = StackTokenPop(&pilhaOperandos);
                Token* abaixo = StackTokenPop(&pilhaOperandos);
                operador = StackTokenPop(&pilhaOperadores);
                
                // Gera o código da operação e coloca a variável
                // temporária criada na pilha de operandos
                geraCodigoOperacao(topo, abaixo, operador);
                StackTokenPush(&pilhaOperadores, t);
            } else {
                StackTokenPush(&pilhaOperadores, t);
            }
        } else {
            StackTokenPush(&pilhaOperadores, t);
        }
        
        
    } else if(a == EMPILHA_OPERADOR_PRIORIDADE) {
        // Verifica se o topo da pilha contém
        // algum operador do tipo * ou /
        Token* operador = 0;
        if(!StackTokenIsEmpty(&pilhaOperadores)) {
            operador = StackTokenPop(&pilhaOperadores);
            StackTokenPush(&pilhaOperadores, operador);
        }
        
        if(operador != 0) {
            if(!strcmp(operador->valor, "*") || !strcmp(operador->valor, "/")) {
                // Executa a operação determinada pelo operador do topo da pilha
                Token* topo = StackTokenPop(&pilhaOperandos);
                Token* abaixo = StackTokenPop(&pilhaOperandos);
                operador = StackTokenPop(&pilhaOperadores);
                    
                // Gera o código da operação e coloca a variável
                // temporária criada na pilha de operandos
                geraCodigoOperacao(topo, abaixo, operador);
                StackTokenPush(&pilhaOperadores, t);
                
            } else {
                StackTokenPush(&pilhaOperadores, t);
            }
        } else {
            StackTokenPush(&pilhaOperadores, t);
        }
        
    } else if(a == SAIDA_EXPRESSAO) { 
        if(!StackTokenIsEmpty(&pilhaOperadores)) {
            // Executa a operação determinada pelo operador do topo da pilha
            Token* topo = 0;
            Token* abaixo = 0;
            Token* operador = 0;
            
            while(!StackTokenIsEmpty(&pilhaOperadores)) {
                topo     = StackTokenPop(&pilhaOperandos);
                abaixo   = StackTokenPop(&pilhaOperandos);
                operador = StackTokenPop(&pilhaOperadores);
                
                // Gera o código da operação e coloca a variável
                // temporária criada na pilha de operandos
                geraCodigoOperacao(topo, abaixo, operador);
            }
            
            // Ao final haverá ainda uma variável temporária
            // na pilha. Deve-se desempilhá-la
            StackTokenPop(&pilhaOperandos);
        } else if(!StackTokenIsEmpty(&pilhaOperandos)) {
            geraCodigoLoad(StackTokenPop(&pilhaOperandos));
        }
    } else if(a == GUARDA_LVALUE) {
        lvalue = (Token*) malloc(sizeof(Token));
        lvalue->coluna  = t->coluna;
        lvalue->linha   = t->linha;
        lvalue->tipo    = t->tipo;
        int i;
        for(i = 0; i < 256; ++i){
            lvalue->valor[i] = '\0';
        }
        
        strcat(lvalue->valor, t->valor);
    } else if(a == REALIZA_ATRIBUICAO) {
        char* label = recuperaLabel(lvalue);
        
        printf("MM %s\n", label);
        free(lvalue);
    }
}

AcaoSemantica decidirAcaoSemantica(Estado anterior, Estado atual) {
    if(atual == REST_COMANDO_ATR_2_AC) {
        int a;
        a = 1+4;
    }
    
    int i;
    for(i = 0; i < NUMRELACOES; ++i) {
        if((relacoes[i].anterior == anterior || relacoes[i].anterior == QUALQUER_ESTADO) && relacoes[i].atual == atual) {
            return relacoes[i].a;
        }
    }
    
    return 0;
}


// Funcoes que declaram as variaveis ao final do programa
void declararVC(Escopo* e) {    
    int i;
    for(i = 0; i < e->numInternos; ++i) {
        declararVC(e->internos[i]);
    }
    
    for(i = 0; i < e->numSimbolos; ++i) {
        printf("%s K /000\n", e->simbolos[i].label);
    }
}

void declararVariaveisConstantes() {
    int i;
    for(i = 0; i < escopos.tamanho; ++i) {
        declararVC(escopos.escopo[i]);
    }
    
    for(i = 0; i < constTab.tamanho; ++i) {
        printf("%s K /%X\n", constTab.constantes[i]->label, constTab.constantes[i]->valor);
    }
}