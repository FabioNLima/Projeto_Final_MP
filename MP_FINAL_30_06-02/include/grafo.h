/**
* @file grafo.h
* @author Guilherme de Sousa Castro
* @brief Implementa funções para grafo direcionado
*/
#include <stdlib.h>

typedef struct lista
{
	char *informacao;
	struct lista *prox;
}Transacao;
 

typedef struct vizinhos{
	struct vertice *p_vertice;
	struct vizinhos *prox;
}Vizinhos;

typedef struct grafo{
	char *nome;
	struct vertice *inicio;
}Grafo;

typedef struct vertice{
	int id;
	void *valor;
	char *login, *nome, *email, *senha;
	struct vertice *prox;
	struct aresta *p_arestas;
}Vertice;

typedef struct aresta{
	void *valor;
	struct aresta *prox;
	struct vertice *p_vertice;
}Aresta;

/**
*   @fn Grafo* cria_grafo(char *)
*   @brief Essa função recebe o nome do grafo, cria e retorna um ponteiro para o grafo.
*   @param nome Nome do grafo.
*   @return Um ponteiro para o grafo criado.
*/
Grafo* cria_grafo(char *nome);
char* retorna_nome_grafo(Grafo *);
int destroi_grafo(Grafo **);
int adjacente(Grafo *, int, int);
Vizinhos* vizinhos(Grafo *, int);
int adiciona_vertice(Grafo *, int, char *login, char *nome, char *email, char*senha);
int remove_vertice(Grafo *, int);
int adiciona_aresta(Grafo *, int, int);
int remove_aresta(Grafo *, int, int);
void *retorna_valor_vertice(Grafo *, int);
int muda_valor_vertice(Grafo *, int, void *);
void *retorna_valor_aresta(Grafo *, int, int);
int muda_valor_aresta(Grafo *, int, int, void *);

int verificador_login(Grafo *, char *, char *);
