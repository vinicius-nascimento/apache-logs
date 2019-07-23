/* 
 * lista.c 
 * 
 * Este arquivo contém as implementações de funções de Alocação, 
 * Inserção, Impressão e Desalocação de Listas Duplamente Encadeadas, 
 * Não Circulares e Sem Nó Cabeça, que serão utilizadas no projeto 
 * ApacheLogs.
 * 
 * As listas Duplamente Encadeadas, Não Circulares e Sem Nó Cabeça,
 * serão referidas neste arquivo como LDE.
 * 
 * Todas as implementações estão adaptadas para o projeto apache-logs.
 *
 * 
 */

#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*Aloca um novo nó para LDE*/
no *novoNo(log ch){
	no *novo = (no *) malloc (sizeof(no));
	if (!novo){
		printf("Erro de alocação.\n");
		return NULL;
	}	
	novo->info = ch;
	novo->prox = NULL;
	novo->ant = NULL;	
	return novo;
}

/*Insere nó no início de uma LDE*/
no *insereInicio (no *Lista, no *novo){
	if (!Lista) return novo;
	novo->prox = Lista;
	Lista->ant = novo;
	return novo;
}

/*Insere nó no final de uma LDE*/
no *insereFim (no *Lista, no *novo){
	if (!Lista) return novo;
	no *aux = Lista;
	while (aux->prox) aux = aux->prox;
	aux->prox = novo;
	novo->ant = aux;
	return Lista;
}

/*Insere nó de forma ordenada em uma LDE*/
no *insereOrd (no *Lista, no *novo){
	if (!Lista) return novo;
	no *aux = Lista;
	while ((aux->prox != NULL) && (aux->info.ip < novo->info.ip)) aux = aux->prox;
	if (aux->info.ip < novo->info.ip){
		novo->ant = aux;
		aux->prox = novo;
		return Lista;	
	}
	if (!aux->ant){
		novo->prox = aux;
		aux->ant = novo;
		return novo; 
	}
	novo->ant = aux->ant;
	novo->prox = aux;
	aux->ant = novo;
	novo->ant->prox = novo;
	return Lista;	
}

/*Imprime nó de uma LDE*/
void imprimeNo (no* No){
	no *aux = No;
	printf("\nIP: %s\nUsuário: %s\nData: %s\nHorário: %d:%d:%d\nMétodo: %s\nPath: %s\nHttp: %s\nStatus: %d\nBytes: %ld\nAgente: %s\n", aux->info.ip, aux->info.usuario, aux->info.data, aux->info.hms.hora, aux->info.hms.minuto, aux->info.hms.segundo, aux->info.metodo, aux->info.path, aux->info.http, aux->info.status, aux->info.bytes, aux->info.agente);
	printf ("\n");	
}

/*Imprime uma LDE*/
void imprimeLista (no *Lista){
	unsigned int i=0;
	no *aux = Lista;
	while (aux){
		i++;
		printf("\nIP: %s\nUsuário: %s\nData: %s\nHorário: %d:%d:%d\nMétodo: %s\nPath: %s\nHttp: %s\nStatus: %d\nBytes: %ld\nAgente: %s\n", aux->info.ip, aux->info.usuario, aux->info.data, aux->info.hms.hora, aux->info.hms.minuto, aux->info.hms.segundo, aux->info.metodo, aux->info.path, aux->info.http, aux->info.status, aux->info.bytes, aux->info.agente);
		aux = aux->prox;	
	}
	printf ("\nQuantidade de registros: %d\n", i);	
}

/*Desaloca uma LDE*/
no *desalocaLista (no *Lista){
	no *aux = Lista;
	while (aux){
		Lista = aux->prox;
		free(aux);
		aux=Lista;
	}
	return NULL;
}
