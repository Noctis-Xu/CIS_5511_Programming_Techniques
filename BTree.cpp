#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h> //rand()
//#define DEBUG

using namespace std;

template<typename T>
class Vector {
	T* _elem; //data, storing elements
	int _size; //valid elements,[0.._size)
	int _capacity; //how many elements can be stored at most. [0.._capacity)
public:
	Vector(int c) :_capacity(c), _size(0) { _elem = new T[_capacity]; } //specified _capacity
	Vector(int c, T k) :_capacity(c), _size(0) { //specified _capacity and value
		_elem = new T[_capacity];
		for (int i = 0; i < _capacity; _elem[i++] = k);
	}
	~Vector() { delete[] _elem; }
	T search(const T& k) { //linearly search k in a sorted sequence [0,_size), return the rank of the last element not greater than k.
		for (int r = 0; r < _size; r++) {
			if (_elem[r] > k) return r - 1;
		}
		return _size - 1;
	}
	int insert(int rank, const T& k) { //Do not check overflow that _size = _capacity, since it will be fixed by overflowSolve()
		for (int i = _size; rank < i; i--)_elem[i] = _elem[i - 1];
		_elem[rank] = k;
		_size++;
		return rank;
	}
	T remove(int rank) {
		T k = _elem[rank];
		for (int i = rank; i < _size - 1; i++) _elem[i] = _elem[i + 1];
		_size--;
		return k;
	}
	int size() { return _size; }
	T& operator[] (int r) //override []. assert that 0 <= r < _size
	{
		return _elem[r];
	}
};


class BTNode {
public:
	//int _m; 
	BTNode* parent = NULL;
	Vector<int> keys;
	Vector<BTNode*> children; //keys[0]'s left child corresponds to children[0], right child to children[1].
	BTNode(int m) :keys(m), children(m + 1) { } //order-m. keys[0..m-1], when keys[m-1] is taken, it is the overflow case, which will be solved by overflowSolve(). Every leaf node has NULL as their external nodes/children.
};


