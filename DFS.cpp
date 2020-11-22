#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

typedef enum { WHITE, GRAY, BLACK } VStatus; //vertex status. UNDISCOVERED--WHITE, DISCOVERED--GRAY, VISITED--BALCK
template <class Tv>
struct Vertex {
	Tv data;
	VStatus color;
	int dTime, fTime; //time label
	int parent;
	Vertex(Tv const& d) :data(d), status(WHITE), dTime(-1), fTime(-1), parent(-1) {}
};

typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType; //edge type
template <class Te> 
struct Edge {
	Te data;
	//int weight;
	EType type;
	Edge(Te const& d) : data(d), type(UNDETERMINED) {}
	//Edge(Te const& d, int w) : data(d), type(UNDETERMINED), weight(w) {}
};

template <class Tv, class Te>
class Graph {
private:
	void DFS_visit() {

	}
public:
	void dfs() {

	}
};

template <class Tv, class Te>
class Graph_AdjList :public Graph<Tv, Te> { //adjacency-list implementation
private:
	vector< Vertex<Tv> > V; //vertices
	

};

int main() {

	return 0;
}