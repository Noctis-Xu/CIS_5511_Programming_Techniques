//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h> //rand()
#include <time.h> //clock()
#include <Windows.h> //time(0), Sleep()


using namespace std;
int len; //A.length
int counter = 0; //count the while loop execution times in binary search
int randomSeed = time(0);


int nonRecursiveBinarySearch(int* A, const int key) {
	int low = 0;
	int high = len - 1;
	int middle;
	while (low <= high) {
		counter++;
		middle = (low + high + 1) / 2;
		if (key < A[middle])
			high = middle - 1;
		else if (A[middle] < key) {
			low = middle + 1;
		}
		else return middle;
	}
	return -1;
}

void randomArray(int* A, const int len, const int left, const int right) {
	//the integer number is generated in [left,right], both inclusive
	srand(randomSeed); //set the seed
	randomSeed = randomSeed + 1000;
	for (int i = 0; i < len; ++i) {
		A[i] = left + rand() % (right - left + 1);
	}
}

void printArray_0_9(int* A) { //print A[0..9]
	for (int i = 0; i < 10; i++) {
		cout << A[i] << ',';
	}
	cout << endl;
}

int main() {
	//Sample
	cout << endl;
	int a1[] = { 3,4,4,4,4,5 };
	len = sizeof(a1) / sizeof(a1[0]);
	cout << "Sample array: ";
	for (int i = 0; i < len; i++) {
		cout << a1[i] << ',';
	}
	cout << endl;
	int index;
	counter = 0;
	index = nonRecursiveBinarySearch(a1, 3);
	cout << "The key=3 is at " << index;
	cout << "  counter: " << counter << endl;
	counter = 0;
	index = nonRecursiveBinarySearch(a1, 4);
	cout << "The key=4 is at " << index;
	cout << "  counter: " << counter << endl;
	counter = 0;
	index = nonRecursiveBinarySearch(a1, 6);
	cout << "The key=6 is at " << index;
	cout << " counter: " << counter << endl;
	cout << endl;

	//Testing
	int key;
	int cases = 100000; //test how many cases
	int counterSum; //the sum of all counters for total cases
	double counterAvg; //the average cost
	cout << "testing cases for a given n: " << cases << endl;
	printf("input size n |%-15s|%-s\n", "average cost", "lg(n)");
	cout << "！！！！！！！！！！！！！！！！！！！！！！！！！！" << endl;
	for (int n = 4, lgn = 2; n < 100000000; n = n * 2, lgn++) {
		len = n;
		printf("%-13d|", len);

		int* a = new int[len];
		for (int i = 0; i < len; i++) {
			a[i] = i;
		}
		counterSum = 0;
		for (int i = 0; i < cases; i++) {
			srand(randomSeed);
			randomSeed = randomSeed + 1000;
			key = rand(); //key is between [0,RAND_MAX], which is [0, 32767].
			//cout << "key: " << key << endl; //for debugging
			counter = 0;
			nonRecursiveBinarySearch(a, key);
			//cout <<"counter: "<< counter << endl; //for debugging
			counterSum = counterSum + counter;
		}
		counterAvg = (counterSum + 0.0) / cases;
		//printf("Average cost: %-10.4f, lg(n)=%d\n", counterAvg, lgn);
		printf("%-15.5f|%d\n", counterAvg, lgn);
		cout << "！！！！！！！！！！！！！！！！！！！！！！！！！！" << endl;
		delete[]a;
	}

}
