#include<stdio.h>
#include<math.h>
#include<string.h>

long long factorial(int a){
	if(a==1 || a==0){
		return 1;
	}
	return a*factorial(a-1);
}

int newtons(int a, int b){
	return factorial(a)/(factorial(b)*factorial(a-b));
}

int main(){
	int n, i, j;
	char* spaces  = "                       ";
	printf("Please input the N in pascals triangle: ");
	scanf("%d", &n);
	for(i=0; i<n; i++){
		printf("%s", spaces);
		int row[i+1];
		for(j=0; j<=i; j++){
			row[i] = newtons(i, j);
			printf("%s %d ",spaces, row[i], spaces);
		}
		
		printf("\n\n");
		spaces = spaces  + 2;
		//printf("%d", sizeof(spaces)); 
	}
	
	
	return 0;
}