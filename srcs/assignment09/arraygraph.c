#include "../../includes/arraygraph.h"

void *free_graph(ArrayGraph *pGraph)
{
    printf("Malloc Error");
    free(pGraph);
    pGraph = NULL;
    return (NULL);
}

void *free_vertex(ArrayGraph *pGraph)
{
    free(pGraph->pVertex);
    pGraph->pVertex = NULL;
    return(free_graph(pGraph));
}

void *free_edge(ArrayGraph *pGraph)
{
    free(pGraph->ppAdjEdge);
    pGraph->ppAdjEdge = NULL;
    return(free_vertex(pGraph));
}

void *free_edgenode(ArrayGraph *pGraph, int i)
{
    
    for (int j = 0; j < i; j++)
    {
        free(pGraph->ppAdjEdge[j]);
        pGraph->ppAdjEdge[j] = 0;
    }
    return (free_edge(pGraph));
}

ArrayGraph *createArrayGraph(int maxVertexCount)
{
    ArrayGraph *graph;

    if (maxVertexCount <= 0)
    {
        printf("maxVertexCount can not be zero or minus\n");
        return (NULL);
    }
    
    graph = (ArrayGraph *)malloc(sizeof(ArrayGraph));
    if (!graph)
    {
        printf("Malloc Error");
        return (NULL);
    }
    
    graph->maxVertexCount = maxVertexCount;
    graph->currentVertexCount = 0;
    graph->graphType = GRAPH_UNDIRECTED;
    
    graph->pVertex = (int *)calloc(maxVertexCount, sizeof(int));
    if (!graph->pVertex)
        return (free_graph(graph));
    
    graph->ppAdjEdge = (int **)calloc((maxVertexCount + 1), sizeof(int *));
    if (!graph->ppAdjEdge)
        return (free_vertex(graph));
    
    for (int i = 0; i < maxVertexCount + 1; i++)
    {
        graph->ppAdjEdge[i] = (int *)calloc((maxVertexCount + 1), sizeof(int));
        if (!graph->ppAdjEdge[i])
            return(free_edgenode(graph, i));
    }
    
    return (graph);
}

ArrayGraph *createArrayDirectedGraph(int maxVertexCount)
{
    ArrayGraph *graph;

    graph = createArrayGraph(maxVertexCount);
    if (!graph)
    {
        printf("Malloc Error");
        return (NULL);
    }
    graph->graphType = GRAPH_DIRECTED;
    return (graph);
}

// 그래프 삭제
void deleteArrayGraph(ArrayGraph* pGraph)
{
    // edge free
    for (int i = 0; i <= pGraph->maxVertexCount; i++)
    {
        free(pGraph->ppAdjEdge[i]);
        pGraph->ppAdjEdge[i] = NULL;
    }
    free(pGraph->ppAdjEdge);
    pGraph->ppAdjEdge = NULL;
    // vertex free
    free(pGraph->pVertex);
    pGraph->pVertex = NULL;
    // graph free
    free(pGraph);
    pGraph = NULL;
}

// 공백 그래프 여부 판단
int isEmptyAG(ArrayGraph* pGraph)
{
    for (int i = 0; i < pGraph->maxVertexCount; i++)
    {
        if (pGraph->pVertex[i] == USED)
            return (FALSE);
    }
    return (TRUE);
}

// 노드 추가
int addVertexAG(ArrayGraph* pGraph, int vertexID)
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
    pGraph->ppAdjEdge[vertexID + 1][0] = vertexID;
    pGraph->ppAdjEdge[0][vertexID + 1] = vertexID;
    pGraph->currentVertexCount++;
    return(TRUE);
}

// 간선 추가
int addEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
    if(!checkVertexValid(pGraph, fromVertexID) || 
        !checkVertexValid(pGraph, toVertexID))
        return (FALSE);
    pGraph->ppAdjEdge[fromVertexID + 1][toVertexID + 1] = 1;
    if(pGraph->graphType == GRAPH_UNDIRECTED)
        pGraph->ppAdjEdge[toVertexID + 1][fromVertexID + 1] = 1;
    return (TRUE);
}

int addEdgewithWeightAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
    if(!checkVertexValid(pGraph, fromVertexID) || 
        !checkVertexValid(pGraph, toVertexID))
        return (FALSE);
    pGraph->ppAdjEdge[fromVertexID + 1][toVertexID + 1] = weight;
    if(pGraph->graphType == GRAPH_UNDIRECTED)
        pGraph->ppAdjEdge[toVertexID + 1][fromVertexID + 1] = weight;
    return (TRUE);
}

