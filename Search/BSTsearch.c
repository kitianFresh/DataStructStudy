#include <stdio.h>
#include <stdlib.h>
typedef struct BTNode {
	int key;
	struct BTNode *lchild;
	struct BTNode *rchild;
}BTNode;

/* Build a BST*/
void CreateBST(BTNode **bt, int key[], int n);

/* Insert a node */
int BSTinsert(BTNode **bt, int key);

/* A recursive version of BSTsearch*/
BTNode* BSTsearch_r(BTNode *bt, int key);

int main() {
	int a[10], key;
	BTNode *bt,*node;
	ScanArray(a, 10);
	//PrintArray(a, 10);
	CreateBST(&bt, a, 10);
	scanf("%d", &key);
	node = BSTsearch_r(bt, key);
	if (NULL != node)
		printf("Succcess %d\n", node->key);
	else 
		printf("Failed\n");
	return 0;
}

void CreateBST(BTNode **bt, int key[], int n) {
	int i;
	*bt = NULL; /* Make sure that *bt is empty,or it will kill*/
	for (i = 0; i < n; i++) {
		BSTinsert(bt,key[i]);
	}
}

BTNode* BSTsearch_r(BTNode *bt, int key) {
	if (NULL == bt) return NULL;
	if (bt->key == key) 
		return bt;
	else if (bt->key > key)
		return BSTsearch_r(bt->lchild, key);
	else 
		return BSTsearch_r(bt->rchild, key);
}

int BSTinsert(BTNode **bt, int key) {
	if (NULL == (*bt)) {
		(*bt) = (BTNode*)malloc(sizeof(BTNode));
		(*bt)->key = key;
		(*bt)->lchild = NULL;
		(*bt)->rchild = NULL;
		//printf("insert %d\n", (*bt)->key);
		return 1;
	}
	else {
		if ((*bt)->key == key) 
			return -1;
		else if ((*bt)->key < key) 
			BSTinsert(&((*bt)->rchild), key);
		else 
			BSTinsert(&((*bt)->lchild), key);
	}
}
