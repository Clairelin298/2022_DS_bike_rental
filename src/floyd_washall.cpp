#include "./nthu_bike.h"

using namespace std;

// this file is the floydwarshall algo for all-pairs shortest path

int **floydWarshall(int dist[][MAX_STATION], int V) // V is the actual station number
{
	int **floyd = new int *[V];
	for (int i = 0; i < V; i++)
	{
		floyd[i] = new int[V];
		for (int j = 0; j < V; j++)
		{
			floyd[i][j] = dist[i][j];
		}
	}

	int i, j, k;
	for (k = 0; k < V; k++)
	{
		// Pick all vertices as source one by one
		for (i = 0; i < V; i++)
		{
			// Pick all vertices as destination for the
			for (j = 0; j < V; j++)
			{
				// If vertex k is on the shortest path from i to j, then update the value of dist[i][j]
				if (floyd[i][j] > (floyd[i][k] + floyd[k][j]) && (floyd[k][j] != IFINITY && floyd[i][k] != IFINITY))
					floyd[i][j] = floyd[i][k] + floyd[k][j];
			}
		}
	}
	return floyd;
}
