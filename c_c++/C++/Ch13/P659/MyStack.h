#ifndef MYSTACK_H
#define MYSTACK_H

class MyStack
{
	int data[100];
	int tos;

public:
	MyStack() { tos = -1; }
	void push(int n) throw(char *);
	int pop() throw(char *);
};

#endif