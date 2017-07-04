/**
* @file grafo.h
* @author Guilherme de Sousa Castro
* @brief Implementa funções para grafo direcionado
*/
#include <stdlib.h>


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
	struct anuncio *p_anuncios;
	struct transacao *p_transacao;

}Vertice;

typedef struct aresta{
	void *valor;
	struct aresta *prox;
	struct vertice *p_vertice;
}Aresta;

typedef struct anuncio{

	char *tipo;
	char *titulo;
	char *descricao;
	struct anuncio *prox;

}Anuncio;

typedef struct transacao{

	Vertice *login;
	int avaliacao;
	struct anuncio *p_anuncios;
	struct transacao *prox;

}Transacao;

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

Anuncio *cria_anuncio();

void destroi_anuncio(Anuncio **);

void adiciona_anuncio(Vertice *, char *, char *, char *);

void retira_anuncio(Anuncio *, char *);

Transacao *cria_transacao();

void destroi_transacao(Transacao **);

void adiciona_transacao(Vertice *, int, Anuncio *);

void retira_transacao(Transacao *, char *);


Vertice *verificador_login(Grafo *, char *, char *);

int total_vertice(Grafo *g);

//char **nomes_vertices(Grafo *g, int x);


int busca_anuncio_grafo(Grafo *g, char *tipo);