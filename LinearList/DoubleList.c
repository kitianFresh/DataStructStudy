#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1

typedef char ElemType;
typedef struct DNode{
	ElemType data;
	struct DNode *prior,*next;
}DNode, *DoubleList;

void InitDoubleList(DoubleList *L);

void CreateFromTail(DoubleList L);

void CreateFromHead(DoubleList L);

int InsDoubleList(DoubleList L, int i, ElemType e);

int DelDoubleList(DoubleList L, int i, ElemType *e);

void PrintList(DoubleList L);

int main(){
	DoubleList DL;
	InitDoubleList(&DL);
	CreateFromTail(DL);
	//CreateFromHead(DL);
	PrintList(DL);
	ElemType e;
	int i;
	printf("请输入元素和要插入的位置(位置-1结束)：\n");
	/*
	 *
	 *
		3、在用"%c"输入时，空格和“转义字符”均作为有效字符。
		例：
		scanf("%c%c%c",&c1,&c2,&c3); 
		输入：a□b□c↙ 
		结果：a→c1，□→c2，b→c3 (其余被丢弃)

		所以在循环中慎重使用scanf接受数据，特别是带字符的数据，都是数值类
		型就比较好，scanf会过滤掉一些非数值字符，但是如果控制可以接受字符
		，那么你敲击的' ' '\n' '\t' 都作为字符在缓冲区中被scanf不加过滤的
		接受了。不要想着屏幕，想着键盘一次敲击都是一次中断，每一次字符都送
		往缓冲区了。屏幕和你的程序scanf是异步的
	*/
	//这里上一次的回车键(\r\n)中的\n被下次的scanf接受了，会得到意外的结果
	//scanf可以认为是对getchar的封装函数
	scanf("%c%d", &e, &i);
	while(1){
		if(i == -1) break;
		InsDoubleList(DL, i, e);
		PrintList(DL);
		scanf("%c%d", &e, &i);
		getchar();//用来过滤掉回车，防止scanf扫描
	}

	printf("请输入要删除的节点号i(-1节结束)\n");
	while(scanf("%d", &i)){
		if(-1 == i) break;
		DelDoubleList(DL,i,&e);
		printf("%c\n", e);
		PrintList(DL);
	}
	return 0;
}

void PrintList(DoubleList L){
	while(L->next){
		L = L->next;//指向下个数据结点
		printf("%c\t",L->data);
	}
	printf("\n");
}

void InitDoubleList(DoubleList *L){
	*L = (DoubleList)malloc(sizeof(DNode));
	(*L)->next = NULL;
	(*L)->prior = NULL;
}

void CreateFromTail(DoubleList L){
	ElemType c;
	DNode *rear;
	rear = L;
	while('$' != (c=getchar())){
		if(' '==c || '\n'==c || '\t'==c) continue;
		DNode *s = (DNode*)malloc(sizeof(DNode));
		s->data = c;
		s->prior = rear;
		s->next = rear->next;
		rear->next = s;
		rear = s;
	}
}

void CreateFromHead(DoubleList L){
	ElemType c;
	while('$' != (c=getchar())){
		if(' '==c || '\n'==c || '\t'==c) continue;
		DNode *s = (DNode*)malloc(sizeof(DNode));
		s->data = c;
		//空链表首次操作
		if(L->next == NULL){
			s->next = L->next;
			s->prior = L;
			L->next = s;
		}
		else{
			s->next = L->next;
			L->next->prior = s;
			s->prior = L;
			L->next = s;
		}
	}
}

int InsDoubleList(DoubleList L, int i, ElemType e){
	int j = 0;
	DNode *pre = L;
	if(i<=0){
		printf("i不合法\n");
		return ERROR;
	} 
	while(pre && j<i-1){
		j ++;
		pre = pre->next;
	}
	if(pre){
		DNode *s = (DNode*)malloc(sizeof(DNode));
		s->data = e;
		//如果不是插入最后节点，则将后续节点的前驱指针指向该新节点
		if(pre->next){
			pre->next->prior = s;
		}
		s->next = pre->next;
		s->prior = pre;
		pre->next = s;
		return OK;
	}

	return ERROR;
}

int DelDoubleList(DoubleList L, int i, ElemType *e){
	int j = 0;
	DNode *pre, *p;
	pre = L;
	if(i<=0){
		printf("参数不合法\n");
		return ERROR;
	}
	//当i链表长时,不做操作
	while(pre && j<i-1){
		j ++;
		pre = pre->next;
	}

	if(pre){
		//如果前驱节点是最后一个节点，直接返回
		if((p = pre->next) == NULL) return ERROR;
		//如果要删除的节点是最后一个节点
		if(p->next == NULL){
			pre->next = NULL;
		}
		else{
			pre->next = p->next;
			p->next->prior = pre;
		}
		*e = p->data;
		free(p);
		return OK;
	}
	return ERROR;
}


