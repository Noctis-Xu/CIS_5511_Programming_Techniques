#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h> //rand()
#include <time.h> //clock()
#include <Windows.h> //sleep()
#include <string>

//#define BinNodePosi BinNode*
using namespace std;



//class BinNode_C {
//public:
//	BinNode* parent = NULL, * left = NULL, * right = NULL;
//	string key;
//	int counter = 0;
//};

class BST {
	//protected:
	//	struct BinNode {
	//		BinNode* parent = NULL, * left = NULL, * right = NULL;
	//		string key;
	//		//int counter = 0;
	//	};
	//	//BinNode* _root;
public:
	virtual int treeSearch(const string&) = 0;
	virtual void treeInsert(const string&) = 0;
	virtual bool treeDelete() = 0;
	virtual void treeWalk() = 0;
	virtual void treePrint() = 0;
};

class BST_string_noDuplicate :public BST { //forbids duplicate keys to be stored in the tree. Use counter to count the same keys.
	struct BinNode {
		BinNode* parent = NULL, * left = NULL, * right = NULL;
		string key;
		int counter = 0;
	};
	BinNode* _root;
	int search(BinNode* x, const string& k) {
		while (x != NULL && k != x->key) {
			if (k < x->key)
				x = x->left;
			else x = x->right;
		}
		if (x == NULL)
			return 0;
		else return x->counter;
	}
public:
	int treeSearch(const string& k) {
		return search(_root, k);
	}
	void treeInsert(const string& k) {
		BinNode* y = NULL;
		BinNode* x = _root;
		while (x != NULL && k != x->key) {
			y = x;
			if (k < x->key)
				x = x->left;
			else x = x->right;
		}
		if (x == NULL) { //k is a new key
			BinNode* z = new BinNode;
			z->key = k;
			z->parent = y;
			if (y == NULL)
				_root = z;
			else if (k < y->key)
				y->left = z;
			else y->right = z;
		}
		else x->counter++; //k is a dulicate key, which means there is a 'x' that x->key equals k, so do not insert k but increment counter.
	}
	bool treeDelete() {

	}
	void treeWalk() {

	}
	void treePrint() {

	}
};




/*Let x be a node in a binary search tree. If y is a node in the left subtree of x,
then y.key<x.key. If y is a node in the right subtree of x, then y.key>=x.key.*/
class BST_string_duplicate :public BST {//allows duplicate keys to be stored in the tree, and a duplicate key will be inserted on the right side
	struct BinNode {
		BinNode* parent = NULL, * left = NULL, * right = NULL;
		string key;
	};
	BinNode* _root;
	BinNode* treeMinimum(BinNode* x) {
		while (x->left != NULL)
			x = x->left;
		return x;
	}
	BinNode* treeSuccessor(BinNode* x) {
		if (x->right != NULL)
			return treeMinimum(x->right);
		BinNode* y = x->parent;
		while (y != NULL && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}
	void transplant(BinNode* u, BinNode* v) {
		if (u->parent == NULL)
			_root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else u->parent->right = v;
		if (v != NULL)
			v->parent = u->parent;
	}
public:
	int treeSearch(const string& k) {
		BinNode* x = _root;
		while (x != NULL && k != x->key) {
			if (k < x->key)
				x = x->left;
			else x = x->right;
		}
		if (x == NULL) //not found
			return 0;
		else { //found, but there may be duplicate keys
			int counter = 1; //includes this node

			/*first method*/
			x = treeSuccessor(x);
			while (x != NULL && x->key == k) {
				counter++;
				x = treeSuccessor(x);
			}

			/*second method is more precise and efficient*/
			/*while (x->right != NULL) {
				x = treeMinimum(x->right);
				if (x->key == k)
					counter++;
				else return counter;
			}*/

			return counter;
		}
	}
	void treeInsert(const string& k) {
		BinNode* y = NULL;
		BinNode* x = _root;
		while (x != NULL) {
			y = x;
			if (k < x->key)
				x = x->left;
			else x = x->right;
		}
		BinNode* z = new BinNode;
		z->key = k;
		z->parent = y;
		if (y == NULL)
			_root = z;
		else if (k < y->key)
			y->left = z;
		else y->right = z;
	}
	bool treeDelete(const string& k) {
		
	}
	void treeWalk() {

	}
	void treePrint() {

	}
};

int main() {


	return 0;
}