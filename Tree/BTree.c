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
int countNodes(BTNode *bt);
int getDepth(BTNode *bt);

/* Application */
typedef struct {
	BTNode *p; /* Node pointer */
	int layno; /* layer number */
} ST;
int maxNode(BTNode *bt);

int main() {
	BTNode *bt;
	int n;
	scanf("%d", &n);
	initBT(&bt, n);
	inorder(bt);
	level(bt);
	printf("maxNode: %d\n", maxNode(bt));
	printf("countNodes: %d\n", countNodes(bt));
	printf("getDepth: %d\n", getDepth(bt));
	return 0;
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
			visit(q);
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
