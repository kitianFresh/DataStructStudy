#ifndef __GRAPH_H_
#define __GRAPH_H_
#define MAX_SIZE 32
/*************************
 * Adjacent Matrix Graph *
 *************************/
typedef struct {
	int no;		/* vertex no. */
	int info;	/* vertex info */
} VertexType;
typedef struct {
	int edges[MAX_SIZE][MAX_SIZE];	/* Martix */
	int n, e;						/* vertex numbers and edges numbers */
	VertexType vex[MAX_SIZE];		/* Vertexes */
} MGraph;

/***********************
 * Adjacent List Graph *
 ***********************/
typedef struct ArcNode {
	int adjvex;				/* vertex pointed by this arc */
	struct ArcNode *nextarc; /* pointer to next arc */
	int info;				/* arc info such as weight */
} ArcNode;
typedef struct VNode {
	int data;			/* vertex info */
	ArcNode *firstarc;	/* pointer to first arc */
} VNode;
typedef struct {
	VNode adjlist[MAX_SIZE]; /* Adjacent List */
	int n, e;				/* vertex and edge numbers*/
} AGraph;

#endif
