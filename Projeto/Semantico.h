//
//  Semantico.h
//  Compilador
//
//  Created by Renan Mendes on 12/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef SEMANTICO_H
#define SEMANTICO_H

#include "TabelaSimbolos.h"
#include "ConstantesSintatico.h"
#include "ConstantesSemantico.h"
#include "Token.h"
#include "stack.h"
#include "stackexp.h"
#include "stacktoken.h"

#define MAX_ESCOPOS 50
#define MAX_TOKENS 50

typedef struct {
    Token* tokens[MAX_TOKENS];
    int tamanho;
} Tokens;

typedef struct {
    Escopo* escopo[MAX_ESCOPOS];
    int tamanho;
} Escopos;

Tokens tokens;
Escopos escopos;
TabelaConstantes constTab;

static int contaWhiles = 0;
static int contaIfs = 0;
static int contaExp = 0;
static int contaTemp = 0;
static int contaComp = 0;

stackT pilhaIfs;
stackT pilhaElses;
stackT pilhaWhiles;

stackToken pilhaOperadores;
stackToken pilhaOperandos;
stackT pilhaExpressoes;


void executarAcaoSemantica(Estado anterior, Estado atual, Token* t);
AcaoSemantica decidirAcaoSemantica(Estado e, Estado atual);
void declararVariaveisConstantes();
void imprimeFim();



// Tabela de relação entre estados correntes e ações semânticas

typedef struct {
    Estado atual;
    Estado anterior;
    AcaoSemantica a;
} EstadoAcao;

static EstadoAcao relacoes[] = {
    
    {QUALQUER_ESTADO, PROGRAM_INICIAL, CABECALHO},
    
//  {ATUAL, ANTERIOR, ACAO_SEMANTICA}
    {PROGRAM_5, PROGRAM_4, PROGRAM_MAIN},
    {PROGRAM_6_AC, PROGRAM_5, PROGRAM_END_MAIN},
    {REST_DECL_VAR_SIMP_1_AC, REST_DECL_VAR_SIMP_INICIAL, VARIAVEL_NA_TABELA},
    {COMANDO_COND_1, COMANDO_COND_INICIAL, EMPILHA_IF},
    {COMANDO_COND_5, COMANDO_COND_4, APOS_CONDICAO_IF},
    {COMANDO_COND_7_AC, COMANDO_COND_5, TERMINA_IF},
    {COMANDO_COND_6, COMANDO_COND_5, TERMINA_IF_EMPILHA_ELSE},
    {COMANDO_COND_7_AC, COMANDO_COND_8, TERMINA_ELSE},
    {COMANDO_ITER_1, COMANDO_ITER_INICIAL, EMPILHA_WHILE},
    {COMANDO_ITER_5, COMANDO_ITER_4, APOS_CONDICAO_WHILE},
    {COMANDO_ITER_6_AC, COMANDO_ITER_5, TERMINA_WHILE},
    
    
    ////////////////// EXPRESSOES //////////////////////////
    // Caso receba um número ou id
    {FATOR_2_AC, FATOR_INICIAL, EMPILHA_OPERANDO},
    {FATOR_1_AC, FATOR_INICIAL, EMPILHA_OPERANDO},
    
    // Caso receba um "("
    // {FATOR_3, FATOR_INICIAL, EMPILHA_OPERADOR},
    
    // Caso receba um "*" ou "/"
    {TERMO_INICIAL, TERMO_1_AC, EMPILHA_OPERADOR_PRIORIDADE},
    
    // Caso receba um "+" ou "-"
    {EXPR_INICIAL, EXPR_1_AC, EMPILHA_OPERADOR},
    
    // Caso fim da expressão, quando desempilha o estado
    {COMANDO_RETORNO_2_AC, EXPR_1_AC, SAIDA_EXPRESSAO},
    {COMPARACAO_1, EXPR_1_AC, SAIDA_EXPRESSAO},
    {COMPARACAO_3_AC, EXPR_1_AC, SAIDA_EXPRESSAO},
    {FATOR_4, EXPR_1_AC, SAIDA_EXPRESSAO},
    {LISTA_EXPR_1_AC, EXPR_1_AC, SAIDA_EXPRESSAO},
    {PARAM_1_AC, EXPR_1_AC, SAIDA_EXPRESSAO},
    {REST_COMANDO_ATR_ARRAY_5_AC, EXPR_1_AC, SAIDA_EXPRESSAO},
    {REST_COMANDO_ATR_STRUCT_4_AC, EXPR_1_AC, SAIDA_EXPRESSAO},
    {REST_COMANDO_ATR_2_AC, EXPR_1_AC, SAIDA_EXPRESSAO},
    ////////////////////////////////////////////////////////
    
    //////////////////// ATRIBUICAO ////////////////////////
    {ATR_OU_CHAMADA_1, ATR_OU_CHAMADA_INICIAL, GUARDA_LVALUE},
    
    // Fim da atribuição, quando desempilha o estado
    {ATR_OU_CHAMADA_2_AC, REST_COMANDO_ATR_2_AC, REALIZA_ATRIBUICAO},
    ////////////////////////////////////////////////////////
    
    //////////////////// CONDICAO //////////////////////////
    // Caso receba um boolean ou id
    {FATOR_COND_2_AC, FATOR_COND_INICIAL, EMPILHA_OPERANDO_COND},
    
    // Caso receba "|"
    {CONDICAO_2, CONDICAO_1_AC, EMPILHA_OPERADOR_COND},
    
    // Caso receba "*"
    {TERMO_COND_INICIAL, TERMO_COND_1_AC, EMPILHA_OPERADOR_PRIORIDADE_COND},
    
    // Na comparação
    {COMPARACAO_2, COMPARACAO_1, GUARDA_TIPO_COMP},
    
    // Caso fim da comparação, desempilha o estado
    {FATOR_COND_2_AC, COMPARACAO_3_AC, REALIZA_COMPARACAO}
    
    // Caso fim da condicao, quando desempilha o estado
    ////////////////////////////////////////////////////////
};

#define NUMRELACOES (sizeof(relacoes)/sizeof(*relacoes))

#endif