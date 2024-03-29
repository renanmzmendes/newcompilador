//
//  TabelasSintatico.h
//  Compilador
//
//  Created by Renan Mendes on 10/30/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef TABELAS_SINTATICO_H
#define TABELAS_SINTATICO_H

#include "Token.h"
#include "ConstantesSintatico.h"

typedef struct {
	Estado estadoOrigem;
    tipoToken tipo;
	const char* token;
	Estado estadoDestino;
    
} transicao;

static transicao transicoes[] = {
    // ATR_OU_CHAMADA
    {ATR_OU_CHAMADA_INICIAL, ID, "", ATR_OU_CHAMADA_1},
    
    // BOOLEAN
    {BOOLEAN_INICIAL, RESERVED_KEYWORD, "false", BOOLEAN_1_AC},
    {BOOLEAN_INICIAL, RESERVED_KEYWORD, "true", BOOLEAN_1_AC},
    
    // COMANDO_COND
    {COMANDO_COND_INICIAL, RESERVED_KEYWORD, "if", COMANDO_COND_1},
    {COMANDO_COND_1, SPECIAL_CHARACTER, "(", COMANDO_COND_2},
    {COMANDO_COND_3, SPECIAL_CHARACTER, ")", COMANDO_COND_4},
    {COMANDO_COND_4, PONTUACAO, "\n", COMANDO_COND_5},
    {COMANDO_COND_5, RESERVED_KEYWORD, "else", COMANDO_COND_6},
    {COMANDO_COND_5, RESERVED_KEYWORD, "elsif", COMANDO_COND_1},
    {COMANDO_COND_5, RESERVED_KEYWORD, "end", COMANDO_COND_7_AC},
    {COMANDO_COND_6, PONTUACAO, "\n", COMANDO_COND_8},
    {COMANDO_COND_8, RESERVED_KEYWORD, "end", COMANDO_COND_7_AC},
    
    // COMANDO_ENTR
    {COMANDO_ENTR_INICIAL, RESERVED_KEYWORD, "input", COMANDO_ENTR_1},
    
    // COMANDO_ITER
    {COMANDO_ITER_INICIAL, RESERVED_KEYWORD, "while", COMANDO_ITER_1},
    {COMANDO_ITER_1, SPECIAL_CHARACTER, "(", COMANDO_ITER_2},
    {COMANDO_ITER_3, SPECIAL_CHARACTER, ")", COMANDO_ITER_4},
    {COMANDO_ITER_4, PONTUACAO, "\n", COMANDO_ITER_5},
    {COMANDO_ITER_5, RESERVED_KEYWORD, "end", COMANDO_ITER_6_AC},
    
    // COMANDO_RETORNO
    {COMANDO_RETORNO_INICIAL, RESERVED_KEYWORD, "return", COMANDO_RETORNO_1},
    
    // COMANDO_SAIDA
    {COMANDO_SAIDA_INICIAL, RESERVED_KEYWORD, "output", COMANDO_SAIDA_1},
    
    // COMANDO (só tem chamada de submáquina)
    
    // COMPARACAO
    {COMPARACAO_1, SPECIAL_CHARACTER, ">", COMPARACAO_2},
    {COMPARACAO_1, SPECIAL_CHARACTER, ">=", COMPARACAO_2},
    {COMPARACAO_1, SPECIAL_CHARACTER, "==", COMPARACAO_2},
    {COMPARACAO_1, SPECIAL_CHARACTER, "<", COMPARACAO_2},
    {COMPARACAO_1, SPECIAL_CHARACTER, "<=", COMPARACAO_2},
    {COMPARACAO_1, SPECIAL_CHARACTER, "!=", COMPARACAO_2},
    
    // CONDICAO
    {CONDICAO_1_AC, SPECIAL_CHARACTER, "|", CONDICAO_2},
    
    // DECL_FUNCAO
    {DECL_FUNCAO_1, ID, "", DECL_FUNCAO_2},
    {DECL_FUNCAO_2, SPECIAL_CHARACTER, "(", DECL_FUNCAO_3},
    {DECL_FUNCAO_3, SPECIAL_CHARACTER, ")", DECL_FUNCAO_5},
    {DECL_FUNCAO_4, SPECIAL_CHARACTER, ")", DECL_FUNCAO_5},
    {DECL_FUNCAO_5, PONTUACAO, "\n", DECL_FUNCAO_6},
    {DECL_FUNCAO_6, RESERVED_KEYWORD, "end", DECL_FUNCAO_7_AC},
    
    // DECL_OU_COMANDO
    {DECL_OU_COMANDO_INICIAL, PONTUACAO, "\n", DECL_OU_COMANDO_2_AC},
    {DECL_OU_COMANDO_1, PONTUACAO, "\n", DECL_OU_COMANDO_2_AC},
    
    // DECL_PARAMS
    {DECL_PARAMS_2_AC, PONTUACAO, ",", DECL_PARAMS_INICIAL},
    {DECL_PARAMS_1, ID, "", DECL_PARAMS_2_AC},
    
    // DECL_VAR_HET
    {DECL_VAR_HET_INICIAL, RESERVED_KEYWORD, "struct", DECL_VAR_HET_1},
    {DECL_VAR_HET_1, ID, "", DECL_VAR_HET_2},
    {DECL_VAR_HET_2, PONTUACAO, "\n", DECL_VAR_HET_3},
    {DECL_VAR_HET_3, RESERVED_KEYWORD, "end", DECL_VAR_HET_4_AC},

        
    // EXPR
    {EXPR_1_AC, SPECIAL_CHARACTER, "+", EXPR_INICIAL},
    {EXPR_1_AC, SPECIAL_CHARACTER, "-", EXPR_INICIAL},
    
    // FATOR_COND
    {FATOR_COND_INICIAL, SPECIAL_CHARACTER, "!", FATOR_COND_1},
    {FATOR_COND_1, SPECIAL_CHARACTER, "(", FATOR_COND_3},
    {FATOR_COND_4, SPECIAL_CHARACTER, ")", FATOR_COND_2_AC},
    
    // FATOR
    {FATOR_INICIAL, SPECIAL_CHARACTER, "(", FATOR_3},
    {FATOR_INICIAL, NUM, "", FATOR_2_AC},
    {FATOR_INICIAL, ID, "", FATOR_1_AC},
    {FATOR_4, SPECIAL_CHARACTER, ")", FATOR_2_AC},
    
    // ID (só tem chamada de submáquina)
    
    // LISTA_EXPR
    {LISTA_EXPR_1_AC, PONTUACAO, ",", LISTA_EXPR_INICIAL},
    
    // LISTA_MEM
    {LISTA_MEM_1_AC, PONTUACAO, ",", LISTA_MEM_INICIAL},
    {LISTA_MEM_INICIAL, ID, "", LISTA_MEM_1_AC},
    
    // NUM_REAL (não precisa fazer transição pra essa submáquina pq virá como NUM do léxico)
    // NUM (vai ser o próprio Token passado pelo léxico)
    
    // PARAM (só tem chamada de submáquina)
    
    // PROGRAM
    {PROGRAM_1, PONTUACAO, "\n", PROGRAM_INICIAL},
    {PROGRAM_INICIAL, RESERVED_KEYWORD, "main", PROGRAM_2},
    {PROGRAM_INICIAL, PONTUACAO, "\n", PROGRAM_INICIAL},
    {PROGRAM_2, SPECIAL_CHARACTER, "(", PROGRAM_3},
    {PROGRAM_3, SPECIAL_CHARACTER, ")", PROGRAM_4},
    {PROGRAM_4, PONTUACAO, "\n", PROGRAM_5},
    {PROGRAM_5, RESERVED_KEYWORD, "end", PROGRAM_6_AC},
    {PROGRAM_6_AC, PONTUACAO, "\n", PROGRAM_6_AC},
    
    // REST_ACESSO_STRUCT
    {REST_ACESSO_STRUCT_INICIAL, PONTUACAO, ".", REST_ACESSO_STRUCT_1},
    {REST_ACESSO_STRUCT_1, ID, "", REST_ACESSO_STRUCT_2_AC},
    
    // REST_ACESSOR_VETOR
    {REST_ACESSO_VETOR_INICIAL, SPECIAL_CHARACTER, "[", REST_ACESSO_VETOR_1},
    {REST_ACESSO_VETOR_1, NUM, "", REST_ACESSO_VETOR_2},
    {REST_ACESSO_VETOR_2, SPECIAL_CHARACTER, "]", REST_ACESSO_VETOR_3_AC},
    
    // REST_CHAMADA_FUNCAO
    {REST_CHAMADA_FUNCAO_INICIAL, SPECIAL_CHARACTER, "(", REST_CHAMADA_FUNCAO_1},
    {REST_CHAMADA_FUNCAO_1, SPECIAL_CHARACTER, ")", REST_CHAMADA_FUNCAO_3_AC},
    {REST_CHAMADA_FUNCAO_2, PONTUACAO, ",", REST_CHAMADA_FUNCAO_4},
    {REST_CHAMADA_FUNCAO_2, SPECIAL_CHARACTER, ")", REST_CHAMADA_FUNCAO_3_AC},
    
    // REST_COMANDO_ATR
    {REST_COMANDO_ATR_INICIAL, SPECIAL_CHARACTER, "=", REST_COMANDO_ATR_1},
    
    // REST_COMANDO_ATR_ARRAY
    {REST_COMANDO_ATR_ARRAY_INICIAL, SPECIAL_CHARACTER, "[", REST_COMANDO_ATR_ARRAY_1},
    {REST_COMANDO_ATR_ARRAY_1, NUM, "", REST_COMANDO_ATR_ARRAY_2},
    {REST_COMANDO_ATR_ARRAY_2, SPECIAL_CHARACTER, "]", REST_COMANDO_ATR_ARRAY_3},
    {REST_COMANDO_ATR_ARRAY_3, SPECIAL_CHARACTER, "=", REST_COMANDO_ATR_ARRAY_4},
    
    // REST_COMANDO_ATR_STRUCT
    {REST_COMANDO_ATR_STRUCT_INICIAL, PONTUACAO, ".", REST_COMANDO_ATR_STRUCT_1},
    {REST_COMANDO_ATR_STRUCT_1, ID, "", REST_COMANDO_ATR_STRUCT_2},
    {REST_COMANDO_ATR_STRUCT_2, SPECIAL_CHARACTER, "=", REST_COMANDO_ATR_STRUCT_3},
    
    // REST_DECL_VAR_HOM
    {REST_DECL_VAR_HOM_INICIAL, SPECIAL_CHARACTER, "[", REST_DECL_VAR_HOM_1},
    {REST_DECL_VAR_HOM_1, NUM, "", REST_DECL_VAR_HOM_2},
    {REST_DECL_VAR_HOM_2, SPECIAL_CHARACTER, "]", REST_DECL_VAR_HOM_3},
    {REST_DECL_VAR_HOM_3, ID, "", REST_DECL_VAR_HOM_4_AC},
    
    // REST_DECL_VAR_SIMP
    {REST_DECL_VAR_SIMP_INICIAL, ID, "", REST_DECL_VAR_SIMP_1_AC},
    
    // TERMO_COND
    {TERMO_COND_1_AC, SPECIAL_CHARACTER, "&", TERMO_COND_INICIAL},
    
    // TERMO
    {TERMO_1_AC, SPECIAL_CHARACTER, "*", TERMO_INICIAL},
    {TERMO_1_AC, SPECIAL_CHARACTER, "/", TERMO_INICIAL},
    {TERMO_1_AC, SPECIAL_CHARACTER, "%", TERMO_INICIAL},
    
    // TIPO
    {TIPO_INICIAL, RESERVED_KEYWORD, "void", TIPO_1_AC},
    {TIPO_INICIAL, RESERVED_KEYWORD, "boolean", TIPO_1_AC},
    {TIPO_INICIAL, RESERVED_KEYWORD, "char", TIPO_1_AC},
    {TIPO_INICIAL, RESERVED_KEYWORD, "float", TIPO_1_AC},
    {TIPO_INICIAL, RESERVED_KEYWORD, "int", TIPO_1_AC}
};

