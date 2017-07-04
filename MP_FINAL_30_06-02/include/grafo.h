
#ifndef grafo_c
#define grafo_c

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#endif /* grafo_c */

struct grafo{
    struct vertice * vertices;
    char * nome;
    float ** arestas;
    int total_vertices;
    
};

struct vertice{
    int id;
    char *login, *nome_completo, *email, *senha;

};

typedef struct grafo *Grafo;
static Grafo g;

/***************************************************************************
 * Função: criar a estrutura de um grafo
 * Descrição
 *    Aloca memória e inicializa uma estrutura do tipo graph
 * Parâmetros
 *    nome - nome do grafo a ser criado
 * Valor retornado
 *    ponteiro para o grafo alocado pela função
 *
 * Assertiva de entrada
 *    nome != null
 *
 * Assertiva de saída
 *    grafo->total_vertices = 0
 *    grafo->nome = nome
 *    dimensao(grafo->vertices) = 0
 *
 * Assertiva de saída - Pseudo código
 *    Se não conseguiu alocar espaço para o grafo
 *       Retorna NULL
 *    Senão
 *       Retorna estrutura do tipo graph inicializada com o nome desejado
 ****************************************************************************/

Grafo cria_grafo (char * nome);

/***************************************************************************
 * Função: consultar nome do grafo
 * Descrição
 *    Dada uma estrutura do tipo graph, retorna o nome dado para o grafo
 * Parâmetros
 *    g - grafo cujo nome é buscado
 * Valor retornado
 *    nome dado ao grafo g
 *
 * Assertiva de entrada
 *    g deve ser um objeto do tipo Graph
 *
 * Assertiva de saída
 *    Entrada(grafo) = Saida(grafo)
 *
 * Assertiva de saída - Pseudo código
 *    Se g foi inicializado
 *       Retorna g->nome
 *    Senão
 *       Retorna NULL
 ****************************************************************************/

char * retorna_nome_grafo(Grafo);

/***************************************************************************
 * Função: Libera matriz
 * Descrição
 *    Libera espaço em memória alocado para uma matriz quadrada, destruindo-a
 * Parâmetros
 *    matriz  - ponteiro para matriz quadrada cujo espaço em memória deve ser
 *             liberado
 *    tamanho - número de colunas (ou linhas) da matriz a ser destruída
 * Valor retornado
 *    Não possui retorno
 *
 * Assertiva de entrada
 *    numero_linhas(matriz) == numero_colunas(matriz)
 *    tamanho > 0
 *    tamanho == numero_linhas(matriz) == numero_colunas(matriz)
 *
 * Assertiva de saída
 *    numero_linhas(matriz) == numero_colunas(matriz) = 0
 *    matriz = NULL
 *
 * Assertiva de saída - Pseudo código
 *    Se matriz foi inicializada
 *       Matriz é destruída
 *    Senão
 *       Não faz nada
 ****************************************************************************/

void matriz_free(float** matriz, int tamanho);

/***************************************************************************
 * Função: Destrói grafo
 * Descrição
 *    Libera espaço em memória alocado para um grafo, destruindo ele e seus
 *    componentes
 * Parâmetros
 *    g - grafo a ser destruído, ou seja, grafo, cuja alocação de memória
 *        deve ser liberada
 * Valor retornado
 *    Não possui retorno
 *
 * Assertiva de entrada
 *    g deve ser um objeto do tipo Graph
 *
 * Assertiva de saída
 *    g = NULL
 *
 * Assertiva de saída - Pseudo código
 *    Se g foi inicializado
 *       g é destruído
 *    Senão
 *       Não faz nada
 ****************************************************************************/

void destroi_grafo(Grafo);

/***************************************************************************
 * Função: Busca posição de vértice
 * Descrição
 *    Dada uma estrutura do tipo graph, busca no array de vértices a posição
 *    do vértice cujo id é nome
 * Parâmetros
 *    g    - grafo onde será buscado o vértice desejado
 *    nome - identificador do vértice buscado
 * Valor retornado
 *    Posição em que se encontra o vértice com id nome (vetor de vértices e
 *    matriz de adjacências)
 *
 * Assertiva de entrada
 *    g deve ser um objeto do tipo Graph
 *    nome é um número inteiro
 *
 * Assertiva de saída
 *    Entrada(grafo) = Saida(grafo)
 *
 * Assertiva de saída - Pseudo código
 *    Se g não foi inicializado
 *       Retorna -1 (posição não encontrada)
 *    Senão
 *       Se existe vértice com id nome
 *          Retorna posição do vértice
 *       Senão
 *          Retorna -1 (posição não encontrada)
 ****************************************************************************/

int posicao_vertice(Grafo g, int nome);

