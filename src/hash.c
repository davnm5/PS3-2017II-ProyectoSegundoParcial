#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _HASHT_C
#define _HASHT_C

typedef struct reg Registro;

int tam;
struct reg{
	char *key;
	struct reg *next;
};

typedef struct reg Registro;

struct h_t{
	int size;
	Registro **arreglo;
};

typedef struct h_t Hasht;


Hasht *new_ht(int size){
	tam=size;
	Hasht *ht = NULL;

	if(size < 1)
		return NULL;

	ht = malloc(sizeof(Hasht));
	if(ht == NULL)
		return NULL;

	ht->arreglo = malloc(sizeof(Registro *) * size);
	if(ht->arreglo == NULL)
		return NULL;

	for(int i = 0; i < size; i++){
		//printf("%d\n",i);
		ht->arreglo[i] = NULL;
	}
	ht->size = size;
	return ht;
}

int hash(char *texto){
	int valor = 0;
	unsigned char *c;
	for(int i = 0; i < strlen(texto)+1; i++){
		c = texto[i-1];
		valor = valor + (i * (int)c);
	}
	return (valor%tam);
}

void *get_ht(Hasht *table, char *c){
	Registro *aux;
	int value = hash(c);
	for(aux = table->arreglo[value]; aux != NULL; aux = aux->next){
		if(strcmp(c, aux->key) == 0)
			return aux;
	}
	return NULL;
}

int add_ht(Hasht *table, char *c){
	Registro *newReg;
	Registro *auxReg;

	int valor = hash(c);
	if(valor > table->size)
		return -1;

	newReg = malloc(sizeof(Registro));
	if(newReg == NULL)
		return -1;

	auxReg = get_ht(table, c);
	if(auxReg != NULL)
		return -1;

	newReg->key = strdup(c);
	newReg->next = table->arreglo[valor];
	table->arreglo[valor] = newReg;
	return 1;
}

void destroy_ht(Hasht *table){
	Registro *tmpReg, *auxReg;

	if(table == NULL)
		return;
	for(int i = 0; i < table->size; i++){
		tmpReg = table->arreglo[i];
		while(tmpReg != NULL){
			auxReg = tmpReg;
			tmpReg = tmpReg->next;
			free(auxReg->key);
			free(auxReg);
		}
	}
	free(table->arreglo);
	free(table);
}

void *remove_ht(Hasht *table, char *c){
	if(table == NULL)
		return NULL;
	Registro *auxReg;
	auxReg = get_ht(table, c);
	if(auxReg != NULL){
		int value = hash(c);
		table->arreglo[value] = auxReg->next;
		free(auxReg->key);
		free(auxReg);
		table->size = table->size -1;
		return table;
	}
	return NULL;

}

void print_ht(Hasht* table){
	if(table != NULL){
		printf("HashTable: \n");
        	for(int i = 0; i < table->size; i++){
			if(table->arreglo[i] != NULL)
				printf("%s\n",table->arreglo[i]->key);
        	}
	}
}


#endif
