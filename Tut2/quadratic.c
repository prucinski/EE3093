#include<stdio.h>

int calculateRoots(){
	float a,b,c;
	float delta;
	float sol1, sol2;
	printf("Please input three coefficients of the quadratic formula ax^2 +bx +c: ");
	scanf("%f %f %f", &a, &b, &c);
	delta = b*b-4*a*c;
	if (delta >= 0){
		sol1 = (-b + sqrt(delta))/(2*a);
		sol2 = (-b - sqrt(delta))/(2*a);
		if (sol1 == sol2){
			printf("The solution to this equation is x = %.2f", sol1);
			return 0;
		}
		printf("The solutions to this equation are x1 = %.2f and x2 = %.2f", sol1, sol2);
		return 0;
	}
	//case where solution is complex - reached if 0 not returned yet
	float realPart, imaginativePart;
	delta = -delta;
	realPart = -b/(2*a);
	imaginativePart = sqrt(delta)/(2*a);
	printf("The complex roots are: %.2f + %.2fj and %.2f - %.2fj", realPart, imaginativePart, realPart, imaginativePart);
	
	
	
	
}




int main(){
	calculateRoots();

	return 0;
}