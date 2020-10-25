#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h> //rand()
#include <string>
//#define DEBUG

using namespace std;

class BinNode {
public:
	BinNode* parent = NULL, * left = NULL, * right = NULL;
	string key;
	int counter = 1; //count the occurrence of each key
	int height = 0;
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
	BinNode*& treeSearch(BinNode* x, const string& k) { //Note: it is a reference to the pointer to the node x
		while (x != NULL && k != x->key) {
			if (k < x->key)
				x = x->left;
			else x = x->right;
		}
		return x;
	}
	void treeInsert(BinNode*& z) { //Note: it is a reference to the node z
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
	void treeDelete(BinNode*& z) { //Note: it is a reference to the node z
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
#ifdef DEBUG
			cout << x->key << x->height << endl;
#endif // DEBUG
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
	virtual int Search(const string& k) {
		BinNode* x = treeSearch(_root, k);
		if (x == NULL)
			return 0;
		else return x->counter;
	}
	virtual void Insert(const string& k) {
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
	virtual bool Delete(const string& k) {
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



class AVL :public BST_string_noDuplicate {
protected:
	int balanceFactor(BinNode* x) {
		int leftHeight = -1, rightHeight = -1;
		if (x->left) leftHeight = x->left->height;
		if (x->right) rightHeight = x->right->height;
		return leftHeight - rightHeight;
	}
	void updateHeight(BinNode* x) {
		int leftHeight = 0, rightHeight = 0;
		if (x->left) leftHeight = x->left->height + 1;
		if (x->right) rightHeight = x->right->height + 1;
		x->height = leftHeight > rightHeight ? leftHeight : rightHeight;
	}
	void leftRotate(BinNode* x) {
		BinNode* y = x->right;
		x->right = y->left; //turn y's left subtree into x's right subtree
		if (y->left) y->left->parent = x;

		y->parent = x->parent; //link x's parent to y
		if (!x->parent) _root = y;
		else if (x == x->parent->left) x->parent->left = y;
		else x->parent->right = y;

		y->left = x; //put x on y's left
		x->parent = y;
	}
	void rightRotate(BinNode* x) {
		BinNode* y = x->left;
		x->left = y->right; //turn y's right subtree into x's left subtree
		if (y->right) y->right->parent = x;

		y->parent = x->parent; //link x's parent to y
		if (!x->parent) _root = y;
		else if (x == x->parent->right) x->parent->right = y;
		else x->parent->left = y;

		y->right = x; //put x on y's right
		x->parent = y;
	}
	void rotateAt(BinNode* x) {
		if (balanceFactor(x) > 1) { //left heavy
			if (balanceFactor(x->left) <= -1) {
				leftRotate(x->left); //LR case
				updateHeight(x->left->left);
			}
			rightRotate(x); //LL case
			updateHeight(x);
			updateHeight(x->parent);
		}
		else if (balanceFactor(x) < -1) { //right heavy
			if (balanceFactor(x->right) >= 1) {
				rightRotate(x->right); //RL case
				updateHeight(x->right->right);
			}
			leftRotate(x); //RR case
			updateHeight(x);
			updateHeight(x->parent);
		}
	}
	BinNode* treeDelete(BinNode*& z) { //Note: it is a reference to the node z. The difference from BST's treeDelete is that 1.this version returns a pointer to the parent of the actual deleted node 2.update the height of y_p
		BinNode* y = z; //y is the actual node to be deleted. It is z by default, otherwise it is z's successor.
		BinNode* y_p = y->parent; //y_p depends on whether the height of the substitute for z is changed. It corresponds to the node (a)q (b)q (c)y (d)r in Figure 12.4 at the page 297, of textbook CLRS 3rd edition.
		if (y->left == NULL)
			transplant(y, y->right); //y_p is the node (a)q in Figure 12.4
		else if (y->right == NULL)
			transplant(y, y->left); //y_p is the node (b)q
		else {
			y = treeMinimum(z->right);
			y_p = y; //y_p is the node (c)y
			if (y->parent != z) {
				y_p = y->parent; //y_p is the node (d)r
				transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
		}
		delete z;
		return y_p;
	}
public:
	virtual void Insert(const string& k) {
		BinNode* y = NULL;
		BinNode* x = _root;
		while (x != NULL && k != x->key) {
			y = x;
			if (k < x->key)
				x = x->left;
			else x = x->right;
		}
		if (x != NULL) {
			x->counter++; //k is a dulicate key, which means there is a 'x' that x->key equals k, so do not insert k but increment counter.
		}
		else { //k is a new key
			BinNode* z = new BinNode;
			z->key = k;
			z->parent = y;
			if (y == NULL)
				_root = z;
			else if (k < y->key)
				y->left = z;
			else y->right = z; //insert of the new key is completed
			/*rebalancing*/
			for (BinNode* p = z->parent; p; p = p->parent) { //check from the parent of the inserted node. It should update height from its parent to the lowest unbalanced node.
				if (balanceFactor(p) < -1 || balanceFactor(p) > 1) {
					rotateAt(p); //including updateHeight()
					return; //Once the lowest unbalanced node is fixed, the above ancestor will also be fixed and return to its original height. The lowest unbalanced node may be the grandparent of the inserted node at least.
				}
				else updateHeight(p);
			}
		}
	}

	virtual bool Delete(const string& k) {
		BinNode* z = treeSearch(_root, k);
		if (z == NULL) //no such key
			return false;
		else if (z->counter > 1) //duplicate keys
			z->counter--;
		else { //only one key
			BinNode* z_p = treeDelete(z);
			/*rebalancing*/
			for (BinNode* p = z_p; p; p = p->parent) { //check from the deleted node or its parent upto the root. The rotation may spread to the root.
				if (balanceFactor(p) < -1 || balanceFactor(p) > 1)
					rotateAt(p); //including updateHeight()
				updateHeight(p);
			}
		}
		return true;
	}
};

int main() {
	//User interface
	cout << "Testing AVL tree" << endl;
	cout << "1 search word, which returns an integer to indicate the number of occurrences of the word in the tree." << endl;
	cout << "2 insert word, which adds one occurrence and returns nothing." << endl;
	cout << "3 delete word, which removes one occurrence and returns 1 for success, 0 for failure (i.e., the word is not in the tree)." << endl;
	cout << "4 treeWalk, which returns nothing, but prints the words in the tree in the dictionary order, one per line. For duplicated words, display the number of occurrences after the word, such as \"car(3)\"." << endl;
	cout << "5 print, which returns nothing, but display the current content of the tree, in a proper format that shows the tree structure." << endl;
	cout << "6 exit, which terminates the program" << endl;
	cout << "Note: duplicated keys will be counted by a counter" << endl;
	cout << endl;

	AVL AVL_noDu;
	string cmd, word;
	while (cin >> cmd) {
		if (cmd == "search") {
			cin >> word;
			cout << AVL_noDu.Search(word) << endl;
		}
		else if (cmd == "insert") {
			cin >> word;
			AVL_noDu.Insert(word);
		}
		else if (cmd == "delete") {
			cin >> word;
			cout << AVL_noDu.Delete(word) << endl;
		}
		else if (cmd == "treeWalk")
			AVL_noDu.treeWalk();
		else if (cmd == "print")
			AVL_noDu.Print();
		else if (cmd == "exit")
			break;
	}
	return 0;
}