#include "../../includes/simlinkedque.h"

const char* stat[] = {"arrival", "start", "end"};

LinkedQueue *createLinkedQueue(void)
{
	LinkedQueue *pQueue;

	pQueue = (LinkedQueue *)calloc(1, sizeof(pQueue));
	if (!pQueue)
		return (NULL);
	return (pQueue);
}

int enqueueLinkedQueue(LinkedQueue *pQueue, QueueNode element)
{
	QueueNode *node;

	if (!pQueue)
		return (FALSE);
	node = (QueueNode *)calloc(1, sizeof(QueueNode));
	if (!node)
		return (FALSE);
	node->customer = element.customer;
	if (pQueue->tail) {
		node->pLink = pQueue->tail->pLink;
		pQueue->tail->pLink = node;
	}
	else
		node->pLink = node;
	pQueue->tail = node;
	pQueue->currentElementCount++;
	return (1);
}

QueueNode *dequeLinkedQueue(LinkedQueue *pQueue)
{
	QueueNode *node;

	node = 0;
	if (!pQueue)
		return (NULL);
	if (isLinkedQueueEmpty(pQueue))
		return (NULL);
	node = pQueue->tail->pLink;
	pQueue->tail->pLink = node->pLink;
	pQueue->currentElementCount--;
	return (node);
}

QueueNode *peekLinkedQueue(LinkedQueue *pQueue)
{
	if (!pQueue)
		return (NULL);
	if (isLinkedQueueEmpty(pQueue))
		return (NULL);
	return (pQueue->tail->pLink);
}

void deleteLinkedQueue(LinkedQueue *pQueue)
{
	QueueNode *pNode;
	QueueNode *delNode;

	if (!pQueue)
		return ;
	pNode =	pQueue->tail;
	while (pNode)
	{
		delNode = pNode;
		pNode = pNode->pLink;
		free(delNode);
		delNode = 0;
	}
	free(pQueue);
	pQueue = 0;
}

int isLinkedQueueEmpty(LinkedQueue *Queue)
{
	return (Queue->currentElementCount == 0);
}

static void dfs(LinkedQueue *pQueue, QueueNode *node, int flag) {

	if (node == pQueue->tail && flag == TRUE)
		return 
	dfs(pQueue, node->pLink, TRUE);
	printf("SimStatus : %s\n", stat[node->customer.status]);
	printf("Arrival Time : %d\n", node->customer.arrivalTime);
	printf("Service Time : %d\n", node->customer.serviceTime);
	printf("Start Time : %d\n", node->customer.serviceTime);
	printf("End Time : %d\n", node->customer.endTime);
	printf("address : %p\n", node);
	printf("next address : %p\n", node->pLink);
}

void displayLinkedQueue(LinkedQueue *pQueue)
{
	QueueNode *node;

	node = pQueue->tail;
	dfs(pQueue, node, FALSE);
}


