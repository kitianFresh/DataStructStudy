#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 128
#define ERROR -1
#define OK 0
typedef char ElemType;
typedef struct{
	ElemType elem[MAXSIZE];
	int last;	
}SeqList;

/*init a SeqList if not initiated*/
void InitList(SeqList *L);

/*get SeqList's length if it exists*/
int ListLength(SeqList *L);

/*get data at index i*/
ElemType getData(SeqList *L, int i);

/*insert data e at index i*/
int InsList(SeqList *L, int i, ElemType e);

/*delete data at index i*/
int DelList(SeqList *L, int i, ElemType e);

/*locate e in the SeqList*/
int Locate(SeqList *L, ElemType e);

/*clear List*/
int ClearList(SeqList *L);

/*judge if the List is empty*/
int IsEmptyList(SeqList *L);

/*merge ordered SeqList A and B ,store it with SeqList C*/
void MergeList(SeqList *LA, SeqList *LB, SeqList *LC);

void printList(SeqList *L);

void InitList(SeqList *L){
	L->last = -1;
}

int ListLength(SeqList *L){
	return L->last+1;
}

int InsList(SeqList *L, int i, ElemType e){
	if(i<=0 || i > L->last+2){
		printf("插入位置不合法\n");
		return ERROR;
	}
	
	if(L->last >= MAXSIZE-1){
		printf("表已满，无法插入\n");
		return ERROR;
	}
	int k = L->last + 1;
	for(;k>=i;k--){
		L->elem[k] = L->elem[k-1];
	}
	L->elem[k] = e;
	L->last ++;
	printf("L->last:%d\n",L->last);
	return OK;
}

int DelList(SeqList *L, int i, ElemType e){
	if(i<=0 || i > L->last+1){
		printf("删除位置不合法\n");
		return ERROR;
	}
	e = L->elem[i-1];
	int k = i-1;
	for(;k<L->last;k++){
		L->elem[k] = L->elem[k+1];
	}
	L->last --;
	return OK;
}

int Locate(SeqList *L, ElemType e){
	int i = 0;
	while((i <= L->last) && (L->elem[i] != e))
		i ++;
	if(i <= L->last){
		return i;
	}	
	else 
		return -1;
}

void MergeList(SeqList *LA, SeqList *LB, SeqList *LC){
	int i,j,k;
	i = 0;
	j = 0;
	k = 0;
	while((i <= LA->last) && (j <= LB->last)){
		if(LA->elem[i] <= LB->elem[j]){
			LC->elem[k] = LA->elem[i];
			i ++;
			k ++;
		}
		else{
			LC->elem[k] = LB->elem[j];
			j ++;
			k ++;
		}	
	}
	while(i <= LA->last){
		LC->elem[k] = LA->elem[i];
		i ++;
		k ++;
	}
	while(j <= LB->last){
		LC->elem[k] = LB->elem[j];
		j ++;
		k ++;
	}
	LC->last = LA->last + LB->last + 1;
}

void printList(SeqList *L){
	int i = 0;
	for(;i<=L->last;i++)
		printf("%c\t",L->elem[i]);
	printf("\n");
}

int main(int argc, char *argv[]){
	SeqList L;
	InitList(&L);
	int flag, i, pos;
	
	ElemType e;
	char str[5];
	
	while(1){
		scanf("%s",str);
		if(!strcmp(str,"help")){
			printf("输入1:插入元素\n输入2:删除元素\n输入3:退出\n");
		}
		else if(!strcmp(str,"1")){
			printf("Please input your element(end up with '$'):\n");
			flag = 1;
			i = 1;
			while(flag){
				e = getchar();
				if(e == '$'){
					flag = 0;
				}
				else if(e == ' ' || e == '\n' || e == '\t'){
					continue;
				}
				else{
					InsList(&L, i, e);
					i ++;	
				}
			}
			printList(&L);
			printf("ListLength:%d\n",ListLength(&L));
		}
		else if(!strcmp(str,"2")){
			printf("Please input element's index to delete(end up with integer -1):\n");
	
			flag = 1;
			while(flag){
				scanf("%d", &pos);
				if(pos != -1){
					DelList(&L, pos, e);
					printList(&L);
					printf("ListLength:%d\n",ListLength(&L));
				}
				else{
					flag = 0;
				}
			}
		}
		else if(!strcmp(str,"3")){
			break;
		}
		else{
			printf("可输入help查看功能\n");
		}
	}
	
	
	return 0;
}
