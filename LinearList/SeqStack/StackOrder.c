#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "SeqStack.h"
#include "../SeqQueue/SeqQueue.h"



/*递归的方法统计n个元素依次入栈之后的出栈顺序总的类数之和*/
int PopStackOrderSum(int n);
/*非递归方法统计n个元素一次入栈之后的出栈顺序总的类别数之和*/
int PopStackOrderSum1(int n);

/*递归的方法，输出所有可能的出栈顺序*/
void PopStackOrder(StackElementType *src, SeqStack *S, StackElementType *dest, int index, int size);

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

int PopStackOrderSum1(int n){
	int k,i;
	if(0 == n) return 1;
	if(1 == n) return 1;
	int *s = (int*)malloc(sizeof(int)*(n+1));
	//一定要清零，因为后面有s[k]直接使用，否则这块内存里的数据直接使用
	//会有意想不到的事发生
	memset(s,0,sizeof(int)*(n+1));
	s[0] = 1; s[1] = 1;
	for(k=2;k<=n;k++)
		for(i=0;i<k;i++)
			s[k] += s[i]*s[k-i-1];
	return s[n];
}

int main(){
	int n;
	scanf("%d", &n);
	printf("Rrecursive : sum = %d\n", PopStackOrderSum(n));
	printf("Non-recursive : sum = %d\n", PopStackOrderSum1(n));

	SeqStack S;
	StackElementType dest[4]={0,0,0,0};
	StackElementType src[3] = {1,2,3};
	PopStackOrder(src,&S,dest,0,sizeof(src)/sizeof(StackElementType));
	return 0;
}

void PopStackOrder(StackElementType *src, SeqStack *S, StackElementType *dest, int index, int size){
	static int count = 0;
	SeqStack temp;
	QueueElementType e;
	int i;
	if(index >= size){
		printf("%d:",++count);
		
		/*打印dest*/
		for(i=1;i<=dest[0];i++){
			printf("\t%d",dest[i]);
		}

		/*打印栈中元素*/
		for(i=0;i<=S->top;i++){
			printf("\t%d",S->elem[S->top-i]);
		}
		printf("\n");
		return ;
	}
	Push(S,src[index]);
	PopStackOrder(src,S,dest,index+1,size);/*遍历左子树*/
	Pop(S,&e);/*恢复现场，让栈中的栈顶元素弹出，返回到上一步*/
	if(!StackIsEmpty(S)){
		Pop(S,&e);
		dest[++dest[0]] = e;
		PopStackOrder(src,S,dest,index,size);
		//恢复现场，让队列中的最后一个元素再弹回到栈中
		e = dest[dest[0]];
		Push(S,e);
		dest[0]--;
	}
}
