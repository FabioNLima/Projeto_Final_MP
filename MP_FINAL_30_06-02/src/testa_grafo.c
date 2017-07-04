
#include "grafo.h"

int main(void)
{
    // Testa a criação de um grafo
    puts("Testa 'cria_grafo (char * nome)':");
    puts("Teste 1");
    Grafo g = cria_grafo("Meu Grafo");
    print_graph(g);
    puts("---------------------------------\n");
    
    puts("Testa 'retorna_nome_grafo(Graph)':");
    puts("Teste 2");
    puts(retorna_nome_grafo(g));
    puts("\n");
    Graph m = NULL;
    puts("Teste 3");
    puts(retorna_nome_grafo(m));
    puts("---------------------------------\n");
   
    
    puts("Testa 'adiciona_vertice(Graph, int x)':\n");
    puts("Teste 4");
    adiciona_vertice(g, 1);
    print_graph(g);
    puts("\nTeste 5");
    adiciona_vertice(g, 1);
    print_graph(g);
    puts("\nTeste 6");
    adiciona_vertice(m, 1);
    print_graph(m);
    
    adiciona_vertice(g, 2);
    adiciona_vertice(g, 3);
    adiciona_vertice(g, 4);
    adiciona_vertice(g, 5);

    puts("---------------------------------\n");
    
    puts("Testa 'remove_vertice(Graph, int x)'\n");
    puts("Teste 7");
    remove_vertice(g, 1);
    print_graph(g);
    puts("\nTeste 8");
    remove_vertice(g, 1);
    print_graph(g);
    puts("\nTeste 9");
    remove_vertice(m, 6);
    print_graph(m);
    puts("---------------------------------\n");


    puts("Testa 'adiciona_aresta(Graph, int x, int y)':\n");
    puts("Teste 10");
    adiciona_aresta(g, 1, 2);
    print_graph(g);
    puts("\nTeste 11");
    adiciona_aresta(g, 2, 4);
    print_graph(g);
    puts("\nTeste 12");
    adiciona_aresta(g, 2, 4);
    print_graph(g);
    puts("\nTeste 13");
    adiciona_aresta(g, 6, 7);
    print_graph(g);
    puts("\nTeste 14");
    adiciona_aresta(m, 1, 2);
    print_graph(m);
    
    adiciona_aresta(g, 2, 1);
    adiciona_aresta(g, 3, 5);
    adiciona_aresta(g, 4, 2);
    adiciona_aresta(g, 4, 3);
    adiciona_aresta(g, 4, 5);
    adiciona_aresta(g, 5, 1);
    adiciona_aresta(g, 5, 3);
    puts("---------------------------------\n");
    
    
    puts("Testa 'remove_aresta(Graph, int x, int y)':\n");
    puts("Teste 15");
    remove_aresta(g, 1, 2);
    print_graph(g);
    puts("\nTeste 16");
    remove_aresta(g, 4, 2);
    print_graph(g);
    puts("\nTeste 17");
    remove_aresta(g, 8, 9);
    print_graph(g);
    puts("\nTeste 18");
    remove_aresta(m, 1, 2);
    print_graph(m);
    puts("---------------------------------\n");
    
    
    puts("Testa 'muda_valor_vertice(Graph, int x, int valor)':\n");
    puts("Teste 19");
    muda_valor_vertice(g, 5, 10);
    print_graph(g);
    puts("\nTeste 20");
    muda_valor_vertice(g, 1, 7);
    print_graph(g);
    puts("\nTeste 21");
    muda_valor_vertice(m, 1, 3);
    print_graph(m);

    puts("---------------------------------\n");
    
    
    
    puts("Testa 'retorna_valor_vertice(Graph, int x)':\n");
    puts("Teste 22");
    printf("%.2f\n", retorna_valor_vertice(g, 1));
    puts("\nTeste 23");
    printf("%.2f\n", retorna_valor_vertice(g, 5));
    puts("\nTeste 24");
    printf("%.2f\n", retorna_valor_vertice(g, 10));
    puts("\nTeste 25");
    printf("%.2f\n", retorna_valor_vertice(m, 10));
    puts("---------------------------------\n");
    
    
    
    puts("Testa 'muda_valor_aresta(Graph, int x, int valor)':\n");
    puts("Teste 26");
    muda_valor_aresta(g, 2, 3, 10);
    print_graph(g);
    puts("\nTeste 27");
    muda_valor_aresta(g, 2, 4, 7);
    print_graph(g);
    puts("\nTeste 28");
    muda_valor_aresta(g, 5, 6, 12);
    print_graph(g);
    puts("\nTeste 29");
    muda_valor_aresta(g, 1, 1, 5);
    print_graph(g);
    puts("\nTeste 30");
    muda_valor_aresta(m, 1, 1, 5);
    print_graph(m);
    puts("---------------------------------\n");
    
    
    
    puts("Testa 'retorna_valor_aresta(Graph, int x, int y)':\n");
    puts("Teste 31");
    printf("%.2f\n", retorna_valor_aresta(g, 2, 4));
    puts("\nTeste 32");
    printf("%.2f\n", retorna_valor_aresta(g, 1, 2));
    puts("\nTeste 33");
    printf("%.2f\n", retorna_valor_aresta(g, 2, 3));
    puts("\nTeste 34");
    printf("%.2f\n", retorna_valor_aresta(m, 2, 3));
    puts("---------------------------------\n");

    
    
    puts("Testa 'adjacente(Graph, int x, int y)':\n");
    puts("Teste 35");
    printf(adjacente(g, 1, 1) ? "true\n" : "false\n");
    puts("\nTeste 36");
    printf(adjacente(g, 2, 4) ? "true\n" : "false\n");
    puts("\nTeste 37");
    printf(adjacente(g, 3, 4) ? "true\n" : "false\n");
    puts("\nTeste 38");
    printf(adjacente(g, 8, 10) ? "true\n" : "false\n");
    puts("\nTeste 39");
    printf(adjacente(m, 8, 10) ? "true\n" : "false\n");
    puts("---------------------------------\n");
    
    
    
    puts("Testa 'vertex * vizinhos(Graph, int x)':\n");
    puts("Teste 40");
    puts("Vizinhos do Vertice 4:");
    vizinhos(g, 4);
    puts("\nTeste 41");
    puts("Vizinhos do Vertice 8:");
    vizinhos(g, 8);
    puts("\nTeste 42");
    puts("Vizinhos do Vertice 1:");
    vizinhos(g, 1);
    puts("\nTeste 43");
    puts("Vizinhos do Vertice 1:");
    vizinhos(m, 8);
    puts("---------------------------------\n");
    
    

    puts("Testa 'destroi_grafo(Graph)':\n");
    puts("Teste 44");
    destroi_grafo(g);
    print_graph(g);
    puts("\nTeste 45");
    destroi_grafo(m);
    print_graph(m);
    puts("---------------------------------\n");

}