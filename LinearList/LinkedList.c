#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
typedef char ElemType;
typedef struct Node {
	ElemType data;
	struct Node* next;
}Node, *LinkedList;

/*初始化链表,注意这里必须使用二级指针*/
void InitList(LinkedList *L);

/*头插法建立单链表*/
void CreateFromHead(LinkedList L);

/*尾插法建立单链表*/
void CreateFromTail(LinkedList L);

/*在单链表中查找第i个结点*/
Node* Get(LinkedList L, unsigned int i);

/*在单链表中定位值为key的结点*/
Node* Locate(LinkedList L, ElemType key);

/*求单链表的长度*/
unsigned int ListLength(LinkedList L);

/*在单链表第i个位置插入值为e的结点*/
int InsList(LinkedList L, unsigned int i, ElemType key);

/*删除单链表第i个位置的结点*/
int DelList(LinkedList L, unsigned int i, ElemType *e);

/*合并两个有序递增链表，不使用额外空间，将LA和LB合并到LC上,返回LC的地址,保证LC也有序递增，LC采用尾插法*/
LinkedList MergeList(LinkedList LA, LinkedList LB);

/*打印链表元素*/
void PrintList(LinkedList L);

int main(){
	Node *s;
	LinkedList L;
	InitList(&L);
	//CreateFromHead(L);
	CreateFromTail(L);
	PrintList(L);
	int i;
	scanf("%d", &i);
	while(i!=-1){
		if(NULL != (s=Get(L, i))){
			printf("%c\n", s->data);
		}
		if(NULL != (s=Locate(L, 'e'))){
			printf("ok\t%c\n",s->data);
		}
		scanf("%d", &i);
	}
	printf("ListLength = %u\n", ListLength(L));

	printf("输入插入的位置i,-1结束\n");
	scanf("%d", &i);
	while(i!=-1){
		InsList(L, i, '$');
		PrintList(L);
		scanf("%d", &i);
	}

	ElemType e;
	printf("输入删除的位置i, -1结束\n");
	scanf("%d", &i);
	while(i!=-1){
		DelList(L, i, &e);
		PrintList(L);
		scanf("%d", &i);
	}

	LinkedList LA,LB,LC;
	InitList(&LA);
	InitList(&LB);
	CreateFromTail(LA);
	PrintList(LA);
	CreateFromTail(LB);
	PrintList(LB);
	LC = MergeList(LA,LB);
	PrintList(LC);
	return 0;
}

void PrintList(LinkedList L){
	while(L->next){
		L = L->next;//指向下个数据结点
		printf("%c\t",L->data);
	}
	printf("\n");
}
/*L用来接受主程序中待初始化单链表的头指针变量的地址，(*L)相当于主程序中待初始化单链表的头指针变量*/
void InitList(LinkedList *L){
	*L = (LinkedList)malloc(sizeof(Node));
	(*L)->next = NULL;
}

void CreateFromHead(LinkedList L){
	char c;
	while('$' != (c=getchar())){
		if(' '==c || '\n'==c || '\t'==c) continue;
		Node *s = (Node*)malloc(sizeof(Node));
		s->data = c;
		s->next = L->next;
		L->next = s;
	}
}
void CreateFromTail(LinkedList L){
	char c;
	Node *rear;
	rear = L;
	while('$' != (c=getchar())){
		if(' '==c || '\n'==c || '\t'==c) continue;
		Node *s = (Node*)malloc(sizeof(Node));
		s->data = c;
		rear->next = s;
		rear = s;
	}
}

Node* Get(LinkedList L, unsigned int i){
	if(i == 0) return L;//头节点
	while(L->next){
		i --;
		L = L->next;
		if(i == 0) return L;
	}
	if(i>0){
		printf("位置超过链表长度，不存在\n");
		return NULL;
	}
}


Node* Locate(LinkedList L, ElemType key){
	while(L->next){
		L = L->next;
		if(L->data == key) return L;
		else 
			continue;
	}
	return NULL;
}

unsigned int ListLength(LinkedList L){
	unsigned int l = 0;
	while(L->next){
		l ++;
		L = L->next;
	}
	return l;
}

int InsList(LinkedList L, unsigned int i, ElemType key){
	Node *pre, *s;
	pre = L;
	int t = 0;
	//找第i-1个位置
	while((t<i-1) && (pre)){
		pre = pre->next;
		t ++;
	}
	if(pre){
		s =(Node*)malloc(sizeof(Node));
		s->data = key;
		s->next = pre->next;
		pre->next = s;
		return OK;
	}
	return ERROR;
}

int DelList(LinkedList L, unsigned int i, ElemType *e){
	Node *pre, *p;//节点前驱
	if(i == 0){
		printf("删除位置不合法\n");
		return ERROR;
	}
	if(pre=Get(L, i-1)){
		p = pre->next;//保存要删除节点位置
		pre->next = p->next;
		*e = p->data;
		free(p);
		return OK;
	}
	else{
		printf("删除位置不合法\n");
		return ERROR;
	}
}

LinkedList MergeList(LinkedList LA, LinkedList LB){
	Node *pa, *pb, *r;
	LinkedList LC;
	pa = LA->next;
	pb = LB->next;
	LC = LA;
	LC->next = NULL;
	r = LC;
	
	while(pa && pb){
		if(pa->data <= pb->data){
			r->next = pa; r = pa; pa = pa->next;
		}
		else{
			r->next = pb; r = pb; pb = pb->next;
		}
	}

	//如果pb还有剩余，则直接链接在pa后面
	if(pa){
		r->next = pa;	
	}
	if(pb){
		r->next = pb;
	}
	//释放pb的头节点
	free(LB);
	return LC;
}
