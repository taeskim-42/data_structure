#include "maze_stack.h"

LinkedStack *createLinkedStack()
{
	LinkedStack *Stack;
	if (!(Stack = (LinkedStack *)calloc(1, sizeof(LinkedStack))))
		return (NULL);
	return (Stack);
}

void reverseLinkedStack(LinkedStack* pStack) 
{
	StackNode *pNextNode = NULL, *pCurrentNode = NULL, *pPrevNode = NULL;
	if (pStack != NULL) 
	{
		pCurrentNode = pStack->pTopElement;
		while (pCurrentNode)
		{
			pNextNode = pCurrentNode->pLink;
			pCurrentNode->pLink = pPrevNode;
			pPrevNode = pCurrentNode;
			pCurrentNode = pNextNode;
		}
		pStack->pTopElement = pPrevNode;
	}
}

void deleteLinkedStack(LinkedStack *pStack)
{
	StackNode *tmp;

	if (pStack)
	{
		while (pStack->currentElementCount > 0)
		{
			tmp = popLSMapPosition(pStack);
			free(tmp);
			tmp = 0;
		}
		free(pStack);
		pStack = 0;
	}
	else
		printf("invalid pStack\n");
}