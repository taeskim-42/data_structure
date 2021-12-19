#include "../../includes/linkedgraph.h"

LinkedList* createLinkedList()
{
    LinkedList *list;

    list = (LinkedList *)malloc(sizeof(LinkedList));
    if(!list)
        return (FALSE);
    list->frontNode = NULL;
    list->rearNode = NULL;
    return(list);
}

int addLLElement(LinkedList* pList, ListNode element)
{
    ListNode *tmp;
    if (!pList)
        return (FALSE);
    tmp = (ListNode *)malloc(sizeof(ListNode));
    if (!tmp)
        return (FALSE);
    *tmp = element;
    if(!pList->frontNode)
    {
        pList->frontNode = pList->rearNode = tmp;
    }
    else
    {
        pList->rearNode->pRLink = tmp;
        tmp->pLLink = pList->rearNode;
        pList->rearNode = tmp;
    }
    return (TRUE);
}

int removeLLElement(LinkedList* pList, int VertexID)
{
    ListNode *tmp;
    ListNode *front;
    ListNode *next;
    
    tmp = getLLElement(pList, VertexID);
    if(!tmp)
        return (FALSE);
    if(tmp != pList->frontNode)
    {
        front = tmp->pLLink;
        front->pRLink = tmp->pRLink;
        if(tmp != pList->rearNode)
        {
            next = tmp->pRLink;
            next->pLLink = front;
        }
    }
    else
        pList->frontNode = tmp->pRLink;
    if(pList->frontNode)
        pList->rearNode = NULL;
    free(tmp);
    return (TRUE);
}

ListNode* getLLElement(LinkedList* pList, int VertexID)
{
    ListNode *tmp;

    tmp = pList->frontNode;
    while(tmp)
    {
        if(tmp->data == VertexID)
            return (tmp);
        tmp = tmp->pRLink;
    }
    return (FALSE);
}

void clearLinkedList(LinkedList* pList)
{
    ListNode *tmpNode;
    ListNode *curr;
    
    if (!pList)
        return ;
    curr = pList->frontNode;
    while (curr)
    {
        tmpNode = curr->pRLink;
        free(curr);
        curr = 0;
        curr = tmpNode;
    }
    pList->frontNode = pList->rearNode = NULL;
}

void deleteLinkedList(LinkedList* pList)
{
    clearLinkedList(pList);
    free(pList);
    pList = NULL;
}