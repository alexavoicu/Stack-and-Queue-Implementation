/*VOICU Alexa-Andreea-312CD*/
#include <stdlib.h>
#include <stdio.h>
#include "ListSort.h"

Node *createNode(char elem)
{
	Node *node = malloc(sizeof(struct Node));
 	node->elem = elem;
 	node->prev = node->next = NULL;
	return node;
}

List* createList(void)
{
	List *list = malloc(sizeof(struct List));
	list->first = list->last = NULL;
	return list;
}

List* initList(List* list)
{
    Node* sentinel = createNode(' ');
    list->first = list->last = sentinel;
    return list;
}

Band* createBand(void)
{
    Band* band = malloc(sizeof(struct Band));
    List* list = createList();
    band->list = initList(list);
    band->current = band->list->first;
    return band;
}

void moveleft(Band* band)
{
    Node* sentinel = band->list->first;
    if (band->current == sentinel->next)
        return;
    band->current = band->current->prev;
    return;
}

void moveright(Band* band)
{
    if (band->current->next == NULL) {    //cazul in care s-a ajuns in capatul din dreapta
        Node* node = createNode('#');   //si trebuie inserat un nod nou
        band->current->next = node;
        node->prev = band->current;
        band->current = band->list->last = node;
        return;
    }
    band->current = band->current->next;
    return;
}

void moverightChar(Band* band, char c)
{
    Node* iter = band->current;
    while(iter->elem != c && iter->next != NULL) {  //parcurg lista pana cand gasesc elem sau ajung la final
        iter = iter->next;
    }
    if(iter->next == NULL && iter->elem != c) {  //cazul in care am ajuns la final si nici ultimul element nu este cel cautat
        Node* node = createNode('#');
        iter->next = node;
        node->prev = iter;
        band->current = band->list->last = node;
        return;
    }
    band->current = iter;
    return;
}

void moveleftChar(Band* band, char c, FILE* output)
{
    Node* iter = band->current;
    while (iter->elem != c && iter->prev != NULL) {
        iter = iter->prev;
    }
    if (iter->prev == NULL) { //cazul in care nici ultimul element nu este cel cautat
        fprintf(output, "ERROR\n");
        return;
    }
    band->current = iter;
    return;
}

void write(Band* band, char c)
{
    band->current->elem = c;
}

void insertLeft(Band* band, char c, FILE* output)
{
    Node* iter =band->current;
    if (band->list->first->next == iter) {    //cazul in care degetul se afla pe santinela si nu se poate insera
        fprintf(output, "ERROR\n");
        return;
    }
    Node* node = createNode(c);
    node->next = iter;
    node->prev = iter->prev;
    iter->prev->next = node;
    iter->prev = node;
    band->current = node;
    return;
}

void insertRight(Band* band, char c)
{
    Node* node = createNode(c);
    Node* iter = band->current;
    if (iter->next == NULL) {    //cazul in care  se ajunge la finalul listei si trebuie  facuta inserare la final
        iter->next = node;
        node->prev = iter;
        band->current = node;
        return;
    }
    iter->next->prev = node;    //inserare la mijloc
    node->next = iter->next;
    iter->next = node;
    node->prev = iter;
    band->current = node;
    return;
}

void showCurrent(Band* band, FILE* output)
{
    Node* current = band->current;
    fprintf(output, "%c\n", current->elem);
    return;
}


void show(Band* band, FILE* output)
{
    Node* iter = band->list->first->next;
    Node* current = band->current;
    while (iter != NULL) {
        if (iter == current) {
            fprintf(output, "|%c|", iter->elem);
        } else
            fprintf(output, "%c", iter->elem);
        iter = iter->next;
    }
    fprintf(output,"\n");
    return;
}

List* freeList(List* list)
{
	if(list == NULL)
    return NULL;
	Node* iter;
	Node* tmp;
	iter = list->first;
	while (iter != NULL) {
		tmp = iter;
		iter = iter->next;
		free(tmp);
	}
	free(list);
	return NULL;
}

Band* freeBand(Band* band)
{
    band->list = freeList(band->list);
    free(band);
    return NULL;
}