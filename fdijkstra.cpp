#include "fdijkstra.h"

#include <iostream>
#include <limits>

using namespace std;

void dijkstra(vector<double> G, int n, int startNode, int endNode, vector <int> &path, double &cost) 
{
	vector<double> mCosts(n * n);
	fill(mCosts.begin(), mCosts.end(), numeric_limits<double>::infinity());
	vector<double> distance(n), pred(n);
	double mindistance;
	vector<bool> visited(n);
	int count, nextNode;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (G[i * n + j] == 0)
				mCosts[i * n + j] = numeric_limits<double>::infinity();
			else
				mCosts[i * n + j] = G[i * n + j];
	for(int i = 0; i < n; i++)
	{
		distance[i] = mCosts[startNode * n + i];
		pred[i] = startNode;
		visited[i] = false;
	}
	distance[startNode] = 0;
	visited[startNode] = true;
	count = 1;
	while (count < n - 1)
	{
		mindistance = numeric_limits<double>::infinity();
		for (int i = 0; i < n; i++)
		{
			if (distance[i] < mindistance && !visited[i])
			{
				mindistance = distance[i];
				nextNode = i;
			}
		}
		visited[nextNode] = true;
		for (int i = 0; i < n; i++)
		{
			if (!visited[i])
				if(mindistance + mCosts[nextNode * n + i] < distance[i])
				{
					distance[i] = mindistance + mCosts[nextNode * n + i];
					pred[i] = nextNode;
				}
		}
		count++;
	}
	if (endNode != startNode) 
	{
		int j = endNode;
		int i = 0;
		path[i++] = j;
		do {
			j = pred[j];
			path[i++] = j;
		} while (j != startNode);
		if (i < n)
			path[i] = -1;
		cost = distance[endNode];
	}
	else
	{
		cost = 0.;
		path[0] = -1;
	}
}