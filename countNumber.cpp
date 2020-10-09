#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

int A_length = 0; //the length of an array
int counter = 0;
int randomSeed = time(0);

int binarySearch_last(const int* A, const int key, int low, int high) { //return the max index of the element to be searched. If it's not there, return -1
	while (low < high) {
		counter++;
		int middle = (low + high + 1) / 2;
		key < A[middle] ? high = middle - 1 : low = middle;
	}
	return key == A[low] ? low : -1;
}

int binarySearch_first(const int* A, const int key, int low, int high) { //return the min index of the element to be searched. The element must be in the array
	while (low < high) {
		counter++;
		int middle = (low + high) / 2;
		key <= A[middle] ? high = middle : low = middle + 1;
	}
	return low;
}

int countNumber(const int* A, const int key) {
	int first, last;
	counter = 0;
	if (key<A[0] || key > A[A_length - 1]) //the key is not in the sorted array
		return 0;
	else { //the key may be in the sorted array
		last = binarySearch_last(A, key, 0, A_length - 1);
		if (last != -1) {
			first = binarySearch_first(A, key, 0, A_length - 1);
			int number = last - first + 1;
			return number;
		}
		else return 0;
	}
}

void printArray(int* A, int begin, int end) { //print A[begin..end]
	int len = end - begin + 1;
	for (int i = 0; i < len; i++) {
		cout << A[i] << ',';
	}cout << endl;
}

void test(int len) {
	A_length = len;
	int* A = new int[A_length];

	for (int k = 1, i = 0;; k++) { //produce [1,2,2,3,3,3,4,4,4,4,5,5,5,5,5,...]
		for (int j = 0; j < k && i < A_length; j++) {
			A[i] = k;
			i++;
		}
		if (i == A_length)
			break;
	}
	//printArray(A, 0, 20);

	srand(randomSeed);
	randomSeed = randomSeed + 1000;
	int key = rand() % 101; //key is between [0,100]
	//cout << "key " << key << endl;

	int num = countNumber(A, key);
	cout << "size n=" << A_length << "    lg(n)="<<log2(A_length)<<endl;
	cout << "the number of " << key << ": " << num << endl;
	cout << "counter: " << counter << endl;
	cout << endl;

	delete[]A;
}

int main() {
	//Sample run
	int a1[] = { -1,4,4,4,4,4,5,5,6 };
	A_length = sizeof(a1) / sizeof(a1[0]);
	int num;
	num = countNumber(a1, -1);
	cout << "the number of -1: " << num << endl;
	num = countNumber(a1, 4);
	cout << "the number of 4: " << num << endl;
	num = countNumber(a1, 5);
	cout << "the number of 5: " << num << endl;
	num = countNumber(a1, 6);
	cout << "the number of 6: " << num << endl;
	num = countNumber(a1, -2);
	cout << "the number of -2: " << num << endl;
	num = countNumber(a1, 1);
	cout << "the number of 1: " << num << endl;
	num = countNumber(a1, 7);
	cout << "the number of 7: " << num << endl;
	cout << endl;

	//Test run
	for (int i = 256; i < 1000000; i = i * 2) {
		test(i);
	}


	return 0;
}