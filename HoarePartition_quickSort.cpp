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

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void printArray(int* A, int len) {
	for (int i = 0; i < len; i++) {
		cout << A[i] << ' ';
	}cout << endl;
}

int hoarePartition(int* A, int p, int r) {
	int x = A[p]; //notice which one to be compared
	int i = p - 1;
	int j = r + 1;
	int counter = 0;
	while (true) {
		counter++;
		cout << "iteration " << counter << endl;
		do {
			j--;

		} while (A[j] > x);
		cout << "j=" << j + 1 << endl;//index starts from 1
		do {
			i++;
		} while (A[i] < x);
		cout << "i=" << i + 1 << endl;//index starts from 1
		if (i < j) {
			swap(A[i], A[j]);
			printArray(A, A_length);
			cout << endl;
		}
		else return j;
	}
}

void quickSort(int* A, int p, int r) {
	if (p < r) {
		int q = hoarePartition(A, p, r);
		quickSort(A, p, q);
		quickSort(A, q + 1, r);
	}
}

int main() {
	//int A[] = { 13, 19, 9, 5, 12, 8, 7, 4, 11, 2, 6, 21 }; //A_length=12
	int A[] = { 8, 3, 7, 1, 4, 2, 9, 6, 0, 5 }; //A_length=12
	A_length = sizeof(A) / sizeof(A[0]);
	printArray(A, A_length);
	int j = hoarePartition(A, 0, A_length - 1);
	printArray(A, A_length);
	//cout << "j=" << j + 1 << endl; //index starts from 1
	return 0;
}