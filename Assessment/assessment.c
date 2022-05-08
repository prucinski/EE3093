#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(){
	int N = 0;
	int n;  //noOfBits
	int i = 0;
	int j = 0;
	int incorrect = 1;  //using int as a bool
	
	while (incorrect == 1){
		n = 0;
		printf("Please provide the size N of data, where N = 2^n: ");
		scanf("%d", &N);
		int i = N;
		if(i<1){
			printf("This value is incorrect. Please try again \n");
		}
		
		//checking whether the value is correct by repeatedly dividing by 2 and seeing
		//if we finish with 1
		while(i>1){
			n+=1;
			if(i % 2 != 0){
				incorrect = 1;
				printf("This value is incorrect. Please try again \n");
				break;
			}
			i = i/2;
			//we're assuming that the value will be correct. It is only changed to incorrect
			//once invalidness is found
			incorrect = 0;
			
		}
		
	}
	printf("The radix 2 points value is %d. \n The original array is as follows: \n", n);
	
	//populating the starting array.
	double *startingArray;
	startingArray = malloc(N*sizeof(startingArray));
	for(i=0; i < N; i++){
		startingArray[i] = i;
		printf("x[%d] = %.2f \n", i, startingArray[i]);
	}
	
	int **binaryStartArray;
	//first - memory for rows allocation - we're pointing to pointers of rows
	binaryStartArray = malloc(N*sizeof(*binaryStartArray));
	for(i =0; i<N; i++){
		//memory for columns allocation - pointers for columns
		binaryStartArray[i] = malloc(n*sizeof(*binaryStartArray[i]));
	}

	

	//loop through columns
	for(j=0; j<n; j++){
		//loop through rows again - last row - one 1, one 0 ..., second to last - two 1s, two 0s...
		//third to last - four 1s, four 0s... and so on
		//because we are going from j =0, the binary values are already reversed for us
		for (i = 0; i<N; i++){
			int insideIf = (int)(i/pow(2,j));
			if(insideIf%2 == 1){
				binaryStartArray[i][j] = 1;
			}
			else{				
				binaryStartArray[i][j] = 0;
			}
			//printf("%d assigned at i = %d, j = %d\n", binaryStartArray[i][j], i, j);	
		}
	}
	
	
	//giving the user the ability to display the bit-reversed binary.
	int choice;
	printf("Would you like to display the bit-reversed binary numbers? (1/0)");
	scanf("%d", &choice);
	if(choice == 1){
		for(i = 0; i<N; i++){
			printf("Number %d as reversed binary is: ", i);
			for(j = 0; j<n; j++){
				printf("%d", binaryStartArray[i][j]);
			}
			printf("\n");
		}
	}
	
	//allocating memory for our final array
	double *endArray;
	endArray = malloc(N*sizeof(endArray));
	
	//calculating it as per algorythm presented in the paper
	int tempResult = 0;
	for(i = 0; i<N; i++){
		tempResult = 0;
		for(j = n-1; j >=0; j--){
			tempResult = tempResult + binaryStartArray[i][(n-1)-j]*pow(2,j);
		}
		
		endArray[i] = (double)tempResult;
		printf("y[%d] = %.2f \n", i, endArray[i]);
	}
		
	//Algorythm & display complete. Now, free the memory
	//first, return 2nd dimension memory for binaryArray
	for (i = N-1; i >= 0; i--){
        free(binaryStartArray[i]);
    }
    //return the rest of the array memory
    free(binaryStartArray);
    free(startingArray);
    free(endArray);
		
	return 0;
}