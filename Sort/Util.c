#include <stdio.h>
void PrintArray(int a[], int n);
void ScanArray(int a[], int n);

void PrintArray(int a[], int n) {
	int i;
	for (i = 0; i < n; i ++)
		printf("%d ", a[i]);
	printf("\n");
}

void ScanArray(int a[], int n) {
	int i;
	for (i = 0; i < n; i ++)
		scanf("%d", a+i);
}
