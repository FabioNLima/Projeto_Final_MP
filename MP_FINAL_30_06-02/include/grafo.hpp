
#include <stdlib.h>

/**
* @file grafo.h
* @author Guilherme de Sousa Castro
* @brief Implementa funções para grafo direcionado
*/

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

	Vertice *login, *comprador;
	int avaliacao;
	char *titulo;
	char *descricao;
	struct transacao *prox;

}Transacao;

/**
*   @fn Grafo* cria_grafo(char *)
*   @brief Essa função recebe o nome do grafo, cria e retorna um ponteiro para o grafo.
*   @param nome Nome do grafo.
*   @return Um ponteiro para o grafo criado.
*/
Grafo* cria_grafo(char *nome);

/**
*   @fn char* retorna_nome_grafo(Grafo *grafo)
*   @brief Essa função recebe um TAD grafo e retorna um ponteiro com o nome do grafo.
*   @param G é um objeto tipo Grafo
*   @return Um ponteiro com o nome do grafo criado.
*/
char* retorna_nome_grafo(Grafo *grafo);

/**
*   @fn int destroi_grafo(Grafo **grafo);
*   @brief Essa função recebe um TAD grafo e retorna um inteiro (zero).
*   @param G é um objeto tipo Grafo
*   @return Um inteiro (zero) informando que o grafo foi destruído.
*/
int destroi_grafo(Grafo **grafo);

/**
*   @fn int adjacente(Grafo *grafo, int vertice_a, int vertice_b)
*   @brief Essa função recebe um TAD grafo e retorna um inteiro (zero).
*   @param G é um objeto tipo Grafo
*	@param vertice_a é um objeto tipo inteiro representado por um vertice
*	@param vertice_b é um objeto tipo inteiro representado por um vertice
*   @return Um inteiro (um) informando que os vertices são adjacentes.
*/
int adjacente(Grafo *grafo, int vertice_a, int vertice_b);

/**
*   @fn Vizinhos* vizinhos(Grafo *grafo, int vertice)
*   @brief Essa função recebe um TAD grafo e retorna um conjunto de vizinhos do vertice.
*   @param G é um objeto tipo Grafo
*	@param vertice é um objeto tipo inteiro representado por um vertice
*   @return Um conjunto de vizinhos do vertice do grafo.
*/
Vizinhos* vizinhos(Grafo *grafo, int vertice);

/**
*   @fn int adiciona_vertice(Grafo *grafo, int, char *login, char *nome, char *email, char*senha)
*   @brief Essa função recebe um TAD grafo, um ponteiro para login, nome, email e senha.
*   @param G é um objeto tipo Grafo
*	@param *login é um objeto tipo ponteiro para char que receberá uma string.
*	@param *nome é um objeto tipo ponteiro para char que receberá uma string.
*	@param *email é um objeto tipo ponteiro para char que receberá uma string.
*	@param *senha é um objeto tipo ponteiro para char que receberá uma string.
*   @return Um inteiro informando se o vertice foi adicionado.
*/

int adiciona_vertice(Grafo *grafo, int, char *login, char *nome, char *email, char*senha);

/**
*   @fn int remove_vertice(Grafo *grafo, int vertice)
*   @brief Essa função recebe um TAD grafo, uma variavel chamada vertice tipo inteiro que será removida do grafo.
*   @param grafo é um objeto tipo Grafo
*	@param vertice é um objeto tipo inteiro que será removido.
*   @return Um inteiro informando se o vertice foi removido.
*/
int remove_vertice(Grafo *grafo, int vertice);

/**
*   @fn int adiciona_aresta(Grafo *grafo, int vertice_a, int vertice_b);
*   @brief Essa função recebe um TAD grafo, dois vertices e retorna um inteiro (zero).
*   @param G é um objeto tipo Grafo
*	@param vertice_a é um objeto tipo inteiro representado por um vertice
*	@param vertice_b é um objeto tipo inteiro representado por um vertice
*   @return Um inteiro (um) informando que os vertices possuem uma aresta.
*/
int adiciona_aresta(Grafo *grafo, int vertice_a, int vertice_b);

