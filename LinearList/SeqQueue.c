#include<stdio.h>
#define MAXSIZE 10

typedef int QueueElementType;
typedef struct {
	QueueElementType elem[MAXSIZE];
	int front;
	int rear;
}SeqQueue;

void InitQueue(SeqQueue *Q);
int EnterQueue(SeqQueue *Q, QueueElementType x);
int DeleteQueue(SeqQueue *Q, QueueElementType *x);
int IsFull(SeqQueue *Q);
int IsEmpty(SeqQueue *Q);
void PrintQueue(SeqQueue *Q);

int main(){
	SeqQueue Q;
	InitQueue(&Q);
	int e;
	while(scanf("%d",&e)){
		if(-1 == e) break;
		EnterQueue(&Q,e);
	}
	PrintQueue(&Q);
	while(!IsEmpty(&Q)){
		DeleteQueue(&Q,&e);
		printf("%d\t", e);
	}
	printf("\n");
	return 0;
}

void InitQueue(SeqQueue *Q){
	Q->front = Q->rear = 0;
}

int IsFull(SeqQueue *Q){
	return (Q->rear+1)%MAXSIZE == Q->front;
}

int IsEmpty(SeqQueue *Q){
	return Q->rear == Q->front;
}

int EnterQueue(SeqQueue *Q, QueueElementType x){
	if(IsFull(Q)){
		printf("队列已满\n");
		return 0;
	}
	Q->elem[Q->rear] = x;
	Q->rear = (Q->rear+1)%MAXSIZE;
	return 1;
}

int DeleteQueue(SeqQueue *Q, QueueElementType *x){
	if(IsEmpty(Q)){
		printf("队列已空\n");
		return 0;
	}
	*x = Q->elem[Q->front];
	Q->front = (Q->front+1)%MAXSIZE;
	return 1;
}

void PrintQueue(SeqQueue *Q){
	int i = Q->front;
	while(i != Q->rear){
		printf("%d\t", Q->elem[i]);
		i = (i+1)%MAXSIZE;
	}
	printf("\n");
}