/***************************************************************************
 * Função: Verifica Adjacência
 * Descrição
 *    Verifica se dois vértices (x e y) são adjacentes (ou seja, verifica
 *    se há uma aresta saindo de x e chegando em y) no grafo g
 * Parâmetros
 *    g - grafo onde será buscada a aresta
 *    x - identificador do vértice de onde parte a aresta buscada
 *    y - identificador do vértice de chagada da aresta buscada
 * Valor retornado
 *    True se há uma aresta de x para y, falso caso contrário
 *
 * Assertiva de entrada
 *    g deve ser um objeto do tipo Graph
 *    x é um número inteiro
 *    y é um número inteiro
 *
 * Assertiva de saída
 *    Entrada(grafo) = Saida(grafo)
 *
 * Assertiva de saída - Pseudo código
 *    Se x e y não são vértices de g
 *       Retorna falso
 *    Senão
 *       Se existe aresta fluindo de x para y
 *          Retorna true
 *       Senão
 *          Retorna false
 ****************************************************************************/

bool adjacente(Grafo, int x, int y);

/***************************************************************************
 * Função: Verifica vizinhança
 * Descrição
 *    Busca a lista de vértices vizinhos a um determiando vértice
 * Parâmetros
 *    g - grafo onde será buscada a lista de vizinhos
 *    x - identificador do vértice cujos vizinhos são procurados
 * Valor retornado
 *    Lista de vértices vizinhos do vértice cujo identificador é dado por x
 *
 * Assertiva de entrada
 *    g deve ser um objeto do tipo Graph
 *    x é um número inteiro
 *
 * Assertiva de saída
 *    Entrada(grafo) = Saida(grafo)
 *
 * Assertiva de saída - Pseudo código
 *    Se g não foi inicializado
 *       Imprime "Grafo nulo"
 *       Retorna NULL
 *    Senão
 *       Se x não é vértice de g
 *          Retorna NULL
 *       Senão
 *          Imprime os dados dos vizinhos
 *          Retorna lista de vizinhos
 ****************************************************************************/

struct vertice * vizinhos(Grafo, int x);

/***************************************************************************
 * Função: Adiciona vértice
 * Descrição
 *    Adiciona um vértice com identificador x numa estrutura do tipo graph
 * Parâmetros
 *    g - grafo onde será acrescentado um vértice com identificador x
 *    x - identificador do vértice a ser inserido no grafo g
 * Valor retornado
 *    Não possui retorno
 *
 * Assertiva de entrada
 *    g deve ser um objeto do tipo Graph
 *    x é um número inteiro
 *
 * Assertiva de saída
 *    grafo->total_vertices = Entrada(grafo->total_vertices) + 1
 *    Unico(chave)
 *    Contains(g, vertice(chave))
 *
 * Assertiva de saída - Pseudo código
 *    Se g não foi inicializado
 *       Não faz nada
 *    Senão
 *       Se x não é vértice de g
 *          Não faz nada
 *       Senão
 *          Adiciona o vértice x no grafo g
 ****************************************************************************/

void adiciona_vertice(Grafo, int x, char *login, char *nome_completo, char *email, char *senha);

/***************************************************************************
 * Função: Aloca matriz
 * Descrição
 *    Aloca espaço em disco para uma matriz quadrada
 * Parâmetros
 *    matriz   - matriz cujo espaço em disco será alocado
 *    elements - número de linhas / colunas da matriz
 * Valor retornado
 *    Matriz com espaço em memória devidamente alocado
 *
 * Assertiva de entrada
 *    matriz foi declarada
 *    elements é um número inteiro
 *
 * Assertiva de saída
 *    linhas(matriz) == colunas(matriz) = elements
 *
 * Assertiva de saída - Pseudo código
 *    Se matriz não foi inicializada
 *       Retorna matriz quadrada com tamanho elements
 *    Senão
 *       Retorna NULL
 ****************************************************************************/

float** aloca_matriz(float** matriz, int elements);

/***************************************************************************
 * Função: Realoca matriz
 * Descrição
 *    Realoca espaço em disco para uma matriz quadrada adicionando uma
 *    coluna e uma linha na matriz
 * Parâmetros
 *    matriz   - matriz cujo espaço em disco será alocado para poder
 *               adicionar mais um elemento
 *    elements - número de linhas / colunas desejado para a matriz após
 *               realocação
 * Valor retornado
 *    Matriz com espaço em memória devidamente realocado
 *
 * Assertiva de entrada
 *    matriz foi declarada
 *    elements é um número inteiro
 *
 * Assertiva de saída
 *    linhas(matriz) == colunas(matriz) = elements - 1
 *    Saida(linhas(matriz)) - 1 == Entrada(linhas(matriz))
 *    Saida(colunas(matriz)) - 1 == Entrada(colunas(matriz))
 *
 * Assertiva de saída - Pseudo código
 *    Se matriz não foi inicializada
 *       Retorna NULL
 *    Senão
 *       Retorna matriz removendo sua última linha e coluna
 ****************************************************************************/

