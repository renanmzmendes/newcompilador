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
#define MAX_COMANDO 60

Escopo* escopoAtual;
Expressao* expressaoAtual;
Token* lvalue; // Para guardar a variável da atribuição
Token* varUltimaExp; // Para guardar a variável temporária da expressão
                       // da última expressao calculada
Token* tempComp; // Variável temporária da comparação
Token* opcomp; // Guarda o token do operador de comparação

char* getEmptyString(int length) {
    char* s = (char*)malloc(length*sizeof(char));
    int i;
    for(i = 0; i < length; ++i) {
        s[i] = '\0';
    }
    
    return s;
}

void escreve(char* comando) {
    printf("%s\n", comando);
    fprintf(out, "%s\n", comando);
}

void INICIO() {
    char* comando = getEmptyString(MAX_COMANDO);
    sprintf(comando, "@ /000");
    escreve(comando);
    free(comando);
}

void JN(char* labelTo, char* label) {
    char* comando = getEmptyString(MAX_COMANDO);
    sprintf(comando, "%s JN %s", label, labelTo);
    escreve(comando);
    free(comando);
}

void JZ(char* labelTo, char* label) {
    char* comando = getEmptyString(MAX_COMANDO);
    sprintf(comando, "%s JZ %s", label, labelTo);
    escreve(comando);
    free(comando);
}

void JP(char* labelTo, char* label) {
    char* comando = getEmptyString(MAX_COMANDO);
    sprintf(comando, "%s JP %s", label, labelTo);
    escreve(comando);
    free(comando);
}

void RS(char* labelTo, char* label) {
    char* comando = getEmptyString(MAX_COMANDO);
    sprintf(comando, "%s RS %s", label, labelTo);
    escreve(comando);
    free(comando);
}

void LV(int i, char* label) {
    char* comando = getEmptyString(MAX_COMANDO);
    sprintf(comando, "%s LV /%x", label, i);
    escreve(comando);
    free(comando);
}

void MM(char* labelTo, char* label) {
    char* comando = getEmptyString(MAX_COMANDO);
    sprintf(comando, "%s MM %s", label, labelTo);
    escreve(comando);
    free(comando);
}

void OS(char* label) {
    char* comando = getEmptyString(MAX_COMANDO);
    sprintf(comando, "%s OS /0", label);
    escreve(comando);
    free(comando);
}

void MINUS(char* operando, char* label) {
    char* comando = getEmptyString(MAX_COMANDO);
    sprintf(comando, "%s - %s", label, operando);
    escreve(comando);
    free(comando);
}

void PLUS(char* operando, char* label) {
    char* comando = getEmptyString(MAX_COMANDO);
    sprintf(comando, "%s + %s", label, operando);
    escreve(comando);
    free(comando);
}

void MULT(char* operando, char* label) {
    char* comando = getEmptyString(MAX_COMANDO);
    sprintf(comando, "%s * %s", label, operando);
    escreve(comando);
    free(comando);
}

void DIV(char* operando, char* label) {
    char* comando = getEmptyString(MAX_COMANDO);
    sprintf(comando, "%s / %s", label, operando);
    escreve(comando);
    free(comando);
}

void LD(char* labelFrom, char* label) {
    char* comando = getEmptyString(MAX_COMANDO);
    sprintf(comando, "%s LD %s", label, labelFrom);
    escreve(comando);
    free(comando);
}

void HM(char* label) {
    char* comando = getEmptyString(MAX_COMANDO);
    sprintf(comando, "%s HM /0", label);
    escreve(comando);
    free(comando);
}

void K(int valor, char* label) {
    char* comando = getEmptyString(MAX_COMANDO);
    sprintf(comando, "%s K /%X", label, valor);
    escreve(comando);
    free(comando);
}

void GD(char* label) {
    char* comando = getEmptyString(MAX_COMANDO);
    sprintf(comando, "%s GD /0", label);
    escreve(comando);
    free(comando);
}

void PD(char* label) {
    char* comando = getEmptyString(MAX_COMANDO);
    sprintf(comando, "%s PD /1", label);
    escreve(comando);
    free(comando);
}

