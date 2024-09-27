/*VOICU Alexa-Andreea-312CD*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ListSort.h"
#include "UndoStack.h"
#include "ExecuteQueue.h"

int main()
{
    FILE* input;
    FILE* output;
    input = fopen("tema1.in", "r");
    output = fopen("tema1.out", "w");
    Band* band = createBand();
    moveright(band);
    char* instruction = malloc(30 * sizeof(char));
    char character;
    TQueue execQueue = NULL;
    UndoStack* undostack = createUndoStack();
    RedoStack* redostack = createRedoStack();
    
    void undo(Band* band, RedoStack* redostack, UndoStack* undostack)
    {
        pushRedoStack(redostack,(void*)(band->current));     //se pune ptr current in stiva
        band->current = (Node*)(undostack->head->current);   //se realizeaza mutarea la ptr retinut
        popUndoStack(undostack);
        return;
    }

    void redo(Band* band, RedoStack* redostack, UndoStack* undostack)
    {
        pushUndoStack(undostack,(void*)(band->current));
        band->current = (Node*)(redostack->head->current);
        popRedoStack(redostack);
        return;
    }

    TQueue execute(TQueue queue, Band* band, UndoStack* undostack)
    {
    char* instruction = queue->head->instruction;
    if (strcmp(instruction, "MOVE_LEFT") == 0){
        if (band->current != band->list->first->next) //verificare daca se poate muta  spre stanga
        pushUndoStack(undostack, (void*)(band->current));
        moveleft(band);
    }
    if (strcmp(instruction, "MOVE_RIGHT") == 0) {
        pushUndoStack(undostack, (void*)(band->current));    //se pune ptr current in stiva
        moveright(band);
    }
    if (strcmp(instruction, "MOVE_LEFT_CHAR") == 0)
        moveleftChar(band, queue->head->c, output);
    if (strcmp(instruction, "MOVE_RIGHT_CHAR") == 0)
        moverightChar(band, queue->head->c);
    if (strcmp(instruction, "WRITE") == 0)
        write(band, queue->head->c);
    if (strcmp(instruction, "INSERT_LEFT") == 0)
        insertLeft(band, queue->head->c, output);
    if (strcmp(instruction, "INSERT_RIGHT") == 0)
        insertRight(band, queue->head->c);
    return dequeue(queue);
    }

    int numOperations;
    fscanf(input, "%d", &numOperations);
    int i = 0;
    while (i < numOperations) {  //citirea instructiunilor
        fscanf(input, "%s", instruction);
        if (strcmp(instruction, "EXECUTE") == 0) {
            execQueue = execute(execQueue, band, undostack);
        } else if (strcmp(instruction, "WRITE") == 0) {
                fscanf(input, "%c", &character);
                fscanf(input, "%c", &character);
            execQueue = enqueue(execQueue, character, instruction);
        } else if (strcmp(instruction, "INSERT_LEFT") == 0 || strcmp(instruction, "INSERT_RIGHT") == 0) {
                    fscanf(input, "%c", &character);
                    fscanf(input, "%c", &character);
                execQueue = enqueue(execQueue, character, instruction);
            } else if (strcmp(instruction, "MOVE_LEFT_CHAR") == 0 || strcmp(instruction, "MOVE_RIGHT_CHAR") == 0) {
                        fscanf(input, "%c", &character);
                        fscanf(input, "%c", &character);
                    execQueue = enqueue(execQueue, character, instruction);
                } else if (strcmp(instruction, "SHOW") == 0) {
                        show(band, output);
                    } else if (strcmp(instruction, "SHOW_CURRENT") == 0) {
                            showCurrent(band, output);
                        } else if (strcmp(instruction, "UNDO") == 0) {
                                undo(band, redostack, undostack);
                            } else if (strcmp(instruction, "REDO") == 0) {
                                    redo(band, redostack, undostack);
                                } else 
                                        execQueue = enqueue(execQueue, '|', instruction);
            i++;
    }
    fclose(input);
    fclose(output);
    freeQueue(execQueue);
    freeRedoStack(redostack);
    freeUndoStack(undostack);
    free(instruction);
    band = freeBand(band);
    return 0;
}
