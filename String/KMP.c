#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*获取子串的next模式值,非递归写法*/
int Next(char *str, int *next, int n);
/*递归写法*/
int Next1(char *str, int j);

int KMP_algorithm(char *src, char *sub, int *index);


int main(){
	/*test next*/
	char src[20];
	char substr[10];
	int next[10];
	int index[10];
	int i,len;
	printf("请输入源串:\n");
	scanf("%s", src);
	printf("请输入子串:\n");
	scanf("%s", substr);

	len = strlen(substr);
	Next(substr,next,len);
	for(i=0;i<len;i++){
		printf("%d\n",next[i]);
	}

	KMP_algorithm(src,substr,index);
	return 0;
}

int KMP_algorithm(char *src, char *sub, int *index){
	int len,i,j,k;
	len = strlen(sub);
	int *next = (int*)malloc(sizeof(int)*len);
	Next(sub,next,len);
	for(i=0;i<len;i++){
		printf("%d\n",next[i]);
	}
	i = j = k = 0;
	while('\0' != src[i]){
		
		if(src[i] == sub[j]) {
			i ++;
			j ++;
			if(j == len) {
				j = next[j-1]+1;
				index[k++] = i - len;
				printf("index:%d\n",index[k-1]);
			}
			continue;
		}
		else {
			j = next[j];
			if(j == -1) {
				j = 0;
				i ++;
			}
		}
		
	}
	if(k == 0) return 0;
	else return 1;
}

int Next1(char *str, int j){
	int k;
	if(0 == j) return -1;
	k = Next1(str,j-1);
	if(str[j] == str[k+1]) return k+1;
	else {
		k = Next1(str,k);
		while(str[j] != str[k+1] && k >= 0){
			k = Next1(str,k);
		}
		if(str[j] == str[k+1]) return k+1;
		else return -1;
	}
}

int Next(char *str, int *next, int n){
	next[0] = -1;
	int i ,k;
	for(i=1;i<n;i++){
		k = next[i-1];
		while(str[i] != str[k+1] && k >= 0){
			k = next[next[k]];
		}
		if(str[i] == str[k+1]) next[i] = k + 1;
		else next[i] = -1;
	}
}
