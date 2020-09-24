#define _CRT_SECURE_NO_WARNINGS
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
class A {
public:
	int v;
	A(int n) {
		v = n;
		cout << "constructed" << endl;
	}
	A(const A& a) {
		v = a.v;
		cout << "test" << endl;
	}
	void func();
	~A() {
		cout << "deleted" << endl;
	}
};
void A::func() {
	cout << 1 << endl;
}

class MyClass
{
public:
	static MyClass object;
	char str[22] = "Matryoshka Prohibited";
	//balabala...
} foo, bar;

MyClass MyClass::object;

class base {
public:
	int n;
	virtual void func() {
		printf("base\n");
	}
	virtual void func2() = 0;
	virtual ~base() { cout << "base" << endl; };
	base() { };
};
class Derived :public base {
	~Derived() { cout << "derived" << endl; }
	void func2() {};
};


class B {
private:
	int nBVal;
public:
	int a;
};

class D :public B{
public:
	int a;
};

class test {
	int n;
public:
	test(int _n) :n(_n) {};
	friend bool operator<(const test &a,const test& b) {
		return (a.n%10) < b.n%10;
	}
	
	friend ostream& operator <<(ostream & o,const test& a)  {
		o << a.n;
		return o;
	}
};

template <class T>
void Print( T begin,  T end) {
	for (; begin != end; ++begin) {
		cout << *begin << " ";
	}
	cout << endl;
}


void fun(int& value) { value=value-1; }
int main() {
	int a1[] = { 1,2,3,4,5,6,7,8,9,10 };
	vector<int> v(a1, a1 + 10);
	for_each(v.begin(), v.end(), fun);
	ostream_iterator<int> output(cout, " ");
	copy(v.begin(), v.end(), output);
}
