
#include "../../includes/arrayqueue.h"


ArrayQueue* createArrayQueue(int maxElementCount)
{
    ArrayQueue *aq;

    aq = 0;
    if (maxElementCount > 0)
    {
        aq = (ArrayQueue *)calloc(1, sizeof(ArrayQueue));
        if (aq)
        {
            aq->maxElementCount = maxElementCount;
        }
        else
        {
            printf("Malloc Error\n");
            return (NULL);
        }
    }
    else
    {
        printf("Count should be greater than zero\n");
        return (NULL);
    }

    aq->pElement = (ArrayQueueNode *)calloc(maxElementCount, sizeof(ArrayQueueNode));
    if (!aq->pElement)
    {
        printf("Malloc Error\n");
        free(aq);
        aq = 0;
        return (NULL);
    }
    return aq;
}

int enqueueAQ(ArrayQueue* pQueue, ArrayQueueNode element)
{
    if (pQueue)
    {
        if (!isArrayQueueFull(pQueue))
        {
            pQueue->pElement[pQueue->rear] = element;
            pQueue->rear = (pQueue->rear + 1) % pQueue->maxElementCount + 1;
            pQueue->currentElementCount++;
            return (TRUE);
        }
        else
        {
            printf("pQueue is full\n\n");
            return (FALSE);
        }
    }
    else
    {
        printf("pQueue is null\n\n");
        return (FALSE);
    }
}

ArrayQueueNode *dequeueAQ(ArrayQueue* pQueue)
{
    ArrayQueueNode *node;

    node = 0;
    if (pQueue)
    {
        if(!isArrayQueueEmpty(pQueue) )
        {
            node = &pQueue->pElement[pQueue->front];
            pQueue->currentElementCount--;
            pQueue->front = (pQueue->front + 1) % pQueue->maxElementCount + 1;
        }
        else
        {
            printf("pQueue is empty\n\n");
        }
    }
    else
    {
        printf("pQueue is NUll\n");
    }
    return (node);
}

ArrayQueueNode *peekAQ(ArrayQueue* pQueue)
{
    if (pQueue)
   {
        if(!isArrayQueueEmpty(pQueue))
        {
            return (&pQueue->pElement[pQueue->front]);
        }
    }
    printf("pQueue is null\n\n");
    return (NULL);
}
void deleteArrayQueue(ArrayQueue* pQueue)
{
    if (pQueue)
    {
        if(!isArrayQueueEmpty(pQueue))
        {
            memset(pQueue->pElement, 0, sizeof(ArrayQueueNode) * pQueue->maxElementCount);
            free(pQueue->pElement);
            memset(pQueue, 0, sizeof(ArrayQueue));
            free(pQueue);
        }
    }
    else
    {
        printf("pQueue is null\n");
    }
}

int isArrayQueueFull(ArrayQueue* pQueue)
{
    return (pQueue->currentElementCount == pQueue->maxElementCount);
}

int isArrayQueueEmpty(ArrayQueue* pQueue)
{
    return (pQueue->front == pQueue->rear);
}