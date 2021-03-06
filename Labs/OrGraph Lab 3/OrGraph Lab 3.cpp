#include <iostream>
#include <vector>
#include <fstream>
#include "graph.h"
#include <queue>
#include <list>

using namespace std;

const int INF = 1000000000;

int main()
{
	ifstream fin("input.txt");
	if (!fin) return 1;
	size_t N;
	int a, b;
	fin >> N >> a >> b;
	--a, --b;

	if ((a > N - 1) || (b > N - 1)) return 1;

	Graph* graph = graph_create(N);

	for (size_t i = 0; !fin.eof(); i++)
	{
		int x, y, weight;
		fin >> x >> y >> weight;
		--x, --y;

		if ((x > N) || (y > N)) return 1;

		add_edge(graph, x, y);
		set_weight(graph, x, y, weight);
	}

	vector <int> dist(N);
	vector <bool> visited(N);
	queue <Data> q;

	q.push(a);
	visited[a] = true;

	while (!q.empty())
	{
		int temp = q.front();
		q.pop();

		int count = 0;

		Iterator* v = iterator_create(graph, temp);

		while (is_neighbors(v))
		{
			if (!visited[get_vertex(v)])
			{
				visited[get_vertex(v)] = true;
				q.push(get_vertex(v));
				dist[get_vertex(v)] += dist[temp] + iterator_weight(v);
			}
			++count;
			next_iterator(v);
		}
	}

	if (!visited[b])
	{
		cout << "Finish vertex not visited." << endl;
	}
	else
	{
		cout << "Length of short path from " << a + 1 << " to " << b + 1 << " is: " << dist[b] << endl;
	}
	fin.close();
	return 0;
}