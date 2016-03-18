#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

char visit[MAX_SIZE] = {0};

void Visit(AGraph *G, int v);
void DFS(AGraph *G, int v);
void BFS(AGraph *G, int v);/* a bug version */
void BFS1(AGraph *G, int v);
void buildGraph(AGraph *G);

/* Application */
int remoteVex(AGraph *G, int v);
void DFS2(AGraph *G, int v, int *vn, int *en);
int GisTree(AGraph *G);
int PathExisted(AGraph *G, int vi, int vj);


int main(){
	AGraph G;
	buildGraph(&G);
	//DFS(&G, 0);
	BFS1(&G, 0);
	printf("%d\n", remoteVex(&G, 0));
	printf("GisTree: %d\n", GisTree(&G));
	printf("PathExisted between %d and %d: %d\n", 0, 4, 
			PathExisted(&G, 0, 4));
	return 0;
}

/* Judge path between i and j existed */
int PathExisted(AGraph *G, int i, int j) {
	int k;
	for (k = 0; k < G->n; k ++)
		visit[k] = 0;
	DFS(G, i);
	if (visit[j] == 1)
		return 1;
	else
		return 0;
}

/* Judge a Graph is a Tree */
int GisTree(AGraph *G) {
	int i, vn, en;
	vn = en = 0;
	for (i = 0; i < G->n; i++) {
		visit[i] = 0;
	}
	DFS2(G, 0, &vn, &en);
	/* vn == G->n && G->n -1 == en/2*/
	if (vn == G->n && en/2 == (G->n - 1))
		return 1;
	else
		return 0;
}

void DFS2(AGraph *G, int v, int *vn, int *en) {
	ArcNode *p;
	visit[v] = 1;
	*vn ++;	/* vn + 1 when visited */
	p = G->adjlist[v].firstarc;
	while (p) {
		*en ++; /* en + 1 when there is arc , but this will double */
		if (!visit[p->adjvex]) {
			DFS2(G, p->adjvex, vn, en);
		}
		p = p->nextarc;
	}
}

/* Return vex the farthest from vertex v of undirected connected graph */
int remoteVex(AGraph *G, int v) {
	int que[MAX_SIZE], front, rear;
	ArcNode *p;
	int i;
	for (i = 0; i < G->n; i++)
		visit[i] = 0;
	front = rear = 0;
	i = v;
	visit[i] = 1;
	rear = (rear + 1) % MAX_SIZE;
	que[rear] = i;
	while (front != rear) {
		front = (front + 1) % MAX_SIZE;
		i = que[front];
		p = G->adjlist[i].firstarc;
		while (p) {
			if (!visit[p->adjvex]) {
				visit[p->adjvex] = 1;
				rear = (rear + 1) % MAX_SIZE;
				que[rear] = p->adjvex;
			}
			p = p->nextarc;
		}
	}
	return i;
}

void buildGraph(AGraph *G) {
	int v1, v2, arcinfo;
	int i, n, e;
	scanf("%d %d", &n, &e);

	/* Notes :Init Graph */
	G->n = n;
	G->e = e;
	for (i = 0; i < n; i++) {
		G->adjlist[i].data = 0;
		G->adjlist[i].firstarc = NULL; /* Remeber set it NULL */
	}

	/* Init arcs*/
	for (i = 0; i < e; i++) {
		scanf("%d %d %d", &v1, &v2, &arcinfo);
		ArcNode *arc = (ArcNode*)malloc(sizeof(ArcNode));
		arc->adjvex = v2;
		arc->info = arcinfo;
		/* Head insert to establish a linkedlist */
		arc->nextarc = G->adjlist[v1].firstarc;
		G->adjlist[v1].firstarc = arc;
	}
}

/* Visit a vertex */
void Visit(AGraph *G, int v) {
	printf("no:%d\tdata:%d\n", v, G->adjlist[v].data);
}

/* Traverse a connected graph by deep first search */
void DFS(AGraph *G, int v) {
	ArcNode *p;
	Visit(G, v);
	visit[v] = 1;
	p = G->adjlist[v].firstarc;
	while (p!= NULL) {
		if (!visit[p->adjvex]){
			DFS(G, p->adjvex);
		}
		p = p->nextarc;
	}
}

/* Note this is a bug BFS, because it doesn't visit at once
 * while entering queue; compare with level traverse of a tree,
 * a tree is 1:n, one parent to many childs, one child to only one
 * parent. but a graph is n:n, one child to many parents; if you doesn't
 * visit at once before entering queue, the same node may enter queue 
 * repeatedly so that it will be visited repeatedly.
 * */
/* Traverse a connected graph by broad first search */
void BFS(AGraph *G, int v) {
	int que[MAX_SIZE], front, rear;
	int i;
	ArcNode *p;
	front = rear = 0;
	i = v;
	rear = (rear + 1) % MAX_SIZE;
	que[rear] = i;
	while (front != rear) {
		front = (front + 1) % MAX_SIZE;
		i = que[front];
		p = G->adjlist[i].firstarc;
		visit[i] = 1;
		Visit(G, i);
		while (p) {
			if (!visit[p->adjvex]) {
				rear = (rear + 1) % MAX_SIZE;
				que[rear] = p->adjvex;
			}
			p = p->nextarc;
		}
	}
}

/* We fix the bug by visiting the node before it entering queue 
 * rather than visiting it after out of a queue */
/* Traverse a connected graph by broad first search */
void BFS1(AGraph *G, int v) {
	int que[MAX_SIZE], front, rear;
	int i;
	ArcNode *p;
	front = rear = 0;
	i = v;
	rear = (rear + 1) % MAX_SIZE;
	que[rear] = i;
	visit[i] = 1;
	Visit(G, i);
	while (front != rear) {
		front = (front + 1) % MAX_SIZE;
		i = que[front];
		p = G->adjlist[i].firstarc;
		while (p) {
			if (!visit[p->adjvex]) {
				visit[p->adjvex] = 1;
				Visit(G, p->adjvex);
				rear = (rear + 1) % MAX_SIZE;
				que[rear] = p->adjvex;
			}
			p = p->nextarc;
		}
	}
}

