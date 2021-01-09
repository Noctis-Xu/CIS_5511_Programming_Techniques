//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h> //rand()
#include <time.h> //clock()
#include <Windows.h> //time(0), Sleep()

using namespace std;

class BinNode {
public:
	BinNode* parent = NULL, * left = NULL, * right = NULL;
	string key;
	int counter = 1; //count the occurrence of each key
};

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

int main() {
	//BinNode* p = new BinNode;
	//cout << p<<endl;
	//cout << p->counter << endl;
	//BinNode*& p2 = p;
	//delete p2;
	//cout << p->counter << endl;
	//cout << p << endl;
	//cout << p2 << endl;
	//
	//cout << p << endl;

	//int* p1 = new int[2];
	//int* p2 = p1;
	//delete[] p2; //释放了int[2]，但是没有释放p1
	//cout << p1 << endl;

	/*Vector<int> a(5);
	a.insert(0, 0);
	cout << a[0] << endl;
	a[0] = 4;
	cout << a[0]<<endl;
	cout << a.size();*/

	int a = 5, b = 6;
	int* p1 = &a;
	int** p2 = &p1;
	*p2 = &b;
	cout << *p1 << endl;
}