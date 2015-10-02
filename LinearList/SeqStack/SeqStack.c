#include<stdio.h>
#include "SeqStack.h"

void InitStack(SeqStack *S){
	S->top = -1;
}

int IsFull(SeqStack *S){
	return S->top == STACK_SIZE-1;
}

int IsEmpty(SeqStack *S){
	return S->top == -1;
}

int Push(SeqStack *S, StackElementType x){
	if(IsFull(S)){
		printf("栈已满\n");
		return ERROR;
	}
	S->top ++;
	S->elem[S->top] = x;
	return OK;
}

int Pop(SeqStack *S, StackElementType *x){
	if(IsEmpty(S)){
		printf("栈已空\n");
		return ERROR;
	}
	*x = S->elem[S->top];
	S->top --;
	return OK;
}

int GetTop(SeqStack *S, StackElementType *x){
	if(IsEmpty(S)){
		printf("栈已空\n");
		return ERROR;
	}
	*x = S->elem[S->top];
	return OK;
}