void SC(char* subrotina, char* label) {
    char* comando = getEmptyString(MAX_COMANDO);
    sprintf(comando, "%s SC %s", label, subrotina);
    escreve(comando);
    free(comando);
}


void FIM() {
    char* comando = getEmptyString(MAX_COMANDO);
    sprintf(comando, "# main");
    escreve(comando);
    free(comando);
}

// Retorna o label/valor da variável temporária
char* criaVariavelTemporaria() {
    char* label = getEmptyString(MAX_LABEL);
    strcat(label, "TEMP");
    char* idx = getEmptyString(5);
    sprintf(idx, "%d", contaTemp);
    strcat(label, idx);
    adicionarSimbolo(ID, label, label, escopoAtual);
//    free(idx);
    
    contaTemp++;
    
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
    
    LD(labelAbaixo, "");
    
    char* comando = getEmptyString(MAX_COMANDO);
    sprintf(comando, "%s %s", operador->valor, labelTopo);
    escreve(comando);
    free(comando);
    
    MM(labelTemp, "");
    
    Token* t = (Token*) malloc(sizeof(Token));
    t->tipo = ID;
    strcpy(t->valor, labelTemp);
    
    StackTokenPush(&pilhaOperandos, t);
}

// O parâmetro i determina qual dos labels será gerado
// i < 0 : comp_false_<contaComp>
// i = 0 : fim_comp_<contaComp>
// i > 0 : comp_true_<contaComp>
char* labelComparacao(int i) {
    char* label = getEmptyString(MAX_LABEL);
    char* idx = getEmptyString(5);
    sprintf(idx, "%d", contaComp);
    
    if(i < 0) {
        strcat(label, "comp_false_");
    } else if(i > 0) {
        strcat(label, "comp_true_");
    } else {
        strcat(label, "fim_comp_");
    }
    
    strcat(label, idx);
    free(idx);
    
    return label;
}

void geraComparacaoMaior() {
    char* labelFalse = labelComparacao(-1);
    char* labelTrue = labelComparacao(1);
    char* labelFim = labelComparacao(0);
    
    JN(labelTrue, "");
    LV(0, labelFalse);
    JP(labelFim, "");
    LV(1, labelTrue);
    OS(labelFim);
    
//    free(labelFalse);
//    free(labelTrue);
//    free(labelFim);
    
}

void geraComparacaoMenor() {
    char* labelFalse = labelComparacao(-1);
    char* labelTrue = labelComparacao(1);
    char* labelFim = labelComparacao(0);
    
    JZ(labelFalse, "");
    JN(labelFalse, "");
    LV(1, labelTrue);
    JP(labelFim, "");
    LV(0, labelFalse);
    OS(labelFim);
    
//    free(labelFalse);
//    free(labelTrue);
//    free(labelFim);
}

void geraComparacaoIgual() {
    char* labelFalse = labelComparacao(-1);
    char* labelTrue = labelComparacao(1);
    char* labelFim = labelComparacao(0);
    
    JZ(labelTrue, "");
    LV(0, labelFalse);
    JP(labelFim, "");
    LV(1, labelTrue);
    OS(labelFim);
    
//    free(labelFalse);
//    free(labelTrue);
//    free(labelFim);
}