float ** realoca_matriz(float** matriz, int elements);

/***************************************************************************
 * Função: Remove vértice
 * Descrição
 *    Remove um vértice de uma estrutura do tipo vértice
 * Parâmetros
 *    g - ponteiro para a estrutura do tipo graph da qual deve ser removido
 *        o vértice cujo identificadr é dado por x
 *    x - identificador do vértice a ser removido da estrutura graph g
 * Valor retornado
 *    Não há retorno
 *
 * Assertiva de entrada
 *    g foi declarado
 *    x é um número inteiro
 *
 * Assertiva de saída
 *    Saida(grafo->total_vertices) = Entrada(grafo->total_vertices)-1
 *    !Contains(g->vertices, chave)
 *    Saida(linhas(grafo->arestas)) = Entrada(linhas(grafo->arestas))-1
 *    Saida(colunas(grafo->arestas)) = Entrada(colunas(grafo->arestas))-1
 *    Saida(total_arestas) <= Entrada(total_Arestas)
 *
 * Assertiva de saída - Pseudo código
 *    Se x não é vértice de g
 *       Não faz nada
 *    Senão
 *       Remove vértice x de g
 ****************************************************************************/

void remove_vertice(Grafo, int x);

/***************************************************************************
 * Função: Adiciona aresta
 * Descrição
 *    Adiciona uma aresta à uma estrutura do tipo graph
 * Parâmetros
 *    g - ponteiro para a estrutura do tipo graph onde deve ser adicionada
 *        uma aresta
 *    x - identificador do vértice de partida da aresta a ser adicionada
 *    y - identificador do vértice destino da aresta a ser inserida no
 *        grafo g
 * Valor retornado
 *    Não há retorno
 *
 * Assertiva de entrada
 *    g foi inicializado
 *    x é um número inteiro
 *    y é um número inteiro
 *
 * Assertiva de saída
 *    Saida(grafo->total_vertices) = Entrada(grafo->total_vertices)+1
 *    Contains(g->vertices, chave)
 *    Saida(linhas(grafo->arestas)) = Entrada(linhas(grafo->arestas))+1
 *    Saida(colunas(grafo->arestas)) = Entrada(colunas(grafo->arestas))+1
 *    Saida(total_arestas) = Entrada(total_Arestas)
 *
 * Assertiva de saída - Pseudo código
 *    Se x ou y não são vértices de g
 *       Não faz nada
 *    Senão
 *       Cria aresta (x, y) com peso 1
 ****************************************************************************/

void adiciona_aresta(Grafo, int x, int y);

/***************************************************************************
 * Função: Remove aresta
 * Descrição
 *    Remove uma aresta de uma estrutura do tipo graph
 * Parâmetros
 *    g - ponteiro para a estrutura do tipo graph onde deve ser removida
 *        uma aresta
 *    x - identificador do vértice de partida da aresta a ser removida
 *    y - identificador do vértice destino da aresta a ser removida do grafo g
 * Valor retornado
 *    Não há retorno
 *
 * Assertiva de entrada
 *    g foi inicializado
 *    x é um número inteiro
 *    y é um número inteiro
 *
 * Assertiva de saída
 *    Saida(grafo->total_vertices) = Entrada(grafo->total_vertices)
 *    Contains(g->vertices, chave)
 *    !Contains(g->arestas, aresta(x,y))
 *    Saida(linhas(grafo->arestas)) = Entrada(linhas(grafo->arestas))-1
 *    Saida(colunas(grafo->arestas)) = Entrada(colunas(grafo->arestas))-1
 *    Saida(total_arestas) < Entrada(total_Arestas)
 *
 * Assertiva de saída - Pseudo código
 *    Se x ou y não são vértices de g ou peso da aresta (x, y) == 0
 *       Não faz nada
 *    Senão
 *       Altera peso de (x, y) para 0
 ****************************************************************************/

void remove_aresta(Grafo, int x, int y);

/***************************************************************************
 * Função: Busca valor de vértice
 * Descrição
 *    Remove uma aresta de uma estrutura do tipo graph
 * Parâmetros
 *    g - ponteiro para a estrutura do tipo graph onde deve ser consultado
 *        o valor de um vértice
 *    x - identificador do vértice do qual se busca o valor
 * Valor retornado
 *    Valor atribuído ao vértice x
 *
 * Assertiva de entrada
 *    g foi inicializado
 *    x é um número inteiro
 *
 * Assertiva de saída
 *    Saida(grafo->total_vertices) = Entrada(grafo->total_vertices)
 *    Saida(grafo) = Entrada(grafo)
 *
 * Assertiva de saída - Pseudo código
 *    Se x não é vértice de g
 *       Retorna -1 (vértice não encontrado)
 *    Senão
 *       Valor do vértice x
 ****************************************************************************/

