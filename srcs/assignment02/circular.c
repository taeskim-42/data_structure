/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacman <pacman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 10:34:40 by pacman            #+#    #+#             */
/*   Updated: 2021/11/25 14:42:23 by pacman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/circular.h"

LinkedList* createLinkedList()
{
	LinkedList *tmp_linked_list;

	tmp_linked_list = (LinkedList *)malloc(sizeof(LinkedList));
	if (!tmp_linked_list)
		return (NULL);
	memset(tmp_linked_list, 0, sizeof(tmp_linked_list));
	return (tmp_linked_list);
}

int addLLElement(LinkedList* pList, int position, ListNode element)
{
	/*
	 currentElementCount가 0인 경우
	 1. header 정해주기
	 2. header는 첫번재 element
	 2. header의 plist가 자기자신을 가리키게 하기

	 currentEementCount가 == 1
	 1. 넣고자 하는 position 확인
	 2. position이 0이면 header로 정하고
	 3. positino이 1이면 header 첫번째 노드의 plink를 새로 들어오는 노드의 메모리로
	 4. 새롭게 들어오는 노드의 plink는 처음 것으로

	 currentElementCount == 1 && position > 0
	*/
	int i;
	ListNode *new_node;
	ListNode *tmp_node;
	
	i = -1;
	new_node = 0;
	tmp_node = 0;
	if (!pList)
	{
		if (position <= pList->currentElementCount && position >= 0)
		{
			new_node = (ListNode *)malloc(sizeof(ListNode));
			if (!new_node)
				return (NULL);
			*new_node = element;
			if (pList->currentElementCount == 0)
			{
				pList->headerNode = element;
				element.pLink = &element;
			}
			else
			{
				tmp_node = &(pList->headerNode);
				while (++i < position)
				{
					tmp_node = tmp_node->pLink;
				}
				new_node->pLink = tmp_node->pLink;
				tmp_node->pLink = new_node;
				if (position == 0)
				{
					pList->headerNode = *(new_node);
					new_node->pLink = new_node;
				}
				if (position == pList->currentElementCount)
				{
					pList->headerNode.pLink = new_node;
					new_node->pLink = &(pList->headerNode);
				}
			}
			pList->currentElementCount++;
		}
		else
		{
			printf("index error");
		}
	}
	else
	{
		printf("plist is null");
	}
}

/*
	position이 0 인경우
	가장 마지막에 있는 node가 가장 처음 node를 가리키도록 변경
		하지만 currentElementCount가 1인경우
		날리고 headernode null로

	postion이 currentElementCount인 경우
		position의 위치까지 이동시킴
	가장 마지막 앞의 node가 가장 처음 node를 가리키도록
		하지만 currentElementCount가 1인경우
		날리고 headernode null로
	
	그이외의 경우
		postion이 currentElementCount인 경우
			position의 위치까지 이동시킴
		직전노드의 값을 가지고 있음.
		직전노드의 plink가 position에 있는 노드의 plink로 연결되게 함.
		그리고 날림.

		

*/

int removeLLElement(LinkedList* pList, int position)
{
	int i;
	ListNode *tmp_node;
	ListNode *del_node;

	i = -1;
	tmp_node = 0;
	del_node = 0;
	if (!pList)
	{
		if (position >= 0 && position < pList->currentElementCount)
		{
			if (position == 0)
			{
				if (pList->currentElementCount == 1)
				{
					free(&pList->headerNode);
					pList->headerNode.pLink = 0;
				}
				else
				{
					tmp_node = pList->headerNode.pLink;
					*(del_node) = pList->headerNode;
					while (++i < pList->currentElementCount - 1)
					{
						tmp_node = tmp_node->pLink;
					}
					tmp_node->pLink = del_node->pLink;
					pList->headerNode = *(del_node);
					free(del_node);
					del_node = 0;
				}
			}
			else
			{
				tmp_node = pList->headerNode.pLink;
				while (++i < position - 1)
				{
					tmp_node = tmp_node->pLink;
				}
				del_node = tmp_node->pLink;
				tmp_node->pLink = del_node->pLink;
				free(del_node);
				del_node = 0;
			}
		}
		else
		{
			printf("index error");
		}
	}
	else
	{
		printf("plist NUll");
	}
}

ListNode* getLLElement(LinkedList* pList, int position)
{
	int i;
	ListNode *tmp_node;
	
	i = -1;
	tmp_node = 0;
	if (!pList)
	{
		if (position >= 0 && position < pList->currentElementCount)
		{
			tmp_node = pList->headerNode.pLink;
			while (++i < position - 1)
			{
				tmp_node = tmp_node->pLink;
			}
		}
		else
		{
			printf("index error");
		}
	}
	else
	{
		printf("pList is Null");
	}
	return (tmp_node);
}


void clearLinkedList(LinkedList* pList)
{
	int i;
	ListNode *tmp_node;

	i = -1;
	tmp_node = 0;
	if (!pList)
	{
		tmp_node = pList->headerNode.pLink;
		while (++i < pList->currentElementCount)
		{
			tmp_node = tmp_node->pLink;
			tmp_node->data = 0;
		}
	}
	else
	{
		printf("pList is null");
	}
}

int getLinkedListLength(LinkedList* pList)
{
	return (!pList ? 0 : pList->currentElementCount);
}

void deleteLinkedList(LinkedList* pList)
{
	int i;

	i = -1;
	if (!pList)
	{
		while (++i < pList->currentElementCount - 1)
		{
			removeLLElement(pList, 0);
		}
	}
	else
	{
		printf("pList Null");
	}
}