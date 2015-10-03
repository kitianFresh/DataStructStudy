#ifndef SEQQUEUE_H
#define SEQQUEUE_H

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
#endif
