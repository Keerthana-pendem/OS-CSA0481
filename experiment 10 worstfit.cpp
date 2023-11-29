#include <stdio.h>
#include <stdlib.h>
typedef struct Block 
{
    int size;
    struct Block* next;
} 
Block;
void initializeMemory(Block** head, int size) 
{
    *head = (Block*)malloc(sizeof(Block));
    (*head)->size = size;
    (*head)->next = NULL;
}
void displayMemory(Block* head) 
{
    while (head != NULL) 
	{
        printf("Free Block: Size = %d\n", head->size);
        head = head->next;
    }
}
void allocateMemory(Block** head, int processSize) 
{
    if (*head == NULL) 
	{
        printf("Memory allocation failed. No free blocks available.\n");
        return;
    }
    Block* worstFitBlock = NULL;
    Block* current = *head;
    Block* prevWorstFit = NULL;
    while (current != NULL) 
	{
        if (current->size >= processSize && (worstFitBlock == NULL || current->size > worstFitBlock->size)) 
		{
            worstFitBlock = current;
            if (prevWorstFit == NULL) 
			{
                *head = current->next;
            }
			 else 
			{
                prevWorstFit->next = current->next;
            }
        }
        prevWorstFit = current;
        current = current->next;
    }
    if (worstFitBlock != NULL) 
	{
        printf("Memory allocated successfully. Allocated block size = %d\n", worstFitBlock->size);
        free(worstFitBlock);
    } 
	else 
	{
        printf("Memory allocation failed. No suitable block found.\n");
    }
}
void deallocateMemory(Block** head, int size) 
{
    Block* newBlock = (Block*)malloc(sizeof(Block));
    newBlock->size = size;
    newBlock->next = *head;
    *head = newBlock;
    printf("Memory deallocated successfully. Deallocated block size = %d\n", size);
}
void freeMemoryList(Block** head) 
{
    while (*head != NULL) 
	{
        Block* temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}
int main() 
{
    Block* freeMemory = NULL;
    initializeMemory(&freeMemory, 100); 
    displayMemory(freeMemory);
    allocateMemory(&freeMemory, 30); 
    displayMemory(freeMemory);
    allocateMemory(&freeMemory, 20); 
    displayMemory(freeMemory);
    deallocateMemory(&freeMemory, 30);
    displayMemory(freeMemory);
    freeMemoryList(&freeMemory); 
    return 0;
}

