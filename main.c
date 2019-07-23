/*
 * main.c
 * 
 * 
 * As informações gerais do programa estão descritas no 
 * arquivo leia-me.txt que se encontra no diretório principal 
 * deste projeto.
 * 
 * 
 */

#include "lista.h"
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>

void menu(void){
	printf("\nMENU - ApacheLogs\n\nDigite o número correspondente à opção desejada:\n\n1 - Carregar dados do arquivo <logs.txt>.\n2 - Buscar um ou mais registros.\n3 - Excluir registro especificado.\n4 - Apresentar registros e suas informações.\n5 - Apresentar quantidade de IPs repetidos.\n6 - Apresentar quantidade de usuários repetidos.\n7 - Informar períodos de maior utilização da rede.\n0 - Encerrar programa.\n\nOpção: ");
}

no *carregaDados (no *Lista){
	no *novo = NULL, *aux = NULL;
	log info;
	int status, i;
	long int bytes;
	char url[] = "logs.txt", ip[20], usuario[255], data[35], metodo[255], path[255], http[255], agente[255], auxHora[3], auxMinuto[3], auxSegundo[3];
	FILE *fp;
	fp = fopen (url,"r");
	while (!feof(fp)){
		fscanf (fp,"%s %s %*s [%s %*d] \"%s %s  %[^\"]\" %d %ld %*s \"%[^\"]\"", ip, usuario, data, metodo, path, http, &status, &bytes, agente);
		strcpy (info.ip,ip);
		strcpy (info.usuario,usuario);
		strcpy (info.data,data);
		strcpy (info.metodo,metodo);
		strcpy (info.path,path);
		strcpy (info.http,http);
		info.status = status;
		info.bytes = bytes;
		strcpy (info.agente,agente);
		auxHora[0] = info.data[12];
		auxHora[1] = info.data[13];
		info.hms.hora = atoi (auxHora);
		auxMinuto[0] = info.data[15];
		auxMinuto[1] = info.data[16];
		info.hms.minuto = atoi (auxMinuto);
		auxSegundo[0] = info.data[18];
		auxSegundo[1] = info.data[19];
		info.hms.segundo = atoi (auxSegundo);
		for (i=11;i<strlen(info.data);i++) info.data[i] = ' ';
		novo = novoNo (info);
		Lista = insereFim (Lista,novo);
	}
	aux = Lista;
	while (aux->prox) aux = aux->prox;
	if (aux->ant) aux->ant->prox = aux->prox;
	else Lista = aux->prox;
	if (aux->prox) aux->prox->ant = aux->ant;
	free(aux);
	fclose(fp);
	return Lista;	
}

void buscaRegistro (no *Lista, char *ip, long int bytes){
	no *aux = Lista;
	unsigned cont=0;
	while (aux){
		if ((strcmp (ip,aux->info.ip) == 0) && bytes == aux->info.bytes){
			imprimeNo (aux);
			cont++;
		}
		aux=aux->prox;
	}
	if (cont == 0) printf ("\nNenhum registro foi encontrado.\n");
	else printf ("\nRegistros buscados e apresentados com sucesso.\n");
	return;
}

no *removeRegistro (no *Lista, char *ip, long int bytes){
	no *aux = Lista;
	unsigned cont=0;
	while (aux){
		if ((strcmp (ip,aux->info.ip) == 0) && bytes == aux->info.bytes){
			if (aux->ant) aux->ant->prox = aux->prox;
			else Lista = aux->prox;
			if (aux->prox) aux->prox->ant = aux->ant;
			free(aux);
			cont++;
		}
		aux=aux->prox;
	}
	if (cont == 0) printf ("\nNenhum registro foi encontrado.\n");
	else printf ("\nRegistro(s) removido(s) com sucesso.\n");
	return Lista;
}

unsigned int ipsRepetidos (no *Lista, char *ip){
	no *aux = Lista;
	unsigned int resp=0;
	while (aux){
		if (strcmp (ip,aux->info.ip) == 0) resp++;
		aux = aux->prox;
	}
	return resp;
}

unsigned int usuRepetidos (no *Lista, char *usuario){
	no *aux = Lista;
	unsigned int resp=0;
	while (aux){
		if (strcmp (usuario,aux->info.usuario) == 0) resp++;
		aux = aux->prox;
	}
	return resp;
}

void horaPico (no *Lista){
	no *aux = Lista;
	unsigned vetHora[24], i=0, maior, auxMaior, auxHora;
	for (i=0;i<24;i++) vetHora[i] = 0;
	while (aux){
		auxHora = aux->info.hms.hora;
		for(i=0;i<24;i++){
			if (i == auxHora) vetHora[i]++;
		}
		aux = aux->prox;
	}
	auxMaior = vetHora[0];
	for (i=0;i<24;i++){
		if (vetHora[i] > auxMaior){
			maior = i;
			auxMaior = vetHora[i];
		}
	}
	printf ("\nIntervalo de maior utilização da rede: das %d às %d horas.\n", maior, maior+1);
}

int main(void){
	no *Lista = NULL;
	char ip[20], usuario[255];
	unsigned int op, quantIp, quantUsu;
	long int bytes;
	do{
		menu ();
		scanf("%d", &op);
		__fpurge (stdin);
		switch (op){
			case 1:
				Lista = desalocaLista (Lista);
				Lista = carregaDados(Lista);
				printf ("\nDados carregados com sucesso.\n");
				break;
			case 2:
				printf ("\nDigite o IP do(s) registro(s) que deseja buscar: ");
				scanf ("%s", ip);
				__fpurge (stdin);
				printf ("Digite o número de bytes do(s) registro(s) que deseja buscar: ");
				scanf ("%ld", &bytes);
				__fpurge (stdin);
				buscaRegistro (Lista,ip,bytes);
				break;
			case 3:
				printf ("\nDigite o IP do(s) registro(s) que deseja remover: ");
				scanf ("%s", ip);
				__fpurge (stdin);
				printf ("Digite o número de bytes do(s) registro(s) que deseja remover: ");
				scanf ("%ld", &bytes);
				__fpurge (stdin);
				Lista = removeRegistro (Lista,ip,bytes);
				break;
			case 4:
				printf ("\nOs registros e suas respectivas informações serão apresentados a seguir:\n");
				imprimeLista(Lista);
				printf ("\nRegistros apresentados com sucesso.\n");
				break;
			case 5:
				printf ("\nDigite o IP do qual deseja obter o número de repetições: ");
				scanf ("%s", ip);
				__fpurge (stdin);
				quantIp = ipsRepetidos(Lista,ip);
				if (quantIp == 0) printf ("\nNenhum IP foi encontrado.\n");
				else printf ("IPs repetidos: %d\n", quantIp); 
				break;
			case 6:
				printf ("\nDigite o usuário do qual deseja obter o número de repetições: ");
				scanf ("%s", usuario);
				__fpurge (stdin);
				quantUsu = usuRepetidos (Lista,usuario);
				if (quantUsu == 0) printf ("\nNenhum usuário foi encontrado.\n");
				else printf ("Usuários repetidos: %d\n", quantUsu); 
				break;
			case 7:
				horaPico (Lista);
				printf ("\nHorário de pico informado com sucesso.\n");
				break;
			case 0:
				Lista = desalocaLista (Lista);
				printf ("\nEncerrando o programa...\n");
			
				break;
			default:
				printf ("\nOpção inválida.\n");
				
		}
	}while(op != 0);
	return 0;
}
