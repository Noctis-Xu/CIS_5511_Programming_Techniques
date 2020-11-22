/*index starts from 1*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;
int counterV_dfs = 0; //count vertex-access in dfs procedure
int counterE_dfs = 0; //count edge-access in dfs procedure
int counterV_trans = 0; // count vertex-access in transpose procedure
int counterE_trans = 0; //count edge-access in transpose procedure


/*The code commented leaves for extension*/
//typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType; //edge type
//template <class Te>
struct EdgeNode { //store edges' data. Edge(u,v) means u to v.
	//Te data;
	//EType type;
	int weight;
	int verIndex; //v's index
	EdgeNode* next; //other edges leaves from u to v
	EdgeNode(int _verIndex = -1) : verIndex(_verIndex), weight(1), next(NULL) {} //initialize with verIndex specified
	//EdgeNode(Te const& d, int w) : data(d), type(UNDETERMINED), weight(w) {}
};

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

//template <class Tv, class Te>
class Graph_AdjList {
private:
	void DFS_visit(VertexNode& u, int& time) { //for the connected domain
		time++;
		u.dTime = time;
		u.color = GRAY;
		cout << u.verIndex << ' ';
		counterV_dfs++;
		for (EdgeNode* v = u.first; v; v = v->next) {
			counterE_dfs++;
			if (V[v->verIndex].color == WHITE) {
				DFS_visit(V[v->verIndex], time);
			}
		}
		u.color = BLACK;
		time++;
		u.fTime = time;

	}
public:
	int vNumber;
	vector< VertexNode > V; //vertices V[1..|V|], V[i] is u in GT, like d[] in the P592 of the textbook of CLRS_E3, 
	///*Vertex operations*/
	//void insertV(int u) { //insert a vertex
	//}
	///*Edge operations*/
	//bool insertE(int u, int v) { //insert an edge from u to v. Here u and v denote the index of a vertex
	//	//we assume u and v exist, which means not greater than |V|
	//	EdgeNode* pParent;
	//	for (EdgeNode* p = V[u].first; p; p = p->next) {
	//		pParent = p;
	//		if (p->verIndex = v) {
	//			return false; //the edge has already been there.
	//		}
	//	}
	//	EdgeNode* vNew = new EdgeNode;
	//	vNew->verIndex = v;
	//	pParent->next = vNew;
	//}

	/*Algorithms*/
	void dfs() { //for the entire graph, including unconnected region. The algorithm is similar to that in P604 of the textbook
		/*for (int i = 1; i <= vNumber; i++) {
			V[i].color = WHITE;
			counterV_dfs++;
		}*/
		int time = 0;
		for (int i = 1; i <= vNumber; i++) {
			if (V[i].color == WHITE) {
				cout << i << ": ";
				DFS_visit(V[i], time);
				cout << endl;
			}
		}
	}
	//Graph_AdjList(GT) {}
	Graph_AdjList tranpose() { //construct the transpose of G. Traverse the adjacency list, so the time is O(V+E). 
		//GT: G's transpose, V[i]£ºu in G, v: u's adjacent vertices in G, uT: u in GT, vT: u's adjacent vertices in GT
		Graph_AdjList GT;
		GT.vNumber = vNumber;
		vector< EdgeNode* > vT_last(vNumber + 1); //point to the last element of Adj[uT]
		for (int i = 1; i <= vNumber; i++) { //Copy V[i].data to GT.V[i].data
			VertexNode uT(i); //vertices in GT
			GT.V.push_back(uT);
			vT_last[i] = NULL;
			counterV_trans++;
		}
		for (int i = 1; i <= vNumber; i++) { //Copy G.(u,v).data to GT.(v,u).data, for example, weight, data carried by the edge.
			for (EdgeNode* v = V[i].first; v; v = v->next) { //traverse each edge
				counterE_trans++;
				EdgeNode* vT = new EdgeNode(i);
				if (!vT_last[v->verIndex]) {
					GT.V[v->verIndex].first = vT;
					vT_last[v->verIndex] = vT;
				}
				else {
					vT_last[v->verIndex]->next = vT;
					vT_last[v->verIndex] = vT;
				}
			}
		}
		return GT;
	}
	void printGraph() { //print the adjacency list of the graph
		for (int i = 1; i <= vNumber; i++) {
			cout << i << ": ";
			for (EdgeNode* v = V[i].first; v; v = v->next) {
				cout << v->verIndex << ' ';
			}
			cout << endl;
		}
	}
	Graph_AdjList(vector< vector<int> > adjList) { //adjList's first elements should be organized in increasing order
		vNumber = adjList.size();
		VertexNode temp(-1);
		V.push_back(temp); //V[1..|V|], V[0] is ignored
		for (int i = 0; i < adjList.size(); i++) {
			int k = adjList[i][0]; //k starts from 1 to |V|
			VertexNode u(k);
			V.push_back(u);
			if (adjList[i].size() == 1) //no edge leaves u
				break;
			else {
				EdgeNode* v1 = new EdgeNode(adjList[i][1]); //the first edge leaves u
				V[k].first = v1;
				if (adjList[i].size() > 2) { //more than one edge leaves u
					EdgeNode* p = V[k].first;
					for (int j = 2; j < adjList[i].size(); j++) {
						EdgeNode* v = new EdgeNode(adjList[i][j]);
						p->next = v;
						p = v;
					}
				}
			}
		}
	}
	Graph_AdjList() {
		vNumber = 0;
		VertexNode temp(-1);
		V.push_back(temp); //V[1..|V|], V[0] is ignored
	}
	//Graph_AdjList(Graph_AdjList &G) { //copy constructor
	//	vNumber = G.vNumber;
	//	VertexNode temp(-1);
	//	V.push_back(temp);
	//	for (int i = 1; i <= vNumber; i++) {
	//		V[i] = G.V[i]; //copy vertices
	//		for (EdgeNode* v = G.V[i].first; v; v = v->next) { //copy edges
	//			EdgeNode* vN = new EdgeNode;
	//			...
	//		}
	//	}
	//}
	//~Graph_AdjList() {}
};

int main() {
	vector< vector<int> > adjList = {
		{1,2,4}, //vertex 1 and its adjacent vertices. Here the edges are (1,2) and (1,4).
		{2,5},
		{3,6,5},
		{4,2},
		{5,4},
		{6,6}
	};

	counterV_dfs = 0; 
	counterE_dfs = 0; 
	counterV_trans = 0; 
	counterE_trans = 0; 
	Graph_AdjList G(adjList);
	Graph_AdjList GT = G.tranpose();
	GT.dfs();
	cout << "vertex-access in dfs procedure: " << counterV_dfs << endl;
	cout << "edge-access in dfs procedure: " << counterE_dfs << endl;
	cout << "vertex-access in transpose procedure: " << counterV_trans << endl;
	cout << "edge-access in transpose procedure: " << counterE_trans << endl;

	return 0;
}