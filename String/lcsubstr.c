#include <stdio.h>
#include <string.h>
#define MAX 128
/* A violent method Time complexity O(n^3), Space complexity O(1)*/
int lcsubstr0(char *X, char *Y, int *start1, int *start2);

/* A dynamic programming time complexity O(n^2), Space complexity O(n^2)*/
int lcsubstr1(char *X, char *Y, int *start1, int *start2);

/* An improved version for dp, time complexity O(n^2), Space O(n) 
 * Just like LCS problem, it only use two adjacent lines in the 
 * process of filling */
int lcsubstr2(char *X, char *Y, int *start1, int *start2);

/* A special version which differs from LCS, its space complexity
 * is O(1). Left and top element is not needed in computing,
 * because it is 0 if not equal, 1 if equal, which is different
 * from LCS. */
int lcsubstr3(char *X, char *Y, int *start1, int *start2);

int main() {
	char X[MAX];
	char Y[MAX];
	int start1, start2, length;
	scanf("%s", X);
	scanf("%s", Y);

	length = lcsubstr0(X, Y, &start1, &start2);
	printf("start1: %d start2: %d length: %d\n", start1, start2, length);

	length = lcsubstr1(X, Y, &start1, &start2);
	printf("start1: %d start2: %d length: %d\n", start1, start2, length);

	length = lcsubstr2(X, Y, &start1, &start2);
	printf("start1: %d start2: %d length: %d\n", start1, start2, length);
	
	length = lcsubstr3(X, Y, &start1, &start2);
	printf("start1: %d start2: %d length: %d\n", start1, start2, length);
	return 0;
}

int lcsubstr0(char *X, char *Y, int *start1, int *start2) {
	int m, n, i, j, k, length, comparison;
	length = comparison = 0;
	m = strlen(X);
	n = strlen(Y);
	if (0 == m || 0 == n) return 0;
	for (i = 0; i < m; i ++) {
		for (j = 0; j < n; j ++) {
			k = 0;
			while (i + k < m && j + k < n) {
				comparison ++;
				if (X[i+k] != Y[j+k]) break;
				k ++;
			}
			if (k > length) {
				length = k;
				*start1 = i;
				*start2 = j;
			}
		}
	}
	printf("X len: %d Y len: %d comparison: %d\n", m, n, comparison);
	return length;
}

int lcsubstr1(char *X, char *Y, int *start1, int *start2) {
	int m, n, i, j, comparison, length;
	m = strlen(X);
	n = strlen(Y);
	length = comparison = 0;
	int L[m+1][n+1]; /* +1 for null string */
	/* Initialize for null string */
	for (i = 0; i < m + 1; i ++)
		L[i][0] = 0;
	for (j = 0; j < n + 1; j ++)
		L[0][j] = 0;

	/* Fill the matrix L */
	for (i = 0; i < m; i ++) {
		for (j = 0; j < n; j ++) {
			L[i+1][j+1] = X[i] == Y[j] ? L[i][j] + 1 : 0;
			if (L[i+1][j+1] > length) {
				length = L[i+1][j+1];
				*start1 = i - length + 1;
				*start2 = j - length + 1;
			}
			comparison ++;
		}
	}
	/* Print the L table */
	printf("  * ");
	for (i = 0; i < n; i ++) {
		printf("%c ", Y[i]);
	}
	printf("\n");
	for (i = 0; i < m + 1; i ++) {
		if (i == 0)
			printf("* ");
		else
			printf("%c ", X[i-1]);
		for (j = 0; j < n + 1; j ++)
			printf("%d ", L[i][j]);
		printf("\n");
	}

	printf("X len: %d Y len: %d comparison: %d\n", m, n, comparison);
	return length;
}

int lcsubstr2(char *X, char *Y, int *start1, int *start2) {
	int m, n, i, j, length, comparison;
	m = strlen(X);
	n = strlen(Y);
	length = comparison = 0;
	int p[n+1], q[n+1], *pre, *cur, *temp;
	/* Initialize */
	for (i = 0; i < n + 1; i ++) {
		p[i] = q[i] = 0;
	}
	pre = p; cur = q;

	/* Computing the array by iterating */
	for (i = 0; i < m; i ++) {
		 for (j = 0; j < n; j ++) {
			cur[j+1] = X[i] == Y[j] ? pre[j] + 1 : 0;
			if (cur[j+1] > length) {
				length = cur[j+1];
				*start1 = i - length + 1;
				*start2 = j - length + 1;
			}
			comparison ++;
		 }
		 temp = cur;
		 cur = pre;
		 pre = temp;
	}
	printf("X len: %d Y len: %d comparison: %d\n", m, n, comparison);
	return length;
}

int lcsubstr3(char *X, char *Y, int *start1, int *start2) {
	int m, n, t, i, j, length, cur, pre, temp, comparison;
	m = strlen(X);
	n = strlen(Y);
	length = comparison = 0;
	/* lower triangular */
	for (i = 0; i < m; i ++) {
		/* compute a new diagonal line */
		t = i;
		j = 0;
		cur = pre = 0; /*Note reset here for a new diagonal line */
		while (t < m && j < n) {
			cur = X[t] == Y[j] ? pre + 1 : 0;
			if (cur > length) {
				length = cur;
				*start1 = t - length + 1;
				*start2 = j - length + 1;
				printf("lower//i: %d, t: %d, j: %d, start1: %d, start2: %d, length: %d\n", 
						i, t, j, *start1, *start2, length);
			}
			/* Next */
			t ++;
			j ++;
			comparison ++;
			/* Swap */
			temp = cur;
			cur = pre;
			pre = temp;
		}
	}

	/* higher triangular */
	for (j = 1; j < n; j ++) {
		/* compute a new diagonal line */
		t = j;
		i = 0;
		cur = pre = 0;
		while (t < n && i < m) {
			cur = X[i] == Y[t] ? pre + 1 : 0;
			if (cur > length) {
				length = cur;
				*start1 = i - length + 1;
				*start2 = t - length + 1;
				printf("higher//i: %d, t: %d, j: %d, start1: %d, start2: %d,length: %d\n", 
						i, t, j, *start1, *start2, length);
			}
			/* Next */
			t ++;
			i ++;
			comparison ++;
			/* Swap */
			temp = cur;
			cur = pre;
			pre = temp;
		}
	}
	printf("X len: %d Y len: %d comparison: %d\n", m, n, comparison);
	return length;
}