#define NUMTRANSICOES (sizeof(transicoes)/sizeof(*transicoes))

typedef struct {
    Estado estadoOrigem;
    tipoToken tipo;
    char* token;
    Estado estadoDestino;
    Estado estadoRetorno;
} chamadaSubmaquina;

// Na definição desta tabela de chamada de submáquina, introduzimos o token auxiliar
// NDEF que indica que a submáquina terá de ser chamada sem ser necessário olhar
// o tipo do token atual
static chamadaSubmaquina chamadas[] = {
    // ATR_OU_CHAMADA
    {ATR_OU_CHAMADA_1, SPECIAL_CHARACTER, "(", REST_CHAMADA_FUNCAO_INICIAL, ATR_OU_CHAMADA_2_AC},
    {ATR_OU_CHAMADA_1, SPECIAL_CHARACTER, "=", REST_COMANDO_ATR_INICIAL, ATR_OU_CHAMADA_2_AC},
    {ATR_OU_CHAMADA_1, SPECIAL_CHARACTER, "[", REST_COMANDO_ATR_ARRAY_INICIAL, ATR_OU_CHAMADA_2_AC},
    {ATR_OU_CHAMADA_1, PONTUACAO, ".", REST_COMANDO_ATR_STRUCT_INICIAL, ATR_OU_CHAMADA_2_AC},
    
    // BOOLEAN (não tem chamada de submáquina)
    
    // COMANDO_COND
    {COMANDO_COND_2, NDEF, "", CONDICAO_INICIAL, COMANDO_COND_3},
    {COMANDO_COND_5, NDEF, "", DECL_OU_COMANDO_INICIAL, COMANDO_COND_5},
    {COMANDO_COND_8, NDEF, "", DECL_OU_COMANDO_INICIAL, COMANDO_COND_8},
    
    // COMANDO_ENTR
    {COMANDO_ENTR_1, NDEF, "", LISTA_MEM_INICIAL, COMANDO_ENTR_2_AC},
    
    // COMANDO_ITER
    {COMANDO_ITER_2, NDEF, "", CONDICAO_INICIAL, COMANDO_ITER_3},
    {COMANDO_ITER_5, NDEF, "", DECL_OU_COMANDO_INICIAL, COMANDO_ITER_5},
    
    // COMANDO_RETORNO
    {COMANDO_RETORNO_1, NDEF, "", EXPR_INICIAL, COMANDO_RETORNO_2_AC},
    
    // COMANDO_SAIDA
    {COMANDO_SAIDA_1, NDEF, "", LISTA_EXPR_INICIAL, COMANDO_SAIDA_2_AC},
    
    // COMANDO
    {COMANDO_INICIAL, RESERVED_KEYWORD, "input", COMANDO_ENTR_INICIAL, COMANDO_1_AC},
    {COMANDO_INICIAL, RESERVED_KEYWORD, "output", COMANDO_SAIDA_INICIAL, COMANDO_1_AC},
    {COMANDO_INICIAL, RESERVED_KEYWORD, "return", COMANDO_RETORNO_INICIAL, COMANDO_1_AC},
    {COMANDO_INICIAL, RESERVED_KEYWORD, "while", COMANDO_ITER_INICIAL, COMANDO_1_AC},
    {COMANDO_INICIAL, RESERVED_KEYWORD, "if", COMANDO_COND_INICIAL, COMANDO_1_AC},
    {COMANDO_INICIAL, ID, "", ATR_OU_CHAMADA_INICIAL, COMANDO_1_AC},
//    {COMANDO_INICIAL, PONTUACAO, "\n", }
    
    // COMPARACAO
    {COMPARACAO_INICIAL, NDEF, "", EXPR_INICIAL, COMPARACAO_1},
    {COMPARACAO_2, NDEF, "", EXPR_INICIAL, COMPARACAO_3_AC},
    
    // CONDICAO
    {CONDICAO_INICIAL, NDEF, "", TERMO_COND_INICIAL, CONDICAO_1_AC},
    {CONDICAO_2, NDEF, "", TERMO_COND_INICIAL, CONDICAO_1_AC},
    
    // DECL_FUNCAO
    {DECL_FUNCAO_INICIAL, NDEF, "", TIPO_INICIAL, DECL_FUNCAO_1},
    {DECL_FUNCAO_3, RESERVED_KEYWORD, "void", DECL_PARAMS_INICIAL, DECL_FUNCAO_4},
    {DECL_FUNCAO_3, RESERVED_KEYWORD, "int", DECL_PARAMS_INICIAL, DECL_FUNCAO_4},
    {DECL_FUNCAO_3, RESERVED_KEYWORD, "float", DECL_PARAMS_INICIAL, DECL_FUNCAO_4},
    {DECL_FUNCAO_3, RESERVED_KEYWORD, "char", DECL_PARAMS_INICIAL, DECL_FUNCAO_4},
    {DECL_FUNCAO_3, RESERVED_KEYWORD, "boolean", DECL_PARAMS_INICIAL, DECL_FUNCAO_4},
    {DECL_FUNCAO_6, ID, "", DECL_OU_COMANDO_INICIAL, DECL_FUNCAO_6},
    {DECL_FUNCAO_6, RESERVED_KEYWORD, "if", DECL_OU_COMANDO_INICIAL, DECL_FUNCAO_6},
    {DECL_FUNCAO_6, RESERVED_KEYWORD, "while", DECL_OU_COMANDO_INICIAL, DECL_FUNCAO_6},
    {DECL_FUNCAO_6, RESERVED_KEYWORD, "input", DECL_OU_COMANDO_INICIAL, DECL_FUNCAO_6},
    {DECL_FUNCAO_6, RESERVED_KEYWORD, "output", DECL_OU_COMANDO_INICIAL, DECL_FUNCAO_6},
    {DECL_FUNCAO_6, RESERVED_KEYWORD, "return", DECL_OU_COMANDO_INICIAL, DECL_FUNCAO_6},
    {DECL_FUNCAO_6, RESERVED_KEYWORD, "int", DECL_OU_COMANDO_INICIAL, DECL_FUNCAO_6},
    {DECL_FUNCAO_6, RESERVED_KEYWORD, "float", DECL_OU_COMANDO_INICIAL, DECL_FUNCAO_6},
    {DECL_FUNCAO_6, RESERVED_KEYWORD, "char", DECL_OU_COMANDO_INICIAL, DECL_FUNCAO_6},
    {DECL_FUNCAO_6, RESERVED_KEYWORD, "boolean", DECL_OU_COMANDO_INICIAL, DECL_FUNCAO_6},
    {DECL_FUNCAO_6, PONTUACAO, "\n", DECL_OU_COMANDO_INICIAL, DECL_FUNCAO_6},
    
    
    // DECL_OU_COMANDO
    {DECL_OU_COMANDO_INICIAL, RESERVED_KEYWORD, "input", COMANDO_INICIAL, DECL_OU_COMANDO_1},
    {DECL_OU_COMANDO_INICIAL, RESERVED_KEYWORD, "output", COMANDO_INICIAL, DECL_OU_COMANDO_1},
    {DECL_OU_COMANDO_INICIAL, RESERVED_KEYWORD, "return", COMANDO_INICIAL, DECL_OU_COMANDO_1},
    {DECL_OU_COMANDO_INICIAL, RESERVED_KEYWORD, "while", COMANDO_INICIAL, DECL_OU_COMANDO_1},
    {DECL_OU_COMANDO_INICIAL, RESERVED_KEYWORD, "if", COMANDO_INICIAL, DECL_OU_COMANDO_1},
    {DECL_OU_COMANDO_INICIAL, ID, "", COMANDO_INICIAL, DECL_OU_COMANDO_1},
    {DECL_OU_COMANDO_INICIAL, RESERVED_KEYWORD, "int", DECL_VAR_SIMP_OU_HOM_INICIAL, DECL_OU_COMANDO_1},
    {DECL_OU_COMANDO_INICIAL, RESERVED_KEYWORD, "float", DECL_VAR_SIMP_OU_HOM_INICIAL, DECL_OU_COMANDO_1},
    {DECL_OU_COMANDO_INICIAL, RESERVED_KEYWORD, "char", DECL_VAR_SIMP_OU_HOM_INICIAL, DECL_OU_COMANDO_1},
    {DECL_OU_COMANDO_INICIAL, RESERVED_KEYWORD, "boolean", DECL_VAR_SIMP_OU_HOM_INICIAL, DECL_OU_COMANDO_1},
    {DECL_OU_COMANDO_INICIAL, RESERVED_KEYWORD, "struct", DECL_VAR_HET_INICIAL, DECL_OU_COMANDO_1},
    
    // DECL_PARAMS
    {DECL_PARAMS_INICIAL, NDEF, "", TIPO_INICIAL, DECL_PARAMS_1},
    
    // DECL_VAR_SIMP_OU_HOM
    {DECL_VAR_SIMP_OU_HOM_INICIAL, NDEF, "", TIPO_INICIAL, DECL_VAR_SIMP_OU_HOM_1},
    {DECL_VAR_SIMP_OU_HOM_1, SPECIAL_CHARACTER, "[", REST_DECL_VAR_HOM_INICIAL, DECL_VAR_SIMP_OU_HOM_2_AC},
    {DECL_VAR_SIMP_OU_HOM_1, ID, "", REST_DECL_VAR_SIMP_INICIAL, DECL_VAR_SIMP_OU_HOM_2_AC},
    
    // DECL_VAR_HET
    {DECL_VAR_HET_3, RESERVED_KEYWORD, "int", DECL_VAR_SIMP_OU_HOM_INICIAL, DECL_VAR_HET_2},
    {DECL_VAR_HET_3, RESERVED_KEYWORD, "float", DECL_VAR_SIMP_OU_HOM_INICIAL, DECL_VAR_HET_2},
    {DECL_VAR_HET_3, RESERVED_KEYWORD, "char", DECL_VAR_SIMP_OU_HOM_INICIAL, DECL_VAR_HET_2},
    {DECL_VAR_HET_3, RESERVED_KEYWORD, "boolean", DECL_VAR_SIMP_OU_HOM_INICIAL, DECL_VAR_HET_2},
    
    
    // EXPR
    {EXPR_INICIAL, NDEF, "", TERMO_INICIAL, EXPR_1_AC},
    
    // FATOR_COND
    {FATOR_COND_INICIAL, ID, "", COMPARACAO_INICIAL, FATOR_COND_2_AC},
    {FATOR_COND_INICIAL, NUM, "", COMPARACAO_INICIAL, FATOR_COND_2_AC},
    {FATOR_COND_INICIAL, SPECIAL_CHARACTER, "(", COMPARACAO_INICIAL, FATOR_COND_2_AC},
    {FATOR_COND_INICIAL, RESERVED_KEYWORD, "true", BOOLEAN_INICIAL, FATOR_COND_2_AC},
    {FATOR_COND_INICIAL, RESERVED_KEYWORD, "false", BOOLEAN_INICIAL, FATOR_COND_2_AC},
    
    // FATOR
    {FATOR_1_AC, SPECIAL_CHARACTER, "[", REST_ACESSO_VETOR_INICIAL, FATOR_2_AC},
    {FATOR_1_AC, PONTUACAO, ".", REST_ACESSO_STRUCT_INICIAL, FATOR_2_AC},
    {FATOR_1_AC,SPECIAL_CHARACTER, "(", REST_CHAMADA_FUNCAO_INICIAL, FATOR_2_AC},
    {FATOR_3, NDEF, "", EXPR_INICIAL, FATOR_4},
    
    // ID (não precisa explicitar chamada de submáquina, pois o token passado já será o ID)
    
    // LISTA_EXPR
    {LISTA_EXPR_INICIAL, NDEF, "", EXPR_INICIAL, LISTA_EXPR_1_AC},
    
    // LISTA_MEM
    
    
    // NUM_REAL (também nao é necessário explicitar)
    // NUM (é o próprio token)
    
    // PARAM
    // {PARAM_INICIAL, ID, CONDICAO_INICIAL, PARAM_1_AC}, // não sei como fazer pra decidir entre uma expressão ou condicao quando o token é ID
    {PARAM_INICIAL, RESERVED_KEYWORD, "true", CONDICAO_INICIAL, PARAM_1_AC},
    {PARAM_INICIAL, RESERVED_KEYWORD, "false", CONDICAO_INICIAL, PARAM_1_AC},
    {PARAM_INICIAL, ID, "", EXPR_INICIAL, PARAM_1_AC},
    {PARAM_INICIAL, NUM, "", EXPR_INICIAL, PARAM_1_AC},
    {PARAM_INICIAL, SPECIAL_CHARACTER, "(", EXPR_INICIAL, PARAM_1_AC},

    // PROGRAM
    {PROGRAM_INICIAL, RESERVED_KEYWORD, "void", DECL_FUNCAO_INICIAL, PROGRAM_1},
    {PROGRAM_INICIAL, RESERVED_KEYWORD, "char", DECL_FUNCAO_INICIAL, PROGRAM_1},
    {PROGRAM_INICIAL, RESERVED_KEYWORD, "int", DECL_FUNCAO_INICIAL, PROGRAM_1},
    {PROGRAM_INICIAL, RESERVED_KEYWORD, "boolean", DECL_FUNCAO_INICIAL, PROGRAM_1},
    {PROGRAM_INICIAL, RESERVED_KEYWORD, "float", DECL_FUNCAO_INICIAL, PROGRAM_1},
    {PROGRAM_INICIAL, RESERVED_KEYWORD, "struct", DECL_VAR_HET_INICIAL, PROGRAM_1},
    {PROGRAM_5, RESERVED_KEYWORD, "int", DECL_OU_COMANDO_INICIAL, PROGRAM_5},
    {PROGRAM_5, RESERVED_KEYWORD, "char", DECL_OU_COMANDO_INICIAL, PROGRAM_5},
    {PROGRAM_5, RESERVED_KEYWORD, "float", DECL_OU_COMANDO_INICIAL, PROGRAM_5},
    {PROGRAM_5, RESERVED_KEYWORD, "boolean", DECL_OU_COMANDO_INICIAL, PROGRAM_5},
    {PROGRAM_5, RESERVED_KEYWORD, "input", DECL_OU_COMANDO_INICIAL, PROGRAM_5},
    {PROGRAM_5, RESERVED_KEYWORD, "output", DECL_OU_COMANDO_INICIAL, PROGRAM_5},
    {PROGRAM_5, RESERVED_KEYWORD, "while", DECL_OU_COMANDO_INICIAL, PROGRAM_5},
    {PROGRAM_5, RESERVED_KEYWORD, "if", DECL_OU_COMANDO_INICIAL, PROGRAM_5},
    {PROGRAM_5, ID, "", DECL_OU_COMANDO_INICIAL, PROGRAM_5},
    {PROGRAM_5, RESERVED_KEYWORD, "return", DECL_OU_COMANDO_INICIAL, PROGRAM_5},
    {PROGRAM_5, PONTUACAO, "\n", DECL_OU_COMANDO_INICIAL, PROGRAM_5},
    
    // REST_ACESSO_STRUCT
    {REST_ACESSO_STRUCT_2_AC, SPECIAL_CHARACTER, "[", REST_ACESSO_VETOR_INICIAL, REST_ACESSO_STRUCT_3_AC},
    
    // REST_CHAMADA_FUNCAO
    {REST_CHAMADA_FUNCAO_1, NDEF, "", PARAM_INICIAL, REST_CHAMADA_FUNCAO_2},
    {REST_CHAMADA_FUNCAO_4, NDEF, "", PARAM_INICIAL, REST_CHAMADA_FUNCAO_2},
    
    // REST_COMANDO_ATR
    {REST_COMANDO_ATR_1, NDEF, "", EXPR_INICIAL, REST_COMANDO_ATR_2_AC},
    
    // REST_COMANDO_ATR_ARRAY
    {REST_COMANDO_ATR_ARRAY_4, NDEF, "", EXPR_INICIAL, REST_COMANDO_ATR_ARRAY_5_AC},
    
    // REST_COMANDO_ATR_STRUCT
    {REST_COMANDO_ATR_STRUCT_3, NDEF, "", EXPR_INICIAL, REST_COMANDO_ATR_STRUCT_4_AC},
    
    // REST_DECL_HOM
    // Não há chamada de submáquina
    
    // REST_DECL_VAR_SIMP
    // Não há chamada de submáquina
    
    // TERMO_COND
    {TERMO_COND_INICIAL, NDEF, "", FATOR_COND_INICIAL, TERMO_COND_1_AC},
    
    // TERMO
    {TERMO_INICIAL, NDEF, "", FATOR_INICIAL, TERMO_1_AC}
    
    // TIPO (não possui chamadas de submáquinas)
};

#define NUMCHAMADAS (sizeof(chamadas)/sizeof(*chamadas))

#endif

