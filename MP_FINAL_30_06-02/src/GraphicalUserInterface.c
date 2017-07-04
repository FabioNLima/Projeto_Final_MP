#include "GraphicalUserInterface.h"
#include <ncurses.h>
#include <string>
#include <form.h>
#include <stdlib.h>
#include <assert.h>

#define WIDTH 30
#define HEIGHT 10

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);


int startx = 0;
int starty = 0;

char *choices[] = {"Login","Cadastro","Exit"};
char *choices_cadastro[] = {"Login:", "Nome Completo:", "Email:", "Senha:"};
char *choices_login[] = {"Login:","Senha:"};
char *choices_pagina_inicial[] = {"Amizade", "Transações", "Anunciar", "Configuracao", "Exit"};
char *choices_amizade[] = {"Amigos ","Adicionar Amigos"};

int n_choices = sizeof(choices) / sizeof(char *);
int n_choices_cadastro = sizeof(choices_cadastro) / sizeof(char *);
int n_choices_login = sizeof(choices_login) / sizeof(char *);
int n_choices_pagina_inicial = sizeof(choices_pagina_inicial) / sizeof(char *);
int n_choices_amizade = sizeof(choices_amizade) / sizeof(char *);


void print_menu(WINDOW *menu_win, int highlight, int num_choices, char** choices_a);
void print_menu_c(WINDOW *menu_win, int num_choices, char** choices_a, Grafo *g);
void print_menu_login(WINDOW *menu_win, int num_choices, char** choices_a, Grafo *g);
void print_menu_pagina_inicial(WINDOW *menu_win, int highlight, int num_choices, char** choices_a);
void print_menu_add_amigos(WINDOW *menu_win, int highlight, int num_choices, Grafo *g, Vertice *aux);
void print_menu_amigos(WINDOW *menu_win, Grafo *g, Vertice *aux);

//Função inicializadora

void UI_Inicializador(Grafo *g)
{
    FILE *teste;
    int i = 0;
	WINDOW *menu_win;
	int highlight = 1;
	int choice = 0;
	int c = 0;

	initscr();
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	printw("A Big string which i didn't care to type fully ");
	mvchgat(0, 0, -1, A_BLINK, 1, NULL);
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;

	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win, TRUE);
	mvprintw(0, 0, "Bem vindo a Rede Social Enconnomica!");
	refresh();
	print_menu(menu_win, highlight, n_choices, choices);
	while(1)
	{	c = wgetch(menu_win);
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_choices;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices)
					highlight = 1;
				else
					++highlight;
				break;
			case 10:
				choice = highlight;
				break;
			default:
				mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
				refresh();
				break;
		}
		print_menu(menu_win, highlight, n_choices, choices);
		if(choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}
	switch(choice)
	{	case 1:
				if(highlight == 1)
					highlight = n_choices;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices)
					highlight = 1;
				else
					++highlight;
				break;
			case 10:
				choice = highlight;
				break;
			default:
				mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
				refresh();
				break;
	}
	mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);
	clrtoeol();
	refresh();
	if (choice == 1){
     	UI_Login(g);
	}
	else if(choice == 2)
	{
		UI_Cadastro(g);
	}


	delwin(menu_win);
	endwin();
	delwin(menu_win);
	return;
}

void print_menu(WINDOW *menu_win, int highlight, int num_choices, char** choices_a)
{
	int x, y, i;

	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < num_choices; ++i)
	{	if(highlight == i + 1) /* High light the present choice */
		{	wattron(menu_win, A_REVERSE);
			mvwprintw(menu_win, y, x, "%s", choices_a[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices_a[i]);
		++y;
	}
	wrefresh(menu_win);
}


void print_menu_c(WINDOW *menu_win, int num_choices, char** choices_a, Grafo *g)
{
	int x, y, i;
    FILE *teste, *f;
    f = fopen("gg.txt","w");
    char palavra[4][40];
    char *login, *nome, *email, *senha;
    teste = fopen("usuarios.txt", "a");
    assert(teste != NULL);

	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < n_choices_cadastro ; i++)
	{
        mvprintw(y, x, "%s", choices_a[i]);
        refresh();
        echo();
        getstr(palavra[i]);
        fprintf(teste,"%s|", palavra[i]);
		y++;
	}
	fprintf(teste,"\n");
	login = palavra[0];
	nome = palavra[1];
	email = palavra[2];
	senha = palavra[3];
	
	adiciona_vertice(g, 1, login, nome, email, senha);
	fprintf(f, "%s %s %s %s\n", g->inicio->login, g->inicio->nome, g->inicio->email, g->inicio->senha);
    fclose(f);
	fclose(teste);
}


