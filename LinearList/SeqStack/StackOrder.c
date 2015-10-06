#include<stdio.h>
#include "SeqStack.h"

/*递归的方法统计n个元素依次入栈之后的出栈顺序总的类数之和*/
int PopStackOrderSum(int n);

/*递归的方法，输出所有可能的出栈顺序*/
void PopStackOrder(StackElementType *arr_push, int num);

int PopStackOrderSum(int n){
	int i;
	int sum = 0;
	if(0 == n) return 1;
	if(1 == n) return 1;
	for(i=0;i<n;i++){
		sum+=PopStackOrderSum(i) * PopStackOrderSum(n-i-1);
	}
	return sum;
}

int main(){
	int n;
	scanf("%d", &n);
	printf("sum = %d\n", PopStackOrderSum(n));
	return 0;
}

void PopStackOrder(StackElementType *arr_push, int num){
}
