/**
* @file grafo.h
* @author Fábio do Nascimento Lima
* @brief Implementa funções gráficas para  uma rede social
*/

#include "grafo.hpp"

#ifndef GRAPHICAL_USER_INTERFACE
#define GRAPHICAL_USER_INTERFACE


/**@fn void UI_Inicializador(Grafo *g);
 * @brief Realiza as operações necessárias para inicializar a interface de usuário e mostra o menu inicial.
 * @param g é um objeto tipo Grafo
 */
void UI_Inicializador(Grafo *g);

/**@fn void UI_FinalizaPrograma()
 * @brief Finaliza a interface gráfica e sai do programa.
 */
void UI_FinalizaPrograma();


/**@fn void UI_Cadastro(Grafo *g);
 * @brief Realiza as operações de cadastro na rede social.
 * @param G é um objeto tipo Grafo
 */ 
void UI_Cadastro(Grafo *g);

/**@fn void UI_Login(Grafo *g);
 * @brief Tela responsável pelo login na rede social
 * @param G é um objeto tipo Grafo
 */ 
void UI_Login(Grafo *g);


/**@fn void UI_PaginaInicial(Grafo *g, Vertice *aux);
 * @brief Tela responsável pelo login na rede social
 * @param G é um objeto tipo Grafo
 * @param Aux é um objeto tipo Vertice
 */ 
void UI_PaginaInicial(Grafo *g, Vertice *aux);


/**@fn void UI_Amizade(Grafo *g, Vertice *aux);
 * @brief Tela responsável pela interface grafica do módulo Amizade
 * @param G é um objeto tipo Grafo
 * @param Aux é um objeto tipo Vertice
 */
void UI_Amizade(Grafo *g, Vertice *aux);


/**@fn void UI_AdicionarAmigos(Grafo *g, Vertice *aux);
 * @brief Tela responsável pela interface grafica do módulo AdicionarAmigos
 * @param G é um objeto tipo Grafo
 * @param Aux é um objeto tipo Vertice
 */
void UI_AdicionarAmigos(Grafo *g, Vertice *aux);


/**@fn void UI_Amigos(Grafo *g, Vertice *aux);
 * @brief Tela responsável pela interface grafica do módulo Amigos
 * @param G é um objeto tipo Grafo
 * @param Aux é um objeto tipo Vertice
 */
void UI_Amigos(Grafo *g, Vertice *aux);


/**@fn void UI_Transacao(Grafo *g, Vertice *aux);
 * @brief Tela responsável pela interface grafica do módulo Transação
 * @param G é um objeto tipo Grafo
 * @param Aux é um objeto tipo Vertice
 */
void UI_Transacao(Grafo *g, Vertice *aux);


/**@fn void UI_Nova_Transacao(Grafo *g, Vertice *aux);
 * @brief Tela responsável pela interface grafica do módulo Nova_Transação
 * @param G é um objeto tipo Grafo
 * @param Aux é um objeto tipo Vertice
 */
void UI_Nova_Transacao(Grafo *g, Vertice *aux);


/**@fn void UI_Busca_Anuncio(Grafo *g, Vertice *aux, int valor);
 * @brief Tela responsável pela interface grafica do módulo Busca_Anuncio
 * @param G é um objeto tipo Grafo
 * @param Aux é um objeto tipo Vertice
 * @param valor
 */
void UI_Busca_Anuncio(Grafo *g, Vertice *aux, int valor);


/**@fn void UI_Anunciar(Grafo *g, Vertice *aux);
 * @brief Tela responsável pela interface grafica do módulo Anunciar
 * @param G é um objeto tipo Grafo
 * @param Aux é um objeto tipo Vertice
 */
void UI_Anunciar(Grafo *g, Vertice *aux);

/**@fn int UI_Tipo_Produto(Grafo *g, Vertice *aux);
 * @brief Tela responsável pela interface grafica do módulo Tipo_Produto
 * @param G é um objeto tipo Grafo
 * @param Aux é um objeto tipo Vertice
 */
int UI_Tipo_Produto(Grafo *g, Vertice *aux);

/**@fn void UI_Transacao_Efetivada(Grafo *g, Vertice *aux);
 * @brief Tela responsável pela interface grafica do módulo Transacao_Efetivada
 * @param G é um objeto tipo Grafo
 * @param Aux é um objeto tipo Vertice
 */
void UI_Transacao_Efetivada(Grafo *g, Vertice *aux);

/**@fn void UI_Configuracoes(Grafo *g, Vertice *aux);
 * @brief Tela responsável pela interface grafica do módulo Transacao_Efetivada
 * @param G é um objeto tipo Grafo
 * @param Aux é um objeto tipo Vertice
 */
void UI_Configuracoes(Grafo *g, Vertice *aux);

/**@fn void UI_Administrador(Grafo *g)
 * @brief Tela responsável pela interface grafica do módulo Administrador
 * @param G é um objeto tipo Grafo
 */
void UI_Administrador(Grafo *g);



#endif