float retorna_valor_vertice(Grafo, int x);


int vertice_verificador(Grafo, char *login, char *senha);

/***************************************************************************
 * Função: Altera valor de vértice
 * Descrição
 *    Altera o valor dado a um vértice em uma estrutura do tipo graph
 * Parâmetros
 *    g     - ponteiro para a estrutura do tipo graph onde deve ser alterado
 *            o valor de um vértice
 *    x     - identificador do vértice do qual se busca alterar o valor
 *    valor - novo valor a ser atribuído ao vértice x
 * Valor retornado
 *    Não possui retorno
 *
 * Assertiva de entrada
 *    g foi inicializado
 *    x é um número inteiro
 *    valor é um número inteiro
 *
 * Assertiva de saída
 *    Saida(grafo->total_vertices) = Entrada(grafo->total_vertices)
 *    Valor(g->vertices(x)) = valor
 *    Saida(grafo->arestas) = Entrada(grafo->arestas)
 *    Saida(total_arestas) = Entrada(total_Arestas)
 *
 * Assertiva de saída - Pseudo código
 *    Se x não é vértice de g
 *       Não faz nada
 *    Senão
 *       Altera valor do vértice x para valor
 ****************************************************************************/

void muda_valor_vertice(Grafo, int x, int valor);

/***************************************************************************
 * Função: Consulta valor de aresta
 * Descrição
 *    Busca o valor atribuído a uma aresta em uma estrutura do tipo graph
 * Parâmetros
 *    g - estrutura do tipo graph onde deve ser consultado o valor de uma
 *       aresta
 *    x - identificador do vértice de partida da aresta buscada
 *    y - identificador do vértice de chegada da aresta buscada
 * Valor retornado
 *    Valor atribuído à aresta de x para y
 *
 * Assertiva de entrada
 *    g foi inicializado
 *    x é um número inteiro
 *    y é um número inteiro
 *
 * Assertiva de saída
 *    Saida(grafo) = Entrada(grafo)
 *
 * Assertiva de saída - Pseudo código
 *    Se x ou y não é vértice de g
 *       Retorna -1 (vértice inexistente)
 *    Senão
 *       Retorna valor da aresta (x, y)
 ****************************************************************************/

float retorna_valor_aresta(Grafo, int x, int y);
/***************************************************************************
 * Função: Altera valor de aresta
 * Descrição
 *    Altera o valor atribuído a uma aresta em uma estrutura do tipo graph
 * Parâmetros
 *    g     - ponteiro para a estrutura do tipo graph onde deve ser
 *            consultado o valor de uma aresta
 *    x     - identificador do vértice de partida da aresta buscada
 *    y     - identificador do vértice de chegada da aresta buscada
 *    valor - novo valor a ser atribuído a aresta que vai de x para y
 * Valor retornado
 *    Não possui retorno
 *
 * Assertiva de entrada
 *    g foi inicializado
 *    x é um número inteiro
 *    y é um número inteiro
 *    valor é um número inteiro
 *
 * Assertiva de saída
 *    Saida(grafo->total_vertices) = Entrada(grafo->total_vertices)
 *    Contains(g->vertices, chave)
 *    Contains(g->arestas, aresta(x,y))
 *    Valor(aresta(x,y)) = valor
 *    Saida(linhas(grafo->arestas)) = Entrada(linhas(grafo->arestas))
 *    Saida(colunas(grafo->arestas)) = Entrada(colunas(grafo->arestas))
 *    Saida(total_arestas) = Entrada(total_Arestas)
 *
 * Assertiva de saída - Pseudo código
 *    Se x ou y não é vértice de g ou se a aresta (x, y) == 0
 *       Não faz nada
 *    Senão
 *       Altera peso da aresta (x, y) para valor
 ****************************************************************************/

void muda_valor_aresta(Grafo, int x, int y, int valor);

/***************************************************************************
 * Função: Imprime dados do grafo
 * Descrição
 *    Imprime no console os dados de uma estrutura do tipo graph
 * Parâmetros
 *    g - estrutura do tipo graph cujos detalhes busca-se imprimir
 * Valor retornado
 *    Não possui retorno
 *
 * Assertiva de entrada
 *    g foi declarado
 *
 * Assertiva de saída
 *    Saida(grafo) = Entrada(grafo)
 *
 * Assertiva de saída - Pseudo código
 *    Se grafo g não foi inicializado
 *       Imprime "Grafo Nulo"
 *    Senão
 *       Imprime os detalhes de g
 ****************************************************************************/

void print_grafo(Grafo);
