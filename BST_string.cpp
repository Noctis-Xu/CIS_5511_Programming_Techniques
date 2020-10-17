#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h> //rand()
#include <time.h> //clock()
#include <Windows.h> //sleep()
#include <string>

//#define BinNodePosi BinNode*
using namespace std;



class BinNode {
public:
	BinNode* parent = NULL, * left = NULL, * right = NULL;
	string key;
	int counter = 1; //count the occurrence of each key
};

class BST {
protected:
	/*virtual struct BinNode {
		BinNode* parent = NULL, * left = NULL, * right = NULL;
		string key;
	};*/
	BinNode* _root;

	BinNode* treeSearch(BinNode* x, const string& k) {
		while (x != NULL && k != x->key) {
			if (k < x->key)
				x = x->left;
			else x = x->right;
		}
		return x;
	}
	void treeInsert(BinNode* z) {
		BinNode* y = NULL;
		BinNode* x = _root;
		while (x != NULL) {
			y = x;
			if (z->key < x->key)
				x = x->left;
			else x = x->right;
		}
		z->parent = y;
		if (y == NULL)
			_root = z;
		else if (z->key < y->key)
			y->left = z;
		else y->right = z;
	}
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
	void treeDelete(BinNode* z) {
		if (z->left == NULL)
			transplant(z, z->right);
		else if (z->right == NULL)
			transplant(z, z->left);
		else {
			BinNode* y = treeMinimum(z->right);
			if (y->parent != z) {
				transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
		}
		delete z;
	}
public:

	//virtual int treeSearch(const string&) = 0;
	//virtual void treeInsert(const string&) = 0;
	//virtual bool treeDelete() = 0;
	virtual void treeWalk() = 0;
	virtual void treePrint() = 0;
};

class BST_string_noDuplicate :public BST { //forbids duplicate keys to be stored in the tree. Use counter to count the same keys.
	//virtual struct BinNode {
	//	BinNode* parent = NULL, * left = NULL, * right = NULL;
	//	string key;
	//	int counter = 0;
	//};
	//BinNode* _root;
	void inorderTreeWalk(BinNode* x) {
		if (x != NULL) {
			inorderTreeWalk(x->left);
			cout << x->key;
			if (x->counter > 1)
				cout << '(' << x->counter << ')';
			cout << endl;
			inorderTreeWalk(x->right);
		}
	}
public:
	int Search(const string& k) {
		BinNode* x = treeSearch(_root, k);
		if (x == NULL)
			return 0;
		else return x->counter;
	}
	void Insert(const string& k) {
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
	bool Delete(const string& k) {
		BinNode* z = treeSearch(_root, k);
		if (z == NULL) //no such key
			return false;
		else if (z->counter > 1) { //duplicate keys
			z->counter--;
			return true;
		}
		else { //only one key
			treeDelete(z);
			return true;
		}	
	}
	
	void Walk() {
		inorderTreeWalk(_root);
	}
	//void treePrint() {

	//}
};




/*Let x be a node in a binary search tree. If y is a node in the left subtree of x,
then y.key<x.key. If y is a node in the right subtree of x, then y.key>=x.key.*/
class BST_string_duplicate :public BST {//allows duplicate keys to be stored in the tree, and a duplicate key will be inserted on the right side
	//struct BinNode {
	//	BinNode* parent = NULL, * left = NULL, * right = NULL;
	//	string key;
	//};
	//BinNode* _root;

public:
	int Search(const string& k) {
		BinNode* x = treeSearch(_root, k);
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
			/*second method, which is more precise and efficient*/
			/*while (x->right != NULL) {
				x = treeMinimum(x->right);
				if (x->key == k)
					counter++;
				else return counter;
			}*/
			return counter;
		}
	}
	void Insert(const string& k) {
		BinNode* z = new BinNode;
		z->key = k;
		treeInsert(z);
	}
	bool Delete(const string& k) {
		BinNode* z = treeSearch(_root, k);
		if (z == NULL) //no such key
			return false;
		else {
			treeDelete(z);
			return true;
		}
	}
	/*void treeWalk() {

	}
	void treePrint() {

	}*/
};

int main() {
	//int* p1 = new int[2];
	//p1[0] = 1;
	//p1[1] = 2;
	//cout << p1[1] << endl;
	//int*p2 = p1;
	//delete [] p2;
	////delete[] p1;
	//cout << p1[1] << endl;

	BinNode* p1 = new BinNode;
	BinNode* p2 = new BinNode;
	BinNode* p3 = new BinNode;
	p1->key = "p1";
	p2->key = "p2";
	p3->key = "p3";

	p1->right = p2;
	cout << p1->right->key << endl;
	BinNode* temp = p1;
	temp->right = p3;
	cout << p1->right->key << endl;
	/*delete p1;
	cout << p1->key << endl;*/
	return 0;
}