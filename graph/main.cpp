#include<iostream>
#include<vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>

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
class edge2 
{
public:
	int from {};
	int to{};
	int cost {};
	edge2(int from, int to, int cost) :
	from{from}, to{to}, cost{cost} {}
	bool operator<(const edge2 &other) const
	{
		return cost < other.cost;
	}

};

typedef vector<edge2> GRAPH3;

void add_edge(GRAPH3 &graph, int from, int to, int cost)
{
	graph.push_back({from, to, cost});
}

void print_adjaceny_matrix(GRAPH3 &graph)
{
	sort(graph.begin(), graph.end());
	for (auto &e:graph) {
		cout<<"from: "<<e.from<<" to: "<<e.to<<" cost: "<<e.cost<<endl;
	}
}

typedef vector<unordered_set<int>> GRAPH4;

void add_directed_edge(GRAPH4 &graph, int from, int to) {
	graph[from].insert(to);
}

void add_undirected_edge(GRAPH4 &graph, int from, int to) {
	graph[from].insert(to);
	graph[to].insert(from);
}

void print_adjaceny_matrix(GRAPH4 &graph) {
	int nodes = graph.size();
	for (int from = 0; from < nodes; ++from) {
		cout << "Node " << from << " has neighbors: ";
		for (int to = 0; to < nodes; ++to)
			if ( graph[from].find(to) != graph[from].end() )
				cout << to << " ";
		cout << "\n";
	}
}

typedef vector<vector<vector<int>>> GRAPH5;

void add_directed_edge(GRAPH5 &graph, int from, int to, int cost) {
	graph[from][to].push_back(cost);
}

void print_adjaceny_matrix(GRAPH5 &graph) {
	int nodes = graph.size();
	for (int from = 0; from < nodes; ++from) {
		for (int to = 0; to < nodes; ++to) {
			for ( int i = 0; i < graph[from][to].size(); i++)
				cout<<"from: "<<from<<" to: "<<to<<" cost: "<<graph[from][to][i]<<endl;
		}
	}
}
struct Edge2{
	string to;
	int cost;
	bool operator <(const Edge2 &e) const{
		if (to != e.to)
			return to < e.to;
		return cost < e.cost;
	}
};

typedef map<string, multiset<Edge2>> GRAPH6;

void add_directed_edge(GRAPH6 &graph, string from, string to, int cost) {
	graph[from].insert({to,cost});
}

void print_adjaceny_matrix(GRAPH6 &graph) 
{
	for(auto from:graph) {
		cout<<"Flights from "<<from.first<<" :\n";
		for (auto edge:from.second){
			cout<<"\tTo "<<edge.to<<" With Cost "<<edge.cost<<"\n";
		}
	}
}

int main()
{
	GRAPH3 hw1p1;
	add_edge(hw1p1, 1, 2, 4);
	add_edge(hw1p1, 1, 4, 1);
	add_edge(hw1p1, 4, 2, 7);
	add_edge(hw1p1, 2, 3, 8);
	add_edge(hw1p1, 3, 4, 3);
	print_adjaceny_matrix(hw1p1);
	cout<<"\n";
	GRAPH4 hw1p2(4);
	add_directed_edge(hw1p2, 1, 2);
	add_directed_edge(hw1p2, 0, 2);
	add_directed_edge(hw1p2, 2, 3);
	add_directed_edge(hw1p2, 1, 0);
	print_adjaceny_matrix(hw1p2);
	cout<<"\n";
	GRAPH5 hw1p3(5,vector<vector<int>>(5));
	add_directed_edge(hw1p3, 1, 2, 4);
	add_directed_edge(hw1p3, 1, 2, 5);
	add_directed_edge(hw1p3, 1, 2, 0);
	add_directed_edge(hw1p3, 1, 4, 1);
	add_directed_edge(hw1p3, 4, 2, 7);
	add_directed_edge(hw1p3, 2, 3, 8);
	add_directed_edge(hw1p3, 2, 3, 0);
	add_directed_edge(hw1p3, 3, 4, 3);
	print_adjaceny_matrix(hw1p3);
	cout<<"\n";
	GRAPH6 hw2p1;
	add_directed_edge(hw2p1, "California", "Texas", 30);
	add_directed_edge(hw2p1, "California", "Texas", 10);
	add_directed_edge(hw2p1, "Florida", "California", 70);
	add_directed_edge(hw2p1, "California", "Florida", 75);
	add_directed_edge(hw2p1, "California", "Texas", 30);
	add_directed_edge(hw2p1, "California", "Texas", 30);
	print_adjaceny_matrix(hw2p1);
    return 0;
}


