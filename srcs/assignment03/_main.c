/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacman <pacman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:32:02 by sujilee           #+#    #+#             */
/*   Updated: 2021/12/06 16:13:35 by pacman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "arraystack.h"
#include "linkedstack.h"

int main()
{
	// // ArrayStack *myArray;
	// // ArrayStackNode *curr;
	// // ArrayStackNode node0 = {0};
	LinkedStack *linkeds;
	StackNode node1 = { 0 };
	StackNode *curr;
	int len = 0;
	int position = 0;
	int max;
	char c;
	printf("input maxsize(0 when linkedlist): ");
	scanf(" %d", &max);
	// myArray = createArrayStack(max);
	linkeds = createLinkedStack();
	while(1)
	{
		// rewind(stdin);
		printf("put Push pOp pEek Delete: ");
		scanf(" %c", &c);
		// rewind(stdin);
		switch (c)
		{
		/*
		------------------------------------------------------------------------

										ARRAY_STACK
										
		------------------------------------------------------------------------
		*/
		// case 'P':
		// 	scanf("%c", &(node0.data));
		// 	pushAS(myArray, node0);
		// 	break ;
		// case 'O':
		// 	printf("%d\n", popAS(myArray)->data);
		// 	break ;
		// case 'K':
		// 	printf("%d\n", peekAS(myArray)->data);
		// 	break ;
		// case 'F':
		// 	printf("stack is %sfull\n", isArrayStackFull(myArray) == TRUE ? "" : "not ");
		// 	break ;
		// case 'E':
		// 	printf("stack is %sempty\n", isArrayStackEmpty(myArray) == TRUE ? "" : "not ");
		// 	break ;
		// case 'R':
		// 	for (int i = 0; i < myArray->currentElementCount; i++)
		// 		printf("%c ", myArray->pElement[i].data);
		// 	printf("\n");
		/*
		------------------------------------------------------------------------

										LINKED_STACK
										
		------------------------------------------------------------------------
		*/
		case 'P':
			scanf("%c", &(node1.data));
			pushLS(linkeds, node1);
			break ;
		case 'O':
			printf("%d\n", (curr = popLS(linkeds)) ? curr->data : -1 );
			break ;
		case 'K':
			printf("%d\n", (curr = peekLS(linkeds)) ? curr->data : -1 );
			break ;
		case 'F':
			printf("stack is %sfull\n", isLinkedStackFull(linkeds) == TRUE ? "" : "not ");
			break ;
		case 'E':
			printf("stack is %sempty\n", isLinkedStackEmpty(linkeds) == TRUE ? "" : "not ");
			break ;
		default:
			break;
		}
	}
	if(linkeds)
		deleteLinkedStack(linkeds);
	return (0);
}