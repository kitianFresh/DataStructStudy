#include <stdio.h>

void merge(int a[], int start, int mid, int end);
void MergeSort(int a[], int start, int end);

int main() {
	int a[10];
	ScanArray(a, 10);
	MergeSort(a, 0, 9);
	PrintArray(a, 10);
	return 0;
}

/* Merge a[start...mid] and a[mid+1...end] which are in order */
void merge(int a[], int start, int mid, int end) {
	int n1,n2;
	n1 = mid - start + 1;
	n2 = end - mid;
	int left[n1],right[n2];
	int i, j, k;
	/* Copy a[start...mid] and a[mid+1...end] 
	 * to left[n1] and right[n2] respectivly */
	for (i = 0; i < n1; i ++)
		left[i] = a[start + i];
	for (j = 0; j < n2; j ++)
		right[j] = a[mid + 1 + j];

	/* Merge */
	i = j = 0;
	k = start;
	while (i < n1 && j < n2) {
		if (left[i] < right[j]) {
			a[k++] = left[i++];
		}
		else {
			a[k++] = right[j++];
		}
	}
	/* Tail */
	if (i != n1) {
		for (;i < n1;)
			a[k++] = left[i++];
	}
	if (j != n2) {
		for (;j < n2;)
			a[k++] = right[j++];
	}
}

void MergeSort(int a[], int start, int end) {
	int mid;
	if (start == end) {
		return;
	} 
	else {
		mid = (start + end)/2;
		MergeSort(a, start, mid);
		MergeSort(a, mid + 1, end);
		merge(a, start, mid, end);
	}
}
