#include<stdio.h>
#include"SeqQueue.h"

void InitQueue(SeqQueue *Q){
	Q->front = Q->rear = 0;
}

int QueueIsFull(SeqQueue *Q){
	return (Q->rear+1)%MAXSIZE == Q->front;
}

int QueueIsEmpty(SeqQueue *Q){
	return Q->rear == Q->front;
}

int EnterQueue(SeqQueue *Q, QueueElementType x){
	if(QueueIsFull(Q)){
		printf("队列已满\n");
		return 0;
	}
	Q->elem[Q->rear] = x;
	Q->rear = (Q->rear+1)%MAXSIZE;
	return 1;
}

int DeleteQueue(SeqQueue *Q, QueueElementType *x){
	if(QueueIsEmpty(Q)){
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
