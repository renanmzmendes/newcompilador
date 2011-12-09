//
//  ConstantesSintatico2.h
//  Compilador
//
//  Created by Renan Mendes on 10/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CONSTANTES_SINTATICO_H
#define CONSTANTES_SINTATICO_H

typedef enum {
    ATR_OU_CHAMADA_INICIAL = 1,
    ATR_OU_CHAMADA_1,
    ATR_OU_CHAMADA_2_AC,
    
    BOOLEAN_INICIAL,
    BOOLEAN_1_AC,
    
    COMANDO_COND_INICIAL,   
    COMANDO_COND_1,  
    COMANDO_COND_2, 
    COMANDO_COND_3,
    COMANDO_COND_4,
    COMANDO_COND_5,
    COMANDO_COND_6,
    COMANDO_COND_7_AC,
    COMANDO_COND_8,
    
    COMANDO_ENTR_INICIAL,
    COMANDO_ENTR_1,
    COMANDO_ENTR_2_AC,
    
    COMANDO_ITER_INICIAL,
    COMANDO_ITER_1,
    COMANDO_ITER_2,
    COMANDO_ITER_3,
    COMANDO_ITER_4,
    COMANDO_ITER_5,
    COMANDO_ITER_6_AC,
    
    COMANDO_RETORNO_INICIAL,
    COMANDO_RETORNO_1,
    COMANDO_RETORNO_2_AC,
    
    COMANDO_SAIDA_INICIAL,
    COMANDO_SAIDA_1,
    COMANDO_SAIDA_2_AC,
    
    COMANDO_INICIAL,
    COMANDO_1_AC,
    
    COMPARACAO_INICIAL, 
    COMPARACAO_1,
    COMPARACAO_2,
    COMPARACAO_3_AC,
    
    CONDICAO_INICIAL,
    CONDICAO_1_AC,
    CONDICAO_2,
    
    DECL_FUNCAO_INICIAL,
    DECL_FUNCAO_1,
    DECL_FUNCAO_2,
    DECL_FUNCAO_3,
    DECL_FUNCAO_4,
    DECL_FUNCAO_5,
    DECL_FUNCAO_6,
    DECL_FUNCAO_7_AC,
    
    DECL_OU_COMANDO_INICIAL,
    DECL_OU_COMANDO_1,
    DECL_OU_COMANDO_2_AC,
    
    DECL_PARAMS_INICIAL,
    DECL_PARAMS_1,
    DECL_PARAMS_2_AC,
    
    DECL_VAR_HET_INICIAL,
    DECL_VAR_HET_1,
    DECL_VAR_HET_2,
    DECL_VAR_HET_3,
    DECL_VAR_HET_4_AC,
    
    DECL_VAR_SIMP_OU_HOM_INICIAL,
    DECL_VAR_SIMP_OU_HOM_1,
    DECL_VAR_SIMP_OU_HOM_2_AC,
    
    EXPR_INICIAL,
    EXPR_1_AC,
    
    FATOR_COND_INICIAL,     
    FATOR_COND_1,    
    FATOR_COND_2_AC,   
    FATOR_COND_3,  
    FATOR_COND_4, 
    
    FATOR_INICIAL,
    FATOR_1_AC,
    FATOR_2_AC,
    FATOR_3,
    FATOR_4,
    
    ID_INICIAL,
    ID_1_AC,
    
    LISTA_EXPR_INICIAL,
    LISTA_EXPR_1_AC,
    
    LISTA_MEM_INICIAL,
    LISTA_MEM_1_AC,
    
    NUM_REAL_INICIAL,
    NUM_REAL_1,
    NUM_REAL_2,
    NUM_REAL_3_AC,
    
    NUM_INICIAL,
    NUM_1_AC,
    
    PARAM_INICIAL,
    PARAM_1_AC,
    
    PROGRAM_INICIAL,
    PROGRAM_1,
    PROGRAM_2,
    PROGRAM_3,
    PROGRAM_4,
    PROGRAM_5,
    PROGRAM_6_AC,
    
    REST_ACESSO_STRUCT_INICIAL,
    REST_ACESSO_STRUCT_1,
    REST_ACESSO_STRUCT_2_AC,
    REST_ACESSO_STRUCT_3_AC,
    
    REST_ACESSO_VETOR_INICIAL,
    REST_ACESSO_VETOR_1,
    REST_ACESSO_VETOR_2,
    REST_ACESSO_VETOR_3_AC,
    
    REST_CHAMADA_FUNCAO_INICIAL,
    REST_CHAMADA_FUNCAO_1,
    REST_CHAMADA_FUNCAO_2,
    REST_CHAMADA_FUNCAO_3_AC,
    REST_CHAMADA_FUNCAO_4,
    
    REST_COMANDO_ATR_INICIAL,
    REST_COMANDO_ATR_1,
    REST_COMANDO_ATR_2_AC,
    
    REST_COMANDO_ATR_ARRAY_INICIAL,
    REST_COMANDO_ATR_ARRAY_1,
    REST_COMANDO_ATR_ARRAY_2,
    REST_COMANDO_ATR_ARRAY_3,
    REST_COMANDO_ATR_ARRAY_4,
    REST_COMANDO_ATR_ARRAY_5_AC,
    
    REST_COMANDO_ATR_STRUCT_INICIAL,
    REST_COMANDO_ATR_STRUCT_1,
    REST_COMANDO_ATR_STRUCT_2,
    REST_COMANDO_ATR_STRUCT_3,
    REST_COMANDO_ATR_STRUCT_4_AC,
    
    REST_DECL_VAR_HOM_INICIAL,
    REST_DECL_VAR_HOM_1,
    REST_DECL_VAR_HOM_2,
    REST_DECL_VAR_HOM_3,
    REST_DECL_VAR_HOM_4_AC,
    
    REST_DECL_VAR_SIMP_INICIAL,
    REST_DECL_VAR_SIMP_1_AC,
    
    TERMO_COND_INICIAL,
    TERMO_COND_1_AC,
    
    TERMO_INICIAL,
    TERMO_1_AC,
    
    TIPO_INICIAL,
    TIPO_1_AC,

    QUALQUER_ESTADO} Estado;

#endif