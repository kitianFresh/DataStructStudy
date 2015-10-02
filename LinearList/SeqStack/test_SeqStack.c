#include "SeqStack.h"
#include<stdio.h>

int main(){
	SeqStack S;
	InitStack(&S);
	char e;
	while((e = getchar()) != '#'){
		//过滤掉回车，制表符，空格
		if('\t'==e || '\n'==e || ' '==e) continue;
		if(!Push(&S,e)) break;
	}

	while(Pop(&S, &e)){
		printf("%c\t", e);
	}
	printf("\n");
	return 0;
}
