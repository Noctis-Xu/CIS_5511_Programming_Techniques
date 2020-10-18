#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h> //rand()
#include <time.h> //clock()
#include <Windows.h> //sleep()
#include <string>
#include <string.h>

using namespace std;

class BinNode {
public:
	BinNode* parent = NULL, * left = NULL, * right = NULL;
	string key;
	int counter = 1; //count the occurrence of each key
};

class BST {
protected:
	BinNode* _root = NULL;
	BinNode* treeMinimum(BinNode* x) {
		while (x->left != NULL)
			x = x->left;
		return x;
	}
	BinNode* treeMaximum(BinNode* x) {
		while (x->right != NULL)
			x = x->right;
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
	BinNode* treePredecessor(BinNode* x) {
		if (x->left != NULL)
			return treeMaximum(x->left);
		BinNode* y = x->parent;
		while (y != NULL && x == y->left) {
			x = y;
			y = y->parent;
		}
		return y;
	}
	BinNode*& treeSearch(BinNode* x, const string& k) {
		while (x != NULL && k != x->key) {
			if (k < x->key)
				x = x->left;
			else x = x->right;
		}
		return x;
	}
	void treeInsert(BinNode*& z) {
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
	void transplant(BinNode* u, BinNode* v) {
		if (u->parent == NULL)
			_root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else u->parent->right = v;
		if (v != NULL)
			v->parent = u->parent;
	}
	void treeDelete(BinNode*& z) {
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
	void treePrint(BinNode* x, int height = 0) { //reverse inorder tree walk
		if (x != NULL) {
			int height_next = height + 1;
			treePrint(x->right, height_next);
			for (int h = height; h; h--)
				cout << '\t';
			cout << x->key << endl;
			treePrint(x->left, height_next);
		}
	}
public:
	virtual int Search(const string&) = 0;
	virtual void Insert(const string&) = 0;
	virtual bool Delete(const string&) = 0;
	virtual void treeWalk() = 0;
	void Print() {
		treePrint(_root);
	}
};



class BST_string_noDuplicate :public BST { //forbids duplicate keys to be stored in the tree. Use counter to count the same keys.
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
		else if (z->counter > 1) //duplicate keys
			z->counter--;
		else //only one key
			treeDelete(z);
		return true;
	}
	void treeWalk() {
		inorderTreeWalk(_root);
	}
};




/*Let x be a node in a binary search tree. If y is a node in the left subtree of x,
then y.key<x.key. If y is a node in the right subtree of x, then y.key>=x.key.*/
class BST_string_duplicate :public BST {//allows duplicate keys to be stored in the tree, and a duplicate key will be inserted on the right side
	void inorderTreeWalk(BinNode* x) {
		if (x != NULL) {
			inorderTreeWalk(x->left);
			if (treePredecessor(x) != NULL && treePredecessor(x)->key == x->key) //if it's not the first same key
				inorderTreeWalk(x->right);
			else { //it's the first key
				string k = x->key;
				int counter = 1;
				BinNode* y = x;
				while (y->right != NULL) { //if there are duplicate keys
					y = treeMinimum(y->right);
					if (y->key == k)
						counter++;
					else break;
				}
				cout << x->key;
				if (counter > 1)
					cout << '(' << counter << ')';
				cout << endl;
				inorderTreeWalk(x->right);
			}
		}
	}
public:
	int Search(const string& k) {
		BinNode* x = treeSearch(_root, k);
		if (x == NULL) //not found
			return 0;
		else { //found, but there may be duplicate keys
			int counter = 1; //includes this node
			/*first method, which is readable*/
			/*x = treeSuccessor(x);
			while (x != NULL && x->key == k) {
				counter++;
				x = treeSuccessor(x);
			}*/

			/*second method, which is more precise and efficient*/
			while (x->right != NULL) {
				x = treeMinimum(x->right);
				if (x->key == k)
					counter++;
				else return counter;
			}
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
	void treeWalk() {
		inorderTreeWalk(_root);
	}
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

	/*BinNode* p1 = new BinNode;
	BinNode* p2 = new BinNode;
	BinNode* p3 = new BinNode;
	p1->key = "p1";
	p2->key = "p2";
	p3->key = "p3";*/

	//BinNode*& p = p1;
	//cout << p->key << endl;
	//p = p2;
	//cout << p->key << endl;
	//cout << p1->key << endl;

	//p1->right = p2;
	//cout << p1->right->key << endl;
	//BinNode* temp = p1;
	//temp->right = p3;
	//cout << p1->right->key << endl;
	/*delete p1;
	cout << p1->key << endl;*/

	//Sample run
	/*BST_string_duplicate BST_du;
	BST_du.Insert("fox");
	BST_du.Insert("cat");
	BST_du.Insert("cat");
	BST_du.Insert("cow");
	BST_du.Insert("tiger");
	BST_du.Insert("horse");
	BST_du.Insert("wolf");
	BST_du.Insert("cat");
	BST_du.Print();
	cout << "cat: " << BST_du.Search("cat") << endl;
	cout << endl;
	cout << BST_du.Delete("cat") << endl;
	cout << BST_du.Delete("dog") << endl;
	BST_du.Print();
	cout << "cat: " << BST_du.Search("cat") << endl;
	cout << "dog: " << BST_du.Search("dog") << endl;
	BST_du.treeWalk();

	cout << endl << endl;
	BST_string_noDuplicate BST_noDu;
	BST_noDu.Insert("fox");
	BST_noDu.Insert("cat");
	BST_noDu.Insert("cat");
	BST_noDu.Insert("cow");
	BST_noDu.Insert("tiger");
	BST_noDu.Insert("horse");
	BST_noDu.Insert("wolf");
	BST_noDu.Insert("cat");
	BST_noDu.Print();
	cout << "cat: " << BST_noDu.Search("cat") << endl;
	cout << endl;
	cout << BST_noDu.Delete("cat") << endl;
	cout << BST_noDu.Delete("dog") << endl;
	BST_noDu.Print();
	cout << "cat: " << BST_noDu.Search("cat") << endl;
	cout << "dog: " << BST_noDu.Search("dog") << endl;
	BST_noDu.treeWalk();*/




	cout << "1 search word, which returns an integer to indicate the number of occurrences of the word in the tree." << endl;
	cout << "2 insert word, which adds one occurrence and returns nothing." << endl;
	cout << "3 delete word, which removes one occurrence and returns 1 for success, 0 for failure (i.e., the word is not in the tree)." << endl;
	cout << "4 treeWalk, which returns nothing, but prints the words in the tree in the dictionary order, one per line. For duplicated words, display the number of occurrences after the word, such as \"car(3)\"." << endl;
	cout << "5 print, which returns nothing, but display the current content of the tree, in a proper format that shows the tree structure." << endl;
	cout << "6 BST_noDu, which shifts to a BST that there is no duplicated keys" << endl;
	cout << "7 BST_du, which shifts to a BST that there can be duplicated keys" << endl;
	cout << "8 exit, which terminates the program" << endl;
	cout << "Note: the default BST is BST_noDu" << endl;
	cout << endl;
	BST_string_duplicate BST_du;
	BST_string_noDuplicate BST_noDu;
	BST* p_BST = &BST_noDu;
	string cmd, word;
	while (cin >> cmd) {
		if (cmd == "search") {
			cin >> word;
			cout << p_BST->Search(word) << endl;
		}
		else if (cmd == "insert") {
			cin >> word;
			p_BST->Insert(word);
		}
		else if (cmd == "delete") {
			cin >> word;
			cout << p_BST->Delete(word) << endl;
		}
		else if (cmd == "treeWalk")
			p_BST->treeWalk();
		else if (cmd == "print")
			p_BST->Print();
		else if (cmd == "BST_noDu")
			p_BST = &BST_noDu;
		else if (cmd == "BST_du")
			p_BST = &BST_du;
		else if (cmd == "exit")
			break;
	}

	return 0;
}