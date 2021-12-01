#include "./maz_stack.h"

LinkedStack *createLinkedStack()
{
	LinkedStack *Stack;
	if (!(Stack = (LinkedStack *)calloc(1, sizeof(LinkedStack))))
		return (NULL);
	return (Stack);
}

int pushLSMapPosition(LinkedStack *pStack, MapPosition data)
{
	int ret = FALSE;
	StackNode *newNode = 0;

	if (pStack)
	{
		if ((newNode = (StackNode *)calloc(1, sizeof(StackNode))))
		{
			newNode->pos = data;
			pStack->currentElementCount++;
			newNode->pLink = pStack->pTopElement;
			pStack->pTopElement = newNode;
			ret = TRUE;
		}
	}
	else
		printf("Invalid pStack");
	return (ret);
}

StackNode *popLSMapPosition(LinkedStack *pStack)
{
	StackNode *ret = 0;

	if (pStack)
	{
		if (pStack->currentElementCount != 0)
		{
			ret = pStack->pTopElement;
			pStack->pTopElement = ret->pLink;
			ret->pLink = 0;
			pStack->currentElementCount--;
		}
	}
	else
		printf("Invalid pStack");
	return (ret);
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