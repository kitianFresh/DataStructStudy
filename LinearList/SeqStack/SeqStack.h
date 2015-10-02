#ifndef STACK_H
#define STACK_H
#define STACK_SIZE 50
#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0

typedef char StackElementType;
typedef struct {
	StackElementType elem[STACK_SIZE];
	int top;
}SeqStack;

void InitStack(SeqStack *S);

int Push(SeqStack *S, StackElementType x);

int Pop(SeqStack *S, StackElementType *x);

int GetTop(SeqStack *S, StackElementType *x);

int IsEmpty(SeqStack *S);

int IsFull(SeqStack *S);

#endif

