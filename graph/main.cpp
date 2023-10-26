#include<iostream>
#include<vector>
using namespace std;

typedef vector<vector<int>> GRAPH;

void add_directed_edge(GRAPH &graph, int from, int to)
{
    graph[from][to] += 1;
}

void add_undirected_edge(GRAPH &graph, int from, int to)
{
    graph[from][to] += 1;
    graph[to][from] += 1;
}

void add_directed_edge(GRAPH &graph, int from, int to, int cost)
{
    graph[from][to] = cost;
}

void add_undirected_edge(GRAPH &graph, int from, int to, int cost)
{
    graph[from][to] = cost;
    graph[to][from] = cost;
}

void add_directed_edge2(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
}

void add_undirected_edge2(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
	graph[to].push_back(from);
}

struct edge {
	int to;
	int cost;
};

typedef vector<vector<edge>> GRAPH2;

void add_directed_edge(GRAPH2 &graph, int from, int to, int cost) {
	graph[from].push_back({to, cost});
}

void add_undirected_edge(GRAPH2 &graph, int from, int to, int cost) {
	graph[from].push_back({to, cost});
	graph[to].push_back({from, cost});
}

void print_adjaceny_matrix(GRAPH &graph)
{
    int nodes = graph.size();
    for( int from = 0; from < nodes; from++) {
        for( int to = 0; to < nodes; to++) {
            if (graph[from][to] > 0)  
                cout << "From " << from << " to " << to
				     << " there are " << graph[from][to] << " edges\n";
        }
    }
}

void print_adjaceny_matrix2(GRAPH &graph) {
	int nodes = graph.size();
	for (int from = 0; from < nodes; ++from) {
		cout << "Node " << from << " has neighbors: ";
		for (int to = 0; to < (int) graph[from].size(); ++to)
			cout << graph[from][to] << " ";
		cout << "\n";
	}
}

void print_adjaceny_matrix(GRAPH2 &graph) {
	int nodes = graph.size();
	for (int from = 0; from < nodes; ++from) {
		cout << "Node " << from << " has neighbors: ";
		for (int edge = 0; edge < (int) graph[from].size(); ++edge)
			cout << "(to "<<graph[from][edge].to
			     << " cost "<<graph[from][edge].cost<<") ";
		cout << "\n";
	}
}

int main()
{


    return 0;
}


