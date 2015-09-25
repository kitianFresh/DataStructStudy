#include<stdio.h>
#include<stdlib.h>

typedef struct Polynode {
	int coef;
	int exp;
	struct Polynode *next;
}Polynode, *Polylist;

Polylist PolyCreate();
void PolyAdd(Polylist polya, Polylist polyb);
void PrintList(Polylist pl);

int main(){
	Polylist pla, plb;
	pla = PolyCreate();
	PrintList(pla);
	
	plb = PolyCreate();
	PrintList(plb);
	
	PolyAdd(pla,plb);
	PrintList(pla);
	return 0;
}

void PrintList(Polylist pl){
	while(pl->next){
		pl = pl->next;
		printf("%d:%d\t",pl->coef,pl->exp);
	}
	printf("\n");
}

Polylist PolyCreate(){
	Polynode *head, *rear, *s;
	int c,e;
	//创建头节点
	head = (Polynode*)malloc(sizeof(Polynode));
	rear = head;
	scanf("%d,%d",&c,&e);
	while(c){
		s = (Polynode*)malloc(sizeof(Polynode));
		s->coef = c;
		s->exp = e;
		rear->next = s;
		rear = s;
		scanf("%d,%d", &c, &e);
	}
	rear->next = NULL;

	return head;
}

void PolyAdd(Polylist polya, Polylist polyb){
	//tail始终指向pa的前驱,同时也是为插法建立的结果链表的尾节点,
	//这个链表不申请新的空间，只是在原来链表的基础上将他们串联起来
	Polynode *pa,*pb,*tail,*temp;
	pa = polya->next; pb = polyb->next;
	tail = polya;
	int sum = 0;
	while(pa && pb){
		//相等，则合并后pa，pb同时前移
		if(pa->exp == pb->exp){
			sum = pa->coef + pb->coef;
			if(sum != 0){
				pa->coef = sum;
				//串联pa，事实上已经串联在一起了
				tail->next = pa;
				tail = pa;
				pa = pa->next;//移动pa到下一个节点

				//保存pb位置
				temp = pb;
				pb = pb->next;//移动pb到下一个节点
				//删除
				free(temp);
			}
			//sum等于0,则同时删除pa和pb两个，并前移
			else{
				temp = pa; pa = pa->next; free(temp);
				temp = pb; pb = pb->next; free(temp);
			}
		}
		else if(pa->exp < pb->exp){
			tail->next = pa;//记录pa的前一个位置
			tail = pa;
			pa = pa->next;
		}
		else{
			tail->next = pb;
			tail = pb;
			//先保存pb的位置
			temp = pb;
			pb = pb->next;
		}
	}

	if(pb){
		pa->next = pb;
	}
	else{
		tail->next = pa;
	}
	free(polyb);
}
