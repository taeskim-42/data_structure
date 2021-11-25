/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverseList.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacman <pacman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:52:21 by pacman            #+#    #+#             */
/*   Updated: 2021/11/25 15:01:09 by pacman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/linkedlist.h"

void reverseLinkedList(LinkedList *linkedList)
{
    int i;
    ListNode *tmp_node;

    i = -1;
    tmp_node = 0;
    if (!linkedList->currentElementCount)
    {
        tmp_node = linkedList->headerNode.pLink;
        while (++i < linkedList->currentElementCount - 1)
        {
            tmp_node->pLink = tmp_node;
        }
    }
    else
    {
        printf("linkedList is empty");
    }
}