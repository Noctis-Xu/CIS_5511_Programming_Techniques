/*Rearrangement inequality problem*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

struct Task {
	int num; //the serial number of a task
	int pTime; //processing time
	bool operator <(const Task& a) {
		return (*this).pTime < a.pTime;
	}
};

template<class T>
int hoarePartition(vector<T>& A, int p, int r) {
	T x = A[p]; //notice which one to be compared
	int i = p - 1;
	int j = r + 1;
	while (true) {
		do {
			j--;
		} while (x < A[j]);
		do {
			i++;
		} while (A[i] < x);
		if (i < j) {
			T temp = A[i];
			A[i] = A[j];
			A[j] = temp;
		}
		else return j;
	}
}
template<class T>
void quickSort(vector<T>& A, int p, int r) {
	if (p < r) {
		int q = hoarePartition(A, p, r);
		quickSort(A, p, q);
		quickSort(A, q + 1, r);
	}
}

template <class T>
void print(const vector<T>& A) { //print tasks and their processing time
	int	size = A.size();
	cout << "Order: \t";
	for (int i = 0; i < size; i++) {
		cout << A[i].num << ' ';
	}
	cout << endl;
	cout << "pTime: \t";
	for (int i = 0; i < size; i++) {
		cout << A[i].pTime << ' ';
	}
	cout << endl;
}

template <class T>
void Sort(vector<T>& A) {
	quickSort(A, 0, A.size() - 1);
}

int main() {
	cout << "Case 1" << endl;
	vector<Task> T1 = { {1,5} ,{2,3} };
	print(T1);
	Sort(T1);
	cout << "***After rearranging***" << endl;
	print(T1);
	cout << endl;

	cout << "Case 2" << endl;
	vector<Task> T2 = { {1,5} ,{2,6}, {3,8}, {4,2}, {5,5} };
	print(T2);
	Sort(T2);
	cout << "***After rearranging***" << endl;
	print(T2);
	cout << endl;

	cout << "Case 3" << endl;
	vector<Task> T3 = { {1,5},{2,3},{3,7} };
	print(T3);
	Sort(T3);
	cout << "***After rearranging***" << endl;
	print(T3);

	return 0;
}