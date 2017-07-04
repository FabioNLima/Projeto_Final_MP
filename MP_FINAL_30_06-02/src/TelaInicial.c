#include <ncurses.h>
#include <form.h>
#include <stdio.h>
#include <string>
#include "GraphicalUserInterface.h"

#define WIDTH 30
#define HEIGHT 10


int main(void)
{
	Grafo g = cria_grafo("REDE");
	char valor[40];

	UI_Inicializador();
	return 0;
}
