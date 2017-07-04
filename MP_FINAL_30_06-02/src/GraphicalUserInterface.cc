#include "GraphicalUserInterface.hpp"
#include <ncurses.h>
#include <string.h>
#include <form.h>
#include <stdlib.h>
#include <assert.h>

#define WIDTH 30
#define HEIGHT 10

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);


int startx = 0;
int starty = 0;

/*
*	Variaveis de controle para manipulação das interfaces graficas
*	Cada choices é responsável por mostrar as informações que serão printadas na interface
*	da sua respectiva janela
*/
char *choices[] = {"Login","Cadastro","Login Administrador","Exit"};
char *choices_cadastro[] = {"Login:", "Nome Completo:", "Email:", "Senha:"};
char *choices_login[] = {"Login:","Senha:"};
char *choices_pagina_inicial[] = {"Amizade", "Transações", "Anunciar", "Configuracao", "Exit"};
char *choices_amizade[] = {"Amigos ","Adicionar Amigos", "VOLTAR"};
char *choices_transacao[] = {"Nova Transacao", "Transacoes Efetivadas", "VOLTAR"};
char *choices_nova_transacao[] = {"Carro", "Bicicleta", "Celular", "Fones de Ouvido", "Computador", "Livros", "VOLTAR"};
char *choices_anunciar[] = {"Titulo:","Descrição:"};
char *choices_configuracao[] = {"Editar Conta","Exlcuir Amigo","Excluir Conta", "VOLTAR"};
char *choices_pagina_administrador[] = {"Pessoas", "Transações", "VOLTAR"};


/*
*	Variaveis de controle para manipulação das interfaces graficas
*	Cada n_choices é responsável por mostrar as informações com o tamanho do numero de
*	seu respectivo choice
*/
int n_choices = sizeof(choices) / sizeof(char *);
int n_choices_cadastro = sizeof(choices_cadastro) / sizeof(char *);
int n_choices_login = sizeof(choices_login) / sizeof(char *);
int n_choices_pagina_inicial = sizeof(choices_pagina_inicial) / sizeof(char *);
int n_choices_amizade = sizeof(choices_amizade) / sizeof(char *);
int n_choices_transacao = sizeof(choices_transacao) / sizeof(char *);
int n_choices_nova_transacao = sizeof(choices_nova_transacao) / sizeof(char *);
int n_choices_anunciar = sizeof(choices_anunciar) / sizeof(char *);
int n_choices_configuracao = sizeof(choices_configuracao) / sizeof(char *);
int n_choices_pagina_administrador = sizeof(choices_pagina_administrador) / sizeof(char *);


/*
*	Funções de controle para manipulação das interfaces graficas
*	Cada print_menu é responsável por mostrar as informações da interface grafica
*	da sua respectiva janela
*/


void print_menu(WINDOW *menu_win, int highlight, int num_choices, char** choices_a);
void print_menu_c(WINDOW *menu_win, int num_choices, char** choices_a, Grafo *g);
void print_menu_login(WINDOW *menu_win, int num_choices, char** choices_a, Grafo *g);
void print_menu_pagina_inicial(WINDOW *menu_win, int highlight, int num_choices, char** choices_a);
void print_menu_add_amigos(WINDOW *menu_win, int highlight, int num_choices, Grafo *g, Vertice *aux);
void print_menu_amigos(WINDOW *menu_win, Grafo *g, Vertice *aux);
void print_menu_anunciar(WINDOW *menu_win, int num_choices, char** choices_a, Grafo *g, char *tipo, Vertice *aux);
void print_menu_busca_anuncio(WINDOW *menu_win, int highlight, int num_choices, Grafo *g, char *tipo, Vertice *logado);
void print_menu_transacacaoefetivada(WINDOW *menu_win, Grafo *g, Vertice *aux);
void print_menu_editar(WINDOW *menu_win, int num_choices, char** choices_a, Grafo *g, Vertice *aux);
void print_menu_login_admin(int num_choices, char** choices_a, Grafo *g);
void print_menu_amigos_admin(Grafo *g);
int print_menu_transacacaoefetivada_admin(WINDOW *menu_win, Grafo *g, Vertice *aux, int x, int y);