void geraCodigoLoad(Token* var) {
    char* labelOperando = recuperaLabel(var);
    LD(labelOperando, "");
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
    
    if(a == CABECALHO){
        INICIO();
        JP("main", "");
        
    } else if(a == PROGRAM_MAIN) {
        // Leu a primeira linha do main
        Escopo* mainScope = (Escopo*) malloc(sizeof(Escopo));
        initEscopo(mainScope);
        mainScope->anterior = 0;
        mainScope->nome = "main";
        
        // Adiciona escopo de primeiro nível
        escopos.escopo[escopos.tamanho] = mainScope;
        escopos.tamanho++;
        
        escopoAtual = mainScope;
        OS("main");
        
    } else if(a == PROGRAM_END_MAIN) {
        // Terminou o main
        HM("");
        
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
        OS(label);
                
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
        JZ(label, "");
        free(label);
    } else if(a == TERMINA_IF) {
        stackElementT idIf = StackPop(&pilhaIfs);
        
        char* label = getEmptyString(MAX_LABEL);
        strcat(label, "fim_if_");
        char idx[4];
        sprintf(idx, "%d", idIf);
        strcat(label, idx);
        OS(label);
        free(label);
        
        // Volta ao escopo anterior
        escopoAtual = escopoAtual->anterior;
        
    } else if(a == TERMINA_IF_EMPILHA_ELSE) {
        // Desempilha if
        stackElementT ifId = StackPop(&pilhaIfs);
        
        // Empilha else com mesmo id
        StackPush(&pilhaElses, ifId);
        
        char* label = getEmptyString(MAX_LABEL);
        strcat(label, "fim_else_");
        char idx[4];
        sprintf(idx, "%d", ifId);
        strcat(label, idx);
        JP(label, "");
        free(label);
                
        
        label = getEmptyString(MAX_LABEL);
        idx[0] = idx[1] = idx[2] = idx[3] = '\0';
        strcat(label, "fim_if_");
        sprintf(idx, "%d", ifId);
        strcat(label, idx);
        OS(label);
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
        OS(label);
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
        OS(label);
        
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
        free(label);
        
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
        JZ(label, "");
        free(label);

    } else if(a == TERMINA_WHILE) {
        stackElementT idWhile = StackPop(&pilhaWhiles);
        
        char* label = getEmptyString(MAX_LABEL);
        strcat(label, "while_");
        char idx[4];
        sprintf(idx, "%d", idWhile);
        strcat(label, idx);
        JP(label, "");
        free(label);
        
        label = getEmptyString(MAX_LABEL);
        strcat(label, "fim_while_");
        idx[0] = idx[1] = idx[2] = idx[3] = '\0';
        sprintf(idx, "%d", idWhile);
        strcat(label, idx);
        OS(label);
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
            
        } else if(!StackTokenIsEmpty(&pilhaOperandos)) {
            Token* temp = StackTokenPop(&pilhaOperandos);
            StackTokenPush(&pilhaOperandos, temp);
            geraCodigoLoad(temp);
        }
        
        // Ao final haverá ainda uma variável (temporária ou não(caso a=b ou ainda a>b, a<b, a==b))
        // na pilha. Guarda-se-a em varUltimaExp
        Token* temp = StackTokenPop(&pilhaOperandos);
        if(varUltimaExp != 0) free(varUltimaExp); // Deleta a variável anterior
        varUltimaExp = (Token*) malloc(sizeof(Token));
        varUltimaExp->tipo = ID;
        strcpy(varUltimaExp->valor, temp->valor);

    } else if(a == GUARDA_LVALUE) {
        lvalue = (Token*) malloc(sizeof(Token));
        lvalue->coluna  = t->coluna;
        lvalue->linha   = t->linha;
        lvalue->tipo    = t->tipo;
        int i;
        for(i = 0; i < 256; ++i){
            lvalue->valor[i] = '\0';
        }
        
        strcpy(lvalue->valor, t->valor);
    } else if(a == REALIZA_ATRIBUICAO) {
        char* label = recuperaLabel(lvalue);
        
        MM(label, "");
        free(lvalue);
    } else if(a == GUARDA_TIPO_COMP) {
        if(opcomp != 0) free(opcomp);
        opcomp = (Token*) malloc(sizeof(Token));
        opcomp->tipo = ID;
        strcpy(opcomp->valor, t->valor);
        
        // Guarda na memória a última expressão
        char* label = criaVariavelTemporaria();
        MM(label, "");
        tempComp = (Token*) malloc(sizeof(Token));
        tempComp->tipo = ID;
        strcpy(tempComp->valor, label);

//        free(label);
        
    } else if(a == REALIZA_COMPARACAO) {
        MINUS(tempComp->valor, "");
        
        if(!strcmp(opcomp->valor, ">")) {
            geraComparacaoMaior();
            
        } else if(!strcmp(opcomp->valor, "<")) {
            geraComparacaoMenor();
            
        } else if(!strcmp(opcomp->valor, "==")) {
            geraComparacaoIgual();
            
        }
        
        contaComp++;
        free(opcomp);
    } else if(a == OUTPUT) {
        SC("output", "");
        
    } else if(a == INPUT) {
        char* labelVar = recuperaLabel(t);

        SC("input", "");
        MM(labelVar, "");
    }
}

