#include <iostream>
#include <limits>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>

#include "json.h"
#include "fdijkstra.h"

using namespace std;

char* getCmdOption(char ** begin, char ** end, const string & option)
{
    char ** itr = find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const string& option)
{
    return find(begin, end, option) != end;
}

string usage()
{
	return "Usage : PROGRAMNAME -i startNode -o endNode -m metric\nMetric can be distance_km or co2_g";
}

int main(int argc, char * argv[])
{
    if(!cmdOptionExists(argv, argv+argc, "-i") || !cmdOptionExists(argv, argv+argc, "-o") || !cmdOptionExists(argv, argv+argc, "-m"))
    {
		cout << usage();
		return 0;
    }

    char * input = getCmdOption(argv, argv + argc, "-i");
	int startNode = 0;
    if (input)
    {
        startNode = atoi(input);
    }
    char * output = getCmdOption(argv, argv + argc, "-o");
	int endNode = 0;
    if (output)
    {
        endNode = atoi(output);
    }
    char * metric = getCmdOption(argv, argv + argc, "-m");

	string line;
	ifstream myFile ("graph3.json");
	myFile.seekg(0, ios_base::end);
	streampos pos = myFile.tellg();
	if (myFile.is_open())
	{
		// get length of file:
		myFile.seekg (0, myFile.end);
		int length = myFile.tellg();
		myFile.seekg (0, myFile.beg);

		// allocate memory:
		char * buffer = new char [length];

		// read data as a block:
		myFile.read (buffer,length);

		myFile.close();

		json_value * jsonValue = json_parse (buffer, length);

		delete[] buffer;
		
		if (jsonValue->type != json_array)
		{
			cout << "Bad file structure";
			json_value_free (jsonValue);
			return 0;
		}
		length = jsonValue->u.array.length;
		vector<double> G(length * length);
		fill(G.begin(), G.end(), 0.);
		for (int i = 0; i < length; i++)
		{
			json_value * row = jsonValue->u.array.values[i];
			if (row->type != json_array)
			{
				cout << "Bad file structure";
				json_value_free (jsonValue);
				return 0;
			}
			for (unsigned int j = 0; j < row->u.array.length; j++)
			{
				json_value * object = row->u.array.values[j];
				if (object->type != json_object)
				{
					cout << "Bad file structure";
					json_value_free (jsonValue);
					return 0;
				}
				int endNode = -1;
				double mass = -1;
				for (unsigned int k = 0; k < object->u.object.length; k++)
				{
					json_object_entry value = object->u.object.values[k];
					if (!strcmp(value.name, metric))
					{
						json_value * metric = value.value;
						if ((metric->type != json_double) && (metric->type != json_integer))
						{
							cout << "Bad file structure";
							json_value_free (jsonValue);
							return 0;
						}
						if (metric->type == json_double)
							mass = metric->u.dbl;
						if (metric->type == json_integer)
							mass = metric->u.integer;
					}
					if (!strcmp(value.name, "vertex_id"))
					{
						json_value * vertex = value.value;
						if (vertex->type != json_integer)
						{
							cout << "Bad file structure";
							json_value_free (jsonValue);
							return 0;
						}
						endNode = vertex->u.integer;
					}
				}
				if (endNode < 0 || mass < 0)
				{
					cout << "Bad file structure";
					json_value_free (jsonValue);
					return 0;
				}
				G[i * length + endNode] = mass;
			}
		}
		json_value_free (jsonValue);
		vector<int> path(length);
		double cost;
		dijkstra(G, length, startNode, endNode, path, cost);
		cout << metric << " from node " << startNode << " to node " << endNode << " = " << cost << endl;
		cout << "Path = ";
		for (int i = 0; path[i]>=0; ++i)
		{
			if (i) cout <<  " <- ";
			cout << path[i];
		}
		cout << endl;
		return 0;
	}

	else 
	{
		cout << "Unable to open file"; 
		return 0;
	}
}