/*
*	Função da interface grafica responsável pela pagina inicial da aplicação
*/

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
	else if(choice == 3)
	{
		print_menu_login_admin(n_choices_login, choices_login, g);
		UI_Administrador(g);
	}

	else
	{
		delwin(menu_win);
		endwin();
		exit(0);

	}

	delwin(menu_win);
	endwin();
}

/*
*	Função da interface grafica responsável pela pagina inicial da aplicação para informar as
*	informações da tela
*/
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

/*
*	Função da interface grafica responsável pela pagina de cadastro da aplicação para informar as
*	informações da tela
*/
void print_menu_c(WINDOW *menu_win, int num_choices, char** choices_a, Grafo *g)
{
	int x, y, i, id;
    FILE *teste;
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

		y++;
	}
	login = palavra[0];
	nome = palavra[1];
	email = palavra[2];
	senha = palavra[3];
	if(g->inicio == NULL)
	{
		id = 0;
	}
	else
	{
		id = g->inicio->id;
	}
	adiciona_vertice(g,id + 1, login, nome, email, senha);
	fprintf(teste, "%d %s %s %s %s\n", g->inicio->id ,g->inicio->login, g->inicio->nome, g->inicio->email, g->inicio->senha);
	fclose(teste);
}

/*
*	Função da interface grafica responsável pela pagina de cadastro da aplicação
*/
void UI_Cadastro(Grafo *g)
{
	int ch, i = 0;
	char palavra[40];
	FILE *teste;
	WINDOW *menu_win;
    teste = fopen("teste.txt", "a");

	/* Initialize curses */
	initscr();
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
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

    clrtoeol();
	refresh();

	delwin(menu_win);
	endwin();
}

/*
*	Função da interface grafica responsável pela pagina de login do administrador da aplicação para informar as
*	informações da tela
*/
void print_menu_login_admin(int num_choices, char** choices_a, Grafo *g)
{
	int x, y;
	Vertice *aux = NULL;;

	char palavra[2][40];
	char *login, *senha;

	int ch, i = 0;
	WINDOW *menu_win1;
   

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

	menu_win1 = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win1, TRUE);
    refresh();

	x = 2;
	y = 2;
	box(menu_win1, 0, 0);
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
	if(strcmp(login, "admin") != 0 || strcmp(senha, "admin")!= 0)
	{
		mvprintw(y, x, "Usuário ou senha incorreta. Tente novamente!");
        refresh();
        getch();
        print_menu_login_admin(num_choices, choices_a, g);
	}

}

/*
*	Função da interface grafica responsável pela pagina de login normal da aplicação para informar as
*	informações da tela
*/
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
		wrefresh(menu_win);
		UI_PaginaInicial(g, aux);
	}


}

/*
*	Função da interface grafica responsável pela pagina de login normal da aplicação
*/
void UI_Login(Grafo *g)
{
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

    clrtoeol();
	refresh();

	delwin(menu_win);
	endwin();

}

/*
*	Função da interface grafica responsável pela pagina inicial da aplicação
*/
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
		UI_Transacao(g, aux);
	}
	else if(choice == 3)
	{
		UI_Anunciar(g, aux);
	}
	else if(choice ==4)
	{
		UI_Configuracoes(g, aux);
	}
	else
	{
		UI_Inicializador(g);
	}
	delwin(menu_win);
	endwin();
}

/*
*	Função da interface grafica responsável pela pagina de Amizade da aplicação
*/
void UI_Amizade(Grafo *g, Vertice *aux)
{
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
	else if(choice == 3)
	{
		UI_PaginaInicial(g, aux);
	}

	delwin(menu_win);
	endwin();
}


