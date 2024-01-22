#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;


template<class T>
void print(vector<T> &v)
{
    for (int i = 0; i < (int) v.size(); ++i) {
		cout << v[i] << " ";
	}
    cout<<endl;
}

template<class T>
void print(vector<vector<T>> &vec){
	for(auto &v : vec)
		print(v);
}

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

vector<GRAPH> getGraphs(const string &path)
{
	freopen(path.c_str(), "rt", stdin);
	int cases;
	cin >> cases;
	vector<GRAPH> graphs;
	while (cases--) {
		int nodes, edges;
		cin >> nodes >> edges;

		GRAPH graph(nodes);

		for (int e = 0; e < edges; ++e) {
			int from, to;
			cin >> from >> to;
			add_directed_edge(graph, from, to);
		}
		graphs.push_back(graph);
	}
	return graphs;
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
        ordering.clear(); //There are cycles

    return ordering;
}

// https://leetcode.com/problems/course-schedule/
class Solution207 {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        GRAPH adjlist(numCourses);

		for (auto item : prerequisites) 
			adjlist[item[1]].push_back(item[0]);
		
		
		vector<int> indegree(numCourses, 0);
		for (int i = 0; i < numCourses; i++)
			for (int j : adjlist[i])
				indegree[j]++;

		queue<int> ready;

		for (int i = 0; i < numCourses; i++)
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

		return ordering.size() == numCourses;
    }
};

// hw1 p1
vector<int> lexicographic(const GRAPH &adjlist)
{
	int sz = adjlist.size();
	vector<int> indegree(sz, 0);
	for (int i = 0; i < sz; i++)
		for(int j : adjlist[i])
			indegree[j]++;

	priority_queue<int, std::vector<int>, std::greater<int> > ready;

	for (int i = 0; i < sz; i++)
		if (!indegree[i])
			ready.push(i);
	
	vector<int> ordering;
	while (!ready.empty()) {
		int i = ready.top();
		ready.pop();

		ordering.push_back(i);

		for (int j : adjlist[i])
			if (--indegree[j] == 0)
				ready.push(j);
	}

	if (ordering.size() != adjlist.size())
		ordering.clear();

	return ordering;
}

// hw1 p2
// https://leetcode.com/problems/parallel-courses/ premium
int minimumSemesters(int n, vector<vector<int>>& relations)
{
	GRAPH adjlist(n);

	for (auto edge: relations){
		int to = edge[0] - 1;
		int from = edge[1] - 1;
		add_directed_edge(adjlist, from, to);
	}

	int sz = adjlist.size();
    vector<int> indegree(sz, 0);
    for (int i = 0; i < sz; i++)
        for (int j : adjlist[i])
            indegree[j]++;

    queue<int> ready;

    for (int i = 0; i < sz; i++)
        if (!indegree[i])
            ready.push(i);

	int level = 0, found_nodes = 0;

    while (!ready.empty()) {
		int level_sz = ready.size();
		
		while ( level_sz--){
			int i = ready.front();
			ready.pop();
			found_nodes++;

			for (int j : adjlist[i])
				if(--indegree[j] == 0)
					ready.push(j);
		}
		level++;
    }

    if (found_nodes != sz)
        return -1;
	
	return level;
}

// https://leetcode.com/problems/sequence-reconstruction/ premium
bool sequenceReconstruction(vector<int> &org, vector<vector<int>> &seqs) 
{
	GRAPH graph(org.size() );

	for (auto seq : seqs) {
		for (int i = 0; i < (int) seq.size() - 1; i++) {
			if (seq[i] > org.size() || seq[i + 1] > org.size() )
				return false;
			add_directed_edge(graph, seq[i] - 1, seq[i + 1] - 1);
		}
	}

	auto ordering = toposort(graph);

	if (ordering.size() != org.size())
		return false;
	
	for (int i = 0; i < ordering.size(); i++)
		if (ordering[i] != org[i] - 1)
			return false;

	return true;
}

// https://leetcode.com/problems/minimum-height-trees/

// https://leetcode.com/problems/longest-increasing-path-in-a-matrix/

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

	cout<<endl; 
	cout<<endl; 

	// hw1 p1 
	vector<GRAPH> hw1p1 = getGraphs("../hw1p1.txt");
	for (auto g : hw1p1) {
		auto ordering = lexicographic(g);
		if (ordering.empty())
			cout << "There is a cycle\n";
		else 
			print(ordering);
	}
	// hw2 p1
	vector<int> org = {1,2,3};
	vector<vector<int>> seqs = {{1,2},{1,3}};
	cout<<sequenceReconstruction(org, seqs)<<endl; 
	seqs = {{1,2}};
	cout<<sequenceReconstruction(org, seqs)<<endl; 
	seqs = {{1,2},{1,3}, {2,3}};
	cout<<sequenceReconstruction(org, seqs)<<endl; 
	org = {4, 1, 5, 2, 6, 3};
	seqs = {{5,2,6,3}, {4,1,5,2}};
	cout<<sequenceReconstruction(org, seqs)<<endl; 
	return 0;
}




