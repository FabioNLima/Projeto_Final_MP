#include <ncurses.h>
#include <form.h>
#include <stdio.h>
#include <string>
#include "GraphicalUserInterface.hpp"

#define WIDTH 30
#define HEIGHT 10


int main(void)
{
	/*
	*	Estrutura tipo grafo criada
	*/
	Grafo *g = cria_grafo("REDE");

	/*
	*	Variaveis de controles
	*	
	*/
	int resulta = 1, id = 0, id_1 = 0, id_2 = 0;
	
	/*
	*	Variaveis que recebem os paramentros para serem armazenados no grafo
	*	
	*/
	char login[40], nome[40], email[40], senha[40], c, avaliacao[5], login_vendedor[40], tipo[40], titulo[40], descricao[80];
	
	/*
	*	Variaveis de controles para manipulação de arquivos
	*	
	*/
	FILE *cadastro, *amigos, *transacao, *anuncio;
	
	/*
	*	Aberturas de arquivos para leitura
	*	
	*/
	cadastro = fopen("usuarios.txt", "r");
	amigos = fopen("aresta.txt", "r");
	transacao = fopen("transacao.txt", "r");
	anuncio = fopen("anuncio.txt", "r");

	

	c = getc(cadastro);
	if (c != EOF)
	{
		rewind(cadastro);
		while(resulta != EOF)
		{	

			resulta = fscanf(cadastro, "%d %s %s %s %s", &id, login, nome, email, senha);
			adiciona_vertice(g, id, login, nome, email, senha);
		}
	}
	rewind(cadastro);
	fclose(cadastro);


	resulta = 1;
	c = getc(amigos);
	if (c != EOF)
	{
		rewind(amigos);
		while(resulta != EOF)
		{	
			resulta = fscanf(amigos, "%d %d", &id_1, &id_2);
			adiciona_aresta(g, id_1, id_2);
		}
	}
	rewind(amigos);	
	fclose(amigos);


	resulta = 1;

	c = getc(anuncio);
	if (c != EOF)
	{
		rewind(anuncio);
		while(resulta != EOF)
		{	

			resulta = fscanf(anuncio, "%s %s %s %s", login, tipo, titulo, descricao);
			if(resulta == 4)
			{
				adiciona_anuncio(busca_login(g, login), tipo, titulo, descricao);
			}
			
			
		}
	}
	rewind(anuncio);	
	fclose(anuncio);


	resulta = 1;

	c = getc(transacao);
	if (c != EOF)
	{
		rewind(transacao);
		while(resulta != EOF)
		{	

			resulta = fscanf(transacao, "%s %s %s %s", login, login_vendedor, titulo, avaliacao);
			if(resulta == 4)

			{
				adiciona_transacao(busca_login(g, login), busca_login(g, login_vendedor), atoi(avaliacao), NULL);			
			}
		}
	}
	rewind(transacao);	
	fclose(transacao);

	UI_Inicializador(g);

	return 0;
}
