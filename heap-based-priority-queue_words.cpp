#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h> //rand()
#include <time.h> //clock()
#include <Windows.h> //time(0), Sleep()
#include <string>
#include <math.h>

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
			if (r <= heapSize && A[r] < A[smallest])
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
	~minHeapPriorityQueue() {
		delete[]A;
	}

	int number() {
		return heapSize;
	}

	string remove() {
		if (heapSize < 1)
			return "Error: no word in the queue!";
		string min = A[1];
		A[1] = A[heapSize];
		heapSize--;
		min_heapify(1);
		return min;
	}

	int search(const string _word) { //Top-down search. When the word to be searched is not in the queue, return -1.
		if (heapSize < 1)
			return -1;
		else
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

	void printHeap() { //print the heap-based priority queue in heap structure
		/*for (int level = 0, i = 1; level <= height; level++, i = 2 * i) { //level means the level of the tree, i is the index of the first node at that level
			int last = 2 * i - 1;
			for (int j = i; j <= last && j <= heapSize; j++) {
				//printf("%s ", A[j]);
				cout << A[j] << ' ';
			}
			cout << endl;
		}*/
		cout << "Print heap priority queue:" << endl;
		int height = log2(heapSize);
		unsigned int max_leaves = 1 << height;
		for (int i = 1; i <= heapSize; i = 2 * i) { //i is the index of the first node at the level 
			int last_blank = max_leaves / i;
			int beign_blank = last_blank - 1;
			int middle_blank = beign_blank + last_blank;
			int last = 2 * i - 1; //the index of the last node at the level
			for (int k = 0; k < beign_blank; k++) //print blank at beginning
				cout << ' ';
			for (int j = i; j <= last && j <= heapSize; j++) {
				cout << A[j];
				for (int k = 0; k < middle_blank; k++) //print blank after word
					cout << ' ';
			}
			cout << endl;
		}
	}
};

int main() {
	minHeapPriorityQueue wordsQueue;

	//test boundary condition
	cout << "Test boundary condition" << endl;
	wordsQueue.printHeap(); //print the heap-based priority queue in heap structure
	cout << "number: " << wordsQueue.number() << endl;
	wordsQueue.remove();
	cout << "search \"aaa\": " << wordsQueue.search("aaa") << endl;

	//test add operation
	cout << endl << endl;
	cout << "Test add operation" << endl;
	wordsQueue.add("aaa");
	wordsQueue.add("a");
	wordsQueue.add("bbb");
	wordsQueue.add("ccc");
	wordsQueue.add("bcc");
	wordsQueue.add("bee");
	wordsQueue.add("dde");
	wordsQueue.add("gggz");
	cout << "add some words" << endl;
	wordsQueue.printHeap();
	cout << "number: " << wordsQueue.number() << endl; //test number operation
	cout << "search \"aaa\": " << wordsQueue.search("aaa") << endl;
	cout << "add a word \"A\"" << endl;
	wordsQueue.add("A");
	wordsQueue.printHeap();
	cout << "number: " << wordsQueue.number() << endl;
	cout << "search \"A\": " << wordsQueue.search("A") << endl;
	cout << "search \"aaa\": " << wordsQueue.search("aaa") << endl;
	//test adding identical word
	cout << endl;
	cout << "Test adding identical word" << endl;
	cout << "add \"aaa\" again" << endl;
	wordsQueue.add("aaa"); 
	wordsQueue.printHeap();
	cout << "number: " << wordsQueue.number() << endl; //test number operation
	cout << "search \"A\": " << wordsQueue.search("A") << endl;
	cout << "search \"aaa\": " << wordsQueue.search("aaa") << endl;

	//test remove operation
	cout << endl << endl;
	cout << "Test remove operation" << endl;
	wordsQueue.remove();
	cout << "remove" << endl;
	wordsQueue.printHeap();
	cout << "number: " << wordsQueue.number() << endl;
	cout << "search \"A\": " << wordsQueue.search("A") << endl;
	cout << "search \"aaa\": " << wordsQueue.search("aaa") << endl;
	wordsQueue.remove();
	cout << "remove" << endl;
	wordsQueue.printHeap();
	cout << "number: " << wordsQueue.number() << endl;
	cout << "search \"A\": " << wordsQueue.search("A") << endl;
	cout << "search \"aaa\": " << wordsQueue.search("aaa") << endl;

	return 0;
}