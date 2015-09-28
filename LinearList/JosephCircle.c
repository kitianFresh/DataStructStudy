/*
 	问题描述：编号为1、2、3、...、N的N个人按顺时针方向围坐一圈，每人持有一个
 	密码（正整数）。从指定编号为1的人开始，按顺时针方向自1开始顺序报数，报
	到指定数M时停止报数，报M的人出列，并将他的密码作为新的M值，从他在顺时针
	方向的下一个人开始，重新从1报数，依此类推，直至所有的人全部出列为止。
 *	
 *	使用循环单链表完成的约瑟夫环问题，只适合数据量较小时候做模拟，算法时间复	杂度是O（mn）。如果不要求模拟过程，只求最后结果的话，可以用数学方法递推
 *
 */
#include<stdio.h>
#include<stdlib.h>

typedef struct CNode{
	int id;
	int number;
	struct CNode *next;
}CNode,*CircleList;

void InitList(CircleList *L);

int CreateFromTail(CircleList L);

int Joseph(CircleList L, int seed);

void PrintList(CircleList L);

int ListLength(CircleList L);

int main(){
	CircleList L;
	int seed;
	InitList(&L);
	printf("请按顺序输入密码(以空格隔开):");
	CreateFromTail(L);
	PrintList(L);
	printf("请输入初始密码:");
	scanf("%d",&seed);
	Joseph(L,seed);
	return 0;
}

void InitList(CircleList *L){
	*L = (CNode*)malloc(sizeof(CNode));
	(*L)->next = *L;
}

void PrintList(CircleList L){
	CNode *p = L;
	while(p->next != L){
		p = p->next;
		printf("%d:%d\t", p->id, p->number);
	}
	printf("\n");
}

int ListLength(CircleList L){
	CNode *p = L;
	int l = 0;
	while(p->next != L){
		p = p->next;
		l ++;
	}
	return l;
}

int CreateFromTail(CircleList L){
	CNode *s,*rear;
	rear = L;
	int number,id;
	id = 0;
	while(scanf("%d",&number)){
		if(-1 == number) break;
		s = (CNode*)malloc(sizeof(CNode));
		s->id = ++id;
		s->number = number;
		s->next = rear->next;
		rear->next = s;
		rear = s;
	}
}

int Joseph(CircleList L, int seed){
	CNode *p,*temp,*pre;
	p = L;
	int k,len;
	if((len=ListLength(L)) == 0) return 0; 
	//里面所有的操作都忽略头节点，他不参与计数
	while(len != 1){
		k = 0;
		seed = seed%len;//去掉多余的循环
		//报数,保存前驱
		while(k<seed){
			pre = p;
			p = p->next;
			if(p == L) continue;//是头节点直接跳过
			k ++;
		}
		//找到剔除，更新种子
		temp = p;
		seed = temp->number;
		printf("%d\t",temp->id);
		pre->next = temp->next;
		len --;//长度减小1
		free(temp);
		//因为p所指向的位置已经释放了，从前驱开始再重新报数
		p = pre;
	}
	//输出最后一个
	if(p == L) p = p->next;
	printf("%d\n", p->id);
	return 1;
}
