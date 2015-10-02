#include<stdio.h>
#include "SeqStack.h"

int Match(char L, char R){
	if((L == '(' && R == ')') || (L == '[' && R == ']') || 
			(L == '{' && R == '}')){
		return OK;
	}
	return ERROR;
}

int BracketMatch(char *str){
	SeqStack S;
	int i;
	char ch;
	InitStack(&S);
	while(*str != '\0'){
		switch(*str){
			case '(':
			case '[':
			case '{':
				Push(&S,*str);
				printf("%c进栈\n",*str);
				break;
			case ')':
			case ']':
			case '}':
				if(IsEmpty(&S)) return ERROR;
				else {
					Pop(&S,&ch);
					printf("%c出栈\n",ch);
					if(!Match(ch,*str)) return ERROR;
				}
				break;
			default:
				return ERROR;
		}
		str ++;
	}
	if(IsEmpty(&S)) return OK;
	else return ERROR;
}

int main(){
	//char *str;scanf("%s",str);是错误的写法；scanf是把缓冲区中的字符串放入
	//str所指向的空间，这里str只是申明的一个指针，没有初始化空间，所以会出
	//现越界错误。应该写成char *str = (char*)malloc(30*sizeof(char));或者
	//定义数组；
	char str[30];
	scanf("%s",str);
	if(BracketMatch(str))
		printf("成功\n");
	else 
		printf("失败\n");
	return 0;
}
