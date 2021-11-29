/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacman <pacman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:26:07 by pacman            #+#    #+#             */
/*   Updated: 2021/11/23 15:00:46 by pacman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/arraylist.h"

ArrayList*	createArrayList(int maxElementCount)
{
	ArrayList	*tmp_arrayList;

	if (maxElementCount > 0)
	{
		tmp_arrayList = (ArrayList *)malloc(sizeof(ArrayList));
		if (!tmp_arrayList)
		{
			return (NULL);
		}
		else
		{
			tmp_arrayList->maxElementCount = maxElementCount;
			tmp_arrayList->currentElementCount = 0;
			tmp_arrayList->pElement = NULL;
		}
	}
	else
	{
		printf("ElementCount is not enough");
		return (NULL);
	}
	tmp_arrayList->pElement = (ArrayListNode *)malloc(sizeof(ArrayListNode) * maxElementCount);
	if (!tmp_arrayList->pElement)
	{
		free(tmp_arrayList);
		tmp_arrayList = 0;
		return (NULL);
	}
	memset(tmp_arrayList->pElement, 0, sizeof(ArrayListNode) * maxElementCount);
	return (tmp_arrayList);
}

int addALElement(ArrayList* pList, int position, ArrayListNode element)
{
	int	i;
	int ret;

	i = pList->currentElementCount;
	ret = FALSE;
	if (!pList)	
	{
		if (!isArrayListFull(pList))
		{
			if (position >= 0 && position <= pList->currentElementCount)
			{
				while (--i >= position)
				{
					pList->pElement[i + 1] = pList->pElement[i];
				}
				pList->currentElementCount++;
				pList->pElement[position] = element;
				ret = TRUE;
			}
			else
			{
				printf("Index Error");
			}
		}
		else
		{
			printf("Overflow");
		}
	}
	retrun (ret);
}

void deleteArrayList(ArrayList* pList)
{
	if (!pList)
	{
		free(pList->pElement);
		pList->pElement = 0;
		free(pList);
		pList = 0;
	}
}

int removeALElement(ArrayList* pList, int position)
{
	int	i;
	int ret;

	i = position - 1;
	ret = FALSE;
	if (!pList)
	{
		if (position >= 0 && position < pList->currentElementCount)
		{
			while (++i < pList->currentElementCount - 1)
			{
				pList->pElement[i] = pList->pElement[i + 1];
			}
			pList->currentElementCount--;
			ret = TRUE;
		}
		else
		{
			printf("Index Error");
		}
	}
	return (ret);
}

ArrayListNode* getALElement(ArrayList* pList, int position)
{
	ArrayListNode	*node;

	node = 0;
	if (!pList)
	{
		if (position >= 0 && position < pList->currentElementCount)
		{
			node = &(pList->pElement[position]);
		}
		else
		{
			printf("index Error");
		}
	}
	return (node);
}

int isArrayListFull(ArrayList* pList)
{
	if (!pList)
		if (pList->currentElementCount == pList->maxElementCount)
			return (TRUE);
	return (FALSE);
}

int getArrayListLength(ArrayList* pList)
{	
	return (!pList ? pList->currentElementCount : 0);
}

void displayArrayList(ArrayList* pList)
{
	int i;

	i = -1;
	if (!pList)
	{
		printf("최대 갯수 %d", pList->maxElementCount);
		printf("현재 갯수 %d", pList->currentElementCount);
		while (++i < pList->currentElementCount)
		{
			printf("index: %d = value: %d\n", i, pList->pElement[i]);
		}
		while (++i < pList->maxElementCount)
		{
			printf("index: %d = empty\n", i);
		}
	}
	else
	{
		printf("AL is null");
	}
}
void clearArrayList(ArrayList* pList)
{
	int i;

	i = -1;
	if (!pList)
	{
		while (++i < pList->currentElementCount)
		{
			pList->pElement[i].data = 0;
		}
	}
	else
	{
		printf("pList Error");
	}
}