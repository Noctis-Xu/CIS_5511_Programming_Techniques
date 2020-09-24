//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h> //rand()
#include <time.h> //clock()
#include <Windows.h> //time(0), Sleep()

using namespace std;

class intArray {
private:
	int* A;
	int len; //the number of the elements in array A
public:
	intArray(int length_ = 0) {
		len = length_;
		A = new int[len];
	}
	intArray(int length_ = 0) {
		len = length_;
		A = new int[len];
	}
	~intArray() { //Destructor, release the dynamic memory
		delete[] A;
	}
	void insertionSort(int A[], int len) {
		//A[0..len-1]
		int key, i;
		int counter_while = 0; //count the while loop
		for (int j = 1; j < len; j++) {
			key = A[j];
			//Insert A[j] into the sorted sequence A[0..j-1].
			i = j - 1;
			while (i > -1 && A[i] > key) {
				A[i + 1] = A[i];
				i = i - 1;
				counter_while++;
			}
			A[i + 1] = key;
		}
		cout << counter_while << endl;
	}

	void merge(int A[], int p, int q, int r) {//r is the last index of A, r = A.length-1
		int n1 = q - p + 1; //the quantity of valid elements in left subarray
		int n2 = r - q; //the quantity of valid elements in right subarray
		int* L = new int[n1 + 1]; //L[p..q,sentinel], the extra element is the sentinel
		int* R = new int[n2 + 1]; //R[q+1..r,sentinel]
		for (int i = 0; i < n1; ++i)
			L[i] = A[p + i]; //L[p..q]
		for (int j = 0; j < n2; ++j)
			R[j] = A[q + 1 + j]; //R[q+1..r]
		L[n1] = INT_MAX; //the sentinel is assigned to infinity, using the max value of int
		R[n2] = INT_MAX;
		int i = 0;
		int j = 0;
		for (int k = p; k <= r; ++k) {
			if (L[i] <= R[j]) {
				A[k] = L[i];
				i = i + 1;
			}
			else {
				A[k] = R[j];
				j = j + 1;
			}
		}
		delete[] L; //release the dynamic memory allocation 
		delete[] R;
	}
	void mergeSort(int A[], int p, int r) {//r is the last index of A
		if (p < r) {
			int q = (p + r) / 2;
			mergeSort(A, p, q);
			mergeSort(A, q + 1, r);
			merge(A, p, q, r);
		}
	}

	void randomArray(int* A, int len, int left, int right) {
		//the number is generated in [left,right], both inclusive
		srand(time(0)); //set the seed
		for (int i = 0; i < len; ++i) {
			A[i] = left + rand() % (right - left + 1);
		}
	}

	void copyArray(int* A, int* B, int len) {//copy A to B
		for (int i = 0; i < len; i++) {
			B[i] = A[i];
		}
	}

	void compareTime(int* a1, int* a2, int len) {
		cout << "testing array1: " << endl;
		for (int i = 0; i < 10; i++) {
			cout << a1[i] << ',';
		}
		cout << endl;
		cout << "testing array2: " << endl;
		for (int i = 0; i < 10; i++) {
			cout << a2[i] << ',';
		}
		cout << endl;

		clock_t beginTime, endTime; //here in my computer the precision is one tick per millisecond
		double duration;

		beginTime = clock();
		insertionSort(a1, len);
		endTime = clock();
		duration = (double(endTime) - double(beginTime)) / CLOCKS_PER_SEC * 1000; //the precision is millisecond
		cout << "The running time is: " << duration << "ms" << endl;
		cout << "Inserting Sort: " << endl;
		for (int i = 0; i < 10; i++) {
			cout << a1[i] << ',';
		}
		cout << endl;

		beginTime = clock();
		mergeSort(a2, 0, len - 1);
		endTime = clock();
		duration = (double(endTime) - double(beginTime)) / CLOCKS_PER_SEC * 1000;
		cout << "The running time is: " << duration << "ms" << endl;
		cout << "Merge Sort: " << endl;
		for (int i = 0; i < 10; i++) {
			cout << a2[i] << ',';
		}
		cout << endl;
	}
};


int main() {
	//sample array
	int a1[] = { 9,4,3,1,5,2,2,6,7,9,8,-1,0 };
	int a2[] = { 9,4,3,1,5,2,2,6,7,9,8,-1,0 };
	int a1_length = sizeof(a1) / sizeof(a1[0]);
	int a2_length = sizeof(a2) / sizeof(a2[0]);
	cout << "Sample array: " << endl;
	for (int i = 0; i < a1_length; i++) {
		cout << a1[i] << ',';
	}
	cout << endl;

	intArray a1_case1;
	insertionSort(a1, a1_length);
	cout << "Inserting Sort: " << endl;
	for (int i = 0; i < a1_length; i++) {
		cout << a1[i] << ',';
	}
	cout << endl;

	mergeSort(a2, 0, a2_length - 1);
	cout << "Merge Sort: " << endl;
	for (int i = 0; i < a2_length; i++) {
		cout << a2[i] << ',';
	}
	cout << endl;


	//testing cases
	int len = 600; //testing case1
	int* a1_case1 = new int[len];
	int* a2_case1 = new int[len];
	randomArray(a1_case1, len, 0, 1000000);
	copyArray(a1_case1, a2_case1, len);
	compareTime(a1_case1, a2_case1, len);
	delete[]a1_case1;//release the dynamic memory allocation 
	delete[]a2_case1;

	len = 1000; //testing case2
	a1_case1 = new int[len];
	a2_case1 = new int[len];
	randomArray(a1_case1, len, 0, 1000000);
	copyArray(a1_case1, a2_case1, len);
	compareTime(a1_case1, a2_case1, len);
	delete[]a1_case1;
	delete[]a2_case1;

	//Sleep(2000);
	len = 3000; //testing case2
	a1_case1 = new int[len];
	a2_case1 = new int[len];
	randomArray(a1_case1, len, 0, 1000000);
	copyArray(a1_case1, a2_case1, len);
	compareTime(a1_case1, a2_case1, len);
	delete[]a1_case1;
	delete[]a2_case1;

	len = 10000; //testing case3
	a1_case1 = new int[len];
	a2_case1 = new int[len];
	randomArray(a1_case1, len, 0, 1000000);
	copyArray(a1_case1, a2_case1, len);
	compareTime(a1_case1, a2_case1, len);
	delete[]a1_case1;
	delete[]a2_case1;

	len = 100000; //testing case4
	a1_case1 = new int[len];
	a2_case1 = new int[len];
	randomArray(a1_case1, len, 0, 1000000);
	copyArray(a1_case1, a2_case1, len);
	compareTime(a1_case1, a2_case1, len);
	delete[]a1_case1;
	delete[]a2_case1;

	len = 100000; //testing case4
	a1_case1 = new int[len];
	a2_case1 = new int[len];
	randomArray(a1_case1, len, 0, 1000000);
	copyArray(a1_case1, a2_case1, len);
	compareTime(a1_case1, a2_case1, len);
	delete[]a1_case1;
	delete[]a2_case1;
}
