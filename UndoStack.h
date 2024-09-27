/*VOICU Alexa-Andreea-312CD*/
#include <stdlib.h>

typedef struct UndoNode {
    struct UndoNode *next;
    void* current;
} UndoNode;

typedef struct UndoStack{
	struct UndoNode* head;
	long size;
}UndoStack;

typedef struct RedoNode {
    struct RedoNode* next;
    void* current;
} RedoNode;

typedef struct RedoStack {
    struct RedoNode *head;
    long size;
}RedoStack;

UndoStack* createUndoStack(void);
RedoStack* createRedoStack(void);
int isUndoStackEmpty(UndoStack*);
int isRedoStackEmpty(RedoStack*);
UndoNode* createUndoNode(void*);
RedoNode* createRedoNode(void*);
void pushUndoStack(UndoStack*, void*);
void pushRedoStack(RedoStack*, void*);
void popUndoStack(UndoStack*);
void popRedoStack(RedoStack*);
void freeUndoStack(UndoStack*);
void freeRedoStack(RedoStack*);