// 노드의 유효성 점검.
int checkVertexValid(ArrayGraph* pGraph, int vertexID)
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
int removeVertexAG(ArrayGraph* pGraph, int vertexID)
{
    if (!checkVertexValid(pGraph, vertexID)|| pGraph->currentVertexCount <= 0 ||
        vertexID >= pGraph->maxVertexCount)
    {
        return (FALSE);
    }
    pGraph->pVertex[vertexID] = NOT_USED;
    for (int i = 1; i <= pGraph->maxVertexCount; i++)
    {
        pGraph->ppAdjEdge[vertexID + 1][i] = 0;
        pGraph->ppAdjEdge[i][vertexID + 1] = 0;
    }
    pGraph->currentVertexCount--;
    return (TRUE);
}

// 간선 제거
int removeEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
    if(!checkVertexValid(pGraph, fromVertexID) || 
        !checkVertexValid(pGraph, toVertexID))
        return (FALSE);
    pGraph->ppAdjEdge[fromVertexID + 1][toVertexID + 1] = 0;
    if(pGraph->graphType == GRAPH_UNDIRECTED)
        pGraph->ppAdjEdge[toVertexID + 1][fromVertexID + 1] = 0;
    return (TRUE);
}

// 그래프 정보 출력
void displayArrayGraph(ArrayGraph* pGraph)
{
    if(!pGraph || !pGraph->pVertex || !pGraph->ppAdjEdge)
        return ;
    printf("========Info==========\n");
    printf("maxVertexCount : %d\n", pGraph->maxVertexCount);
    printf("currentVertexCount : %d\n", pGraph->currentVertexCount);
    printf("graphType : ");
    if(pGraph->graphType == GRAPH_UNDIRECTED)
        printf("GRAPH_UNDIRECTED\n");
    else
        printf("GRAPH_DIRECTED\n");
    printf("========Graph=========\n"); 
    for(int i = 1 ; i <= pGraph->maxVertexCount ; i++)
    {
        for(int j = 1 ; j <= pGraph->maxVertexCount ; j++)
            printf("%d ", pGraph->ppAdjEdge[i][j]);
        printf("\n");
    }
    printf("======================\n");
}

void test()
{
    int i = 0;
    ArrayGraph *pG1 = 0;
    ArrayGraph *pG2 = 0;
    ArrayGraph *pG4 = 0;

    pG1 = createArrayGraph(6);
    pG2 = createArrayDirectedGraph(6);
    pG4 = createArrayDirectedGraph(6);
    if (pG1 && pG2 && pG4)
    {
        for (i = 0; i < 6; i++)
        {
            addVertexAG(pG1, i);
            addVertexAG(pG2, i);
            addVertexAG(pG4, i);
        }

        addEdgeAG(pG1, 0, 1);
        addEdgeAG(pG1, 0, 2);
        addEdgeAG(pG1, 1, 2);
        addEdgeAG(pG1, 2, 3);
        addEdgeAG(pG1, 3, 4);
        addEdgeAG(pG1, 3, 5);
        addEdgeAG(pG1, 4, 5);

        addEdgeAG(pG2, 0, 1);
        addEdgeAG(pG2, 1, 2);
        addEdgeAG(pG2, 2, 0);
        addEdgeAG(pG2, 2, 1);
        addEdgeAG(pG2, 2, 3);
        addEdgeAG(pG2, 3, 2);
        addEdgeAG(pG2, 3, 4);
        addEdgeAG(pG2, 4, 5);
        addEdgeAG(pG2, 5, 3);
        
        addEdgewithWeightAG(pG4, 0, 1, 4);
        addEdgewithWeightAG(pG4, 1, 2, 1);
        addEdgewithWeightAG(pG4, 2, 0, 2);
        addEdgewithWeightAG(pG4, 2, 1, 3);
        addEdgewithWeightAG(pG4, 2, 3, 2);
        addEdgewithWeightAG(pG4, 3, 2, 1);
        addEdgewithWeightAG(pG4, 3, 4, 1);
        addEdgewithWeightAG(pG4, 4, 5, 1);
        addEdgewithWeightAG(pG4, 5, 3, 2);

        printf("G1: Undirected\n");
        displayArrayGraph(pG1);
        printf("G2: Directed\n");
        displayArrayGraph(pG2);
        printf("G4: Directed Weighted\n");
        displayArrayGraph(pG4);

        deleteArrayGraph(pG1);
        deleteArrayGraph(pG2);
        deleteArrayGraph(pG4);
    }
}

int main()
{
    test();
    system("leaks a.out");
    return 0;
}
