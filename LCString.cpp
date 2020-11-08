/*a DP algorithm for the longest common substring of two strings, where a substring must be consecutive in the given string.
For example, if X is ABCBDAB and Y is BDCABA, then their longest common substring can be AB or BD.*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

vector<vector<int> > LCString(const string X, const string Y) { //generate a table "c"
	int m = X.length();
	int n = Y.length();
	vector<vector<int> > c;
	c.resize(m + 1);
	for (int i = 0; i <= m; i++)
		c[i].resize(n + 1);

	//i=0 or j=0
	for (int i = 1; i <= m; i++)
		c[i][0] = 0;
	for (int j = 0; j <= n; j++)
		c[0][j] = 0;

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (X[i - 1] == Y[j - 1])
				c[i][j] = c[i - 1][j - 1] + 1;
			else c[i][j] = 0;
		}
	}
	return c;
}

string findAndPrint(const string X, const vector<vector<int> >& c) { //find one optimal solution from the table "c" and print it with its length.
	int m = c.size() - 1;
	int n = c[0].size() - 1;
	int max = 0; //the longest length
	int max_i = 0; //the index of the last character of the longest common substring in table c

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (c[i][j] > max) {
				max = c[i][j];
				max_i = i;
			}
		}
	}
	cout << "longest length: " << max << endl;
	cout << "a longest common substring: " << X.substr(max_i - max, max) << endl; //note the index of string starts from 0

	return X.substr(max_i - max, max);
}

void printTable(const string& X, const string& Y, const vector<vector<int> >& c) {
	int m = c.size() - 1;
	int n = c[0].size() - 1;

	cout << "table c (the number matrix): "<< endl;
	cout << "    ";
	for (int j = 0; j < n; j++)
		cout << Y[j] << ' ';
	cout << endl;

	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			if (i > 0 && j == 0) {
				cout << X[i - 1] << ' ';
				cout << c[i][j] << ' ';
			}
			else if (i == 0 && j == 0) {
				cout << "  " << c[i][j] << " ";
			}
			else {
				cout << c[i][j] << ' ';
			}
		}
		cout << endl;
	}
}

void test(const string& X, const string& Y) {
	vector<vector<int> > table;
	cout << "X: " << X << endl;
	cout << "Y: " << Y << endl;
	table = LCString(X, Y);
	printTable(X, Y, table);
	findAndPrint(X, table);
	cout << endl;
}

int main() {
	test("ABCBDAB", "BDCABA");
	test("ABCBADB", "BCBAAB");
	test("ABCDEFZG", "ABCDEFG");
	test("Helloworld!", "Hello,world!");
	return 0;
}