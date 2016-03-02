#include <stdio.h>

void PrintArray(int a[], int n);

void InsertSort(int a[], int n);
void BinSort(int a[], int n);

void ShellInsert(int a[], int n, int d);
void ShellSort(int a[], int n, int d[], int t);
void ShellInsert1(int a[], int n, int d);

int main(){
	int a[10];
	int delta[3] = {5, 3, 1};
	int i;
	for (i = 0; i < 10; i++)
		scanf("%d",a+i);
	//InsertSort(a, 10);
	//BinSort(a, 10);
	ShellSort(a, 10, delta, 3);
	PrintArray(a, 10);
	return 0;
}

void PrintArray(int a[], int n){
	int i;
	for (i=0; i < n; i++)
		printf("%d ",a[i]);
	printf("\n");
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

void ShellInsert(int a[], int n, int d){
	int trip, k, i, j, temp;
	trip = n / d;
	for (i = 0; i < trip; i++){
		for (k = i + d; k < n; k+=d){
			temp = a[k]; j = k - d;
			while (j >= i && a[j] > temp) {
				a[j+d] = a[j];
				j -= d;
			}
			a[j+d] = temp;
		}
	}
}

/* Another version of shellinsert, don't need trip 
 * because it will acess all elem in every subsequence
 * when it iterates the array in order
 * */
void ShellInsert1(int a[], int n, int d){
	int i, j, temp;
	for (i = d; i < n; i++) {
		if (a[i] < a[i-d]) { /* Check the order to avoid redundant compare*/
			temp = a[i]; /* Save the elem to insert */
			/* Find the position to insert */
			for (j = i - d; j >= 0 && a[j] > temp; j -= d)
				a[j+d] = a[j];
			a[j+d] = temp; /* Insert the elem */
		}
	}
}

void ShellSort(int a[], int n, int d[], int t){
	int i = 0;
	for (;i < t; i ++)
		//ShellInsert(a, n, d[i]);
		ShellInsert1(a, n, d[i]);
}
