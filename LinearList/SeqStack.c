#include<stdio.h>
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

int main(){
	SeqStack S;
	InitStack(&S);
	char e;
	while((e = getchar()) != '#'){
		//过滤掉回车，制表符，空格
		if('\t'==e || '\n'==e || ' '==e) continue;
		if(!Push(&S,e)) break;
	}

	while(Pop(&S,&e)){
		printf("%c\t", e);
	}
	printf("\n");
	return 0;
}

void InitStack(SeqStack *S){
	S->top = -1;
}

int Push(SeqStack *S, StackElementType x){
	if(S->top == STACK_SIZE-1){
		printf("栈已满\n");
		return ERROR;
	}
	S->top ++;
	S->elem[S->top] = x;
	return OK;
}

int Pop(SeqStack *S, StackElementType *x){
	if(S->top == -1){
		printf("栈已空\n");
		return ERROR;
	}
	*x = S->elem[S->top];
	S->top --;
	return OK;
}

int GetTop(SeqStack *S, StackElementType *x){
	if(S->top == -1){
		printf("栈已空\n");
		return ERROR;
	}
	*x = S->elem[S->top];
	return OK;
}
