#include "linkedstack.h"

LinkedStack *createLinkedStack()
{
	LinkedStack *Stack;
	if (!(Stack = (LinkedStack *)calloc(1, sizeof(LinkedStack))))
		return (NULL);
	return (Stack);
}

int pushLS(LinkedStack *pStack, StackNode element)
{
	int ret = FALSE;
	StackNode *newNode = 0;

	if (pStack)
	{
		if ((newNode = (StackNode *)calloc(1, sizeof(StackNode))))
		{
			*newNode = element;
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

StackNode *popLS(LinkedStack *pStack)
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

StackNode *peekLS(LinkedStack *pStack)
{
	StackNode *ret = 0;

	if (pStack)
	{
		if (pStack->currentElementCount != 0)
			ret = pStack->pTopElement;
	}
	else
		printf("Invalid pStack\n");
	return (ret);
}

void deleteLinkedStack(LinkedStack *pStack)
{
	StackNode *tmp;

	if (pStack)
	{
		while (pStack->currentElementCount > 0)
		{
			tmp = popLS(pStack);
			free(tmp);
			tmp = 0;
		}
		free(pStack);
	    pStack = 0;
	}
    else
        printf("invalid pSTack\n");
}

int isLinkedStackFull(LinkedStack *pStack)
{
	return FALSE;
}

int isLinkedStackEmpty(LinkedStack *pStack)
{
    return (pStack->currentElementCount == 0 ? TRUE : FALSE);
}
