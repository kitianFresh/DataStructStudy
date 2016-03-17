#include <stdio.h>
#include <stdlib.h>
#define QUE_SIZE 100
typedef struct BTNode {
	int key;
	struct BTNode *left;
	struct BTNode *right;
} BTNode;

void initBT(BTNode **bt, int n);
BTNode *insertBT(BTNode **bt, int key);
void visit(BTNode *bt);
void preorder(BTNode *bt);
void inorder(BTNode *bt);
void postorder(BTNode *bt);
void level(BTNode *p);



int main() {
	BTNode *bt;
	int n;
	scanf("%d", &n);
	initBT(&bt, n);
	inorder(bt);
	level(bt);
	return 0;
}

void initBT(BTNode **bt, int n) {
	int i, key;
	*bt = NULL; /* clear */
	for (i = 0; i < n; i ++) {
		scanf("%d", &key);
		insertBT(bt, key);
	}
}

BTNode *insertBT(BTNode **bt, int key) {
	if (NULL == *bt) {
		*bt = (BTNode*)malloc(sizeof(BTNode));
		(*bt)->key = key;
		(*bt)->left = NULL;
		(*bt)->right = NULL;
		return *bt;
	}
	else {
		if ((*bt)->key >= key)
			insertBT(&(*bt)->left, key);
		else
			insertBT(&(*bt)->right, key);
	}
}

void visit(BTNode *bt) {
	printf("%d\n", bt->key);
}

void preorder(BTNode *bt) {
	if (NULL != bt) {
		printf("preorder:%d\n", bt->key);
		preorder(bt->left);
		preorder(bt->right);
	}
	return ;
}

void inorder(BTNode *bt) {
	if (NULL != bt) {
		inorder(bt->left);
		printf("inorder:%d\n", bt->key);
		inorder(bt->right);
	}
	return ;
}

void postorder(BTNode *bt) {
	if (NULL != bt) {
		postorder(bt->left);
		postorder(bt->right);
		printf("postorder:%d\n", bt->key);
	}
}

void level(BTNode *p) {
	int front, rear;
	BTNode *queue[QUE_SIZE];
	BTNode *q;
	front = rear = 0;
	if (NULL != p) {
		rear = (rear+1)%QUE_SIZE;
		queue[rear] = p;
		while (front != rear) {
			front = (front+1)%QUE_SIZE;
			q = queue[front];
			visit(q);
			if (NULL != q->left) {
				rear = (rear+1)%QUE_SIZE;
				queue[rear] = q->left;
			}
			if (NULL != q->right) {
				rear = (rear+1)%QUE_SIZE;
				queue[rear] = q->right;
			}
		}
	}
}
