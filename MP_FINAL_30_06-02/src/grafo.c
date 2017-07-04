#include "grafo.h"
#include <string.h>
#include <stdio.h>

int ID = 0;

Grafo* cria_grafo(char *nome){
	Grafo *grafo;
	if (nome != NULL){
		grafo = (Grafo *) malloc(sizeof(Grafo));
		if (grafo == NULL)
            return NULL;
		grafo->nome = (char *) malloc(sizeof(char) * (strlen(nome)));
		if (grafo->nome == NULL)
            return NULL;
		strcpy(grafo->nome, nome);
		grafo->inicio = NULL;
		return grafo;
	}
	else
		return NULL;
}

char* retorna_nome_grafo(Grafo *grafo){
	if (grafo != NULL){
        return grafo->nome;
	}
	return NULL;
}

int destroi_grafo(Grafo **grafo){
	if (*grafo != NULL){
		Vertice *p_vertice;
		Aresta *p_aresta;
		p_vertice = (*grafo)->inicio;

		if ((*grafo)->inicio != NULL){
			while (p_vertice != NULL){
				(*grafo)->inicio = (*grafo)->inicio->prox;
				p_aresta = p_vertice->p_arestas;

				while (p_aresta != NULL){
					p_vertice->p_arestas = p_vertice->p_arestas->prox;
					free(p_aresta);
					p_aresta = p_vertice->p_arestas;
				}
				free(p_vertice);
				p_vertice = (*grafo)->inicio;
			}
		}
		free(*grafo);
		*grafo = NULL;
	}
	return 0;
}

int adjacente(Grafo *grafo, int x, int y){
	Vertice *p_vertice_x, *p_vertice_y;
	Aresta *p_aresta;

	if (grafo != NULL){
        p_vertice_x = grafo->inicio;
        while ((p_vertice_x != NULL) && (p_vertice_x->id != x)){
            p_vertice_x = p_vertice_x->prox;
        }
        p_vertice_y = grafo->inicio;
        while ((p_vertice_y != NULL) && (p_vertice_y->id != y)){
            p_vertice_y = p_vertice_y->prox;
        }
        if ((p_vertice_x != NULL) && (p_vertice_y != NULL)){
            p_aresta = p_vertice_x->p_arestas;
            while (p_aresta != NULL){
                if (p_aresta->p_vertice->id == y)
                    return 0;
                p_aresta = p_aresta->prox;
            }

            p_aresta = p_vertice_y->p_arestas;
            while (p_aresta != NULL){
                if (p_aresta->p_vertice->id == x)
                    return 0;
                p_aresta = p_aresta->prox;
            }
        }
	}
	return 1;
}

Vizinhos* vizinhos(Grafo *grafo, int x){
	Vertice *p_vertice;
	Aresta *p_aresta;
	Vizinhos *p_vizinhos, *p_vizinhos_aux;

	p_vizinhos = NULL;

    if (grafo != NULL){
        p_vertice = grafo->inicio;
        while ((p_vertice != NULL) && (p_vertice->id != x)){
            p_vertice = p_vertice->prox;
        }
        if ((p_vertice != NULL) && (p_vertice->p_arestas != NULL)){
            p_aresta = p_vertice->p_arestas;
            while (p_aresta != NULL){
                p_vizinhos_aux = (Vizinhos *)malloc(sizeof(Vizinhos));
                if (p_vizinhos_aux == NULL)
                    return NULL;
                p_vizinhos_aux->prox = p_vizinhos;
                p_vizinhos_aux->p_vertice = p_aresta->p_vertice;
                p_vizinhos = p_vizinhos_aux;
                p_aresta = p_aresta->prox;
            }
        }
    }

	return p_vizinhos;
}

