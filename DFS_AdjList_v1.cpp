/*index starts from 0*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

/*The code commented leaves for extension*/
typedef enum { WHITE, GRAY, BLACK } VStatus; //vertex status. UNDISCOVERED--WHITE, DISCOVERED--GRAY, VISITED--BALCK
//template <class Tv> //for extension
struct VertexNode { //Vertex u
	//Tv data;
	int verIndex; //vertex index starting from 0, serves as a key for locating
	VStatus color;
	int dTime, fTime; //time label
	EdgeNode* first; //the first node in Adj[u]
	VertexNode(int _verIndex = -1) :verIndex(_verIndex), color(WHITE), dTime(-1), fTime(-1), first(NULL) {}
	//int parentLabel;
	//VertexNode(Tv const& d) :verIndex(-1), data(d), color(WHITE), dTime(-1), fTime(-1), parentLabel(-1), first(NULL) {}
};

//typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType; //edge type
//template <class Te>
struct EdgeNode { //store edges' data. Edge(u,v) means u to v.
	//Te data;
	//EType type;
	int weight;
	int verIndex; //v's index
	EdgeNode* next; //other edges leaves from u to v
	//EdgeNode() : verIndex(-1), next(NULL) {} //initialize
	EdgeNode() : verIndex(-1), weight(1), next(NULL) {} //initialize
	//EdgeNode(Te const& d, int w) : data(d), type(UNDETERMINED), weight(w) {}
};

//template <class Tv, class Te>
class Graph_AdjList {
private:
	void DFS_visit(VertexNode& u, int& time) { //for the connected domain
		time++;
		u.dTime = time;
		u.color = GRAY;
		for (EdgeNode* v = u.first; v; v = v->next) {
			if (V[v->verIndex].color == WHITE) {
				DFS_visit(V[v->verIndex], time);
			}
		}
		u.color = BLACK;
		//cout << u.
		time++;
		u.fTime = time;

	}
public:
	//int vNumber = 0;
	vector< VertexNode > V; //vertices V[0..|V|-1], V[i] is u in GT, like d[] in the P592 of the textbook of CLRS_E3, 
	//Vertex operations
	void insertV(int u) { //insert a vertex
		V.push_back(u);
	}

	//Edge operations
	bool insertE(int u, int v) { //insert an edge from u to v. Here u and v denote the index of a vertex
		//we assume u and v exist, which means not greater than |V|
		EdgeNode* pParent;
		for (EdgeNode* p = V[u].first; p; p = p->next) {
			pParent = p;
			if (p->verIndex = v) {
				return false; //the edge has already been there.
			}
		}
		EdgeNode* vNew = new EdgeNode;
		vNew->verIndex = v;
		pParent->next = vNew;
	}

	//Algorithms
	void dfs() { //for the entire graph, including unconnected region. The algorithm is similar to that in P604 of the textbook
		for (int i = 0; i < V.size(); i++) {
			V[i].color = WHITE;
		}
		int time = 0;
		for (int i = 0; i < V.size(); i++) {
			if (V[i].color = WHITE)
				DFS_visit(V[i], time);
		}
	}
	//Graph_AdjList(GT) {}
	Graph_AdjList GTranpose() { //construct the transpose of G. Traverse the adjacency list, so time is O(V+E). 
		//GT: G's transpose, V[i]£ºu in G, v: u's adjacent vertices in G, uT: u in GT, vT: u's adjacent vertices in GT
		Graph_AdjList GT;
		VertexNode uT; //vertex in GT
		vector< EdgeNode* > vT_last(V.size()); //point to the last element of Adj[uT]
		for (int i = 0; i < V.size(); i++) {
			//Copy V[i].data to GT.V[i].data
			uT.verIndex = i;
			GT.V.insert(GT.V.begin() + i, uT);
			vT_last[i] = GT.V[i].first;
		}
		VertexNode vT;
		for (int i = 0; i < V.size(); i++) { //traverse each vertex
			for (EdgeNode* v = V[i].first; v; v = v->next) { //traverse each edge
				//Copy G.(u,v).data to GT.(v,u).data, for example, weight, data carried by edge.
				EdgeNode* vT = new EdgeNode;
				vT->verIndex = i;
				vT_last[v->verIndex]->next = vT;
				vT_last[v->verIndex] = vT;
			}
		}
		return GT;
	}
	/*~Graph_AdjList() {

	}*/
};

int main() {
	Graph_AdjList G;
	/*VertexNode u;
	for (int i = 0; i < 5; i++) {
		u.verIndex = i;
		G.V.insert(G.V.begin() + i, u);
	}*/
	//vector<int> adjList = {1,2,3,4,5};
	for (int i = 0; i < 5; i++) {
		G.insertV(i);
	}
	



	return 0;
}