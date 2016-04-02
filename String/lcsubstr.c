#include <stdio.h>
#include <string.h>
#define MAX 32
/* A violent method Time complexity O(n^3), Space complexity O(1)*/
int lcsubstr0(char *X, char *Y, int *start1, int *start2);

/* A dynamic programming time complexity O(n^2), Space complexity O(n^2)*/
int lcsubstr1(char *X, char *Y, int *start1, int *start2);

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
				if (X[i+k] != Y[j+k]) break;
				k ++;
				comparison ++;
			}
			comparison ++;
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
	printf("X len: %d Y len: %d comparison: %d\n", m, n, comparison);
	return length;
}
