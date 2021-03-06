/*
 *实现一个算法，将无括号表达式转换成逆波兰式；
 *
 *copyright by kinny tian
 *
 */

#include<stdio.h>
#include"SeqStack.h"

void reversePolishNotation(char *exp, char *rpn);


int prior[128];

void InitPriority(int *p){
	p['#'] = 0;
	p['+'] = 1;
	p['-'] = 1;
	p['*'] = 2;
	p['/'] = 2;
	p['^'] = 3;

	p['('] = 0;
	//这里做括号优先级默认为0,表示任何一个运算符都优先级都大于'('，因为是if
	//条件控制遇到'('立即入栈，所以总是（在前，而后进入的符号在后，就可以
	//复用comparePrior了，否则真正的优先级是一种偏序关系，关系符号用<*
	//表示，'('<*'其他'；'其他'<*'(',要使用编译原理里的偏序关系表来
	//实现comparePrior，这里只是实现一个简单的功能，所以没有打一个二维的
	//偏序关系表
}

int IsOptr(char ch){
	switch(ch){
		case '#':
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
		case '(':
		case ')':
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

int main(){
	char exp[20];
	char rpn[20];
	scanf("%s",exp);
	reversePolishNotation(exp,rpn);
	printf("%s\n",rpn);
	return 0;
}
//该方法是利用表达式求值ExpEvaluation.c中的过程，每次遇到运算数时，运算数
//压入运算数栈OVS同时将运算数保存到rpn中，每次求值时，将符号栈OPTR弹出的符
//号保存到rpn中
void reversePolishNotation(char *exp, char *rpn){
	SeqStack OPTR;
	char ch;
	int i=0;
	InitStack(&OPTR);
	Push(&OPTR, '#');
	GetTop(&OPTR,&ch);
	while(*exp!='#' || ch != '#'){
		if(IsOptr(*exp)){
			if(*exp == '('){
				Push(&OPTR,*exp);
				exp ++;
			}
			else if(*exp == ')'){
				Pop(&OPTR,&ch);
				//不断出栈直到匹配到'('
				while(ch != '('){
					rpn[i++] = ch;
					Pop(&OPTR,&ch);
				}
				exp ++;
			}
			else {
				switch(ComparePrior(*exp,ch)){
					case '<':
					case '=':
						Pop(&OPTR,&ch);
						rpn[i++] = ch;//将该运算符存入rpn中；
						break;
					case '>':
						Push(&OPTR,*exp);
						exp ++;
						break;
				}
			}
		}
		else {
			rpn[i++] = *exp;//将该运算数存入rpn；
			exp ++;
		}
		GetTop(&OPTR,&ch);
	}
	rpn[i] = '\0';
}
