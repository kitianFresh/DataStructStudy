/*
 *
 *简易版计算无括号表达式的值，由于没有做词法分析，所以只能计算个位数，
 但是可以用来表示表达式求值的过程。如果想计算整数和浮点数的加减乘除，
 可以自定义运算数栈的元素类型为一个结构体，里面包含一个可以容纳int和double
 类型的union；
 *
 *
 *
 *
 */


#include<stdio.h>
#include"SeqStack.h"

int prior[128];

void InitPriority(int *p){
	p['#'] = 0;
	p['+'] = 1;
	p['-'] = 1;
	p['*'] = 2;
	p['/'] = 2;
}

int IsOptr(char ch){
	switch(ch){
		case '#':
		case '+':
		case '-':
		case '*':
		case '/':
			return 1;
		default:
			return 0;
	}
}

char ComparePrior(char c1, char c2){
	InitPriority(prior);
	if(prior[c1] < prior[c2]){
		return '<';
	}
	else if(prior[c1] == prior[c2]){
		return '=';
	}
	else
		return '>';
}

char Compute(char l, char r, char opt){
	switch(opt){
		case '+':
			return (l-48) + (r-48) + 48;
			break;
		case '-':
			return (l-48) - (r-48) + 48;
			break;
		case '*':
			return (l-48) * (r-48) + 48;
			break;
		case '/':
			return (l-48) / (r-48) + 48;
			break;
	}
}

int ExpEvaluate(char *exp, char *result){
	SeqStack OPTR,OVS;//定义运算符栈和运算数栈
	char ch,l,r,temp;
	InitStack(&OPTR);
	InitStack(&OVS);
	Push(&OPTR,'#');//为了计算方便，先将一个'#'入栈
	GetTop(&OPTR,&ch);
	while(*exp != '#' || ch != '#'){
		if(IsOptr(*exp)){
				switch(ComparePrior(*exp,ch)){
					case '=':
					case '<':
						Pop(&OVS,&r);Pop(&OVS,&l);
						Pop(&OPTR, &ch);
						temp = Compute(l,r,ch);
						printf("计算%c\n",temp);
						Push(&OVS,temp);
						break;
					case '>':
						Push(&OPTR,*exp);
						printf("%c进入OPTR栈\n",*exp);
						exp ++;
						break;
				}
		}
		else {
			Push(&OVS,*exp);
			printf("%c进入OVS栈\n",*exp);
			exp ++;
		}
		GetTop(&OPTR,&ch);
	}
	Pop(&OVS,result);
	return OK;
}

int main(){
	char str[10];
	char result;
	scanf("%s", str);
	ExpEvaluate(str,&result);
	printf("result = %c\n", result);
	return 0;
}
