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
    PROGRAM_MAIN = 1,
    PROGRAM_END_MAIN,
    FUNCAO_HEADER,
    TIPO_NA_PILHA,
    VARIAVEL_NA_TABELA,
    
    EMPILHA_IF,
    APOS_CONDICAO_IF,
    TERMINA_IF,
    TERMINA_IF_EMPILHA_ELSE,
    TERMINA_ELSE,
    
    EMPILHA_WHILE,
    APOS_CONDICAO_WHILE,
    TERMINA_WHILE,
    
    IMPRIMIR,
    OBTER_ENTRADA,
    
    EMPILHA_OPERANDO,
    EMPILHA_OPERADOR,
    EMPILHA_EXPRESSAO,
    RESOLVE_EXPRESSAO,
    
    GUARDA_LVALUE,
    REALIZA_ATRIBUICAO
    
//    ACRESCENTA_OPERANDO_OPERADOR,
//    EMPILHAR_NOVA_EXPRESSAO,
//    TRADUZIR_EXPRESSAO
    
} AcaoSemantica;

#endif