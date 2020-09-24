//#define _CRT_SECURE_NO_WARNINGS
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

int nonRecursiveBinarySearch(int* A, int key, int low, int high) {
	while (low < high) {
		int middle = (low + high + 1) / 2;
		key < A[middle] ? high = middle - 1 : low = middle;
	}
	return key == A[low] ? low : -1;
}

int recursiveBinarySearch(int* A, int key, int low, int high) {
	if (low == high)
		return (key == A[low]) ? low : -1;
	else {
		int middle = (low + high + 1) / 2;
		key < A[middle] ? high = middle - 1 : low = middle;
		return recursiveBinarySearch(A, key, low, high);
	}
}

int main() {
	int a1[] = { 3,4,4,4,4,4 };
	int index1 = nonRecursiveBinarySearch(a1, 3, 0, sizeof(a1) / sizeof(a1[0]) - 1);
	cout << index1 << endl;
	int index2 = recursiveBinarySearch(a1, 4, 0, sizeof(a1) / sizeof(a1[0]) - 1);
	cout << index2 << endl;
}
