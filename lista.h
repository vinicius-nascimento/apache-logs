/* 
 * lista.h
 * 
 * Este arquivo contém os protótipos de funções de Alocação, 
 * Inserção, Impressão e Desalocação de Listas Duplamente Encadeadas, 
 * Não Circulares e Sem Nó Cabeça. 
 * 
 * As listas Duplamente Encadeadas, Não Circulares e Sem Nó Cabeça,
 * serão referidas neste arquivo como LDE.
 * 
 * Além dos protótipos supracitados, o arquivo contém as estruturas
 * de uma LDE, de um Registro de Log do Apache e de um registro de 
 * horário, que serão utilizadas no projeto ApacheLogs. 
 * 
 * Todos os protótipos estão adaptados para o projeto apache-logs.
 * 
 * 
 */
 
#ifndef LISTA_H
#define LISTA_H

/*Estrutura de um horario*/
typedef struct horario{
	int hora, minuto, segundo;
}horario;

/*Estrutura de um log*/
typedef struct registo{
	char ip[50];
	char usuario[255];
	char data[35];
	char metodo[255];
	char path[255];
	char http[255];
	int status;
	long int bytes;
	char agente[255];
	horario hms;
}log;

/*Estrutura de uma LDE*/
typedef struct no{   
	log info;       
	struct no *prox;  
	struct no *ant;   
}no;                  

no *novoNo(log ch); // Aloca um novo nó para LDE

no *insereInicio (no *Lista, no *novo); // Insere nó no início de uma LDE

no *insereFim (no *Lista, no *novo); // Insere nó no final de uma LDE

no *insereOrd (no *Lista, no *novo); // Insere nó de forma ordenada em uma LDE

void imprimeNo (no* No); // Imprime nó de uma LDE

void imprimeLista (no *Lista); // Imprime uma LDE

no *desalocaLista (no *Lista); // Desaloca uma LDE

#endif
