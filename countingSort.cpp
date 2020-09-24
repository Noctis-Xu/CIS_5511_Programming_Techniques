//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h> //rand()
#include <time.h> //clock()
#include <Windows.h> //time(0), Sleep()

using namespace std;
int A_length;

void printArray(int* A, int begin, int end) { //print A[begin..end]
	int len = end - begin + 1;
	for (int i = 0; i < len; i++) {
		cout << A[i] << ',';
	}cout << endl;
}

void countingSort(int* A, int* B, int k) {
	int* C = new int[k + 1]; //C[0..k]
	for (int i = 0; i <= k; i++)
		C[i] = 0;
	for (int j = 0; j < A_length; j++) { //the index of A starts from 0
		C[A[j]]++; //C[i] now contains the number of elements equal to i.
	}
	cout << "After 2nd for-loop, C: ";
	printArray(C, 0, k);
	for (int i = 1; i <= k; i++) {
		C[i] = C[i] + C[i - 1]; //C[i] now c contains the number of elements less than or equal to i.
	}
	cout << "After 3rd for-loop, C: ";
	printArray(C, 0, k);
	for (int j = A_length - 1; j >= 0; j--) {
		B[C[A[j]]-1] = A[j]; //NOTE that C[A[j]] is the number of elements, but the B starts from[0..A_length - 1],
		C[A[j]]--;			 //when use the number of elements as index for B, it should be subtracted by 1.
	}
	cout << "After 4th for-loop, C: ";
	printArray(C, 0, k);
	delete[]C;
}

int main() {
	//int A[] = { 2,5,3,0,2,3,0,3 };
	int A[] = { 2,5,3,0,2,3,0,3 };
	A_length = sizeof(A) / sizeof(A[0]);
	cout << "A:";
	printArray(A, 0, A_length - 1);
	int* B = new int[A_length];
	for (int j = A_length - 1; j >= 0; j--) {
		B[j] = 10;
	}
	countingSort(A, B, 5);
	cout << "B:";
	printArray(B, 0, A_length-1);
	cout << "A:";
	printArray(A, 0, A_length - 1);
	delete[]B;
	return 0;
}