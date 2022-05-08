

#include<stdio.h>

int calculateInt(){
	int choice, a, b, answer;
	printf("Please input an value - 1 for addition, 2 for substraction, 3 for multiplication, 4 for division: ");
	scanf("%d", &choice);
	printf("Please input two integers to perform the operation on, separated by space: ");
	scanf("%d %d", &a, &b);
	switch(choice){
		case 1:
			answer = a + b;
			break;
		case 2:
			answer = a - b;
			break;
		case 3:
			answer = a * b;
			break;
		case 4:
			answer = a/b;
			break;
		default:
			printf("Error - invalid operation number! \n");
			answer = 0;
	}
	return answer;
}

float calculateFloat(){
	int choice;
	float a, b, answer;
	printf("Please input an value - 1 for addition, 2 for substraction, 3 for multiplication, 4 for division: ");
	scanf("%d", &choice);
	printf("Please input two floats to perform the operation on, separated by space: ");
	scanf("%f %f", &a, &b);
	switch(choice){
		case 1:
			answer = a + b;
			break;
		case 2:
			answer = a - b;
			break;
		case 3:
			answer = a * b;
			break;
		case 4:
			answer = a/b;
			break;
		default:
			printf("Error - invalid operation number! \n");
			answer = 0;
	}
	return answer;
}


int main(){
	printf("The result of the operation is %f",calculateFloat());
	return 0;
}