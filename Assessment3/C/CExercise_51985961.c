
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

//declaring struct holding the signal data
struct Signal{
	double **data;
	double maxPower;
	int N;  //no of samples
};
//function structure for computeAverage(). It can take
//as much data as it needs -but it needs to be parsed
//into an array first.
double computeAverage(double *array, int arraySize);


//declaring type to be called in code
typedef struct Signal signal;

int main(){
	//declaring empty signal and pointer
	signal powerSignal;
	FILE *filePointer;
	
	//running variable
	int i;
	
	//read data - no need to put it into else statement
	if((filePointer = fopen("pulse.txt", "r")) == NULL){
		printf("File could not be opened. Program terminated...");
		return 0;
	}
	printf("File opened successfully!\n");
	//data found - calculate the number of lines in the file - copy pointer
	int numberOfLines = 0;
	//the reason why it's an int and not a character is to handle EOF condition.
	//it will be converted into a character inside the loop
	int currentCharacter; 
	while((currentCharacter = fgetc(filePointer)) != EOF){
		if(currentCharacter == '\n'){
			numberOfLines = numberOfLines + 1;
			}
		}
	//file ends not with a newline, but with EOF character - therefore,
	//add 1 to numberOfLines	
	numberOfLines = numberOfLines + 1;
	powerSignal.N = numberOfLines;
	printf("Number of sampled points is %d \n", powerSignal.N);
	
	//allocate memory - of type double - pointer to rows
	powerSignal.data = malloc(powerSignal.N*sizeof(*powerSignal.data));
	//second dimension - two entries (timestamp & power)
	for(i = 0; i < powerSignal.N; i++){
		powerSignal.data[i] = malloc(2*sizeof(*powerSignal.data[i]));
	}
	
	//go back to the beginning of the file
	fseek(filePointer, 0, SEEK_SET);
	int parsed;
	//input file into the struct
	for(i = 0; i < powerSignal.N; i++){
		//lf, not 1f...
		fscanf(filePointer, "%lf %lf", &powerSignal.data[i][0], &powerSignal.data[i][1]);
		//printf("%.4e\t%.7e\n",powerSignal.data[i][0],powerSignal.data[i][1]);
	}
	//data loaded - we don't need the file anymore.
	fclose(filePointer);
	
	//find maximum pulse power.
	double tempPower = -DBL_MAX;
	int peakPowerPos = 0;
	for(i = 0; i < powerSignal.N; i++){
		if(powerSignal.data[i][1] > tempPower){
			tempPower = powerSignal.data[i][1];
			peakPowerPos = i;
		}
	}
	powerSignal.maxPower = tempPower;
	printf("Pulse peak power is %.6f \n", powerSignal.maxPower);
	
	//variables used for finding thev values.
	int leftAboveIndex, leftBelowIndex, rightBelowIndex, rightAboveIndex;
	
	//go through left side & find index which is just bigger than maxPower/2
	for(i = 0; i<peakPowerPos; i++){
		if(powerSignal.data[i][1] < powerSignal.maxPower/2){
			continue;
		}
		else{
			leftAboveIndex = i;
			leftBelowIndex = leftAboveIndex - 1;
			break;
		}
	}
	//go through right side & find index which is just smaller than maxPower/2
		for(i = peakPowerPos; i<powerSignal.N; i++){
		if(powerSignal.data[i][1] > powerSignal.maxPower/2){
			continue;
		}
		else{
			rightBelowIndex = i;
			rightAboveIndex = i-1;
			break;
		}
	}
	//assign the values of t.
	double t1, t2, t3, t4;
	t1 = powerSignal.data[leftBelowIndex][0];
	t2 = powerSignal.data[leftAboveIndex][0];
	t3 = powerSignal.data[rightBelowIndex][0];
	t4 = powerSignal.data[rightAboveIndex][0];
	
	//preparing them to be parsed by our "computeAverage" function. This isn't a good
	//scalable option, but it works for this simple exmaple.
	const int size = 2;
	double firstTime[size];
	firstTime[0] = t1; firstTime[1] = t2;
	double secondTime[size];
	secondTime[0] = t3; secondTime[1] = t4;
	
	double leftAvg, rightAvg, fwhm;
	leftAvg = computeAverage(firstTime, size);
	rightAvg = computeAverage(secondTime, size);
	
	fwhm = rightAvg - leftAvg;
	printf("Pulse FWHM is %.6f ", fwhm);
	//execution of the program is finished. Free up the memory.
	for (i = powerSignal.N-1; i >= 0; i--)
    {
        free(powerSignal.data[i]);
    }
    //Fre the second dimension of memory.
    free(powerSignal.data);
		

}


// computeAverage function definition.
double computeAverage(double *array, int arraySize){
	double temp = 0;
	for(int i=0; i<arraySize;i++){
		temp = temp + array[i];
	}
	return temp/arraySize;
}
	
	