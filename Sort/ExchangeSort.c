#include <stdio.h>
void BubbleSort(int a[], int n);
void QuickSort(int a[], int start, int end);

int main() {
	int a[10];
	ScanArray(a, 10);
	//BubbleSort(a, 10);
	QuickSort(a, 0, 9);
	PrintArray(a, 10);
	return 0;
}

void BubbleSort(int a[], int n) {
	int i, j, temp, flag;
	for (i = n - 1; i >= 1; i--) {
		flag = 0;
		for (j = 0; j < i; j++) {
			if (a[j] > a[j+1]) {
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
				flag = 1;
			}
		}
		if (flag == 0) return ;
	}
}

void QuickSort(int a[], int start, int end) {
	int i, j, temp;
	if (start == end) return ;
	i = start, j = end;
	if (start < end) { /* Make sure that start < end !!!*/
		temp = a[i];
		while (i != j) {
			while (i < j && a[j] > temp) j --;
			if (i < j) {
				a[i] = a[j];
				i ++;
			}
			while (i < j && a[i] < temp) i ++;
			if (i < j) {
				a[j] = a[i];
				j --;
			}
		}
		a[i] = temp;
		PrintArray(a, 10);
		QuickSort(a, start, i - 1);
		QuickSort(a, i + 1, end);
	}
}
