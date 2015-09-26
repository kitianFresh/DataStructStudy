/*
 1.链栈具有无限制（当然是不超过进程的堆空间大小）的增长空间，
 而顺序栈最大持续增长空间是有限的。
 2.链栈的存储空间是动态申请，程序运行时期动态申请，
 顺序栈的存储空间是静态的，在编译时期确定。
 3.链栈限定在一端的操作通过Push和Pop封装，由于是先进后处的特点，因此采用头插法进栈，每次出栈只需要删除第一个节点，不需要制定额外的top指向栈顶
 *
 */


#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
typedef char StackElementType;
typedef struct Node{
	StackElementType data;
	struct Node *next;
}LinkStackNode, *LinkStack;

void InitStack(LinkStack *top);

int Push(LinkStack top, StackElementType x);

int Pop(LinkStack top, StackElementType *x);

int GetTop(LinkStack top,StackElementType *x);

int main(){
	LinkStack top;
	InitStack(&top);
	char e;
	while((e=getchar()) != '#'){
		if('\t'==e || '\n'==e || ' '==e) continue;
		if(!Push(top,e)) break;
	}

	while(Pop(top,&e)){
		printf("%c\t",e);
	}
	printf("\n");
}

void InitStack(LinkStack *top){
	*top = (LinkStackNode *)malloc(sizeof(LinkStackNode));
	(*top)->next = NULL;
}

int Push(LinkStack top, StackElementType x){
	LinkStackNode *temp;
	temp = (LinkStackNode*)malloc(sizeof(LinkStackNode));
	if(!temp) return ERROR;
	temp->data = x;
	temp->next = top->next;
	top->next = temp;
	return OK;
}

int Pop(LinkStack top, StackElementType *x){
	if(NULL == top->next){
		printf("栈已空\n");
		return ERROR;
	}
	LinkStackNode *temp;
	temp = top->next;
	*x = temp->data;
	top->next = temp->next;
	free(temp);
	return OK;
}

int GetTop(LinkStack top, StackElementType *x){
	if(NULL == top->next){
		printf("栈已空\n");
		return ERROR;
	}
	*x = top->next->data;
	return OK;
}
