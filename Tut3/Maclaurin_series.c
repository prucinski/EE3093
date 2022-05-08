#include<stdio.h>
#include<math.h>

//a very unoptimised factorial function
long long factorial(long long number){   //<---- this does not help at all!
	if (number == 1){
	return 1;
	}
	return number*factorial(number -1);
}

int maclurinSeriesCheck(){
	float th;
	int counter = 1;
	int sign = -1;  //this is rather lazy of me, but it works
	int counterOfPowers = 3;
	double  intendedValue, currentValue;
	printf("Please input the angle in radians: ");
	scanf("%f", &th);
	intendedValue = sin(th); 
	currentValue = th;
	printf("%f %f \n", intendedValue, currentValue);
	printf("%f", intendedValue - currentValue);
	
	//This is limited by the computers ability to store high factorials - so it'll return nonsense for factorials over something!
	while( fabs(intendedValue - currentValue) > 0.00001){
		currentValue = currentValue + sign*pow(th, counterOfPowers)/factorial(counterOfPowers);
		counter+=1;
		sign *= -1;
		counterOfPowers +=2;
		//command below can be uncommented for debugging
		printf("expectedValue %f, value %f, counter %i, counterOfPowers %i \n", intendedValue, currentValue, counter, counterOfPowers);
		}

	return counter;
}


int main(){
	int result;
	printf("%d", factorial(15));
	result = maclurinSeriesCheck();
	//printf("%f", sin(0.3));
	printf("There need to be just %i terms in the Maclurin series", result);
	return 0;
}