/*
*	Função da interface grafica responsável pela pagina que adiciona amigos da aplicação para informar as
*	informações da tela
*/
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
    FILE *aresta;
    int i = 0;
	WINDOW *menu_win;
	int highlight = 1;
	int choice = 0;
	int c = 0;
	char **choices_adicionar_amigos;
	int n_choices_adicionar_amigos;
	Vertice *atual = NULL;
	aresta = fopen("aresta.txt", "a");

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
	fprintf(aresta, "%d %d\n", aux->id, atual->id);
	adiciona_aresta(g, atual->id, aux->id);
	fprintf(aresta, "%d %d\n", atual->id, aux->id);

	fclose(aresta);

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
	y = 5;
	box(menu_win, 0, 0);

	while (aresta != NULL){

			mvprintw(y, x, "%s", aresta->p_vertice->nome);
			refresh();

            aresta = aresta->prox;
            y++;
    }
	wrefresh(menu_win);
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

void UI_Transacao(Grafo *g, Vertice *aux)
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
	refresh();
	print_menu(menu_win, highlight, n_choices_transacao, choices_transacao);
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
		print_menu(menu_win, highlight, n_choices_transacao, choices_transacao);
		if(choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}
	switch(choice)
	{	case 1:
				if(highlight == 1)
					highlight = n_choices_transacao;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices_transacao)
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
	if (choice == 1){
     	UI_Nova_Transacao(g, aux);
	}
	else if(choice == 2)
	{
		UI_Transacao_Efetivada(g, aux);
	}
	else if(choice ==3)
	{
		UI_PaginaInicial(g, aux);
	}

	delwin(menu_win);
	endwin();
}


void UI_Nova_Transacao(Grafo *g, Vertice *aux)
{
    
	
	UI_Busca_Anuncio(g, aux, UI_Tipo_Produto(g, aux));

}




void print_menu_busca_anuncio(WINDOW *menu_win, int highlight, int num_choices, Grafo *g, char *tipo, Vertice *logado)
{
	int x, y, i;
	//Vertice *atual;
	//Anuncio *aux;
	//atual = g->inicio;
	//aux = g->inicio->p_anuncios;
	initscr();
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	printw("A Big string which i didn't care to type fully ");
	mvchgat(0, 0, -1, A_BLINK, 1, NULL);
	clear();
	noecho();
	cbreak();

	x = 0;
	y = 6;
	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;

	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win, TRUE);
    refresh();

	box(menu_win, 0, 0);
	refresh();

	Vertice *atual = NULL;
    Anuncio *aux = NULL;
    
    for(atual = g->inicio; atual != NULL; atual = atual->prox )
    {
        for (aux = atual->p_anuncios; aux != NULL; aux = aux->prox)
        {
            if(!strcmp(aux->tipo, tipo))
            {
                mvprintw(y, x, "Login: %s |Titulo: %s |Descricacao: %s\n", atual->login, aux->titulo, aux->descricao);
                y++;
            }
        }
           
    }

    if(y == 6)
    {
    	mvprintw(y, x, "Nenhum produto deste tipo cadastrado tente outro");
    	getch();
    	UI_Transacao(g, logado);
    }

	//for(i = 0; i < num_choices; ++i)
	//{	
		
			//if(highlight == i + 1) /* High light the present choice */
			//{	
		//		wattron(menu_win, A_REVERSE);
				//mvprintw(y, x, "Titulo: %s Descricacao: %s\n", aux->titulo, aux->descricao);
		//		wattroff(menu_win, A_REVERSE);
		//	}
			//else
				//mvwprintw(menu_win, y, x, "%s %s", aux->titulo, aux->descricao);
	//		++y;
	
		
		//atual = atual->prox;
	//}
	wrefresh(menu_win);
}



