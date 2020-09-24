#include <iostream>
#include <stdio.h>
#include <stdlib.h> //rand()
#include <time.h> //clock()
#include <Windows.h> //time(0), Sleep()

using namespace std;

long long int counter_insertionSort = 0; //count how many times the while-loop body in insertionSort executes
long long int counter_mergeSort = 0; //count how many times the for-loop body in merge procedure executes

void insertionSort(int A[], const int len) {
	//A[0..len-1]
	int key, i;
	for (int j = 1; j < len; j++) {
		key = A[j];
		//Insert A[j] into the sorted sequence A[0..j-1].
		i = j - 1;
		while (i > -1 && A[i] > key) {
			counter_insertionSort++;
			A[i + 1] = A[i];
			i = i - 1;
		}
		A[i + 1] = key;
	}
}

void merge(int A[], int p, int q, int r) {//r is the last index of A, r = A.length-1
	int n1 = q - p + 1; //the number of valid elements in left subarray
	int n2 = r - q; //the number of valid elements in right subarray
	int* L = new int[n1 + 1]; //L[p..q,sentinel], the extra element is the sentinel
	int* R = new int[n2 + 1]; //R[q+1..r,sentinel]
	//the two for-loop bodies totally executes r-p+1 times
	for (int i = 0; i < n1; ++i)
		L[i] = A[p + i]; //L[p..q]
	for (int j = 0; j < n2; ++j)
		R[j] = A[q + 1 + j]; //R[q+1..r]
	L[n1] = INT_MAX; //the sentinel is assigned to infinity, using the max value of int
	R[n2] = INT_MAX;
	int i = 0;
	int j = 0;
	for (int k = p; k <= r; ++k) { //the loop body executes r-p+1 times
		counter_mergeSort++;
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

void randomArray(int* A, const int len, const int left, const int right) {
	//the integer number is generated in [left,right], both inclusive
	srand(time(0)); //set the seed
	for (int i = 0; i < len; ++i) {
		A[i] = left + rand() % (right - left + 1);
	}
}

void copyArray(int* A, int* B, const int len) {//copy A to B
	for (int i = 0; i < len; i++)
		B[i] = A[i];
}

void compareTime(const int len) { //len is the number of elements in array
	counter_insertionSort = 0; //reset the counter
	counter_mergeSort = 0;
	int left = 0, right = 1000000; //the range of random number, both inclusive
	int* a1, * a2;
	a1 = new int[len];
	a2 = new int[len];
	Sleep(1000); //change time(0) to get different random seed
	randomArray(a1, len, left, right);
	copyArray(a1, a2, len); //copy a1 to a2

	cout << "The size of the testing array: " << len << endl;

	clock_t beginTime, endTime; //here in my computer the precision is one tick per millisecond
	double duration;

	beginTime = clock();
	insertionSort(a1, len);
	endTime = clock();
	duration = (double(endTime) - double(beginTime)) / CLOCKS_PER_SEC * 1000; //the precision is millisecond
	cout << "The running time of Insertion Sort: " << duration << "ms" << endl;

	beginTime = clock();
	mergeSort(a2, 0, len - 1);
	endTime = clock();
	duration = (double(endTime) - double(beginTime)) / CLOCKS_PER_SEC * 1000;
	cout << "The running time of Merge Sort:     " << duration << "ms" << endl;

	cout << "The while-loop body in insertionSort executes: " << counter_insertionSort << " times" << endl;
	cout << "The for-loop body in mergeSort executes: " << counter_mergeSort << " times" << endl;
	cout << endl;
	delete[]a1; //release the dynamic memory allocation 
	delete[]a2;
}

void sampleTest(int* a1_sample, int* a2_sample, const int len) {
	cout << "Sample array: " << endl;
	for (int i = 0; i < len; i++) {
		cout << a1_sample[i] << ',';
	}
	cout << endl;

	counter_insertionSort = 0;
	insertionSort(a1_sample, len);
	cout << "Inserting Sort: " << endl;
	for (int i = 0; i < len; i++) {
		cout << a1_sample[i] << ',';
	}
	cout << endl;
	cout << "The while-loop body in insertionSort executes: " << counter_insertionSort << " times" << endl;

	counter_mergeSort = 0;
	mergeSort(a2_sample, 0, len - 1);
	cout << "Merge Sort: " << endl;
	for (int i = 0; i < len; i++) {
		cout << a2_sample[i] << ',';
	}
	cout << endl;
	cout << "The for-loop body in mergeSort executes: " << counter_mergeSort << " times" << endl;
}

int main() {
	//sample array
	int a1_sample1[] = { 3, 2, 5, 1, 4 };
	int a2_sample1[] = { 3, 2, 5, 1, 4 };
	int length_sample1 = sizeof(a1_sample1) / sizeof(a1_sample1[0]);
	sampleTest(a1_sample1, a2_sample1, length_sample1);
	cout << endl;

	int a1_sample2[] = { 1, 2, 3, 4, 5 };
	int a2_sample2[] = { 1, 2, 3, 4, 5 };
	int length_sample2 = sizeof(a1_sample2) / sizeof(a1_sample2[0]);
	sampleTest(a1_sample2, a2_sample2, length_sample2);
	cout << endl;

	int a1_sample3[] = { 5, 4, 3, 2, 1 };
	int a2_sample3[] = { 5, 4, 3, 2, 1 };
	int length_sample3 = sizeof(a1_sample3) / sizeof(a1_sample3[0]);
	sampleTest(a1_sample3, a2_sample3, length_sample3);
	cout << endl;

	int a1_sample4[] = { -1, -1, 5, 1, 4, 4 };
	int a2_sample4[] = { -1, -1, 5, 1, 4, 4 };
	int length_sample4 = sizeof(a1_sample4) / sizeof(a1_sample4[0]);
	sampleTest(a1_sample4, a2_sample4, length_sample4);
	cout << endl;

	//testing cases
	compareTime(500);
	compareTime(1000);
	compareTime(1500);
	compareTime(2000);
	compareTime(3000);
	compareTime(5000);
	compareTime(10000);
	compareTime(100000);
	compareTime(100000);
	compareTime(200000);
	compareTime(400000);
}
