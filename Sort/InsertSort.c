#include <stdio.h>
void InsertSort(int a[], int n);

int main(){
	int a[10];
	int i;
	for (i = 0; i < 10; i++)
		scanf("%d",a+i);
	InsertSort(a,10);
	for (i = 0; i < 10; i++)
		printf("%d ",a[i]);

	return 0;
}

void InsertSort(int a[], int n){
	int k,j,temp;
	for (k = 1; k < n; k++){
		temp = a[k];
		j = k - 1;
		while (j >= 0 && a[j] > temp) {
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = temp;
	}
}
