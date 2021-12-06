#include "../../includes/linkeddeque.h"

// typedef struct DequeNodeType
// {
// 	char data;
// 	struct DequeNodeType* pRLink;
// 	struct DequeNodeType* pLLink;
// } DequeNode;

// typedef struct LinkedDequeType
// {
// 	int currentElementCount;	// ���� ������ ����
// 	DequeNode* pFrontNode;		// Front ����� ������
// 	DequeNode* pRearNode;		// Rear ����� ������
// } LinkedDeque;

LinkedDeque* createLinkedDeque()
{
	LinkedDeque *pDeque;

	pDeque = (LinkedDeque *)calloc(1, sizeof(LinkedDeque));
	if (!pDeque)
	{
		printf("Malloc Error!\n");
		return (NULL);
	}
	return (pDeque);
}

int insertFrontLD(LinkedDeque* pDeque, DequeNode element)
{
	DequeNode *pNode;
    
    if (!pDeque)
    {
        printf("pDeque is null\n");
        return (FALSE);
    }
	pNode = (DequeNode *)malloc(sizeof(DequeNode));
	if (!pNode)
		return (FALSE);
	*pNode = element;
	pNode->pRLink = pDeque->pFrontNode;
    if (pDeque->pFrontNode)
        pDeque->pFrontNode->pLLink = pNode;
	pDeque->pFrontNode = pNode;
    pNode->pLLink = NULL;	
    if (isLinkedDequeEmpty(pDeque))
        pDeque->pRearNode = pNode;
    pDeque->currentElementCount++;
    return (TRUE);
}

int insertRearLD(LinkedDeque* pDeque, DequeNode element)
{
	DequeNode *pNode;

	if (!pDeque)
	{
		printf("pDeque is null\n");
		return (FALSE);
	}
	pNode = (DequeNode *)malloc(sizeof(DequeNode));
	if (!pNode)
		return (FALSE);
	*pNode = element;
	pNode->pLLink = pDeque->pRearNode;
	if (pDeque->pRearNode)
		pDeque->pRearNode->pRLink = pNode;
	pDeque->pRearNode = pNode;
	pNode->pRLink = NULL;
	if (isLinkedDequeEmpty(pDeque))
		pDeque->pFrontNode = pNode;
	pDeque->currentElementCount++;
	return (TRUE);
}

DequeNode* deleteFrontLD(LinkedDeque* pDeque)
{
	DequeNode *node;

    node = 0;
    if (!pDeque)
    {
        printf("pDeque is null\n");
        return (NULL);
    }
	node = pDeque->pFrontNode;
	if (isLinkedDequeEmpty(pDeque))
    {
        printf("pDeque is empty\n");
        return (NULL);
    }
	pDeque->pFrontNode = node->pRLink;
	if (pDeque->pFrontNode)
		pDeque->pFrontNode->pLLink = NULL;
    pDeque->currentElementCount--;
	return (node);
}

DequeNode* deleteRearLD(LinkedDeque* pDeque)
{
	DequeNode *node;

    node = 0;
    if (!pDeque)
    {
        printf("pDeque is null\n");
        return (NULL);
    }
	node = pDeque->pRearNode;
	if (isLinkedDequeEmpty(pDeque))
    {
        printf("pDeque is empty\n");
        return (NULL);
    }
	pDeque->pRearNode = node->pLLink;
	if (pDeque->pRearNode)
		pDeque->pRearNode->pRLink = NULL;
	pDeque->currentElementCount--;
	return (node);
}

DequeNode* peekFrontLD(LinkedDeque* pDeque)
{
	if (!pDeque)
	{
		printf("pDeque is null\n");
		return (NULL);
	}
	if (isLinkedDequeEmpty(pDeque))
	{
		printf("pDeque is empty\n");
		return (NULL);
	}
	return (pDeque->pFrontNode);
}

DequeNode* peekRearLD(LinkedDeque* pDeque)
{
    if (!pDeque)
	{
		printf("pDeque is null\n");
		return (NULL);
	}
	if (isLinkedDequeEmpty(pDeque))
	{
		printf("pDeque is empty\n");
		return (NULL);
	}
	return (pDeque->pRearNode);
}

void deleteLinkedDeque(LinkedDeque* pDeque)
{
    DequeNode *pNode;
    DequeNode *delNode;

    pNode = 0;
    delNode = 0;
    if (pDeque)
    {
        pNode = pDeque->pFrontNode;
        while (pNode)
        {
            delNode = pNode;
            pNode = pNode->pRLink;
            free(delNode);
            delNode = 0;
        }
        free(pDeque);
        pDeque = 0;
    }	
    else
    {
        printf("pDeque is null\n");
    }
}

void displayLinkedDeque(LinkedDeque *pDeque) {
	DequeNode *node;

	if (!pDeque)
		return ;
	node = pDeque->pFrontNode;
	for (int i = 0; i < pDeque->currentElementCount; i++) {
		printf("%c ", node->data);
		if (i < pDeque->currentElementCount - 1)
			printf("-> ");
		node = node->pRLink;
	}
	printf("\n");
	return ;
}
int isLinkedDequeSize(LinkedDeque* pDeque)
{
    return (pDeque->currentElementCount);
}

int isLinkedDequeEmpty(LinkedDeque* pDeque)
{
	return (pDeque->currentElementCount == 0);
}