//Função de cadastro
void UI_Cadastro(Grafo *g)
{
	FIELD *field[4];
	FORM  *my_form;
	int ch, i = 0;
	char palavra[40];
	FILE *teste;
	WINDOW *menu_win;
    teste = fopen("teste.txt", "a");

	/* Initialize curses */
	initscr();
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	printw("A Big string which i didn't care to type fully ");
	mvchgat(0, 0, -1, A_BLINK, 1, NULL);
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;

	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win, TRUE);
    refresh();
	print_menu_c(menu_win, n_choices_cadastro, choices_cadastro, g);

	UI_Inicializador(g);

	mvprintw(23, 0, "You chose choice with choice string \n");
    clrtoeol();
	refresh();

	//if (choice == 1)
	delwin(menu_win);
	endwin();
}

void print_menu_login(WINDOW *menu_win, int num_choices, char** choices_a, Grafo *g)
{
	int x, y, i;
	Vertice *aux;

	char palavra[2][40];
	char *login, *senha;

	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < n_choices_login; i++)
	{
        mvprintw(y, x, "%s", choices_a[i]);
        refresh();
        echo();
        getstr(palavra[i]);
		y++;
	}
	login = palavra[0];
	senha = palavra[1];

	aux = verificador_login(g, login, senha); 

	if (aux == NULL)
	{	
		mvprintw(y, x, "Usuário ou senha incorreta. Tente novamente!");
        refresh();
        getch();
        UI_Login(g);

	}
	else
	{
		UI_PaginaInicial(g, aux);
	}


}

//Função de cadastro
void UI_Login(Grafo *g)
{
	FIELD *field[4];
	FORM  *my_form;
	int ch, i = 0;
	char palavra[40];
	WINDOW *menu_win;
   

	/* Initialize curses */
	initscr();
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	printw("A Big string which i didn't care to type fully ");
	mvchgat(0, 0, -1, A_BLINK, 1, NULL);
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;

	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win, TRUE);
    refresh();
	print_menu_login(menu_win, n_choices_login, choices_login, g);
	mvprintw(23, 0, "You chose choice with choice string \n");
    clrtoeol();
	refresh();

	//if (choice == 1)
	delwin(menu_win);
	endwin();

}


//Pagina Inicial
void UI_PaginaInicial(Grafo *g, Vertice *aux)
{
	WINDOW *menu_win;
	int highlight = 1;
	int choice = 0;
	int c = 0;

	initscr();
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	printw("A Big string which i didn't care to type fully ");
	mvchgat(0, 0, -1, A_BLINK, 1, NULL);
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
	startx = (30 - WIDTH) / 2;
	starty = (15 - HEIGHT) / 2;

	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win, TRUE);
	mvprintw(0, 0, "No que você está pensando, usuário?");
	refresh();
	print_menu(menu_win, highlight, n_choices_pagina_inicial, choices_pagina_inicial);
	while(1)
	{	c = wgetch(menu_win);
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_choices_pagina_inicial;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices_pagina_inicial)
					highlight = 1;
				else
					++highlight;
				break;
			case 10:
				choice = highlight;
				break;
			default:
				mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
				refresh();
				break;
		}
		print_menu(menu_win, highlight, n_choices_pagina_inicial, choices_pagina_inicial);
		if(choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}
	mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices_pagina_inicial[choice - 1]);
	clrtoeol();
	refresh();
	if (choice == 1){
     	UI_Amizade(g, aux);
	}
	else if(choice == 2)
	{
		UI_Cadastro(g);
	}
	delwin(menu_win);
	endwin();
	delwin(menu_win);
}

void UI_Amizade(Grafo *g, Vertice *aux)
{
    FILE *teste;
    int i = 0;
	WINDOW *menu_win;
	int highlight = 1;
	int choice = 0;
	int c = 0;

	initscr();
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	printw("A Big string which i didn't care to type fully ");
	mvchgat(0, 0, -1, A_BLINK, 1, NULL);
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;

	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win, TRUE);
	mvprintw(0, 0, "Bem vindo a Rede Social Enconnomica!");
	refresh();
	print_menu(menu_win, highlight, n_choices_amizade, choices_amizade);
	while(1)
	{	c = wgetch(menu_win);
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_choices_amizade;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices_amizade)
					highlight = 1;
				else
					++highlight;
				break;
			case 10:
				choice = highlight;
				break;
			default:
				mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
				refresh();
				break;
		}
		print_menu(menu_win, highlight, n_choices_amizade, choices_amizade);
		if(choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}
	switch(choice)
	{	case 1:
				if(highlight == 1)
					highlight = n_choices_amizade;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices_amizade)
					highlight = 1;
				else
					++highlight;
				break;
			case 10:
				choice = highlight;
				break;
			default:
				mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
				refresh();
				break;
	}
	mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices_amizade[choice - 1]);
	clrtoeol();
	refresh();
	if (choice == 1){
     	UI_Amigos(g, aux);
	}
	else if(choice == 2)
	{
		UI_AdicionarAmigos(g, aux);
	}


	delwin(menu_win);
	endwin();
	delwin(menu_win);
	return;
}



