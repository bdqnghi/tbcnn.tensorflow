#include "Floyd-Warshall.h"

void FloydWarshallShortestPath::Init()
{
    for (int i = 0; i <= MAXV; i++)
    {
        for (int j = 0; j < MAXV; j++)
        {
            g->weight[i][j] = MAX_INT;
        }
    }
}

void FloydWarshallShortestPath::InsertEdget(int x, int y, int weight)
{
    g->weight[x][y] = weight;
}

void FloydWarshallShortestPath::ComputeShortestPath()
{
    int through_k;
    for (int k = 1; k <= g->nvertices; k++)
    {
        for (int i = 1; k <= g->nvertices; i++)
        {
            for (int j = 1; j<=g->nvertices;j++)
            {
                through_k = g->weight[i][k] + g->weight[k][j];
                if (through_k < g->weight[i][j])
                {
                    g->weight[i][j] = through_k;
                }
            }
        }
    }
}


