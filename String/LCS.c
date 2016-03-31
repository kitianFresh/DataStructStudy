#include <stdio.h>
#include <string.h>
#define MAX 32
int max(int a, int b);
/* A recursive version O(2^n)*/
int LCS_R(char *X, char *Y, int m, int n);

/* A non-recursive version with dynamic programming O(mn)*/
int LCS(char *X, char *Y, int m, int n);

int main(){
	char X[MAX];
	char Y[MAX];
	scanf("%s", X);
	scanf("%s", Y);
	int m = strlen(X);
	int n = strlen(Y);
	printf("LCS_R:%d\n", LCS_R(X, Y, m, n));
	printf("LCS:%d\n", LCS(X, Y, m, n));
	return 0;
}

int max(int a, int b) {
	return a > b ? a : b;
}

int LCS_R(char *X, char *Y, int m, int n) {
	if (m == 0 || n == 0)
		return 0;
	if (X[m-1] == Y[n-1])
		return LCS_R(X, Y, m - 1, n - 1) + 1;
	else
		return max(LCS_R(X, Y, m, n-1), LCS_R(X, Y, m-1, n));
}
/* Memoization */
int LCS(char *X, char *Y, int m, int n) {
	int L[m+1][n+1];/* +1 for null X and null Y */
	int i, j, index;
	/* Initialize L */
	for (i = 0; i < m + 1; i ++)
		for (j = 0; j < n + 1; j ++)
			L[i][j] = 0;

	/* Compute the L Matrix */
	for (i = 0; i < m; i ++) {
		for (j = 0; j < n; j ++) {
			if (X[i] == Y[j]) {
				L[i+1][j+1] = L[i][j] + 1;
			}
			else {
				L[i+1][j+1] = max(L[i+1][j], L[i][j+1]);
			}
		}
	}

	/* Print the L table */
	printf("  @ ");
	for (i = 0; i < n; i ++) {
		printf("%c ", Y[i]);
	}
	printf("\n");
	for (i = 0; i < m + 1; i ++) {
		if (i == 0)
			printf("@ ");
		else
			printf("%c ", X[i-1]);
		for (j = 0; j < n + 1; j ++)
			printf("%d ", L[i][j]);
		printf("\n");
	}

	index = L[m][n];
	char lcs[index + 1];
	lcs[index] = '\0';
	i = m; j = n;
	while (i > 0 && j > 0) {
		if (X[i-1] == Y[j-1]) {
			lcs[--index] = X[i-1];
			i --; j --;
		}
		else if (L[i-1][j] > L[i][j-1]) {
			i --;
		}
		else {
			j --;
		}
	}
	printf("LCS of %s and %s is %s\n", X, Y, lcs);
	return L[m][n];
}