void print_menu_add_amigos(WINDOW *menu_win, int highlight, int num_choices, Grafo *g, Vertice *aux)
{
	int x, y, i;
	Vertice *atual;
	atual = g->inicio;

	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < num_choices; ++i)
	{	
		if(atual->nome != aux->nome)
		{
			if(highlight == i + 1) /* High light the present choice */
			{	
				wattron(menu_win, A_REVERSE);
				mvwprintw(menu_win, y, x, "%s", atual->nome);
				wattroff(menu_win, A_REVERSE);
			}
			else
				mvwprintw(menu_win, y, x, "%s", atual->nome);
			++y;
		}
		
		atual = atual->prox;
	}
	wrefresh(menu_win);
}


void UI_AdicionarAmigos(Grafo *g, Vertice *aux)
{
    FILE *teste;
    int i = 0;
	WINDOW *menu_win;
	int highlight = 1;
	int choice = 0;
	int c = 0;
	char **choices_adicionar_amigos;
	int n_choices_adicionar_amigos;
	Vertice *atual = NULL;

	initscr();
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	printw("A Big string which i didn't care to type fully ");
	mvchgat(0, 0, -1, A_BLINK, 1, NULL);
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;

	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win, TRUE);
	mvprintw(0, 0, "Bem vindo a Rede Social Enconnomica!");
	refresh();
	//quantos vertices tem o grafo
	n_choices_adicionar_amigos = total_vertice(g);

	print_menu_add_amigos(menu_win, highlight, n_choices_adicionar_amigos, g, aux);
	while(1)
	{	c = wgetch(menu_win);
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_choices_adicionar_amigos;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices_adicionar_amigos)
					highlight = 1;
				else
					++highlight;
				break;
			case 10:
				choice = highlight;
				break;
			default:
				mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
				refresh();
				break;
		}
		print_menu_add_amigos(menu_win, highlight, n_choices_adicionar_amigos, g, aux);
		if(choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}
	switch(choice)
	{	case 1:
				if(highlight == 1)
					highlight = n_choices_adicionar_amigos;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices_adicionar_amigos)
					highlight = 1;
				else
					++highlight;
				break;
			case 10:
				choice = highlight;
				break;
			default:
				mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
				refresh();
				break;
	}
	//mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices_[choice - 1]);
	clrtoeol();
	refresh();

	atual = g-> inicio;

	for(i = 1; i < choice; i++)
	{
		atual = atual->prox;
	}

	adiciona_aresta(g, aux->id, atual->id);
	adiciona_aresta(g, atual->id, aux->id);

	UI_Amizade(g, aux);

	delwin(menu_win);
	endwin();
}


void print_menu_amigos(WINDOW *menu_win, Grafo *g, Vertice *aux)
{
	int x, y, i;
	Aresta *aresta = NULL;
	aresta = aux->p_arestas;
    
	x = 2;
	y = 2;
	box(menu_win, 0, 0);

	while (aresta != NULL){

			mvprintw(y, x, "%s", aresta->p_vertice->nome);
			refresh();

            aresta = aresta->prox;
            y++;
    }

}


void UI_Amigos(Grafo *g, Vertice *aux)
{
	FIELD *field[4];
	FORM  *my_form;
	int ch, i = 0;
	WINDOW *menu_win;

	/* Initialize curses */
	initscr();
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	printw("A Big string which i didn't care to type fully ");
	mvchgat(0, 0, -1, A_BLINK, 1, NULL);
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;

	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win, TRUE);
    refresh();
	print_menu_amigos(menu_win, g, aux);

	mvprintw(23, 0, "You chose choice with choice string \n");
    clrtoeol();
	refresh();
	getch();

	UI_Amizade(g, aux);

	//if (choice == 1)
	delwin(menu_win);
	endwin();
}