int adiciona_vertice(Grafo *grafo, int x, char *login, char *nome, char *email, char *senha){
	
    Vertice *p_vertice;
    ID++;

    if (grafo != NULL){
        p_vertice = grafo->inicio;
        while ((p_vertice != NULL) && (p_vertice->id != ID)){
            p_vertice = p_vertice->prox;
        }
        if (p_vertice != NULL)
            return 1;

        p_vertice = (Vertice *)malloc(sizeof(Vertice));
        if (p_vertice == NULL)
            return 1;

        p_vertice->id = ID;
        p_vertice->login = (char*)malloc(sizeof(char) * (strlen(login) + 1));
        p_vertice->nome = (char*)malloc(sizeof(char) * (strlen(nome) + 1));
        p_vertice->email = (char*)malloc(sizeof(char) * (strlen(email) + 1));
        p_vertice->senha = (char*)malloc(sizeof(char) * (strlen(senha) + 1));
        strcpy(p_vertice->login, login);

        strcpy(p_vertice->nome, nome);
        strcpy(p_vertice->email, email);
        strcpy(p_vertice->senha, senha);
        p_vertice->p_arestas = NULL;
        p_vertice->prox = grafo->inicio;
        grafo->inicio = p_vertice;
        
        return 0;
    }
    else
    {
        ID--;
        return 1;
    }
}

int remove_vertice(Grafo *grafo, int x){
    Vertice *p_vertice, *p_vertice1;
    Aresta *p_aresta;

    if (grafo != NULL){
        p_vertice = grafo->inicio;
        while ((p_vertice != NULL) && (p_vertice->id != x)){
            p_vertice = p_vertice->prox;
        }

        if (p_vertice == NULL)
            return 1;

        p_vertice = grafo->inicio;
        while (p_vertice != NULL){
            if (p_vertice->id == x){
                if (grafo->inicio == p_vertice){
                    grafo->inicio = grafo->inicio->prox;
                    p_vertice1 = grafo->inicio;
                }
                else
                    p_vertice1->prox = p_vertice->prox;
                p_aresta = p_vertice->p_arestas;
                while (p_aresta != NULL){
                    p_vertice->p_arestas = p_vertice->p_arestas->prox;
                    free(p_aresta);
                    p_aresta = p_vertice->p_arestas;
                }
                free(p_vertice);
                if(p_vertice1 != NULL)
                    p_vertice = p_vertice1;
            }
            if(p_vertice1 != NULL)
                p_vertice1 = p_vertice;
            p_vertice = p_vertice->prox;
        }

        return 0;
    }
    else
        return 1;
}

int adiciona_aresta(Grafo *grafo, int x, int y){
    Vertice *p_vertice_x, *p_vertice_y;
	Aresta *p_aresta;

    if (grafo != NULL){
        p_vertice_x = grafo->inicio;
        while ((p_vertice_x != NULL) && (p_vertice_x->id != x)){
            p_vertice_x = p_vertice_x->prox;
        }
        p_vertice_y = grafo->inicio;
        while ((p_vertice_y != NULL) && (p_vertice_y->id != y)){
            p_vertice_y = p_vertice_y->prox;
        }

        if ((p_vertice_x != NULL) && (p_vertice_y != NULL)){
            p_aresta = p_vertice_x->p_arestas;
            while ((p_aresta != NULL) && (p_aresta->p_vertice->id != y)){
                p_aresta = p_aresta->prox;
            }
            if (p_aresta != NULL)
                return 1;

            p_aresta = (Aresta *)malloc(sizeof(Aresta));
            p_aresta->p_vertice = p_vertice_y;
            p_aresta->prox = p_vertice_x->p_arestas;
            p_vertice_x->p_arestas = p_aresta;
            return 0;
        }
    }
    else
        return 1;
}

int remove_aresta(Grafo *grafo, int x, int y){
    Vertice *p_vertice_x, *p_vertice_y;
	Aresta *p_aresta, *p_aresta1;

    if (grafo != NULL){
        p_vertice_x = grafo->inicio;
        while ((p_vertice_x != NULL) && (p_vertice_x->id != x)){
            p_vertice_x = p_vertice_x->prox;
        }
        p_vertice_y = grafo->inicio;
        while ((p_vertice_y != NULL) && (p_vertice_y->id != y)){
            p_vertice_y = p_vertice_y->prox;
        }
        if ((p_vertice_x != NULL) && (p_vertice_y != NULL)){
            p_aresta = p_vertice_x->p_arestas;
            while ((p_aresta != NULL) && (p_aresta->p_vertice->id != y)){
                p_aresta1 = p_aresta;
                p_aresta = p_aresta->prox;
            }
            if (p_aresta == NULL)
                return 0;

            else{
                if (p_aresta == p_vertice_x->p_arestas){
                    p_vertice_x->p_arestas = p_vertice_x->p_arestas->prox;
                    p_aresta1 = p_vertice_x->p_arestas;
                }
                else
                    p_aresta1->prox = p_aresta->prox;
                free(p_aresta);
                p_aresta = p_aresta1;
            }
            return 0;
        }
        else
            return 1;
    }
    else
        return 1;
}

