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
	//delete[] p2; //�ͷ���int[2]������û���ͷ�p1
	//cout << p1 << endl;

	int* p1 = new int[2];
	int*& p2 = p1;
	delete[] p2; //�ͷ���int[2]�����ͷ���p1
	cout << p1 << endl;

}