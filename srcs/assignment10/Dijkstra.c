#include "../../includes/linkedgraph.h"

# define MAX 100

int getEdgeWeight(LinkedGraph *pGraph, int fromVertexID, int toVertextID)
{
    LinkedList *from = pGraph->ppAdjEdge[fromVertexID];
    ListNode *curr = from->frontNode;

    while(curr)
    {
        if(curr->data == toVertextID)
            return (curr->weight);
        curr = curr->pRLink;
    }
    return (MAX);
}

int getMinDistance(int *distance, int *isSelected, int maxNodeCount)
{
    int min = MAX, flag = 0;
    int i, dot;
    dot = 0;
    for(i = 0 ; i < maxNodeCount ; i++)
    {
        if(distance[i] < min && !isSelected[i])
        {
            min = distance[i];
            dot = i;
            flag = 1;
        }    
    }
    if(flag)
        return (dot);
    return (0);
}

int *Dijkstra(LinkedGraph *pGraph, int startVertexId)
{
    int *isSelected;
    int *distance;
    int id;
    int toVertexID;
    ListNode *curr;
    
    distance = (int *)calloc(pGraph->maxVertexCount, sizeof(int));
    //시작 기점으로 거리
    isSelected = (int *)calloc(pGraph->maxVertexCount, sizeof(int));
    //방문여부
    if (!distance || !isSelected)
        printf("Mal Error\n");
    //init
    for(int i = 0 ; i < pGraph->maxVertexCount ; i++)
        distance[i] = MAX;
    //거리 초기화
    distance[startVertexId] = 0;
    //시작 점의 거리는 0으로 초기화.

    for(int i = 0 ; i < pGraph->maxVertexCount - 1 ; i++)
    {
        id = getMinDistance(distance, isSelected, pGraph->maxVertexCount);
        if(id == -1)
            break;
        curr = pGraph->ppAdjEdge[id]->frontNode;
        isSelected[id] = 1;
        while(curr)
        {
            toVertexID = curr->data;
            if(distance[toVertexID] > distance[id] + curr->weight)
                distance[toVertexID] = distance[id] + curr->weight;
            curr = curr->pRLink;
        }
    }
    free(isSelected);
    return (distance);
}

void test()
{
    int i = 0;
    int *sol;

    LinkedGraph *pG4 = 0;
    pG4 = createLinkedGraph(6);

    if (!pG4)
        return;
    for (i = 0; i < 6; i++)
    {
        addVertexLG(pG4, i);
    }

    // ✅학습 자료와 동일한 데이터
    addEdgewithWeightLG(pG4, 0, 1, 1);
    addEdgewithWeightLG(pG4, 1, 2, 2);
    addEdgewithWeightLG(pG4, 2, 0, 4);
    addEdgewithWeightLG(pG4, 2, 1, 2);
    addEdgewithWeightLG(pG4, 2, 3, 1);
    addEdgewithWeightLG(pG4, 3, 4, 8);
    //addEdgewithWeightLG(pG4, 4, 5, 4);
    //addEdgewithWeightLG(pG4, 5, 3, 3);

    printf("G4: Directed Weighted\n");
    displayLinkedGraph(pG4);
    sol = Dijkstra(pG4, 0);
    for(int i = 0 ; i < 6 ; i++)
        printf("%d ", sol[i]);
    printf("\n");
    free(sol);
    deleteLinkedGraph(pG4);
}

int main()
{
    test();
    system("leaks a.out");
    return 0;
}

// 0 : [1 : 0] [2 : 0]
// 1 : [0 : 0] [2 : 0]
// 2 : [0 : 0] [1 : 0] [3 : 0]
// 3 : [2 : 0] [4 : 0] [5 : 0]
// 4 : [3 : 0] [5 : 0]
// 5 : [3 : 0] [4 : 0]

// 0 :
// 1 : [2 : 0]
// 2 : [1 : 0] [3 : 0]
// 3 : [2 : 0] [5 : 0]
// 4 : [5 : 0]
// 5 : [3 : 0] [4 : 0]