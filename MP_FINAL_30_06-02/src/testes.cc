
#include "GraphicalUserInterface.hpp"
#include <string.h>
#include <stdio.h>
#include "gtest/gtest.h"


/** @file test_romanos.cc
*   @brief Arquivo de testes relativos a romanos.cc
*   @sa romanos.h
*/

/** @fn TEST(Verifica_função relacionada, Return_0)
*   @brief Testes relativos à escrita de uma algarismo romano.
*/

/*Todos os testes a seguir
    * apenas verificar se o algarismo digitado está correto
    * se estiver correto a função é validada e retorna 0
    *caso contrário retorna -1*/

Grafo *grafo = cria_grafo("REDE");

/*TEST (Cria_Grafo, Return_NULL) { 
    
    char algarismo[] = "REDE";

    EXPECT_EQ (0, cria_grafo(algarismo));
}

*/
//Teste para destruit um grafo

TEST (Destroi_Grafo, Return_0) { 


    EXPECT_EQ (0, destroi_grafo(&grafo));
}

//Teste para verificar se os vertices são adjacentes
int adjacente(Grafo *grafo, int vertice_a, int vertice_b);

TEST (Adjacentes, Return_0) { 

    EXPECT_EQ (1, adjacente(grafo, 1, 2));
}

//Teste para adicionar um vertice no grafo
int adiciona_vertice(Grafo *grafo, int, char *login, char *nome, char *email, char*senha);

TEST (Adiciona_vertice, Return_0) { 

    EXPECT_EQ (1, adiciona_vertice(grafo, 1, "login", "nome", "email", "senha"));
}

//Teste para remover um vertice de um grafo
int remove_vertice(Grafo *grafo, int vertice);

TEST (Remove_vertice, Return_0) { 

    EXPECT_EQ (1, remove_vertice(grafo, 2));
}

//Teste responsavel para adiciona uma aresta entre dois vertices
int adiciona_aresta(Grafo *grafo, int vertice_a, int vertice_b);

TEST (Adiciona_aresta, Return_0) { 

    EXPECT_EQ (1, adiciona_aresta(grafo, 2, 3));
}

//Teste responsavel para remover uma aresta entre dois vertices
int remove_aresta(Grafo *, int vertice_a, int vertice_b);

TEST (Remove_aresta, Return_0) { 

    EXPECT_EQ (1, remove_aresta(grafo, 2, 3));
}

//Teste para para criar um anuncio
Anuncio *cria_anuncio();



//Teste para informar o total de vertice de um grafo
int total_vertice(Grafo *g);

TEST (Total_vertice, Return_0) { 

    EXPECT_EQ (0, total_vertice(grafo));
}

//Teste para buscar um anuncio
int busca_anuncio_grafo(Grafo *g, char *tipo);

TEST (BUsca_Anuncio_Grafo, Return_0) { 

    EXPECT_EQ (1, busca_anuncio_grafo(grafo, "carro"));
}



/** @fn TEST(Converte_função relacionada, Return_0)
*   @brief Testes relativos à conversão do algarismo romano para arabico
*/

/*Todos os testes a seguir
    * apenas verificar se o algarismo digitado está correto
    * se estiver correto a função é validada e retorna 0
    *caso contrário retorna -1*/





















