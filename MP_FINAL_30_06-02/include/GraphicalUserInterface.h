#include "grafo.h"

#ifndef GRAPHICAL_USER_INTERFACE
#define GRAPHICAL_USER_INTERFACE


/**@fn void UI_InicializaGUI()
 * @brief Realiza as operações necessárias para inicializar a interface de usuário e mostra o menu inicial.
 */
void UI_Inicializador(Grafo *g);

/**@fn void UI_FinalizaPrograma()
 * @brief Finaliza a interface gráfica e sai do programa.
 */
void UI_FinalizaPrograma();


/**@fn void UI_Cadastro()
 * @brief Realiza as operações de cadastro na rede social.
 *@param Recebe uma TAD tipo grafo
 */ 
void UI_Cadastro(Grafo *g);

/**@fn void UI_Login()
 * @brief Tela responsável pelo login na rede social
 *@param Recebe uma TAD tipo grafo, para verificar se está cadastrado ou não na rede
 */ 
void UI_Login(Grafo *g);


/**@fn void UI_PaginaInicial()
 * @brief Tela responsável pelo login na rede social
 *@param Recebe uma TAD tipo grafo, para verificar se está cadastrado ou não na rede
 */ 
void UI_PaginaInicial();


#endif
