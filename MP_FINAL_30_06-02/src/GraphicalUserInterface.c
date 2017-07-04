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

int n_choices = sizeof(choices) / sizeof(char *);
int n_choices_cadastro = sizeof(choices_cadastro) / sizeof(char *);
int n_choices_login = sizeof(choices_login) / sizeof(char *);

void print_menu(WINDOW *menu_win, int highlight, int num_choices, char** choices_a);
void print_menu_c(WINDOW *menu_win, int num_choices, char** choices_a, Grafo g);
void print_menu_login(WINDOW *menu_win, int num_choices, char** choices_a, Grafo g);

//Função inicializadora

void UI_Inicializador(Grafo g)
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


void print_menu_c(WINDOW *menu_win, int num_choices, char** choices_a, Grafo g)
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
	
	adiciona_vertice(g, 3, login, nome, email, senha);
	fprintf(f, "%s %s %s %s\n", g->vertices[g->total_vertices].login, g->vertices[g->total_vertices].nome_completo, g->vertices[g->total_vertices].email, g->vertices[g->total_vertices].senha);
    fclose(f);
	fclose(teste);
}


//Função de cadastro
void UI_Cadastro(Grafo g)
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

void print_menu_login(WINDOW *menu_win, int num_choices, char** choices_a, Grafo g)
{
	FILE *arquivo;
	int x, y, i;

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
        printf("%s\n",palavra[i] );
		y++;
	}
	login = palavra[0];
	senha = palavra[1];

	if (vertice_verificador(g, login, senha) != -2)
	{	
		mvprintw(y, x, "Usuário ou senha incorreta. Tente novamente %d", vertice_verificador(g, login, senha));
        refresh();
        getch();
        UI_Login(g);

	}

}




//Função de cadastro
void UI_Login(Grafo g)
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
	delwin(menu_win);
}