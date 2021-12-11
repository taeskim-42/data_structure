#include "../../includes/simlinkedque.h"
#include "../../includes/simutil.h"
#include "../../includes/simdef.h"

/*
==================================================================

							LINKED_QUEUE

==================================================================
*/

// static void display_node(QueueNode *qNode) {
// 		//SimStatus status;
// 	//int arrivalTime;	// 도착 시각.
// 	//int serviceTime;	// 서비스 시간.
// 	//int startTime;		// 시작 시각.
// 	//int endTime;		// 종료 시각: 시작 시각 + 서비스 시간.
// 	if (!qNode)
// 		return ;
// 	printf("%d\n", qNode->customer.status);
//     printf("%d \n", qNode->customer.arrivalTime);
//     printf("%d \n", qNode->customer.serviceTime);
//     printf("%d \n", qNode->customer.startTime);
//     printf("%d \n", qNode->customer.endTime);
// }
// void	delete_test()
// {
// 	LinkedQueue *as = 0;
// 	QueueNode ele;

// 	as = createLinkedQueue();
// 	for (int i = 0; i < 3; i++)
// 		enqueueLinkedQueue(as, ele);
// 	deleteLinkedQueue(as);
// }

// void sim_init(SimCustomer *sc)
// {
//     sc->arrivalTime = 0;
//     sc->endTime = 0;
//     sc->serviceTime = 0;
//     sc->startTime = 0;
//     sc->status = arrival;
// }


// int		main(void)
// {
// 	char c;
//     SimCustomer sc;
// 	LinkedQueue *as = 0;
// 	QueueNode *dequeue;
// 	QueueNode node;
//     sim_init(&sc);
// 	while(1)
// 	{
// 		printf(" 1: createLinkedQueue 2: enqueueLinkedQueue 3: dequeLinkedQueue 4: deleteLinkedQueue 5: isLinkedQueueEmpty 6: displayLinkedQueue 7: leak check 8: peek\n");
// 		scanf(" %c", &c);
// 		switch (c)
// 		{
// 		case '1':
// 			as = createLinkedQueue();
// 			break;
// 		case '2':
// 			//SimStatus status;
// 			//int arrivalTime;	// 도착 시각.
// 			//int serviceTime;	// 서비스 시간.
// 			//int startTime;		// 시작 시각.
// 			//int endTime;		// 종료 시각: 시작 시각 + 서비스 시간.
// 			printf("put status : ");
// 			scanf(" %d", &node.customer.status);
// 			printf("put arrival time : ");
// 			scanf(" %d", &node.customer.arrivalTime);
// 			printf("put service time : ");
// 			scanf(" %d",  &node.customer.serviceTime);
// 			printf("put start time : ");
// 			scanf(" %d", &node.customer.startTime);
// 			printf("put end time : ");
// 			scanf(" %d", &node.customer.endTime);
// 			enqueueLinkedQueue(as, node);
// 			break;
// 		case '3':
// 			printf("put node : ");
// 			dequeue = dequeLinkedQueue(as);
// 			display_node(dequeue);
// 			free(dequeue);
// 			break;
// 		case '4':
// 			deleteLinkedQueue(as);
// 			break;
// 		case '5':
// 			isLinkedQueueEmpty(as);
// 			break;
// 		case '6':
// 			displayLinkedQueue(as);
// 			break;
// 		case '7':
// 			delete_test();
// 			system("leaks a.out");
// 			break;
// 		case '8':
// 			dequeue = peekLinkedQueue(as);
// 			display_node(dequeue);
// 			break;
// 		default:
// 			break;
// 		}
// 	}
//     return 0;
// }

/*
==================================================================

							SIMCHECKER

==================================================================
*/
#include <unistd.h>
typedef enum e_cmd {
	NONE,
	CUSTOMER,
	AQUEUE,
	WQUEUE,
	REPORT,
	EXIT
}				t_cmd;

int	main(void)
{
	int	t;
	LinkedQueue *arrival;
	LinkedQueue *wait;
	QueueNode *node;
	SimCustomer sc;
	int cmd;
	int cnt = 0;
	int wait_time = 0;
	int user;

	t = 0;
	node = 0;
	user = 1;
	arrival = createLinkedQueue();
	wait = createLinkedQueue();
	printf("도착 시간과 서비스 시간을 입력해주세요\n");
	while (scanf("%d %d", &sc.arrivalTime, &sc.serviceTime) != EOF) {
		insertCutomer(sc.arrivalTime, sc.serviceTime, arrival);
	}
	rewind(stdin);
	while (!isLinkedQueueEmpty(arrival) || !isLinkedQueueEmpty(wait)
			|| node) {
		printf("현재시간 : %d\n", t);
		cmd = 0;
		processArrival(t, arrival, wait);
		if (!node)
			node = processServiceNodeStart(t, wait);
		node = processServiceNodeEnd(t, node, &cnt, &wait_time);
		if (node && node->customer.status == end) {
			node->customer.status = 0;
			node->customer.arrivalTime = 0;	// 도착 시각.
			node->customer.serviceTime = 0;;	// 서비스 시간.
			node->customer.startTime = 0;		// 시작 시각.
			node->customer.endTime = 0;
			free(node);
			node = NULL;
			node = processServiceNodeStart(t, wait);
			user++;
		}
		printf("출력하고 싶은 데이터 (숫자로 입력해주세요)\n");
		printf("1. 현재 서비스 처리 고객 상태\n");
		printf("2. Arrival 대기열 상태\n");
		printf("3. Wait 대기열 상태\n");
		printf("4. 서비스 처리 현황\n");
		printf("5. 출력모드 종료");
		while (cmd != EXIT) {
			scanf("%d", &cmd);
			switch (cmd) {
				case CUSTOMER:
					if(!node) {
						printf("현재 서비스를 받는 고객이 없습니다.\n");
						break ;
					}
					printf("고객 %d\n", user);
					printSimCustomer(t, node->customer);
					break ;
				case AQUEUE:
					printf("Arrival Queue\n");
					printWaitQueueStatus(t, arrival);
					break ;
				case WQUEUE:
					printf("Wait Queue\n");
					printWaitQueueStatus(t, wait);
					break ;
				case REPORT:
					printReport(wait, cnt, wait_time);
					break ;
				case EXIT:
					break ;
				default:
					printf("잘못된 값을 입력했습니다.\n");
					break ;
			}
		}
		t++;
		sleep(1);
	}
	printReport(wait, cnt, wait_time);
	deleteLinkedQueue(arrival);
	deleteLinkedQueue(wait);
}