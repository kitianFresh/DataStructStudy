#include<stdio.h>
int Bsearch(int a[], int left, int right, int key);

int main(int argc, int **agrv) {
	int a[10];
	int key = 0;
	ScanArray(a, 10);
	PrintArray(a, 10);
	scanf("%d", &key);
	printf("index of %d is %d\n", key, Bsearch_r(a, 0, 9, key));
	return 0;
}

int Bsearch(int a[], int left, int right, int key) {
	int mid;
	while (left <= right) {
		mid = (left + right)/2;
		if (a[mid] == key) return mid;
		else if (a[mid] < key) left = mid + 1;
		else right = mid - 1;
	}
	return -1;
}

int Bsearch_r(int a[], int left, int right, int key) {
	int mid;
	if (left > right) return -1;
	mid = (left + right)/2;
	if (a[mid] == key) 
		return mid;
	else if (a[mid] < key) 
		return Bsearch_r(a, mid + 1, right, key);
	else 
		return Bsearch_r(a, left, mid - 1, key);
}
