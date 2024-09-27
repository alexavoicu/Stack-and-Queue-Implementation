/*VOICU Alexa-Andreea-312CD*/
#include <stdlib.h>

typedef struct Node{
	char elem; // Stored node value
	struct Node* next; // link to next node
	struct Node* prev; // link to prev node
} Node;

typedef struct List{
	Node* first; // link to the first node
	Node* last; // link to the last node
}List;

typedef struct Band{
	List* list;
	Node* current;
}Band;

Node *createNode(char);
List* createList(void);
List* initList(List*);
Band* createBand(void);
void moveleft(Band*);
void moveright(Band*);
void moverightChar(Band*, char);
void moveleftChar(Band*, char, FILE*);
void write(Band*, char);
void insertLeft(Band*, char, FILE*);
void insertRight(Band*, char);
void showCurrent(Band*, FILE*);
void show(Band*, FILE*);
List* freeList(List*);
Band* freeBand(Band*);