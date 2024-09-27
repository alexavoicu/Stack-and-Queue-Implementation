/*VOICU Alexa-Andreea-312CD*/
#include <stdlib.h>
#include "UndoStack.h"

UndoStack* createUndoStack(void)
{
	UndoStack* s = (UndoStack*) malloc(sizeof(struct UndoStack));
	s->head = NULL;
	s->size = 0;
	return s;
}

int isUndoStackEmpty(UndoStack* stack)
{
	if (stack->size == 0 && stack->head == NULL)
		return 1;
	return 0;
}

UndoNode* createUndoNode(void* current)
{
	UndoNode* node = (UndoNode*) malloc(sizeof(UndoNode));
	node->next = NULL;
	node->current = current;	//pointerul catre pozitia din banda pe care l-am transformat in void*
	return node;
}

void pushUndoStack(UndoStack *stack, void* current)
{
	UndoNode* top;
	top = createUndoNode(current);
    if (isUndoStackEmpty(stack) == 1) {	//verificare stiva goala
        stack->head = top;
		stack->size++;
		return;
    }
	top->next = stack->head;
	stack->head = top;
	stack->size++;
	return;
}

void popUndoStack(UndoStack *stack)
{
	UndoNode* tmp;
	tmp = stack->head;
	stack->head = stack->head->next;
	stack->size--;
	free(tmp);
}

void freeUndoStack(UndoStack *stack)
{
	while (isUndoStackEmpty(stack) == 0) {
		popUndoStack(stack);
	}
	free(stack);
}

RedoStack* createRedoStack(void)
{
	RedoStack* s = (RedoStack*) malloc(sizeof(struct RedoStack));
	s->head = NULL;
	s->size = 0;
	return s;
}

int isRedoStackEmpty(RedoStack* stack)
{
	if (stack->size == 0 && stack->head == NULL)
		return 1;
	return 0;
}

RedoNode* createRedoNode(void* current)
{
	RedoNode* node = (RedoNode*) malloc(sizeof(RedoNode));
	node->next = NULL;
	node-> current = current;
	return node;
}

void pushRedoStack(RedoStack *stack, void* current)
{
	RedoNode* top;
	top = createRedoNode(current);
    if (isRedoStackEmpty(stack) == 1) {	//verificare stiva goala
        stack->head = top;
		stack->size++;
		return;
    }
	top->next = stack->head;
	stack->head = top;
	stack->size++;
	return;
}

void popRedoStack(RedoStack *stack)
{
	RedoNode* tmp;
	tmp = stack->head;
	stack->head = stack->head->next;
	stack->size--;
	free(tmp);
}

void freeRedoStack(RedoStack *stack)
{
	while (isRedoStackEmpty(stack) == 0) {
		popRedoStack(stack);
	}
	free(stack);
}