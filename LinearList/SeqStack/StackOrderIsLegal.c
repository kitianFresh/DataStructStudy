#include<stdio.h>
#include"SeqStack.h"

int StackOrderIsLegal(StackElementType *input,StackElementType *output,int n);

int main(){
	StackElementType input[] = {1,2,3,4};
	StackElementType output[] = {2,3,4,1};
	if(StackOrderIsLegal(input,output,4)) printf("Legal!\n");
	else printf("Illegal!\n");
	return 0;
}

int StackOrderIsLegal(StackElementType *input,StackElementType *output,int n){
	SeqStack S;
	StackElementType e;
	int i,j;
	i = j = 0;
	InitStack(&S);
	while(j<n){
		if(StackIsEmpty(&S)){
			Push(&S,input[i]);
			printf("Push%d\t",input[i]);
			i ++;
			continue;
		}
		GetTop(&S,&e);
		if(e == output[j]) {
			Pop(&S,&e);
			printf("Pop%d\t",e);
			i ++;
			j ++;
		}
		else if(i < n){
			Push(&S,input[i]);
			printf("Push%d\t",input[i]);
			i ++;
		}
		else {
			break;
		}
	
	}
	if(j < n) return 0;
	return 1;
}
