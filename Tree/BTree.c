#include <stdio.h>
#include <stdlib.h>
#define QUE_SIZE 100
#define MAX_NODES 100
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
int countNodes(BTNode *bt);
int getDepth(BTNode *bt);

/* Application */
typedef struct {
	BTNode *p; /* Node pointer */
	int layno; /* layer number */
} ST;
int maxNode(BTNode *bt);

static int pre[MAX_NODES] = {0};
static int in[MAX_NODES] = {0};
static int post[MAX_NODES] = {0};
static int pre_index = 0;
static int in_index = 0;
static int post_index = 0;

BTNode *buildBT(int pre[], int in[], int l1, int r1, int l2, int r2);

int main() {
	BTNode *bt, *p;
	int n;
	scanf("%d", &n);
	initBT(&bt, n);

	printf("************preorder***********\n");
	preorder(bt);
	printf("\n");

	printf("************inorder************\n");
	inorder(bt);
	printf("\n");

	printf("*************postorder*********\n");
	postorder(bt);
	printf("\n");

	printf("*************level*************\n");
	level(bt);
	printf("\n");

	printf("maxNode: %d\n", maxNode(bt));
	printf("countNodes: %d\n", countNodes(bt));
	printf("getDepth: %d\n", getDepth(bt));
	p = buildBT(pre, in, 0, pre_index - 1, 0, in_index - 1);

	printf("*********************************\n");
	level(p);
	printf("\n");
	return 0;
}

BTNode *buildBT(int pre[], int in[], int l1, int r1, int l2, int r2) {
	int i;
	if ( l1 > r1 || l2 > r2) return NULL;
	BTNode *p = (BTNode*)malloc(sizeof(BTNode));
	p->key = pre[l1];
	p->left = NULL;
	p->right = NULL;
	for (i = l2; i <= r2; i ++)
		if (in[i] == pre[l1])
			break;
	p->left = buildBT(pre, in, l1 + 1, l1 + i - l2, l2, i - 1);
	p->right = buildBT(pre, in, l1 + i - l2 + 1, r1, i + 1, r2);
	return p;
}

int countNodes(BTNode *bt) {
	if (NULL == bt) /* An empty tree */
		return 0;
	else 
		return countNodes(bt->left) + countNodes(bt->right) + 1;
}

int getDepth(BTNode *bt) {
	int left, right;
	if (NULL == bt) /* An empty tree */
		return 0;
	else {
		left = getDepth(bt->left) + 1;
		right = getDepth(bt->right) + 1;
		return left > right ? left : right;
	}
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
	printf("%d ", bt->key);
}

void preorder(BTNode *bt) {
	if (NULL != bt) {
		visit(bt);
		pre[pre_index++] = bt->key;
		preorder(bt->left);
		preorder(bt->right);
	}
	return ;
}

void inorder(BTNode *bt) {
	if (NULL != bt) {
		inorder(bt->left);
		visit(bt);
		in[in_index++] = bt->key;
		inorder(bt->right);
	}
	return ;
}

void postorder(BTNode *bt) {
	if (NULL != bt) {
		postorder(bt->left);
		postorder(bt->right);
		visit(bt);
		post[post_index++] = bt->key;
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

int maxNode(BTNode *p) {
	int front, rear, lno;
   	int max, i, j, n;
	ST queue[QUE_SIZE];
	BTNode *q;
	front = rear = 0;
	if (NULL != p) {
		rear++;
		queue[rear].p = p;
		queue[rear].layno = 1;
		
		while (front != rear) {
			front++;
			q = queue[front].p;
			lno = queue[front].layno;
			if (NULL != q->left) {
				rear ++;
				queue[rear].p = q->left;
				queue[rear].layno = lno + 1;
			}
			if (NULL != q->right) {
				rear ++;
				queue[rear].p = q->right;
				queue[rear].layno = lno + 1;
			}
		}
		max = 0;
		for (i = 1; i <= lno; i ++) {
			n = 0;
			for (j = 1; j <= rear; j ++) {
				if (queue[j].layno == i)
					++n;
			}
			if (max < n)
				max = n;
		}
		return max;
	}
	else 
		return 0;
}
