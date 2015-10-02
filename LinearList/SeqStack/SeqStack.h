#ifndef STACK_H
#define STACK_H
#define STACK_SIZE 50
#define ERROR 0
#define OK 1

typedef char StackElementType;
typedef struct {
	StackElementType elem[STACK_SIZE];
	int top;
}SeqStack;

void InitStack(SeqStack *S);

int Push(SeqStack *S, StackElementType x);

int Pop(SeqStack *S, StackElementType *x);

int GetTop(SeqStack *S, StackElementType *x);
#endif

