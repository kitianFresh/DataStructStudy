#include <stdio.h>

void SelectSort(int a[], int n);

/* Heap sort index from 1 not 0 */
void sift(int a[], int low, int high);
void HeapSort(int a[], int n);

int main(){
	int a[10];
	ScanArray(a, 10);
	//SelectSort(a, 10);
	HeapSort(a, 9);
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

void sift(int a[], int low, int high) {
	int i,j,temp;
	i = low; j = 2 * i; /* a[j] is the left child of a[i] */

	temp = a[i];
	while (j <= high) {
		if (j < high && a[j] < a[j+1]) /*Check j < high for j+1 */
			j ++;
		if (temp < a[j]) { /* Parent less than child */
			a[i] = a[j]; /* sift */
			i = j;
			j = 2 * i;
		}
		else 
			break;
	}
	a[i] = temp;
}

void HeapSort(int a[], int n) {
	int i, temp;
	/* Init a heap */
	for (i = n/2; i >= 1; i --) {
		sift(a, i, n);
		PrintArray(a, 10);
	}
	/* Loop n-1 times, move the max elem a[0] to the end */
	for (i = n; i >= 2; i --) {
		temp = a[1];
		a[1] = a[i];
		a[i] = temp;
		sift(a, 1, i - 1);
		PrintArray(a, 10);
	}
}
