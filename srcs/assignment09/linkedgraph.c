#include "../../includes/linkedgraph.h"

void *free_graph(LinkedGraph *pGraph)
{
    printf("Malloc Error");
    free(pGraph);
    pGraph = NULL;
    return (NULL);
}

void *free_vertex(LinkedGraph *pGraph)
{
    free(pGraph->pVertex);
    pGraph->pVertex = NULL;
    return(free_graph(pGraph));
}

void *free_edge(LinkedGraph *pGraph)
{
    free(pGraph->ppAdjEdge);
    pGraph->ppAdjEdge = NULL;
    return(free_vertex(pGraph));
}

void *free_edgenode(LinkedGraph *pGraph, int i)
{
    for (int j = 0; j < i; j++)
    {
        free(pGraph->ppAdjEdge[j]);
        pGraph->ppAdjEdge[j] = 0;
    }
    return (free_edge(pGraph));
}

// 그래프 생성
LinkedGraph* createLinkedGraph(int maxVertexCount)
{
    LinkedGraph *graph;

    if (maxVertexCount <= 0)
    {
        printf("maxVertexCount can not be zero or minus\n");
        return (NULL);
    }
    graph = (LinkedGraph *)malloc(sizeof(LinkedGraph));
    if (!graph)
    {
        printf("Malloc Error");
        return (NULL);
    }
    graph->maxVertexCount = maxVertexCount;
    graph->currentVertexCount = 0;
    graph->currentEdgeCount = 0;
    graph->graphType = GRAPH_UNDIRECTED;
    graph->pVertex = (int *)calloc(maxVertexCount, sizeof(int));
    if (!graph->pVertex)
        return (free_graph(graph));
    graph->ppAdjEdge = (int **)calloc(maxVertexCount, sizeof(int *));
    if (!graph->ppAdjEdge)
        return(free_vertex(graph));
    for(int i = 0 ; i < maxVertexCount ; i++)
    {
        graph->ppAdjEdge[i] = createLinkedList();
        if (!graph->ppAdjEdge[i])
            return (free_edgenode(graph, i)); 
    }

}
LinkedGraph* createLinkedDirectedGraph(int maxVertexCount)
{
    LinkedGraph *graph;

    graph = createLinkedGraph(maxVertexCount);
    if (!graph)
    {
        printf("Malloc Error");
        return (NULL);
    }
    graph->graphType = GRAPH_DIRECTED;
    return (graph);
}

// 그래프 삭제
void deleteLinkedGraph(LinkedGraph* pGraph);

// 공백 그래프 여부 판단
int isEmptyLG(LinkedGraph* pGraph);

// 노드 추가
int addVertexLG(LinkedGraph* pGraph, int vertexID)
{
    if(!pGraph || !pGraph->pVertex || !pGraph->ppAdjEdge)
        return (FALSE);
     if(vertexID >= pGraph->maxVertexCount ||\
        pGraph->pVertex[vertexID] == USED)
    {
        printf("node is already exist\n");
        return (FALSE);
    }
    pGraph->pVertex[vertexID] = USED;
    pGraph->currentVertexCount++;
    return(TRUE);
}

// 간선 추가
int addEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
    ListNode elem = {toVertexID, 0, 0};
    if(!checkVertexValid(pGraph, fromVertexID) || 
        !checkVertexValid(pGraph, toVertexID))
        return (FALSE);
    addLLElement(pGraph->ppAdjEdge[fromVertexID], elem);
    if(pGraph->graphType == GRAPH_UNDIRECTED)
    {
        elem.data = fromVertexID;
        addLLElement(pGraph->ppAdjEdge[toVertexID], elem);
    }
    pGraph->currentEdgeCount++;
}

int addEdgewithWeightLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
    ListNode elem = {toVertexID, weight, 0};
    if(!checkVertexValid(pGraph, fromVertexID) || 
        !checkVertexValid(pGraph, toVertexID))
        return (FALSE);
    addLLElement(pGraph->ppAdjEdge[fromVertexID], elem);
    if(pGraph->graphType == GRAPH_UNDIRECTED)
    {
        elem.data = fromVertexID;
        elem.weight = weight;
        addLLElement(pGraph->ppAdjEdge[toVertexID], elem);
    }
}

// 노드의 유효성 점검.
int checkVertexValid(LinkedGraph* pGraph, int vertexID)
{
    if(!pGraph || !pGraph->pVertex || !pGraph->ppAdjEdge)
        return (FALSE);
    if (vertexID >= pGraph->maxVertexCount ||\
        pGraph->pVertex[vertexID] == NOT_USED)
    {
        printf("node is not valid\n");
        return (FALSE);
    }
    return (TRUE);
}

// 노드 제거
int removeVertexLG(LinkedGraph* pGraph, int vertexID)
{
    ListNode *curr;
    ListNode *next;

    if (!checkVertexValid(pGraph, vertexID)|| pGraph->currentVertexCount <= 0 ||
        vertexID >= pGraph->maxVertexCount)
    {
        return (FALSE);
    }
    curr = pGraph->ppAdjEdge[vertexID];
    while(curr)
    {
        next = curr->pRLink;
        removeEdgeLG(pGraph, vertexID, curr->data);
        if(pGraph->graphType == GRAPH_DIRECTED)
            removeEdgeLG(pGraph, curr->data, vertexID);
        curr = next;
    }
    return (TRUE);
}

int removeEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
    if(!checkVertexValid(pGraph, fromVertexID) || 
        !checkVertexValid(pGraph, toVertexID))
        return (FALSE);
    deleteGraphNode(pGraph->ppAdjEdge[fromVertexID], toVertexID);
}

// 노드 개수 반환
int getVertexCountLG(LinkedGraph* pGraph)
{
    return (!pGraph ? -1 : pGraph->currentVertexCount);
}

// 최대 노드 개수 반환
int getMaxVertexCountLG(LinkedGraph* pGraph)
{
    return (!pGraph ? -1 : pGraph->maxVertexCount);
}

// 그래프 종류 반환.
int getGraphTypeLG(LinkedGraph* pGraph)
{
    return (!pGraph ? FALSE : pGraph->graphType);
}
