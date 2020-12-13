#include "fdijkstra.h"

#include <iostream>
#include <limits>

using namespace std;

bool testNull()
{
	vector<double> G(2 * 2);
	fill(G.begin(), G.end(), 0.);
	G[0 * 2 + 1] = 1.;
	G[1 * 2 + 0] = 1.;
	vector <int> path(2);
	double cost;
	dijkstra(G, 2, 1, 1, path, cost);
	return cost == 0 && path[0] == -1;
}

bool testShorter()
{
	vector<double> G(4 * 4);
	fill(G.begin(), G.end(), 0.);
	G[0 * 4 + 1] = 3.;
	G[1 * 4 + 0] = 3.;
	G[0 * 4 + 2] = 1.;
	G[2 * 4 + 0] = 1.;
	G[1 * 4 + 3] = 1.;
	G[3 * 4 + 1] = 1.;
	G[2 * 4 + 3] = 1.;
	G[3 * 4 + 2] = 1.;
	vector <int> path(4);
	double cost;
	dijkstra(G, 4, 0, 3, path, cost);
	return path[0] == 3 && path[1] == 2 && path[2] == 0 && path[3] == -1;
}

bool testUnaccessible()
{
	vector<double> G(4 * 4);
	fill(G.begin(), G.end(), 0.);
	G[0 * 4 + 1] = 3.;
	G[1 * 4 + 0] = 3.;
	G[0 * 4 + 2] = 1.;
	G[2 * 4 + 0] = 1.;
	vector <int> path(4);
	double cost;
	dijkstra(G, 4, 0, 3, path, cost);
	return cost == numeric_limits<double>::infinity();
}

bool testAllNodes()
{
	vector<double> G(4 * 4);
	fill(G.begin(), G.end(), 0.);
	G[0 * 4 + 1] = 3.;
	G[1 * 4 + 0] = 3.;
	G[1 * 4 + 2] = 1.;
	G[2 * 4 + 1] = 1.;
	G[2 * 4 + 3] = 1.;
	G[3 * 4 + 2] = 1.;
	vector <int> path(4);
	double cost;
	dijkstra(G, 4, 0, 3, path, cost);
	return path[0] == 3 && path[1] == 2 && path[2] == 1 && path[3] == 0;
}

int main()
{
	if (testNull())
	{
		cout << "testNull SUCCESS" << endl;
	}
	else
	{
		cout << "testNull FAIL" << endl;
	}
	if (testShorter())
	{
		cout << "testShorter SUCCESS" << endl;
	}
	else
	{
		cout << "testShorter FAIL" << endl;
	}
	if (testUnaccessible())
	{
		cout << "testUnaccessible SUCCESS" << endl;
	}
	else
	{
		cout << "testUnaccessible FAIL" << endl;
	}
	if (testAllNodes())
	{
		cout << "testAllNodes SUCCESS" << endl;
	}
	else
	{
		cout << "testAllNodes FAIL" << endl;
	}
	return 0;
}