void UI_Busca_Anuncio(Grafo *g, Vertice *aux, int choices_2)
{
    int i = 0;
	WINDOW *menu_win;
	int highlight = 1;
	int choice = 0;
	int c = 0;
	char *tipo;
	char titulo[40], login[40], avaliacao[5], SimOuNao[5];
	int n_choices_busca_anuncio;
	Vertice *atual = NULL;
	Vertice *novo;
	FILE *transacao;
	transacao = fopen("transacao.txt", "a");

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
	box(menu_win, 0, 0);
	mvprintw(0, 0, "Bem vindo a Rede Social Enconnomica!");
	refresh();
	switch(choices_2)
	{
		case 1:
			tipo = (char *)malloc(sizeof(char) * 6 );
			strcpy(tipo, "Carro");
			break;
		case 2:
			tipo = (char *)malloc(sizeof(char) * 10);
			strcpy(tipo, "Bicicleta");
			break;
		case 3:
			tipo = (char *)malloc(sizeof(char) * 8 );
			strcpy(tipo, "Celular");
			break;
		case 4:
			tipo = (char *)malloc(sizeof(char) * 16);
			strcpy(tipo, "Fones de Ouvido");
			break;
		case 5:
			tipo = (char *)malloc(sizeof(char) * 11);
			strcpy(tipo, "Computador");
			break;
		case 6:
			tipo = (char *)malloc(sizeof(char) * 7);
			strcpy(tipo, "Livros");
			break;
		case 7:
			UI_Transacao(g, aux);
			break;

	}
	n_choices_busca_anuncio = busca_anuncio_grafo(g, tipo);


	print_menu_busca_anuncio(menu_win, highlight, n_choices_busca_anuncio, g, tipo, aux);


	
	mvprintw(2, 0, "Voce quer mesmo fazer uma transacao s/n: ");
	refresh();
	echo();
	getstr(SimOuNao);
	if(strcmp(SimOuNao,"n") != 0)
	{
	mvprintw(3, 0, "Qual transacao voce escolhe? Digite o login do vendedor:");
	refresh();
	echo();
	getstr(login);
	mvprintw(4, 0, "Digite o titulo do produto:");
	refresh();
	echo();
	getstr(titulo);
	mvprintw(5, 0, "Avalie a transação: de 1 a 5:");
	refresh();
	echo();
	getstr(avaliacao);
	}
	else
		UI_Transacao(g, aux);

	novo = busca_login(g, login);
	
	adiciona_transacao(aux, novo, atoi(avaliacao), busca_anuncio(g, login, titulo));

	fprintf(transacao, "%s %s %s %s\n", aux->login, novo->login, titulo, avaliacao);

	fclose(transacao);
	


	retira_anuncio(g, login, titulo);

	UI_Transacao(g, aux);
	
	refresh();
	getch();

	delwin(menu_win);
	endwin();
}



int UI_Tipo_Produto(Grafo *g, Vertice *aux)
{
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
	refresh();
	print_menu(menu_win, highlight, n_choices_nova_transacao, choices_nova_transacao);
	while(1)
	{	c = wgetch(menu_win);
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_choices_nova_transacao;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices_nova_transacao)
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
		print_menu(menu_win, highlight, n_choices_nova_transacao, choices_nova_transacao);
		if(choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}
	switch(choice)
	{	case 1:
				if(highlight == 1)
					highlight = n_choices_nova_transacao;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices_nova_transacao)
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
	

	delwin(menu_win);
	endwin();
	return choice;
}


void print_menu_anunciar(WINDOW *menu_win, int num_choices, char** choices_a, Grafo *g, char *tipo, Vertice *aux)
{
	int x, y, i;
    FILE *anuncio;
    //f = fopen("gg.txt","w");
    char palavra[2][80];
    char *titulo, *descricao;
    anuncio = fopen("anuncio.txt", "a");
    //assert(teste != NULL);


	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < n_choices_anunciar; i++)
	{
        mvprintw(y, x, "%s", choices_a[i]);
        refresh();
        echo();
        getstr(palavra[i]);
        //fprintf(teste,"%s|", palavra[i]);
		y++;
	}
	//fprintf(teste,"\n");
	titulo = palavra[0];
	descricao = palavra[1];

	adiciona_anuncio(aux, tipo, titulo, descricao);
	fprintf(anuncio, "%s %s %s %s\n", aux->login, tipo, titulo, descricao);

	fclose(anuncio);

}


