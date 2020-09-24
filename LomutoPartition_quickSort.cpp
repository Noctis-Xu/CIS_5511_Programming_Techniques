#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
//#include <cstdio>
//#include <cstdlib>
//#include <string.h>
#include <cstring>
#include <list>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;
int A_length;
int counter = 0;

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void printArray(int* A, int begin, int end) { //print A[begin..end]
	int len = end - begin + 1;
	for (int i = 0; i < len; i++) {
		cout << A[i] << ',';
	}cout << endl;
}

int partition(int* A, int p, int r) {
	int x = A[r]; //x is the value of the pivot
	int i = p - 1;
	for (int j = p; j < r; j++) {
		if (A[j] <= x) {
			i++;
			swap(A[i], A[j]);
			printArray(A, p, r);
		}	
	}
	swap(A[i + 1], A[r]);
	//printArray(A, p, r);
	//cout << "q=" << i + 1 + 1 << endl; //index starts from 1
	return i + 1;
}

void quickSort(int* A, int p, int r) {
	//printArray(A, p, r);
	if (p < r) {
		int q = partition(A, p, r);
		quickSort(A, p, q - 1);
		quickSort(A, q + 1, r);
	}
}

int main() {
	//int A[] = { 13, 19, 9, 5, 12, 8, 7, 4, 11, 2, 6, 21 }; //A_length=12
	int A[] = { 8, 3, 7, 1, 4, 2, 9, 6, 0, 5 };
	A_length = sizeof(A) / sizeof(A[0]);
	//printArray(A, 0, A_length - 1);
	//quickSort(A, 0, A_length - 1);
	//printArray(A, 0, A_length - 1);

	//int A[] = { 13, 19, 9, 5, 12, 8, 7, 4, 11, 2, 6, 9 }; //A_length=12
	//A_length = sizeof(A) / sizeof(A[0]);
	printArray(A, 0, A_length - 1);
	int q = partition(A, 0, A_length - 1);
	printArray(A, 0, A_length - 1);
	cout << "q=" << q + 1 << endl; //index starts from 1

	return 0;
}