class BTree {
protected:
	BTNode* _root;
	int _m; //order-m, it at least is 3.
	void overflowSolve(BTNode* x) {
		if (x->keys.size() < _m) return;
		else { //size=_m
			int mid = _m / 2;
			int k_mid = x->keys[mid]; //k will be lifted
			/*splitting*/
			/*one node splits to two node, the first splited node is the original node x*/
			BTNode* y = new BTNode(_m); //the second splited node y
			int j = _m - mid - 2;
			for (int i = 0; i <= j; i++) { //move x[mid+1..m-1] to y[0..j]
				y->keys.insert(i, x->keys.remove(mid + 1));//note that all the elements after x->key[mid] will automatically move forward.
				/*fix the relationship between the splited nodes and their children*/
				y->children.insert(i, x->children.remove(mid + 1));
				if (y->children[i]) y->children[i]->parent = y;
			}
			y->children.insert(j + 1, x->children.remove(_m)); //move x->children[m] to y->children[j+1]
			if (y->children[j + 1]) y->children[j + 1]->parent = y;

			/*fix the relationship between the splited nodes and their parent*/
			if (x == _root) { //if x is the root
				_root = new BTNode(_m);
				x->parent = _root;
				_root->children.insert(0, x);
			}
			int r = x->parent->keys.search(k_mid);
			x->parent->keys.insert(r + 1, x->keys.remove(mid));
			x->parent->children.insert(r + 2, y);
			y->parent = x->parent;
			overflowSolve(x->parent); //overflow may spread upward
		}
	}
	void underflowSolve(BTNode* x) {
		//note that x->keys[] may be empty, e.g. 2-3 B-tree or the root
		if ((_m - 1) / 2 <= x->keys.size()) return;
		BTNode* p = x->parent;
		if (!p) { //if x is the root
			if (!x->keys.size() && x->children[0]) { //the root x is empty
				_root = x->children[0];
				_root->parent = NULL;
				delete x;
			}
			return;
		}
		int r = 0;
		while (p->children[r] != x) r++; //locate the node x in p
		//case 1: if x has a left sibling, then borrow from it
		if (0 < r) {
			BTNode* left = p->children[r - 1];
			if ((_m - 1) / 2 < left->keys.size()) { //if the left sibling is big to borrow
				x->keys.insert(0, p->keys[r - 1]); //x's parent p acts as intermediary
				p->keys[r - 1] = left->keys.remove(left->keys.size() - 1);
				x->children.insert(0, left->children.remove(left->children.size() - 1)); //fix their children. The left sibling's right most child transfers to x's left most child.
				if (x->children[0]) x->children[0]->parent = x; //x->children[0] may be an external node NULL
				return;
			}
		} //x's left sibling is small or nonexistent, so turn to case 2
		//case 2: if x has a right sibling, then borrow from it. Case 2 is similar to case 1
		if (r < p->children.size() - 1) {
			BTNode* right = p->children[r + 1];
			if ((_m - 1) / 2 < right->keys.size()) {
				x->keys.insert(x->keys.size(), p->keys[r]);
				p->keys[r] = right->keys.remove(0);
				x->children.insert(x->children.size(), right->children.remove(0));
				if (x->children[x->children.size() - 1])x->children[x->children.size() - 1]->parent = x;
				return;
			}
		}
		//case 3: merge x with its left sibling
		if (r < 0) {
			BTNode* left = p->children[r - 1];
			left->keys.insert(left->keys.size(), p->keys.remove(r - 1));
			p->children.remove(r);
			left->children.insert(left->children.size(), x->children[0]); //note that x->keys[] may be empty
			if (left->children[left->children.size() - 1]) //its child may be an external node NULL
				left->children[left->children.size() - 1]->parent = left;
			for (int i = 0; i < x->keys.size(); i++) { //note that x->keys[] may be empty
				left->keys.insert(left->keys.size(), x->keys[i]); //for efficiency, copy and paste x->keys rather than remove, since x will be deleted at last anyway.
				left->children.insert(left->children.size(), x->children[i + 1]);
				if (left->children[left->children.size() - 1])
					left->children[left->children.size() - 1]->parent = left;
			}
			delete x;
		}//x's left sibling is nonexistent, so turn to case 4
		//case 4: merge x with its right sibling. Case 4 is similar to case 3
		else {
			BTNode* right = p->children[r + 1];
			right->keys.insert(0, p->keys.remove(r));
			p->children.remove(r);
			right->children.insert(0, x->children[x->children.size() - 1]);
			if (right->children[0])
				right->children[0]->parent = right;
			for (int i = x->keys.size() - 1; i >= 0; i--) {
				right->keys.insert(0, x->keys[i]);
				right->children.insert(0, x->children[i]);
				if (right->children[0])
					right->children[0]->parent = right;
			}
			delete x;
		}
		underflowSolve(p);
	}
	void treePrint(BTNode* x, int height = 0) { //reverse inorder tree walk
		if (x->keys.size() != 0) {
			int height_next = height + 1;
			int mid = (x->children.size() + 1) / 2;
			for (int i = x->children.size() - 1; x->children[i] && i >= mid; i--) { //note while x is leaf, x->children is NULL.
				treePrint(x->children[i], height_next);
			}
			/*print*/
			for (int h = height; h; h--)
				cout << '\t';
			for (int i = 0; i < x->keys.size() - 1; i++) {
				cout << x->keys[i] << ',';
			}
			cout << x->keys[x->keys.size() - 1] << endl;

			for (int i = mid - 1; x->children[i] && i >= 0; i--) {
				treePrint(x->children[i], height_next);
			}
		}
	}
public:
	BTree(int m) : _m(m) { _root = new BTNode(_m); _root->children.insert(0, NULL); }
	BTNode* search(const int& k) {
		BTNode* v = _root;
		while (v) {
			int r = v->keys.search(k); //since every node is valid, r is in [0..m-2]
			if (0 <= r && v->keys[r] == k) return v; //successful
			v = v->children[r + 1];
		}
		return NULL; //failed
	}
	bool insert(const int& k) {
		BTNode* v = _root;
		BTNode* p = NULL;
		int p_r = -1;
		while (v) {
			int r = v->keys.search(k); //since every node is valid, r is in [0..m-2]
			if (0 <= r && v->keys[r] == k) break; //successful
			p = v; p_r = r;
			v = v->children[r + 1]; //DISK I/O
		}
		if (v) return false; //duplicated keys
		else { //a new key
			p->keys.insert(p_r + 1, k); //here k may be at keys[m-1], which is the overflow case
			p->children.insert(p_r + 2, NULL); //external nodes
			overflowSolve(p);
			return true;
		}
	}
	bool remove(const int& k) {
		BTNode* v = _root;
		int r;
		while (v) {
			r = v->keys.search(k); //since every node is valid, r is in [0..m-2]
			if (0 <= r && v->keys[r] == k) break; //successful
			v = v->children[r + 1]; //DISK I/O
		}
		if (!v) return false; //key is not found
		else { //key exists
			if (v->children[0]) { //if v is not a leaf
				BTNode* s = v->children[r + 1]; //s is k's sucessor in inorder traversal
				while (s->children[0]) s = s->children[0];
				v->keys[r] = s->keys[0];
				v = s; r = 0; //direct v to s which is the actual node whose keys[0] is to be deleted
			}
			v->keys.remove(r); v->children.remove(r + 1); //maybe underflow
			underflowSolve(v); //v must be a leaf node
			return true;
		}
	}
	void print() {
		treePrint(_root);
	}
};


int main() {
	/*BTNode q(5);
	int r = 5;
	r = q.keys.search(0);
	cout << q.children[0] << endl;
	if (0 == NULL)cout << 123 << endl;*/
	//if (-1 < i) { cout << 1 << endl; }

	BTree myBTree(6);
	myBTree.print();
	/*myBTree.insert(1);
	myBTree.insert(2);*/
	for (int i = 0; i <= 50; i++) {
		myBTree.insert(i);
		myBTree.print();
		cout << "********************************" << endl;
	}
	cout << "-----------------------------------" << endl;
	for (int i = 0; i <= 50; i++) {
		myBTree.remove(i);
		myBTree.print();
		cout << "********************************" << endl;
	}

	return 0;
}