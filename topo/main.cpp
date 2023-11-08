#include <iostream>
#include<vector>
#include<queue>
using namespace std;

typedef vector<vector<int>> GRAPH;


void add_directed_edge(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
}

void add_directed_edge(GRAPH &graph, vector<vector<int>> &nodes_edge) {
	for(auto &item:nodes_edge) {
		int from = item[0];
		int to = item[1];
		add_directed_edge(graph, from, to);
	}
}

void print_adjaceny_matrix(GRAPH &graph) {
	int nodes = graph.size();
	for (int from = 0; from < nodes; ++from) {
		cout << "Node " << from << " has neighbors: ";
		for (int to = 0; to < (int) graph[from].size(); ++to)
			cout << graph[from][to] << " ";
		cout << "\n";
	}
}

vector<int> toposort(const GRAPH &adjlist)
{
    int sz = adjlist.size();
    vector<int> indegree(sz, 0);
    for (int i = 0; i < sz; i++)
        for (int j : adjlist[i])
            indegree[j]++;

    queue<int> ready;

    for (int i = 0; i < sz; i++)
        if (!indegree[i])
            ready.push(i);

    vector<int> ordering;
    while (!ready.empty()) {
        int i = ready.front();
        ready.pop();
        ordering.push_back(i);

        for (int j : adjlist[i])
            if(--indegree[j] == 0)
                ready.push(j);
    }

    if (ordering.size() != adjlist.size() )
        ordering.clear();

    return ordering;
}

int main() {
	freopen("../data.txt", "rt", stdin);
	int cases;
	cin >> cases;

	while (cases--) {
		int nodes, edges;
		cin >> nodes >> edges;

		GRAPH graph(nodes);

		for (int e = 0; e < edges; ++e) {
			int from, to;
			cin >> from >> to;
			add_directed_edge(graph, from, to);
		}
        print_adjaceny_matrix(graph);
        cout<<endl; 
		vector<int> ordering = toposort(graph);

		if (ordering.empty())
			cout << "There is a cycle\n";
		else {
			for (int node : ordering)
				cout << node << " ";
			cout << "\n";
		}
	}
	return 0;
}




