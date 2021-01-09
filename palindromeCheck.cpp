//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h> //rand()

using namespace std;

bool palindromeCheck(head) {
	node x = head;
	create stack S; //the type of the elements in S is head.data
	while (x != NIL) {
		S.push(x.data);
		x = x.next;
	}
	x = head;
	while (x != NIL) {
		if (x.data != S.pop())
			return false;
		x = x.next;
	}
	return true;
}

bool palindromeCheck_half(head, length) {
	mid = length / 2;
	node x = head;
	create stack S;
	for (i = 1; i <= mid; i++) {
		S.push(x);
		x = x.next;
	}
	if (length % 2 == 1) { //skip the middle one if the length is odd
		x = x.next;
	}
	while (x != NIL) {
		if (x != S.pop())
			return false;
		x = x.next;
	}
	return true;
}

int main() {

	return 0;
}