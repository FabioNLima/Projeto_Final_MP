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

int n_choices = sizeof(choices) / sizeof(char *);

void print_menu(WINDOW *menu_win, int highlight, int num_choices, char** choices_a);

//Função inicializadora

void UI_Inicializador()
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
	//if (choice == 1){
     //   teste = fopen("usuarios.txt", "r");

	//}

	delwin(menu_win);
	endwin();
	delwin(menu_win);
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


