#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //clock()

using namespace std;
int A_length;
long long int counterH = 0;
long long int counterL = 0;
int randomSeed = time(0);


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

int hoarePartition(int* A, int p, int r) { //times:  j+i: n, comparison: n + swap times, swap: between[0,n]. Note that while(true) doesn't take comparison
	int x = A[r]; //notice which one to be compared
	int i = p - 1;
	int j = r + 1;
	counterH = 0;
	while (true) {
		do {
			j--;
		} while (A[j] > x);
		do {
			i++;
		} while (A[i] < x);
		if (i < j) {
			counterH++;
			swap(A[i], A[j]);
		}
		else return j;
	}
}

int lomutoPartition(int* A, int p, int r) { //times:  j: n, comparison: 2n, i: n/2, swap: between[0,n]
	int x = A[r]; //x is the value of the pivot 
	int i = p - 1;
	counterL = 0;
	for (int j = p; j < r; j++) {
		if (A[j] <= x) {
			counterL++;
			i++;
			swap(A[i], A[j]);
		}
	}
	swap(A[i + 1], A[r]);
	counterL++;
	return i + 1;
}

void randomArray(int* A, const int len, const int left, const int right) {
	//the integer number is generated in [left,right], both inclusive
	srand(randomSeed); //set the seed
	randomSeed = randomSeed + 1500;
	for (int i = 0; i < len; ++i) {
		A[i] = left + rand() % (right - left + 1);
	}
}

void copyArray(int* A, int* B, const int len) {//copy A to B
	for (int i = 0; i < len; i++)
		B[i] = A[i];
}

void compare() {
	int cases = 1000;
	for (int n = 16; n < 100000; n = n * 2) {
		int len = n;
		long long int counterSumH = 0; //the sum of all counters for hoarePartition
		long long int counterSumL = 0; //the sum of all counters for lomutoPartition
		double counterAvgH; //the average cost for hoarePartition
		double counterAvgL; //the average cost for lomutoPartition
		for (int i = 0; i < cases; i++) {

			int* A1 = new int[len];
			int* A2 = new int[len];
			randomArray(A1, len, 0, 32767);
			copyArray(A1, A2, len);

			int pivotH = hoarePartition(A1, 0, len - 1);
			int pivotL = lomutoPartition(A2, 0, len - 1);

			//cout << "pivotH=" << pivotH << endl; //index starts from 0
			//cout << "counterH=" << counterH << endl;
			//cout << "pivotL=" << pivotL << endl; //index starts from 0
			//cout << "counterL=" << counterL << endl << endl;

			counterSumH += counterH;
			counterSumL += counterL;

			delete[] A1;
			delete[] A2;
		}
		cout << "length=" << len << endl;
		counterAvgH = (counterSumH + 0.0) / cases;
		counterAvgL = (counterSumL + 0.0) / cases;
		cout << "Average swap times for Hoare  Partition=" << counterAvgH << endl;
		cout << "Average swap times for Lomuto Partition=" << counterAvgL << endl;
		cout << endl;
	}

}


int main() {
	//sample test for correctness
	int A1[] = { 8, 3, 7, 1, 4, 2, 9, 6, 0, 5 }; //A_length=10
	int A2[] = { 8, 3, 7, 1, 4, 2, 9, 6, 0, 5 }; //A_length=10
	A_length = sizeof(A1) / sizeof(A1[0]);
	cout << "Sample: " << endl;
	printArray(A1, 0, A_length - 1);

	cout << endl << "Hoare Partition: " << endl;
	int pivotH = hoarePartition(A1, 0, A_length - 1);
	printArray(A1, 0, A_length - 1);
	cout << "pivotH=" << pivotH << endl; //index starts from 0
	cout << "counterH=" << counterH << endl;

	cout << endl << "Lomuto Partition: " << endl;
	int pivotL = lomutoPartition(A2, 0, A_length - 1);
	printArray(A2, 0, A_length - 1);
	cout << "pivotL=" << pivotL << endl; //index starts from 0
	cout << "counterL=" << counterL << endl;
	cout << endl;

	//Test for comparing
	compare();


	return 0;
}