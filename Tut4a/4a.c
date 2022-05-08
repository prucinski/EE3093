#include<stdio.h>
#include<string.h>

int factorial(int a){
if(a==1){
return 1;
}
return a*factorial(a-1);
}

int newtons(int a, int b){
return factorial(a)/(factorial(b)*factorial(a-b));
}

const char* binomialExpansion(int n){
int r = 0;
char *my = "(a+b)";
char inFront[10];
do{
sprintf(inFront, "%d", newtons(n,r));
printf("%s", inFront);
printf("somethings happening");
r = r+1;
}
while(r<n);
return my;
}