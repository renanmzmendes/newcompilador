//
//  ConstantesSemantico.h
//  Compilador
//
//  Created by Renan Mendes on 12/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CONSTANTES_SEMANTICO_H
#define CONSTANTES_SEMANTICO_H

typedef enum {
    CABECALHO = 1,
    PROGRAM_MAIN,
    PROGRAM_END_MAIN,
    VARIAVEL_NA_TABELA,
    
    EMPILHA_IF,
    APOS_CONDICAO_IF,
    TERMINA_IF,
    TERMINA_IF_EMPILHA_ELSE,
    TERMINA_ELSE,
    
    EMPILHA_WHILE,
    APOS_CONDICAO_WHILE,
    TERMINA_WHILE,
    
    EMPILHA_OPERANDO,
    EMPILHA_OPERADOR,
    EMPILHA_OPERADOR_PRIORIDADE,
    SAIDA_EXPRESSAO,
    
    //EMPILHA_OPERANDO_COND,
    //EMPILHA_OPERADOR_COND,
    //EMPILHA_OPERADOR_PRIORIDADE_COND,
    
    //EMPILHA_EXPRESSAO,
    //RESOLVE_EXPRESSAO,
    
    GUARDA_LVALUE,
    REALIZA_ATRIBUICAO,
    
    REALIZA_COMPARACAO,
    GUARDA_TIPO_COMP,
    
    OUTPUT,
    INPUT
} AcaoSemantica;

#endif