/**
*   @fn int remove_aresta(Grafo *, int vertice_a, int vertice_b);
*   @brief Essa função recebe um TAD grafo, dois vertices e retorna um inteiro (zero).
*   @param G é um objeto tipo Grafo
*	@param vertice_a é um objeto tipo inteiro representado por um vertice
*	@param vertice_b é um objeto tipo inteiro representado por um vertice
*   @return Um inteiro (um) informando que a aresta entre os vertices foi removido.
*/
int remove_aresta(Grafo *, int vertice_a, int vertice_b);

/**
*   @fn void *retorna_valor_vertice(Grafo *grafo , int valor);
*   @brief Essa função recebe um TAD grafo, dois vertices e retorna um inteiro (zero).
*   @param G é um objeto tipo Grafo
*	@param valor é um objeto tipo inteiro que armazena o valor do vertice
*   @return Um ponteiro contendo o valor do vertice
*/
void *retorna_valor_vertice(Grafo *grafo, int valor);

/**
*   @fn void *retorna_valor_vertice(Grafo *grafo , int valor);
*   @brief Essa função recebe um TAD grafo, dois vertices e retorna um inteiro (zero).
*   @param G é um objeto tipo Grafo
*	@param valor é um objeto tipo inteiro que armazena o valor do vertice
*   @return Um ponteiro contendo o valor do vertice
*/
int muda_valor_vertice(Grafo *grafo , int vertice , void *valor);

/**
*   @fn void *retorna_valor_vertice(Grafo *grafo , int valor);
*   @brief Essa função recebe um TAD grafo, dois vertices e retorna um inteiro (zero).
*   @param G é um objeto tipo Grafo
*	@param valor é um objeto tipo inteiro que armazena o valor do vertice
*   @return Um ponteiro contendo o valor do vertice
*/
void *retorna_valor_aresta(Grafo *, int, int);

/**
*   @fn void *retorna_valor_vertice(Grafo *grafo , int valor);
*   @brief Essa função recebe um TAD grafo, dois vertices e retorna um inteiro (zero).
*   @param G é um objeto tipo Grafo
*	@param valor é um objeto tipo inteiro que armazena o valor do vertice
*   @return Um ponteiro contendo o valor do vertice
*/
int muda_valor_aresta(Grafo *, int, int, void *);

/**
*   @fn void *retorna_valor_vertice(Grafo *grafo , int valor);
*   @brief Essa função recebe um TAD grafo, dois vertices e retorna um inteiro (zero).
*   @param G é um objeto tipo Grafo
*	@param valor é um objeto tipo inteiro que armazena o valor do vertice
*   @return Um ponteiro contendo o valor do vertice
*/
Anuncio *cria_anuncio();

/**
*   @fn void *retorna_valor_vertice(Grafo *grafo , int valor);
*   @brief Essa função recebe um TAD grafo, dois vertices e retorna um inteiro (zero).
*   @param G é um objeto tipo Grafo
*	@param valor é um objeto tipo inteiro que armazena o valor do vertice
*   @return Um ponteiro contendo o valor do vertice
*/
void destroi_anuncio(Anuncio **);

/**
*   @fn void adiciona_anuncio(Vertice *, char *, char *, char *);
*   @brief Essa função recebe um TAD Vertice e 3 ponteiros para um tipo char.
*   @param Vertice é um tipo struct que recebe vertices de um grafo
*	@param ponteiro para um tipo char que será o tipo do produto
*	@param ponteiro para um tipo char que será o titulo do produto
*	@param ponteiro para um tipo char que será o descrição do produto
*   @return Não retorna nada
*/
void adiciona_anuncio(Vertice *, char *tipo, char *titulo, char *descricao);