//Função de cadastro
void UI_Anunciar(Grafo *g, Vertice *aux)
{

	
	int ch, i = 0;

	WINDOW *menu_win;
	char *tipo;
  
  	ch = UI_Tipo_Produto(g, aux);

  	switch(ch)
	{
		case 1:
			tipo = (char *)malloc(sizeof(char) * 6 );
			strcpy(tipo, "Carro");
			break;
		case 2:
			tipo = (char *)malloc(sizeof(char) * 10);
			strcpy(tipo, "Bicicleta");
			break;
		case 3:
			tipo = (char *)malloc(sizeof(char) * 8 );
			strcpy(tipo, "Celular");
			break;
		case 4:
			tipo = (char *)malloc(sizeof(char) * 16);
			strcpy(tipo, "Fones de Ouvido");
			break;
		case 5:
			tipo = (char *)malloc(sizeof(char) * 11);
			strcpy(tipo, "Computador");
			break;
		case 6:
			tipo = (char *)malloc(sizeof(char) * 7);
			strcpy(tipo, "Livros");
			break;
		case 7:
			UI_PaginaInicial(g, aux);
			break;

	}

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
    mvprintw(0, 0, "Cadastre um Produto!");
	print_menu_anunciar(menu_win, n_choices_anunciar, choices_anunciar, g, tipo, aux);

	UI_PaginaInicial(g, aux);


	mvprintw(23, 0, "You chose choice with choice string \n");
    clrtoeol();
	refresh();
	//if (choice == 1)
	delwin(menu_win);
	endwin();
}

void print_menu_editar(WINDOW *menu_win, int num_choices, char** choices_a, Grafo *g, Vertice *aux)
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
	
	strcpy(aux->login, login);
	strcpy(aux->nome, nome);
	strcpy(aux->email, email);
	strcpy(aux->senha, senha);
	
}




void UI_Configuracoes(Grafo *g, Vertice *aux)
{
    int i = 0;
	WINDOW *menu_win;
	Vertice *amigo = NULL;
	int highlight = 1;
	int choice = 0;
	int c = 0;
	char nome[40];

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
	print_menu(menu_win, highlight, n_choices_configuracao, choices_configuracao);
	while(1)
	{	c = wgetch(menu_win);
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_choices_configuracao;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices_configuracao)
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
		print_menu(menu_win, highlight, n_choices_configuracao, choices_configuracao);
		if(choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}
	switch(choice)
	{	case 1:
				if(highlight == 1)
					highlight = n_choices_configuracao;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices_configuracao)
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
	//mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);
	clrtoeol();
	refresh();
	if (choice == 1){
     	print_menu_editar(menu_win, n_choices_cadastro, choices_cadastro, g, aux);
     	UI_Configuracoes(g, aux);
	}
	else if(choice == 2)
	{

		print_menu_amigos(menu_win, g, aux);
		mvprintw(2, 0, "Digite o nome do amigo para excluir: ");
		refresh();
		echo();
		getstr(nome);

		amigo = g->inicio;
		while(amigo != NULL)
		{
			if(strcmp(amigo->nome, nome) == 0)
			{
				break;
			}
			amigo = amigo->prox;
		}

		remove_aresta(g, aux->id, amigo->id);
		remove_aresta(g, amigo->id, aux->id);

		UI_Configuracoes(g, aux);

	}
	else if(choice ==3)
	{

		amigo = g->inicio;
		while(amigo != NULL)
		{
			remove_aresta(g, aux->id, amigo->id);
			remove_aresta(g, amigo->id, aux->id);
			amigo = amigo->prox;


		}
		
		remove_vertice(g, aux->id);

		UI_Inicializador(g);
	}
	else if(choice == 4)
	{
		UI_PaginaInicial(g, aux);
	}


	delwin(menu_win);
	endwin();
}


