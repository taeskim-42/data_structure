#ifndef _LINKED_DEQUE_
#define _LINKED_DEQUE_
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "simdef.h"
typedef struct QueueNodeType
{
	SimCustomer             customer;
	struct QueueNodeType*   pLink;
} QueueNode;

typedef struct LinkedQueueType
{
	int                     currentElementCount;
	QueueNode*              tail;
} LinkedQueue;

LinkedQueue *createLinkedQueue(void);
int enqueueLinkedQueue(LinkedQueue *pQueue, QueueNode element);
QueueNode *dequeLinkedQueue(LinkedQueue *pQueue);
QueueNode *peekLinkedQueue(LinkedQueue *pQueue);
void deleteLinkedQueue(LinkedQueue *pQueue);
int isLinkedQueueEmpty(LinkedQueue *Queue);
void displayLinkedQueue(LinkedQueue *pQueue);

#endif

#ifndef _COMMON_QUEUE_DEF_
#define _COMMON_QUEUE_DEF_

#define TRUE		1
#define FALSE		0

#endif