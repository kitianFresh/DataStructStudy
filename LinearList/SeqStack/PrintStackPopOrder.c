#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "SeqStack.h"

/*递归的方法，输出所有可能的出栈顺序*/
void PopStackOrder(StackElementType *src, SeqStack *S, StackElementType *dest, int index, int size);

/*数组的第0个元素不使用，用于存放数组中元素的个数*/
void InitArray(StackElementType *arr,int n){	
	memset(arr,0,sizeof(StackElementType)*n);
}


int main(){
	int n,i;
	SeqStack S;
	InitStack(&S);
	StackElementType *dest;
	StackElementType *src;
	printf("请输入元素个数：");
	scanf("%d",&n);
	dest = (StackElementType*)malloc(sizeof(StackElementType)*(n+1));
	src = (StackElementType*)malloc(sizeof(StackElementType)*n);
	InitArray(dest,n+1);
	for(i=0;i<n;i++){
		src[i] = i+1;
	}

	PopStackOrder(src,&S,dest,0,n);
}
void PopStackOrder(StackElementType *src, SeqStack *S, StackElementType *dest, int index, int size){
	static int count = 0;
	int i = 0;
	StackElementType e;
	for(i=1;i<=dest[0];i++){
		printf("%d",dest[i]);
	}
	printf(":");
	for(i=0;i<=S->top;i++){
		printf("%d",S->elem[i]);
	}
	printf(":");
	for(i=index;i<size;i++){
		printf("%d",src[i]);
	}
	printf("\n");

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

	//无论是遍历左子树还是右子树，返回到上一层时，都必须保证不改变
	//刚开始进栈时输入队列src，栈S，输出队列dest的状态

	Push(S,src[index]);//选择进栈，然后遍历左子树
	PopStackOrder(src,S,dest,index+1,size);/*遍历左子树*/
	//左子树遍历完成，也就是第一种选择做完，现在该做第二种选择，也就是出栈
	
	//但是左子树的遍历是进栈操作，此时的栈已经被破坏了，所以需要恢复到本层次
	//最开始的状态
	Pop(S,&e);/*恢复现场，让栈中的栈顶元素弹出，返回到本层的开始状态*/

	//选择出栈，遍历右子树
	if(!StackIsEmpty(S)){
		//出栈，元素进入输出队列
		Pop(S,&e);
		dest[++dest[0]] = e;
		PopStackOrder(src,S,dest,index,size);

		//恢复现场，让队列中的最后一个元素再回到栈中，以返回到本层开始状态
		e = dest[dest[0]];
		Push(S,e);
		dest[0]--;
	}
}
