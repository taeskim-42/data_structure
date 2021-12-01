#include "arraystack.h"

ArrayStack* createArrayStack(int maxElementCount)
{
	ArrayStack *s;

	if (maxElementCount <= 0)
		return (NULL);
	s = (ArrayStack *)malloc(sizeof(ArrayStack));
	if (!s)
		return (NULL);
	if (!(s->pElement = (ArrayStackNode *)calloc(maxElementCount, sizeof(ArrayStackNode))))
		return (NULL);
	s->currentElementCount = 0;
	s->maxElementCount = maxElementCount;
	return (s);
}

int pushAS(ArrayStack* pStack, ArrayStackNode element)
{
	if (!pStack || !pStack->pElement)
		return (FALSE);
	if (pStack->maxElementCount == pStack->currentElementCount)
		return (FALSE);
	pStack->pElement[pStack->currentElementCount++] = element;	
	return (TRUE);
}

ArrayStackNode* popAS(ArrayStack* pStack)
{
	ArrayStackNode *ret;

	if (!pStack || !pStack->pElement)
		return (NULL);
	if (pStack->currentElementCount == 0)
		return (NULL);
	if (!(ret = (ArrayStackNode *)calloc(1, sizeof(ArrayStackNode))))
		return (NULL);
	ret->data = pStack->pElement[pStack->currentElementCount - 1].data;
	pStack->currentElementCount--;
	return (ret);
}

ArrayStackNode* peekAS(ArrayStack* pStack)
{
	ArrayStackNode *ret;

	if (!pStack || !pStack->pElement)
		return (NULL);
	if (pStack->currentElementCount == 0)
		return (NULL);
	ret = &(pStack->pElement[pStack->currentElementCount - 1]);
	return (ret);
}

void deleteArrayStack(ArrayStack* pStack)
{
	if (!pStack || !pStack->pElement)
		return ;
	free(pStack->pElement);
	pStack->pElement = 0;
	free(pStack);
	pStack = 0;	
}


int isArrayStackFull(ArrayStack* pStack)
{
	return pStack->maxElementCount == pStack->currentElementCount ? TRUE : FALSE;
}


int isArrayStackEmpty(ArrayStack* pStack)
{
	return pStack->currentElementCount == 0 ? TRUE : FALSE;
}