/**
*   @fn void retira_anuncio(Grafo *grafo, char *login, char *titulo)
*   @brief Essa função recebe um TAD grafo, dois ponteiro para um tipo char
*   @param G é um objeto tipo Grafo
*	@param ponteiro para um tipo char que será o login do vendedor
*	@param ponteiro para um tipo char que será o titulo do produto
*   @return Não retorna nada
*/
void retira_anuncio(Grafo *grafo, char *login, char *titulo);

/**
*   @fn Transacao *cria_transacao();
*   @brief Essa função cria uma struct de Transação para armazenar as transações
*   @return Um ponteiro para NULL
*/
Transacao *cria_transacao();

/**
*   @fn void destroi_transacao(Transacao **)
*   @brief Essa função recebe um TAD Transação
*   @param Um ponteiro para ponteiro para uma Transação
*   @return Não retorna nada
*/
void destroi_transacao(Transacao **);

/**
*   @fn void adiciona_transacao(Vertice *logado, Vertice *vendedor, int avaliacao, Anuncio *anuncio)
*   @brief Essa função serve para adicionar uma transação que foi realizada
*   @param logado é um objeto tipo Vertice que recebe o login da pessoa logada
*   @param vendedor é um objeto tipo Vertice que recebe o login da pessoa que vendeu
*   @param avaliacao objeto tipo inteiro que recebe uma nota sobre a transação
*   @param anuncio é um objeto tipo Anuncio que contem uma anuncio sobre um produto
*   @return Um ponteiro contendo o valor do vertice
*/
void adiciona_transacao(Vertice *logado, Vertice *vendedor, int avaliacao, Anuncio *anuncio);

/**
*   @fn void retira_transacao(Transacao *, char *)
*   @brief transação é um TAD Transação que contem as todas as transações
*	@param titulo é um objeto tipo ponteiro para char que contem o titulo da transação
*   @return Não retorna nada
*/
void retira_transacao(Transacao *transacao, char *titulo);


/**
*   @fn Vertice *verificador_login(Grafo *, char *, char *)
*   @brief Essa função é responsável por retornar um vertice que contem determinado login
*   @param grafo é um objeto tipo Grafo
*	@param login é um objeto tipo ponteiro para char que armazena o login do usuário
*	@param senha é um objeto tipo ponteiro para char que armazena a senha do usuário
*   @return um vertice contendo o login e a senha de determinado usuário
*/
Vertice *verificador_login(Grafo *grafo, char *login, char *senha);

/**
*   @fn int total_vertice(Grafo *g)
*   @brief Essa função é responsável por retornar a quantidade de vertices de um grafo
*   @param G é um objeto tipo Grafo
*   @return Um valor contendo a quantidade de vertices de um grafo
*/
int total_vertice(Grafo *g);

/**
*   @fn int busca_anuncio_grafo(Grafo *g, char *tipo)
*   @brief Essa função é responsável por busca um anuncio
*   @param G é um objeto tipo Grafo
*	@param tipo é um ponteiro para char que contém o tipo do anuncio
*   @return Um valor contendo a quantidade de anuncios
*/
int busca_anuncio_grafo(Grafo *g, char *tipo);

/**
*   @fn Vertice *busca_login(Grafo *g, char *login);
*   @brief Essa função é responsável por retornar um vertice contendo determinado login
*   @param G é um objeto tipo Grafo
*	@param login é um ponteiro para char que contém o login a ser buscado
*   @return Um TAD tipo Vertice contendo o vertice do usuário
*/
Vertice *busca_login(Grafo *g, char *login);

/**
*   @fn Anuncio *busca_anuncio(Grafo *g, char *login, char *titulo)
*   @brief Essa função é responsável por buscar um anuncio em um Grafo
*   @param G é um objeto tipo Grafo
*	@param login é um ponteiro para char que contém o login a ser buscado
*	@param titulo é um objeto tipo ponteiro para char que contem o titulo da transação
*   @return Um ponteiro contendo o anuncio
*/
Anuncio *busca_anuncio(Grafo *g, char *login, char *titulo);