void print_menu_transacacaoefetivada(WINDOW *menu_win, Grafo *g, Vertice *aux)
{
	int x, y, i;
	Transacao *transacao = NULL;
	transacao = aux->p_transacao;
    
	x = 2;
	y = 2;
	box(menu_win, 0, 0);

	while (transacao != NULL)
	{
		mvprintw(y, x, "Vendedor: %s | Comprador: %s | Titulo: %s | Descricacao: %s |", transacao->login->login, transacao->comprador->login, transacao->titulo, transacao->descricao);
		refresh();

        transacao = transacao->prox;
        y++;
    }

	wrefresh(menu_win);
}


void UI_Transacao_Efetivada(Grafo *g, Vertice *aux)
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
	print_menu_transacacaoefetivada(menu_win, g, aux);

	mvprintw(23, 0, "You chose choice with choice string \n");
    clrtoeol();
	refresh();
	getch();

	UI_Transacao(g, aux);
	
	delwin(menu_win);
	endwin();
}



void print_menu_amigos_admin(Grafo *g)
{
	
	
	int ch, i = 0;
	char palavra[40];

	WINDOW *menu_win1;
   

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

	menu_win1 = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win1, TRUE);
    refresh();

	int x = 2;
	int y = 2;
	box(menu_win1, 0, 0);


	Vertice *atual;
	Aresta *aresta;
	for(atual = g->inicio; atual != NULL; atual = atual->prox)
	{	
			 /* High light the present choice */		
			mvprintw(y, x, "Id: %d| Login: %s| Nome: %s| Email: %s| Senha: %s| ", atual->id, atual->login,atual->nome,atual->email,atual->senha);
			refresh();
			y++;
			for (aresta = atual->p_arestas; aresta != NULL; aresta = aresta->prox)
			{
				mvprintw(y, x, "Amigo: Id: %d| Login: %s|", aresta->p_vertice->id, aresta->p_vertice->login);
				refresh();
				y++;

			}
	}

}

int print_menu_transacacaoefetivada_admin(WINDOW *menu_win, Grafo *g, Vertice *aux, int x, int y)
{
	
	Transacao *transacao = NULL;
	transacao = aux->p_transacao;

	while (transacao != NULL)
	{
		mvprintw(y, x, "Vendedor: %s | Comprador: %s | Titulo: %s | Descricacao: %s | avaliacao: %d", transacao->login->login, transacao->comprador->login, transacao->titulo, transacao->descricao, transacao->avaliacao);
		refresh();

        transacao = transacao->prox;
        y++;
    }
	return y;
}

//Pagina Inicial
void UI_Administrador(Grafo *g)
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
	print_menu(menu_win, highlight, n_choices_pagina_administrador, choices_pagina_administrador);
	while(1)
	{	c = wgetch(menu_win);
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_choices_pagina_administrador;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices_pagina_administrador)
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
		print_menu(menu_win, highlight, n_choices_pagina_administrador, choices_pagina_administrador);
		if(choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}
	//mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices_pagina_inicial[choice - 1]);
	clrtoeol();
	refresh();
	if (choice == 1)
	{
		print_menu_amigos_admin(g);
		getch();
		UI_Administrador(g);
	}
	else if(choice == 2)
	{
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
		int x =2, y = 2;

		box(menu_win, 0, 0);
		Vertice *aux = NULL;
		aux = g->inicio;
		while(aux != NULL)
		{
			y = print_menu_transacacaoefetivada_admin(menu_win, g, aux, x, y);
			aux = aux->prox;
		}
		getch();
		UI_Administrador(g);	
	}
	else if(choice == 3)
	{
		UI_Inicializador(g);
	}

	delwin(menu_win);
	endwin();
}