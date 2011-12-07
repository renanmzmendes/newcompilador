#include <stdio.h>
#include <stdlib.h>
#include "Lexico.h"
#include "Sintatico.h"
#include "ConstantesSintatico.h"
#include "ConstantesSemantico.h"
#include "TabelasSintatico.h"
#include "Semantico.h"

#define MAX 30
#define MAX_SIZE 50

int main() {
    
	Token *token;
	token = (Token*) malloc(sizeof(Token));
    
    // Inicializando lista de tokens e escopos
    tokens.tamanho = 0;
    escopos.tamanho = 0;
    constTab.tamanho = 0;
    
    // Inicializando pilhas de ifs, whiles e expressoes
    StackInit(&pilhaIfs, MAX_SIZE);
    StackInit(&pilhaWhiles, MAX_SIZE);
    StackInit(&pilhaElses, MAX_SIZE);
    StackTokenInit(&pilhaOperandos, MAX_SIZE);
    StackTokenInit(&pilhaOperadores, MAX_SIZE);
    StackInit(&pilhaExpressoes, MAX_SIZE);
        
	FILE *entrada;
    entrada = fopen("/Users/renanmzmendes/newcompilador/Projeto/in.txt", "r");
    //verificando se arquivo existe
    if(entrada == NULL) {
        printf("arquivo nao encontrado\n\n");
        return 1;
    }
    
    // Abre o arquivo de saída
    out = fopen("/Users/renanmzmendes/newcompilador/Projeto/out.txt", "wr");
	
	InicializaLexico();

	//ImprimirTabelaLexico(); //se quiser ver a tabela de estados
	
	//printf("Linha  Coluna     Token     Tipo\n");
    //Lendo o Arquivo pegando todos os Tokens até terminar o arquivo o ch deve iniciar com NULL
    StackInit(&pilha, MAX_SIZE);
    Estado estadoCorrente = PROGRAM_INICIAL;
    Estado estadoAnterior = 0;
    token = getNextToken(entrada);
	while (token->tipo != EoF) {
        
        transicao trans;
        chamadaSubmaquina chamada;
        
        // Procura transição
        if(!procuraTransicao(estadoCorrente, token, &trans)) {
            
            // Se não encontrar transição procura chamada de submáquina
            if(!procuraChamadaSubmaquina(estadoCorrente, token, &chamada)) {
                // Caso não encontra chamada de submáquina, verifica se é estado final,
                // se for aceita, senão dá erro
                if(estadoFinal(estadoCorrente)) {       
                    estadoAnterior = estadoCorrente;
                    estadoCorrente = desempilha();
                    executarAcaoSemantica(estadoAnterior, estadoCorrente, token);

                } else {
                    printf("Erro no reconhecimento de sintaxe, linha %d", token->linha);
                    getchar();
                    exit(1);
                }
            } else { // Se acha chamada de submáquina
                estadoAnterior = estadoCorrente;
                estadoCorrente = chamada.estadoDestino;
                executarAcaoSemantica(estadoAnterior, estadoCorrente, token);
                empilha(chamada.estadoRetorno);
            }
            
        } else { // Se encontrar transição
            estadoAnterior = estadoCorrente;
            estadoCorrente = trans.estadoDestino;    
            executarAcaoSemantica(estadoAnterior, estadoCorrente, token);
            token = getNextToken(entrada);
            
        }
	}
    
    // Dump das variáveis e constantes no fim do programa
    declararVariaveisConstantes();
    escreveFuncoesMvn();
    imprimeFim();
	
    free(token);
	return 0;
}
