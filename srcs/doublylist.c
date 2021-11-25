/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublylist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacman <pacman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 10:35:47 by pacman            #+#    #+#             */
/*   Updated: 2021/11/25 14:44:31 by pacman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doublylist.h"

DoublyList* createDoublyList()
{
    DoublyList *tmp_list;

    tmp_list = (DoublyList *)malloc(sizeof(DoublyList));
    if (!tmp_list)
        return (NULL);
    else
        memset(tmp_list, 0, sizeof(tmp_list));
    return (tmp_list);
}

int addDLElement(DoublyList* pList, int position, DoublyListNode element)
{
    int i;
    DoublyListNode *tmp_node;
    DoublyListNode *new_node;

    i = -1;
    tmp_node = 0;
    new_node = 0;
    if (!pList)
    {
        if (position >= 0 && position <= pList->currentElementCount)
        {
            new_node = (DoublyListNode *)malloc(sizeof(DoublyListNode));
            if (!new_node)
                return (NULL);
            *(new_node) = element;
            if (position == 0)
            {
                if (!pList->currentElementCount)
                {
                    pList->headerNode = *(new_node);
                }
                else
                {
                    *(tmp_node) = pList->headerNode;
                    new_node->pRLink = tmp_node->pLLink;
                    tmp_node->pRLink = new_node;
                    tmp_node->pLLink = new_node;
                    new_node->pLLink = tmp_node;
                }
            }
            else
            {
                if (pList->currentElementCount / position)
                {
                    tmp_node = pList->headerNode.pRLink;
                    while (++i < position - 1)
                    {
                        tmp_node = tmp_node->pRLink;
                    }
                }
                else
                {
                    tmp_node = pList->headerNode.pLLink;
                    while (++i < pList->currentElementCount - position)
                    {
                        tmp_node = tmp_node->pLLink;
                    }
                }
                new_node->pLLink = tmp_node->pLLink;
                new_node->pRLink = tmp_node;
                tmp_node->pLLink = new_node;
                tmp_node->pLLink->pRLink = new_node;
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
        printf("pList is NULL");
    }
}

void clearDoublyList(DoublyList* pList)
{
    int i;
    DoublyListNode *tmp_node;

    i = -1;
    tmp_node;
    if (!pList)
    {
        *(tmp_node) = pList->headerNode;
        while (++i < pList->currentElementCount)
        {
            tmp_node->data = 0;
            tmp_node = tmp_node->pRLink;
        }
    }
    else
    {
        printf("pList null");
    }
}
int getDoublyListLength(DoublyList* pList)
{
    return (!pList ? 0 : pList->currentElementCount);
}

DoublyListNode* getDLElement(DoublyList* pList, int position)
{
    int i;
    DoublyListNode *tmp_node;

    i = -1;
    tmp_node = 0;
    if (!pList)
    {
        if (position >= 0 && position < pList->currentElementCount)
        {
            *(tmp_node) = pList->headerNode;
            if (pList->currentElementCount / position)
            {
                while (++i < position - 1)
                {
                    tmp_node = tmp_node->pRLink;
                }
            }
            else
            {
                while (++i < pList->currentElementCount - position)
                {
                    tmp_node = tmp_node->pLLink;
                }
            }
        }
        else
        {
            printf("index error");
        }
    }
    else
    {
        printf("pList null");
    }
    return (tmp_node);
}

void deleteDoublyList(DoublyList* pList)
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

int removeDLElement(DoublyList* pList, int position)
{
     int i;
	DoublyListNode *tmp_node;
	DoublyListNode *del_node;

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
					free(pList->headerNode.pLLink);
					pList->headerNode.pLLink = 0;
                    pList->headerNode.pRLink = 0;
				}
				else
				{
                    *(del_node) = pList->headerNode;
                    tmp_node->pRLink->pLLink = tmp_node->pLLink;
                    tmp_node->pLLink->pRLink = tmp_node->pRLink;
					pList->headerNode = *(tmp_node->pRLink);
					free(del_node);
					del_node = 0;
				}
			}
			else
			{
				*(tmp_node) = pList->headerNode;
                if (pList->currentElementCount / position)
                {
                    while (++i < position - 1)
                    {
                        tmp_node = tmp_node->pRLink;
                    }
                }
                else
                {
                    while (++i < pList->currentElementCount - position)
                    {
                        tmp_node = tmp_node->pLLink;
                    }
                }
                tmp_node->pRLink->pLLink = tmp_node->pLLink;
                tmp_node->pLLink->pRLink = tmp_node->pRLink;
                pList->headerNode = *(tmp_node->pRLink);
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

void displayDoublyList(DoublyList* pList)
{
   
}