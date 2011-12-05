#ifndef TABELA_SIMBOLOS
#define TABELA_SIMBOLOS

#define MAX_ESCOPOS 50
#define MAX_SIMBOLOS 50
#define MAX_CONSTANTES 50

typedef enum {INT, CHAR, FLOAT, BOOLEAN} Tipo;

//global
typedef struct  {
	char* label;
	int valor;
} Constante;

typedef struct {
    int tamanho;
    Constante* constantes[MAX_CONSTANTES];
} TabelaConstantes;

void insereConstante(int c, TabelaConstantes* t);
int existeConstante(int c, TabelaConstantes* t);
char* recuperaLabelConstante(int c, TabelaConstantes* t);


typedef struct {
	Tipo tipo;
	char* nome;
	char* label;
}  Simbolo;

//Escopo com no maximo MAX_SIMBOLOS
typedef struct _Escopo {
	Simbolo simbolos[MAX_SIMBOLOS];
	struct _Escopo* anterior;
	struct _Escopo* internos[MAX_ESCOPOS];
	int numSimbolos;
	int numInternos;
    char* nome;
} Escopo;

void initEscopo(Escopo* e);
void insereEscopoInterno(Escopo* e, Escopo* interno);

void adicionarSimbolo(Tipo t, char* nome, char* label, Escopo* e);
int existeSimbolo(char* nome, Escopo* e);

char* recuperaLabelSimbolo(char* nome, Escopo* e);

#endif