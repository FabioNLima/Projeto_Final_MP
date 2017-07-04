#include <ncurses.h>
#include <form.h>
#include <stdio.h>
#include <string>
#include "GraphicalUserInterface.h"

#define WIDTH 30
#define HEIGHT 10


int main(void)
{
	g = cria_grafo("REDE");
	char valor[40];

	UI_Inicializador(g);
	//UI_Cadastro(g);
	//print_grafo(g);
	return 0;
}
