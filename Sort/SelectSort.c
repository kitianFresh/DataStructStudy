#include <stdio.h>
void SelectSort(int a[], int n);
int main(){
	int a[10];
	int delta[3] = {5, 3, 1};
	int i;
	ScanArray(a, 10);
	SelectSort(a, 10);
	PrintArray(a, 10);
	return 0;
}

void SelectSort(int a[], int n) {
	int i, j, k, temp;
	for (i = 0; i < n; i++) {
		k = i;
		for (j = i + 1; j < n; j ++) {
			if (a[j] < a[k])
				k = j;
		}
		temp = a[i];
		a[i] = a[k];
		a[k] = temp;
	}
}
