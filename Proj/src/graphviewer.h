#ifndef _GRAPH_VIEWER_H_
#define _GRAPH_VIEWER_H_

#ifdef linux
	#include <unistd.h>
#else
	#include <winsock2.h>
	#include <Windows.h>
#endif

#include <stdlib.h>
#include <signal.h>
#include <string>

#include "edgetype.h"
#include "connection.h"

#define BLUE "BLUE"
#define RED "RED"
#define PINK "PINK"
#define BLACK "BLACK"
#define WHITE "WHITE"
#define ORANGE "ORANGE"
#define YELLOW "YELLOW"
#define GREEN "GREEN"
#define CYAN "CYAN"
#define GRAY "GRAY"
#define DARK_GRAY "DARK_GRAY"
#define LIGHT_GRAY "LIGHT_GRAY"
#define MAGENTA "MAGENTA"

/**
 * Classe que guarda o grafo e o representa. Todas as suas fun��es retornam um booleano a indicar
 * se a sua execu��o decorreu ou n�o com sucesso.
 */
class GraphViewer {
 public:
  /**
   * Vari�vel que guarda a pr�xima porta que o programa vai usar. O valor inicial � 7772.
   */
  static short port;

  /**
   * Construtor que cria um novo grafo e atribui automaticamente a porta.
   * @param width Inteiro que representa a lagura da �rea do grafo.
   * @param height Inteiro que representa a altura da �rea do grafo.
   * @param dynamic Booleano que determina se a localiza��o dos n�s � automaticamente.
   * determinado pelo programa (true) ou se deve ser determinado pelo utilizador (false).
   */
  GraphViewer(int width, int height, bool port_n);

  /**
   * Construtor que cria um novo grafo, utilizando uma porta especificada pelo utilizador para a liga��o.
   * @param width Inteiro que representa a lagura da �rea do grafo.
   * @param height Inteiro que representa a altura da �rea do grafo.
   * @param dynamic Booleano que determina se a localiza��o dos n�s � automaticamente.
   * determinado pelo programa (true) ou se deve ser determinado pelo utilizador (false).
   * @param port_n Inteiro que determina a porta a utilizar. Deve-se ter cuidado para n�o utilizar uma porta
   * j� usada por outro programa ou pelo sistema.
   */
  GraphViewer(int width, int height, bool dynamic, int port_n);

  /**
   * Fun��o que cria a janela para visualiza��o.
   * @param width Largura da janela a criar.
   * @param height Altura da janela a criar.
   */
  bool createWindow(int width, int height);
  /**
   * Fecha a janela a ser utilizada para visualiza��o.
   */
  bool closeWindow();

  /**
   * Acrescenta um n� � representa��o do grafo, numa posi��o espec�fica, irrelevante se o grafo
   * for din�mico.
   * @param id Identificador �nico do n�.
   * @param x Posi��o horizontal do n�.
   * @param y Posi��o vertical do n�.
   */
  bool addNode(int id, int x, int y);
  /**
   * Acrescenta um n� � representa��o do grafo, numa posi��o ao crit�rio do programa.
   * @param id Identificador �nico do n�.
   */
  bool addNode(int id);
  /**
   * Acrescenta uma aresta � representa��o do grafo.
   * @param id Identificador �nico da aresta.
   * @param v1 Identificador �nico do n� de origem da aresta.
   * @param v2 Identificador �nico do n� de destino da aresta.
   * @param edgeType EdgeType.DIRECTED caso a aresta seja unidirecional
   * ou EdgeType.UNDIRECTED caso a aresta seja bidirecional.
   */
  bool addEdge(int id, int v1, int v2, int edgeType);

  /**
   * Remove um n� da representa��o do grafo e todas as arestas ligadas a este.
   * @param id Identificador �nico do n� a a remover.
   */
  bool removeNode(int id);
  /**
   * Remove uma aresta da representa��o do grafo.
   * @param id Identificador �nico da aresta a remover.
   */
  bool removeEdge(int id);

  /**
   * Fun��o que define o texto de um n�.
   * @param id Identificador �nico do n� com o texto a alterar.
   * @param label Novo texto do n�.
   */
  bool setVertexLabel(int id, string label);

  /**
   * Fun��o que define o texto de uma aresta.
   * @param id Identificador �nico da aresta com o texto a alterar.
   * @param label Novo texto da aresta.
   */
  bool setEdgeLabel(int id, string label);
  /**
   * Fun��o que define a cor de uma aresta.
   * @param id Identificador �nico da aresta com a cor a alterar.
   * @param color Nova cor da aresta, utilizar as constantes definidas no graphviewer.h para conveni�ncia.
   */
  bool setEdgeColor(int id, string color);

  /**
   * Fun��o que define a cor de um n�.
   * @param id Identificador �nico do n� com a cor a alterar.
   * @param color Nova cor do n�, utilizar as constantes definidas no graphviewer.h para conveni�ncia.
   */
  bool setVertexColor(int id, string color);

  /**
   * Fun��o que define a cor global das arestas.
   * @param color Nova cor das arestas, utilizar as constantes definidas no graphviewer.h para conveni�ncia.
   */
  bool defineEdgeColor(string color);
  /**
   * Fun��o que define a cor global dos n�s.
   * @param color Nova cor dos n�s, utilizar as constantes definidas no graphviewer.h para conveni�ncia.
   */
  bool defineVertexColor(string color);
  /**
   * Fun��o que define a espessura de uma aresta.
   * @param id Identificador �nico da aresta com a espessura a alterar.
   * @param thickness Nova espessura da aresta, sendo que por base, as
   * arestas s�o criadas com a espessura de 1.
   */
  bool setEdgeThickness(int id, int thickness);

  /**
   * Fun��o que altera a imagem de fundo do grafo.
   * @param path Caminho para o ficheiro com a imagem.
   */
  bool setBackground(string path);

  /**
   * Fun��o que define o peso de uma aresta na representa��o do grafo, a ser visualizado
   * como w: valor_do_peso, seguido de qualquer outro texto associado � aresta.
   * @param id Identificador �nico da aresta a modificar.
   * @param weight Peso associado � aresta.
   */
  bool setEdgeWeight(int id, int weight);
  /**
   * Fun��o que define o fluxo de uma aresta na representa��o do grafo, a ser visualizado
   * como f: valor_do_fluxo, precedido pelo peso e seguido por texto definido pelo utilizador.
   * @param id Identificador �nico da aresta a modificar.
   * @param flow Fluxo associado � aresta.
   */
  bool setEdgeFlow(int id, int flow);

  /**
   * Fun��o que actualiza a visualiza��o do grafo.
   */
  bool rearrange();

#ifdef linux
  static pid_t procId;
#endif

 private:
  int width, height;
  bool isDynamic;

  Connection *con;

  void initialize(int, int, bool, int);
};

#endif
