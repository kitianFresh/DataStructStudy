#include <stdio.h>
void InsertSort(int a[], int n);
void BinSort(int a[], int n);

int main(){
	int a[10];
	int i;
	for (i = 0; i < 10; i++)
		scanf("%d",a+i);
	//InsertSort(a, 10);
	BinSort(a, 10);
	for (i = 0; i < 10; i++)
		printf("%d ",a[i]);

	return 0;
}

void InsertSort(int a[], int n){
	int k,j,temp;
	for (k = 1; k < n; k++) {
		temp = a[k];
		j = k - 1;
		while (j >= 0 && a[j] > temp) {
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = temp;
	}
}

void BinSort(int a[], int n){
	int k,j,temp; /* For Insert */
	int low,high,mid; /* For Binary Search */
	for (k = 1; k < n; k++) {
		temp = a[k];
		
		/* Search the position for inserting */
		low = 0; high = k - 1;
		while (low <= high) {
			mid = (low + high)/2;
			if (temp >= a[mid]) 
				low = mid + 1;
			else 
				high = mid -1;
		}
		/* Move the position */
		j = k -1;
		while (j >= low) {
			a[j+1] = a[j];
			j --;
		}
		a[j+1] = temp;
	}
}
