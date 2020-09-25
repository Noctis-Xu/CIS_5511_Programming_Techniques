#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h> //rand()
#include <time.h> //clock()
#include <Windows.h> //time(0), Sleep()
#include <string>

using namespace std;

class minHeapPriorityQueue {
	int MAX_heapSize = 100; //how many words can be stored
	string* A = new string[MAX_heapSize + 1]; //[1..heapSize] is valid for storing words.
	int heapSize = 0; //how many words are stored

	int parent(const int i) {
		return i / 2;
	}
	int left(const int i) {
		return 2 * i;
	}
	int right(const int i) {
		return 2 * i + 1;
	}

	void min_heapify(int i) {
		int smallest;
		while (true) {
			int l = left(i);
			int r = right(i);
			if (l <= heapSize && A[l] < A[i])
				smallest = l;
			else smallest = i;
			if (r <= heapSize && A[r] < A[i])
				smallest = r;
			if (smallest == i)
				break;
			swap(A[i], A[smallest]);
			i = smallest;
		}
	}
	/*void build_min_heap() {
		for (int i = heapSize / 2; i >= 1; i--)
			min_heapify(i);
	}*/

	int search_subtree(const string _word, int i) {
		if (A[i] == _word)
			return i;
		else if (_word < A[i])
			return -1;
		else {
			int left_result = -1;
			int right_result = -1;
			if (left(i) <= heapSize)
				left_result = search_subtree(_word, left(i)); //search the left subtree
			if (right(i) <= heapSize)
				right_result = search_subtree(_word, right(i)); //search the right subtree
			if (left_result >= right_result) //1. If one subtree gets -1 while another gets the right index, like 5, 
				return left_result; //then return the greater one; 2. If both are -1, just return -1;
			else return right_result; //3. If node i is a leaf, then both IF statements fail to execute and the results remain -1.
		}
	}

public:
	int number() {
		return heapSize;
	}

	void remove() {
		if (heapSize < 1) {
			cout << "Error: no word in the queue!" << endl;
		}
		string min = A[1];
		A[1] = A[heapSize];
		heapSize--;
		min_heapify(1);
		//return min;
	}

	int search(const string _word) { //Top-down search. When the word to be searched is not in the queue, return -1.
		/*if (heapSize < 1)
			cout << "Error: no word in the queue!" << endl;*/
		return search_subtree(_word, 1);
	}

	void add(const string _word) { //seems like HEAP-INSERT in the textbook
		if (search(_word) == -1) {
			heapSize++;
			int i = heapSize;
			while (i > 1 && _word < A[parent(i)]) {
				A[i] = A[parent(i)];
				i = parent(i);
			}
			A[i] = _word;
		}
	}

	void printHeap() {
		for (int i = 1; i <= heapSize; i = 2 * i) {
			int last = 2 * i - 1;
			for (int j = i; j <= last && j <= heapSize; j++) {
				//printf("%s ", A[j]);
				cout << A[j]<<' ';
			}
			cout << endl;
		}
	}
};

int main() {
	minHeapPriorityQueue wordsQueue;

	cout << wordsQueue.number() << endl;
	wordsQueue.add("ccc");
	wordsQueue.add("bbb");
	wordsQueue.add("aaa");
	cout << wordsQueue.number() << endl;
	cout << wordsQueue.search("aaa") << endl;
	wordsQueue.add("aaa");
	wordsQueue.printHeap();
	
	
	wordsQueue.remove();
	cout << wordsQueue.number() << endl;
	cout << wordsQueue.search("aaa") << endl;
	wordsQueue.printHeap();

	

	return 0;
}