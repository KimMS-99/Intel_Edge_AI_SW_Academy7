#include "MyStack.h"

void MyStack::push(int n) {
	if(tos == 99) 
		throw "Stack Full";
	tos++;
	data[tos] = n;
}

int MyStack::pop() {
	if(tos == -1) 
		throw "Stack Empty";
	int rData = data[tos--];
	return rData;
}