/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacman <pacman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:19:10 by pacman            #+#    #+#             */
/*   Updated: 2021/11/23 15:02:50 by pacman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/linkedlist.h"

LinkedList* createLinkedList()
{
    LinkedList *ll;

    ll = 0;
    ll = (LinkedList *)malloc(sizeof(LinkedList));
    if (!ll)
    {
        return (NULL);
    }
    else
    {
        memset(ll, 0, sizeof(LinkedList));
    }
    return (ll);
}

int addLLElement(LinkedList* pList, int position, ListNode element)
{
    int i;
    int ret;
    ListNode *newNode;
    ListNode *tmpNode;

    i = -1;
    ret = FALSE;
    newNode = 0;
    tmpNode = 0;
    if (!pList)
    {
        if (position >= 0 && position <= pList->currentElementCount)
        {
            newNode = (ListNode *)malloc(sizeof(ListNode));
            if (!newNode)
            {
                printf("memory allocation error");
            }
            else
            {
                *newNode = element;
                *tmpNode = pList->headerNode;
                while (++i < position)
                {
                    tmpNode = tmpNode->pLink;
                }
                newNode->pLink = tmpNode->pLink;
                tmpNode->pLink = newNode;
                pList->currentElementCount++;
                ret = TRUE;
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
    return (ret);
}

int removeLLElement(LinkedList* pList, int position)
{
    int i;
    int ret;
    ListNode *tmpNode;
    ListNode *delNode;

    i = -1;
    ret = FALSE;
    tmpNode = 0;
    delNode = 0;
    if (!pList)
    {
        if (position >= 0 && position < pList->currentElementCount)
        {
            *tmpNode = pList->headerNode;
            while (++i < position)
            {
                tmpNode = tmpNode->pLink;
            }
            delNode = tmpNode->pLink;
            tmpNode->pLink = delNode->pLink;
            free(delNode);
            delNode = 0;
            pList->currentElementCount--;
            ret = TRUE;
        }
        else
        {
            printf("index Error");
        }
    }
    else
    {
        printf("pList Error");
    }      
    return (ret);
}

ListNode* getLLElement(LinkedList* pList, int position)
{
    int i;
    ListNode *tmpNode;

    i = -1;
    tmpNode = 0;
    if (!pList)
    {
        if(position >= 0 && position <= pList->currentElementCount)
        {
            *tmpNode = pList->headerNode;
            while (++i < position)
            {
                tmpNode = tmpNode->pLink;   
            }
            return tmpNode->pLink;
        }
    }
    else
    {
        printf("pList Error");
        return (tmpNode);
    }
}

void clearLinkedList(LinkedList* pList)
{
    int i;
    ListNode *tmpNode;

    i = -1;
    tmpNode = 0;
    if (!pList)
    {
        *tmpNode = pList->headerNode;
        while(++i < pList->currentElementCount)
        {
            tmpNode = tmpNode->pLink;
            tmpNode->data = 0;
        }
    }
}
int getLinkedListLength(LinkedList* pList)
{
    return (!pList ? pList->currentElementCount : 0);
}
void deleteLinkedList(LinkedList* pList)
{
    int i;
    int ret;
    ListNode *tmpNode;
    ListNode *delNode;

    i = -1;
    ret = FALSE;
    tmpNode = 0;
    delNode = 0;
    if (!pList)
    {
        *tmpNode = pList->headerNode;
        while (++i < pList->currentElementCount)
        {
            removeLLElement(pList, i);
        }
        free(pList);
        pList = 0;
    }
    else
    {
        printf("pList already deleted");
    }
    return (ret);
}
