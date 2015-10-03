#include<stdio.h>
#include "SeqQueue.h"

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