void *retorna_valor_vertice(Grafo *grafo, int x){
    Vertice *p_vertice;

    if (grafo != NULL){
        p_vertice = grafo->inicio;
        while ((p_vertice != NULL) && (p_vertice->id != x)){
            p_vertice = p_vertice->prox;
        }

        if (p_vertice == NULL)
            return NULL;
        else{
            return p_vertice->valor;
        }
    }
    else
        return NULL;
}

int muda_valor_vertice(Grafo *grafo, int x, void *valor){
    Vertice *p_vertice;

    if (grafo != NULL){
        p_vertice = grafo->inicio;
        while ((p_vertice != NULL) && (p_vertice->id != x)){
            p_vertice = p_vertice->prox;
        }

        if (p_vertice == NULL)
            return 1;
        else{
            p_vertice->valor = valor;
            return 0;
        }
    }
    else
        return 1;
}

void *retorna_valor_aresta(Grafo *grafo, int x, int y){
    Vertice *p_vertice_x, *p_vertice_y;
	Aresta *p_aresta;

    if (grafo != NULL){
        p_vertice_x = grafo->inicio;
        while ((p_vertice_x != NULL) && (p_vertice_x->id != x)){
            p_vertice_x = p_vertice_x->prox;
        }
        p_vertice_y = grafo->inicio;
        while ((p_vertice_y != NULL) && (p_vertice_y->id != y)){
            p_vertice_y = p_vertice_y->prox;
        }

        if ((p_vertice_x != NULL) && (p_vertice_y != NULL)){
            p_aresta = p_vertice_x->p_arestas;
            while ((p_aresta != NULL) && (p_aresta->p_vertice->id != y)){
                p_aresta = p_aresta->prox;
            }
            if (p_aresta == NULL)
                return NULL;

            return p_aresta->valor;
        }
    }
    else
        return NULL;
}

int muda_valor_aresta(Grafo *grafo, int x, int y, void *valor){
    Vertice *p_vertice_x, *p_vertice_y;
	Aresta *p_aresta;

    if (grafo != NULL){
        p_vertice_x = grafo->inicio;
        while ((p_vertice_x != NULL) && (p_vertice_x->id != x)){
            p_vertice_x = p_vertice_x->prox;
        }
        p_vertice_y = grafo->inicio;
        while ((p_vertice_y != NULL) && (p_vertice_y->id != y)){
            p_vertice_y = p_vertice_y->prox;
        }

        if ((p_vertice_x != NULL) && (p_vertice_y != NULL)){
            p_aresta = p_vertice_x->p_arestas;
            while ((p_aresta != NULL) && (p_aresta->p_vertice->id != y)){
                p_aresta = p_aresta->prox;
            }
            if (p_aresta == NULL)
                return 1;

            p_aresta->valor = valor;
            return 0;
        }
    }
    else
        return 1;
}



Vertice *verificador_login(Grafo *g, char *login, char *senha)
{
    Vertice *p_vertice = NULL;

    if (g != NULL){
        p_vertice = g->inicio;
        while ((p_vertice != NULL) && ((strcmp(p_vertice->login,login) != 0) || (strcmp(p_vertice->senha,senha) != 0))){
            p_vertice = p_vertice->prox;
        }

        if (p_vertice == NULL)
            return p_vertice;
        else{
            return p_vertice;
        }
    }
    else
        return p_vertice;
}


int total_vertice(Grafo *g)
{
    Vertice *p_vertice;
    int cont = 0;

    if (g != NULL){
        p_vertice = g->inicio;

        while (p_vertice != NULL){
            p_vertice = p_vertice->prox;
            cont++;
        }
    return cont;
    }
    else
        return cont;
}
/*
char *nomes_vertices(Grafo *g, int x)
{
    Vertice *p_vertice;
    char nomes[x][40];

    if (g != NULL){
        p_vertice = g->inicio;

        //nomes = (char **)malloc((sizeof(p_vertice->nome) + 1) * x);

        while (p_vertice != NULL){
            
            //strcpy(*nomes[contador], p_vertice->nome);
            p_vertice = p_vertice->prox;
        }
    return nomes;
    }
    else
        return nomes;
}*/