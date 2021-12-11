#include "../../includes/simlinkedque.h"
#include <math.h>

void insertCutomer(int arrivalTime, int processTime, LinkedQueue *pQueue) {
	QueueNode ele;

    if (pQueue != NULL)
    {
	    ele.customer.arrivalTime = arrivalTime;
	    ele.customer.serviceTime = processTime;
	    ele.customer.status = arrival;
	    ele.customer.startTime = 0;
	    ele.customer.endTime = 0;
        if (!enqueueLinkedQueue(pQueue, ele))
            printf("더이상 입장할 수 없습니다.\n");
    }
}
void processArrival(int currentTime, LinkedQueue *pArrivalQueue, LinkedQueue *pWaitQueue) {
    QueueNode *arrivalCustomer;
	arrivalCustomer = peekLinkedQueue(pArrivalQueue);
	if (!arrivalCustomer)
	{
		printf("도착한 손님이 없습니다.\n");
		return ;
	}
	while (arrivalCustomer->customer.arrivalTime <= currentTime)
	{

	    arrivalCustomer = dequeLinkedQueue(pArrivalQueue);
        enqueueLinkedQueue(pWaitQueue, *arrivalCustomer);
        arrivalCustomer->customer.status = 0;
        arrivalCustomer->customer.arrivalTime = 0;
        arrivalCustomer->customer.serviceTime = 0;
        arrivalCustomer->customer.startTime = 0;
        arrivalCustomer->customer.endTime = 0;
		arrivalCustomer->pLink = 0;
        free(arrivalCustomer);
		arrivalCustomer = peekLinkedQueue(pArrivalQueue);
    	if (!arrivalCustomer)
		{
			printf("도착한 손님이 없습니다.\n");
			return ;
		}
	}
}

QueueNode* processServiceNodeStart(int currentTime, LinkedQueue *pWaitQueue) {
    QueueNode *node;

    node = 0;
    if (!pWaitQueue)
        return (NULL);
    if (!isLinkedQueueEmpty(pWaitQueue))
    {
         node = dequeLinkedQueue(pWaitQueue);
         node->customer.status = start;
         node->customer.startTime = currentTime;
         node->customer.endTime = node->customer.startTime + node->customer.serviceTime; 
         return (node);
    }
    else
    {
        printf("대기줄이 비어있습니다.\n");
        return (NULL);
    }
}

QueueNode* processServiceNodeEnd(int currentTime, QueueNode *pServiceNode,
					  int *pServiceUserCount, int *pTotalWaitTime) {
	if (!pServiceNode)
        return (NULL);
    if (pServiceNode->customer.endTime != currentTime)
		return (pServiceNode);
	pServiceNode->customer.status = end;
	*pServiceUserCount += 1;
	printf("start : %d\n",pServiceNode->customer.startTime);
	*pTotalWaitTime += pServiceNode->customer.startTime - pServiceNode->customer.arrivalTime;
	return (pServiceNode);
}

void printSimCustomer(int currentTime, SimCustomer customer) {
	printf("현재 시간 : %d\n", currentTime);

	switch(customer.status) {
		case arrival:
			printf("고객 상태 : 대기\n");
			printf("도착 시간 : %d\n", customer.arrivalTime);
            break;
        case start:
			printf("고객 상태 : 시작\n");
			printf("대기 시간 : %d\n", customer.startTime - customer.arrivalTime);
            break;
		case end:
			printf("고객 상태 : 종료\n");
			printf("종료 시간 : %d\n", customer.endTime);
            break;
		default:
			break;
	}
}

void printWaitQueueStatus(int currentTime, LinkedQueue *pWaitQueue) {
    QueueNode *node;
    char *status[] = {"arrival", "start", "end"};

    if (isLinkedQueueEmpty(pWaitQueue)) {
		printf("wait Queue가 비어있습니다.\n");
        return ;
	}
    printf("현재 시간 : %d\n", currentTime);

    printf("대기열\n");
    node = pWaitQueue->tail->pLink;
    do {
        printf("%s ", status[node->customer.status]);
        node = node->pLink;
    } while(node != pWaitQueue->tail->pLink);
    printf("\n");
}

void printReport(LinkedQueue *pWaitQueue,
				 int serviceUserCount,
				 int totalWaitTime) {
	double wait;
	wait = (double)totalWaitTime / serviceUserCount;
	if (isnan(wait))
		wait = 0;
    printf("현재 대기 인원 : %d\n", pWaitQueue->currentElementCount);
    printf("서비스 완료 인원 : %d\n", serviceUserCount);
    printf("평균 대기 시간 : %.2f\n", wait);
}