AcaoSemantica decidirAcaoSemantica(Estado anterior, Estado atual) {    
    int i;
    for(i = 0; i < NUMRELACOES; ++i) {
        if((relacoes[i].anterior == anterior || relacoes[i].anterior == QUALQUER_ESTADO) && (relacoes[i].atual == atual || relacoes[i].atual == QUALQUER_ESTADO)) {
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
        K(0, e->simbolos[i].label);
    }
}

void declararVariaveisConstantes() {
    int i;
    for(i = 0; i < escopos.tamanho; ++i) {
        declararVC(escopos.escopo[i]);
    }
    
    for(i = 0; i < constTab.tamanho; ++i) {
        K(constTab.constantes[i]->valor, constTab.constantes[i]->label);
    }
}

void escreveFuncoesMvn() {    
    // OUTPUT
    // Instruções:
    // 1. A variável já vai estar no acumulador quando
    //    a subrotina for chamada
    // 2. A subroutine call (SC) é feita para o label
    //    "output"
	
	OS("output");
	MM("NUM", "");
	LD("NUM", "");
	OS("w");
	JZ("fim_w", "");
	DIV("Ka", "");
	MM("NUM_PROX", "");
	MULT("Ka", "");			// multiplica por Ka
	MM("NUM_TEMP", "");
	LD("K9K", "");			// K9K deve existir
	PLUS("SP", "");
	PLUS("SP_INICIO", "");
	MM("EMPILHA", "");
	LD("SP", "");
	PLUS("K2", "");
	MM("SP", "");
	LD("NUM", "");
	MINUS("NUM_TEMP", "");
	OS("EMPILHA");
	LD("NUM_PROX", "");
	MM("NUM", "");
	JP("w", "");
	OS("fim_w");
	OS("w1");
	LD("SP", "");
	JZ("fw0", "");
	LD("SP", "");
	MINUS("K2", "");
	MM("SP", "");
	LD("K8K", "");
	PLUS("SP", "");
	PLUS("SP_INICIO", "");
	MM("Des", "");
	OS("Des");
	PLUS("K48", "");
	PD("");
	JP("w1", "");
	OS("fw0");
	RS("output", "");
	
    // INPUT
    // Instruções:
    // 1. Antes de fazer a chamada de subrotina (SC)
    //    o programa já faz os comandos GD /0 e grava
    //    o valor na variável correspondente (MM <label da variavel>)
    //    Lembre que a sintaxe para comando de entrada é
    //    "input a" para gravar o input na variável a"
	
	OS("input");
	
	// 0-8 >
	LV(48, "");
	PD("");
	LV(45, "");
	PD("");
	LV(56, "");
	PD("");
	LV(62, "");
	PD("");
	LV(32, "");
	PD("");
	
	GD("");
	DIV("K256", "");
	MINUS("K48", "");
	RS("input", "");
    
    insereConstante(0x100, &constTab);
    insereConstante(0x30, &constTab);
    insereConstante(2, &constTab);
	//Constantes e variáveis utilizadas e nescessárias
	/*
	 para o output
	 NUM		K /000
	 NUM_PROX	K /000
	 NUM_TEMP	K /000
	 SP			K /0000
	 SP_INICIO	K /0F00
	 K2			K /2
	 Ka			K /A
	 K9K		K /9000
	 K8K		K /8000
	 
	 para o input
	 K100		K /100
	 K30		K /30	 
	 */
	
}

void imprimeFim() {
    escreve("NUM        K /0000");
    escreve("NUM_PROX   K /0000");
    escreve("NUM_TEMP   K /0000");
    escreve("SP         K /0000");
    escreve("SP_INICIO  K /0F00");
    escreve("Ka         K /000A");
    escreve("K9K        K /9000");
    escreve("K8K        K /8000");
    FIM();
}
