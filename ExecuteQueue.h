/*VOICU Alexa-Andreea-312CD*/
#include <stdlib.h>
#include <string.h>

typedef struct ExecNode {
    char c;
    char* instruction;
    struct ExecNode* next;
} ExecNode;

typedef struct queue {
    ExecNode *head, *tail;
    int size;
} *TQueue;

ExecNode *initNode(char c, char* instruc)
{
    ExecNode *node = malloc(sizeof(struct ExecNode));
    node->c = c;
    node->instruction = strdup(instruc);
    node->next = NULL;
    return node;
}

TQueue initQueue(char c, char* instruc)
{    
    TQueue queue = malloc(sizeof(struct queue));
    queue->head = queue->tail = initNode(c, instruc);
    queue->size = 1;
    return queue;
}

TQueue enqueue(TQueue queue, char c, char* instruc)
{
    ExecNode *node;
    if (queue == NULL || queue->head == NULL || queue->size == 0) {
    if (queue == NULL)  //lista vida
    return initQueue(c, instruc);
    free(queue);    //lista nu este vida, dar este goala
    return initQueue(c, instruc);
    }
    node = initNode(c, instruc);
    queue->tail->next = node;
    queue->tail = node;
    queue->size++;
    return queue;
}

ExecNode *freeNode(ExecNode *node)
{
    if (node){
        free(node->instruction);
        free(node);  
    }
    return NULL;
}

TQueue dequeue(TQueue queue)
{
    ExecNode *tmp;
    tmp = queue->head;
    if (queue->head == queue->tail) {
		queue->head = queue->tail = NULL;
		queue->size--;
		tmp = freeNode(tmp);
		return queue;
	}
    queue->head = queue->head->next;
    tmp = freeNode(tmp);
    queue->size--;
    return queue;
}

int isQueueEmpty(TQueue queue)
{
	if (queue == NULL || queue->head == NULL || queue->tail == NULL)
	return 1;
	return 0;
}

void freeQueue(TQueue queue)
{
    while (isQueueEmpty(queue) == 0) {
		dequeue(queue);
	}
	free(queue);
	return;
}