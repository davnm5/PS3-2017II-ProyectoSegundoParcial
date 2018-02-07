#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mxml.h>

#ifndef _HASHT_C
#define _HASHT_C
int t=0;
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
        	for(int i = 0; i < table->size; i++){
			if(table->arreglo[i] != NULL)
				printf("%s\n",table->arreglo[i]->key);
        	}
	}
}

void guardarHash(Hasht* ht,char *c){
	/*
Crea un nuevo archivo y guarda todos los elementos, se basa en recorrer la tabla hash y añadir al archivo*/
		FILE *fp;
		char buf[10];
		if(ht!=NULL){
		mxml_node_t *xml;
    mxml_node_t *data;
    mxml_node_t *node;
    mxml_node_t *s;
		mxml_node_t *elements;
    sprintf(buf, "%d",ht->size);
   xml = mxmlNewXML("1.0");
   data = mxmlNewElement(xml, "hash_table");
		s= mxmlNewElement(data, "size");
						mxmlNewText(s,0,buf);
    elements=mxmlNewElement(data, "elements");
		for(int i = 0; i < ht->size; i++){
						if(ht->arreglo[i] != NULL){
						node = mxmlNewElement(elements,"key");
						mxmlNewText(node, 0,ht->arreglo[i]->key);
					}
				}
	fp = fopen(c, "w+");
	mxmlSaveFile(xml,fp,MXML_NO_CALLBACK);
	fclose(fp);

}
}


Hasht *crear_hash_xml(char* archivo){
/*Nueva función para la librería estática, crea una tabla_hash a partir del archivo XML existente
y busca nodo a nodo y extrae aquellos valores que tengan longitud igual a 6 y los añade a la tabla hash
*/

         FILE *fp  = NULL;
         Hasht *ht;
         int k = 0;

         mxml_node_t * tree = NULL;
         mxml_node_t * node  = NULL;

         fp = fopen (archivo, "r");
         if (fp ){
             tree = mxmlLoadFile (NULL , fp , MXML_OPAQUE_CALLBACK);
         }else {
             perror("Could Not Open the File Provided");
             exit(1);
         }
         if (tree){
                 for (node = mxmlFindElement(tree, tree,NULL,NULL, NULL,MXML_DESCEND);
                         node != NULL;
                         node=mxmlWalkNext (node, NULL, MXML_DESCEND)
                 ){
                         if (node->type  == MXML_ELEMENT) {
                             for (k = 0; k < node->value.element.num_attrs; k++){
                                 if (node->value.element.attrs ){
                                     printf ("Attribute Name :: %s \n", node->value.element.attrs[k].name);
                                     printf ("Attribute Value:: %s \n", node->value.element.attrs[k].value);
                                 }

                             }
                         }

                         else if(node->type == MXML_OPAQUE){
													    if(t==0){
																ht=new_ht(atoi(node->value.element.name));
																t++;
															}

                              if(strlen(node->value.element.name)-1==6)
                                add_ht(ht,node->value.element.name);
                         }

                 }
         }
         if (tree){
            mxmlDelete(tree);
         }
         if (fp){
            fclose(fp);
         }
return ht;
}





#endif
