#ifndef _SIM_UTIL_
#define _SIM_UTIL_

# include "simdef.h"
# include "simlinkedque.h"

// 고객 도착 큐에 고객 추가.
/*
arrivalTime : 대기큐에 도착한 시간
processTime : 처리하는데 걸리는 시간
pQueue : 대기큐

노드를 동적할당하고 노드에 arrivaltime(node->arrivaltime), processTime(node->serviceTime)을 넣고 
대기큐에 넣습니다.
*/

void insertCutomer(int arrivalTime, int processTime, LinkedQueue *pQueue);

// 고객 도착 처리.

/*

*/

void processArrival(int currentTime, LinkedQueue *pArrivalQueue, LinkedQueue *pWaitQueue);

// 서비스 시작 처리.
/*

*/

QueueNode* processServiceNodeStart(int currentTime, LinkedQueue *pWaitQueue);

// 서비스 종료 처리.
/*

*/
QueueNode* processServiceNodeEnd(int currentTime, QueueNode *pServiceNode,
					  int *pServiceUserCount, int *pTotalWaitTime);

// 고객의 상태를 출력.
/*

*/
void printSimCustomer(int currentTime, SimCustomer customer);

// 대기 열의 상태를 출력.
/*

*/
void printWaitQueueStatus(int currentTime, LinkedQueue *pWaitQueue);

// 최종 시뮬레이션 결과(통계치) 출력.
/*

*/
void printReport(LinkedQueue *pWaitQueue,
				 int serviceUserCount,
				 int totalWaitTime);

#endif