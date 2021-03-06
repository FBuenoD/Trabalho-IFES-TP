/*
Arquivo: lista_clientes.c (Implementacao das funcoes do Cliente)

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_clientes.h"

// funcao que inicializa a lista
ListaClientes* ListaClientes_inicializa (){
	ListaClientes *nova = (ListaClientes *) malloc(sizeof(ListaClientes));
	if (!nova){
		printf("Funcao inicializa: nao foi possivel alocar espaco para uma nova ListaClientes. ");
		exit(1);
	}

	/* Inicializa os dados */
	nova->prim = NULL;
	return nova;
}

// imprime os elementos da lista
void ListaClientes_imprime (ListaClientes *lc){
	NoListaClientes *aux; /* variavel auxiliar para percorrer a fila */

	printf("######### Elementos da ListaClientes: ###########\n");
	for (aux = lc->prim; aux != NULL; aux = aux->prox){
		printf("\t\tNOME = %s\n", aux->info.nome);
		printf("Idade = %i \n", aux->info.idade);
	/*
		printf("\t\tCPF = %s\n", aux->info.cpf);
		printf("\t\tNASCIMENTO = %s\n", aux->info.nascimento);
	*/
		printf("\n");
 	}
}

void ImprimiIdade (ListaClientes *lc, int idade){
	NoListaClientes *aux; /* variavel auxiliar para percorrer a fila */

	printf("######### Elementos da ListaClientes Por Idade: ###########\n");
	for (aux = lc->prim; aux != NULL; aux = aux->prox){
		if(aux->info.idade >= idade){
			printf("\t\tNOME = %s\n", aux->info.nome);
			printf("Idade: %i\n",aux->info.idade);
			/*
				printf("\t\tCPF = %s\n", aux->info.cpf);
				printf("\t\tNASCIMENTO = %s\n", aux->info.nascimento);
			*/
			printf("\n");
		}
 	}
}



// retorna 1 se vazia ou 0 se nao vazia
int ListaClientes_vazia (ListaClientes *lc){
	return (lc->prim == NULL);
}


// busca um elemento na lista
int ListaClientes_busca (ListaClientes *lc, char cpf[15]){
	NoListaClientes *aux; 	/* variavel auxiliar para percorrer a lista */
	for (aux = lc->prim; aux != NULL; aux = aux->prox)
		if (strcmp(aux->info.cpf, cpf) == 0)
			return 1;

	// nao achou o elemento
	return 0;
}


// insere elemento novo na lista
void ListaClientes_insere (ListaClientes *lc, Cliente cliente){
	NoListaClientes *novo = (NoListaClientes*) malloc(sizeof(NoListaClientes));
	strcpy(novo->info.cpf, cliente.cpf);
	strcpy(novo->info.nome, cliente.nome);
	strcpy(novo->info.nascimento, cliente.nascimento);
	novo->info.idade = cliente.idade;
	novo->prox = lc->prim;
	novo->ant = NULL;
	/* nao esta vazia, ou seja, este nao eh o primeiro elemento da lista */
	if (lc->prim != NULL)
		lc->prim->ant = novo;
	lc->prim = novo;
}

//remove um elemento da lista
int ListaClientes_retira (ListaClientes* lc, char cpf[15]){
	NoListaClientes *aux = lc->prim; /* ponteiro para percorrer a lista*/
	/* procura elemento na lista, guardando anterior */
	while ( (aux != NULL) && ((strcmp(aux->info.cpf, cpf)==0))) {
		aux = aux->prox;
	}
	if(aux != NULL){
		if(aux->prox != NULL)
			aux->prox->ant = aux->ant;
		if(aux->ant != NULL)
			aux->ant->prox = aux->prox;
		else
			lc->prim = aux->prox;
		free(aux);
		return 1;
	}else{
		return 0;
	}
}
