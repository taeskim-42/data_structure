/*
======================================================================================

                        ARRAY_QUEUE && CIRCULAR_ARRAY_QUEUE

======================================================================================
*/

// #include "../../includes/arrayqueue.h"

// void	delete_test()
// {
// 	ArrayQueue *as = 0;
// 	ArrayQueueNode ele;

// 	ele.data = 3;
// 	as = createArrayQueue(3);
// 	for (int i = 0; i < 3; i++)
// 		enqueueAQ(as, ele);
// 	deleteArrayQueue(as);
// }

// int		main(void)
// {
// 	char c;
// 	ArrayQueue *as = 0;
// 	ArrayQueueNode node;
// 	ArrayQueueNode *pop;
// 	node.data = 0;
// 	while(1)
// 	{
// 		printf("put Create Push pOp pEek Delete: ");
// 		scanf(" %c", &c);
// 		switch (c)
// 		{
// 		case 'C':
// 			as = createArrayQueue(3);
// 			break;
// 		case 'P':
// 			printf("put node : ");
// 			scanf(" %c", &c);
// 			node.data = c;
// 			enqueueAQ(as, node);
// 			break;
// 		case 'O':
// 			pop = dequeueAQ(as);
// 			if (pop)
// 				printf("%c\n", pop->data);
// 			break;
// 		case 'E':
// 			pop = peekAQ(as);
// 			if (pop)
// 				printf("%c\n", pop->data);
// 			break;
// 		case 'D':
// 			delete_test();
// 			system("leaks a.out");
// 			break;
// 		default:
// 			break;
// 		}
// 	}
//     return 0;
// }

/*
======================================================================================

                        			LINKDEDDEQUE

======================================================================================
*/

#include "../../includes/linkeddeque.h"

void	delete_test()
{
	LinkedDeque *as = 0;
	DequeNode ele;

	ele.data = 3;
	as = createLinkedDeque(3);
	for (int i = 0; i < 3; i++)
		insertFrontLD(as, ele);
	deleteLinkedDeque(as);
}

int		main(void)
{
	char c;
	LinkedDeque *as = 0;
	DequeNode node;
	DequeNode *pop;
	node.data = 0;
	while(1)
	{
		printf("put Create Push pOp pEek Delete: ");
		scanf(" %c", &c);
		switch (c)
		{
		case 'C':
			as = createLinkedDeque(3);
			break;
		case 'F':
			printf("put node : ");
			scanf(" %c", &c);
			node.data = c;
			insertFrontLD(as, node);
			break;
		case 'R':
			printf("put node : ");
			scanf(" %c", &c);
			node.data = c;
			insertRearLD(as, node);
			break;
		case 'O':
			pop = deleteFrontLD(as);
			if (pop)
				printf("%c\n", pop->data);
			free(pop);
			break;
		case 'I':
			pop = deleteRearLD(as);
			if (pop)
				printf("%c\n", pop->data);
			free(pop);
			break;
		case 'E':
			pop = peekFrontLD(as);
			if (pop)
				printf("%c\n", pop->data);
			break;
		case 'W':
			pop = peekRearLD(as);
			if (pop)
				printf("%c\n", pop->data);
			break;
		case 'D':
			delete_test();
			system("leaks a.out");
			break;
		case 'S':
			displayLinkedDeque(as);
			break;
		default:
			break;
		}
	}
    return 0;
}