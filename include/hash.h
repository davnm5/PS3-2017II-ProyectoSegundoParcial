#ifndef _HASHT_H
#define _HASHT_H


typedef struct h_t Hasht;

Hasht *new_ht(int size);
int hash(char *texto);
void *get_ht(Hasht *table, char *c);
int add_ht(Hasht *table, char *c);
void destroy_ht(Hasht *table);
void *remove_ht(Hasht *table, char *c);
void print_ht(Hasht* table);

#endif