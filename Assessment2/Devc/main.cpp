#include <iostream>
#include "WeatherTag.h"
#include "WeatherMeasurement.h"
#include "WeatherLog.h"

#include<time.h>
/* initialization of static variable(s)*/
int weatherTag::dayNumberList[13] = {-1,31,28,31,30,31,30,31,31,30,31,30,31};

void exampleTest_Tag_and_Measurements()
{
	weatherTag testTagA, testTagB; 
	cout << " Test WeatherTag" << endl << endl;
	cout << "Using setRandomTag() and then printTag():" << endl;
	if (testTagA.setRandomTag()){ 
		testTagA.printTag();
	}
	else{
		cout << "Set function failed." << endl;
	}
	cout << endl << endl;
	
		cout<<"Test whether getTag() works properly" <<endl;
	int myMonth, myDay;
	if(testTagA.getTag(myMonth, myDay)){
		cout<<"myMonth initialized to: "<<myMonth<<endl;
		cout<<"myDay initialized to: "<<myDay<<endl<<endl;
	}
	else{
		cout<<"getTag() failed"<<endl;
	}
	
	cout<<"Test WeatherTag - manual input - try input value when object already init."<<endl<<endl;
	if(testTagA.setTag(1,24)){
		testTagA.printTag();

	}
	else{
		cout<<"Task failed successfully."<<endl<<endl;
	}
	
	testTagA.resetTag();
	cout<<"Test WeatherTag - manual input - input must fail (30th of February)"<<endl<<endl;
	if(testTagA.setTag(2,31)){
		testTagA.printTag();
		cout<<"This shouldn't have happened! Check code."<<endl;
	}
	else{
		cout<<"Task failed successfully."<<endl<<endl;
	}
	cout<<"Test resetTag() - check if unitialized object can be reset"<<endl;
	testTagA.resetTag();
	
	cout<<"Test isTagSet() and printTag() on an uninitialized object"<<endl;
	if(!testTagA.isTagSet()){
			testTagA.printTag();
			cout<<"Task failed successfully"<<endl<<endl;
	}
	else{
		cout<<"Tag is still set - check code."<<endl<<endl;
	}
	
	cout<<endl<<endl;

	weatherMeasurement testMeasurementA, testMeasurementB; 
	cout << " Test WeatherMeasurement" << endl << endl;
	cout << "Using setRandomMeasurement() and then printMeasurement():" << endl;
	if (testMeasurementA.setRandomMeasurement()){ 
		testMeasurementA.printMeasurement();
	}
	else{
		cout << "Set function failed." << endl;
	}
	cout << endl << endl;
	
		cout<<"Test whether getMeasurement() works properly" <<endl;
	float myHumidity;
	if(testMeasurementA.getMeasurement(myHumidity)){
		cout<<"myHumidity initialized to: "<<myHumidity<<endl;
	}
	else{
		cout<<"getMeasurement() failed"<<endl;
	}
	
	cout<<"Test WeatherMeasurement - manual input - try input value when object already init."<<endl<<endl;
	if(testMeasurementA.setMeasurement(24.5)){
		testMeasurementA.printMeasurement();

	}
	else{
		cout<<"Task failed successfully."<<endl<<endl;
	}
	
	testMeasurementA.resetMeasurement();
	cout<<"Test WeatherTag - manual input - input must fail (105%)"<<endl<<endl;
	if(testMeasurementA.setMeasurement(105)){
		testMeasurementA.printMeasurement();
		cout<<"This shouldn't have happened! Check code."<<endl;
	}
	else{
		cout<<"Task failed successfully."<<endl<<endl;
	}
	cout<<"Test resetMeasurement() - check if unitialized object can be reset"<<endl;
	testMeasurementA.resetMeasurement();
	
	cout<<"Test isMeasurementSet() and printMeasurement() on an uninitialized object"<<endl;
	if(!testMeasurementA.isMeasurementSet()){
			testMeasurementA.printMeasurement();
			cout<<"Task failed successfully"<<endl<<endl;
	}
	else{
		cout<<"Measurement is still set - check code."<<endl<<endl;
	}
	
	cout<<"Test WeatherTag"<<endl<<endl<<"set A and B with Random values then print:" << endl;
	testTagA.setRandomTag(); 
	testTagB.setRandomTag();
	cout << "Object A: "; testTagA.printTag();
	 cout << "Object B: "; testTagB.printTag();
	cout << "then test A < B, A == B, A > B" << endl;
	if (testTagA < testTagB){
		cout << "A < B is True." << endl;
	}	
	if (testTagA == testTagB){
		cout << "A == B is True." << endl;
	}
	if (testTagA > testTagB){
		cout << "A > B is True." << endl;
		cout << endl << endl;
	}
	cout<<"Test WeatherTag - = operator & copy constructor"<<endl<<endl<<"set A with Random values, set B = A and weatherMeasurement C(A) :" << endl;
// insert additional instructions to test any remaining operators in Table 4
	testTagA.resetTag();
	testTagB.resetTag();
	testTagA.setRandomTag(); 
	
	testTagB = testTagA;
	weatherTag testTagC(testTagA);

	cout<<"Object A: ";testTagA.printTag();
	cout<<"Object B: ";testTagB.printTag();
	cout<<"Object C: ";testTagC.printTag();
	cout << "then test A < B, A == B, A > B" << endl;
	if (testTagA < testTagB){
		cout << "A < B is True." << endl;
	}
	if (testTagA == testTagB){
		cout << "A == B is True." << endl;
	}
	if (testTagA > testTagB){
		cout << "A > B is True." << endl;
		cout << endl << endl;
	}
	if (testTagA < testTagC){
		cout << "A < C is True." << endl;
	}
	if (testTagA == testTagC){
		cout << "A == C is True." << endl;
	}
	if (testTagA > testTagC){
		cout << "A > C is True." << endl;
		cout << endl << endl;
	}
	
	cout<<"Test WeatherMeasurement"<<endl<<endl<<"set A and B with Random values then print:" << endl;
	testMeasurementA.setRandomMeasurement(); 
	testMeasurementB.setRandomMeasurement();
	cout << "Object A: "; testMeasurementA.printMeasurement();
	 cout << "Object B: "; testMeasurementB.printMeasurement();
	cout << "then test A < B, A == B, A > B" << endl;
	if (testMeasurementA < testMeasurementB){
		cout << "A < B is True." << endl;
	}	
	if (testMeasurementA == testMeasurementB){
		cout << "A == B is True." << endl;
	}
	if (testMeasurementA > testMeasurementB){
		cout << "A > B is True." << endl;
		cout << endl << endl;
	}
	
	cout<<"Test WeatherMeasurement - = operator & copy constructor"<<endl<<endl<<"set A with Random values, set B = A and weatherMeasurement C(A) :" << endl;
// insert additional instructions to test any remaining operators in Table 4
	testMeasurementA.resetMeasurement();
	testMeasurementB.resetMeasurement();
	testMeasurementA.setRandomMeasurement(); 
	
	testMeasurementB = testMeasurementA;
	weatherMeasurement testMeasurementC(testMeasurementA);

	cout<<"Object A: ";testMeasurementA.printMeasurement();
	cout<<"Object B: ";testMeasurementB.printMeasurement();
	cout<<"Object C: ";testMeasurementC.printMeasurement();
	cout << "then test A < B, A == B, A > B" << endl;
	if (testMeasurementA < testMeasurementB){
		cout << "A < B is True." << endl;
	}
	if (testMeasurementA == testMeasurementB){
		cout << "A == B is True." << endl;
	}
	if (testMeasurementA > testMeasurementB){
		cout << "A > B is True." << endl;
		cout << endl << endl;
	}
	if (testMeasurementA < testMeasurementC){
		cout << "A < C is True." << endl;
	}
	if (testMeasurementA == testMeasurementC){
		cout << "A == C is True." << endl;
	}
	if (testMeasurementA > testMeasurementC){
		cout << "A > C is True." << endl;
		cout << endl << endl;
	}


	
}
void testLogOperators(weatherLog a, weatherLog b){
	cout << "Obj A: "; a.printLog();
	cout <<endl << "Obj B: "; b.printLog();
	cout << "Test A < B, A == B, A > B" << endl;
	if (a< b){
		cout << "A < B is True." << endl;
	}	
	if (a == b){
		cout << "A == B is True." << endl;
	}
	if (a > b){
		cout << "A > B is True." << endl;	
	}
	cout << endl << endl;
	
}

void testLog(){
	
	//I personally believe setting them into else-if statements is redundant.
	//It makes it look much worse, and we're testing for states we'll never reach
	//anyway.
	cout<<"Testing setRandomLog() and printLog().."<<endl<<endl;
	weatherLog testA, testB, testC;
	testA.setRandomLog();
	testA.printLog();
	cout<<"Testing if setRandomLog() behaves properly when log set"<<endl<<endl;
	testA.setRandomLog();
	cout<<endl<<"Is testA set? Ans: "<<testA.isLogSet()<<endl;
	
	cout<<"Testing operator ="<<endl<<endl;;
	testB = testA;

	testLogOperators(testA, testB);
	
	cout<<"Testing copy constructor weatherLog B(A)"<<endl<<endl;
	testC = testA;

	testLogOperators(testA, testC);
	
	cout<<"Testing random comparisons..."<<endl<<endl;
	testB.reset();
	cout<<"Reseting testB... "<<endl;
	cout<<"Is testB set? Ans: "<<testB.isLogSet()<<endl<<"Setting random value for testB..."<<endl<<endl;
	testB.setRandomLog();
	testLogOperators(testA, testB);
	weatherMeasurement testMes;
	
	//testing for equality when measurements are the same
	testMes.setMeasurement(4.4);
	weatherTag testTag1, testTag2;
	testTag1.setRandomTag();
	testTag2.setRandomTag();
	
	weatherLog testEqual(testTag1, testMes);
	weatherLog testEqual2(testTag2, testMes);
	cout<<"Testing comparisons when measurements are the same..."<<endl<<endl;
	testLogOperators(testEqual, testEqual2);
	
	
	
	
	
	

}
void sortWithArrays(){
	const int size = 10;
	weatherLog inArray[size];
	weatherLog outArray[size];
	cout<<endl<<endl<<"---UBSORTED ARRAY HERE:---"<<endl<<endl;
	//randomly fill array with data
	for(int i = 0; i<size; i++){
		inArray[i].setRandomLog();
		inArray[i].printLog();
	}
	
	cout<<endl<<endl<<"---SORTED ARRAY HERE:---"<<endl<<endl;
	
	sortWeatherLogArray(inArray, outArray, size);
	//print results, ascending order
	for(int i = 0; i<size; i++){
		outArray[i].printLog();
	}
	
}
void filterWithArrays(){
	const int size = 10;
	weatherLog inArray[size];
	weatherLog outArray[size];
	weatherLog b1, b2;
	b1.setRandomLog();
	b2.setRandomLog();
	cout<<endl<<endl<<"---UNFILTERED ARRAY HERE:---"<<endl<<endl;
	for(int i = 0; i<size; i++){
		inArray[i].setRandomLog();
		inArray[i].printLog();
	}
	
	cout<<endl<<endl<<"The average logs are as follows:"<<endl<<"Boundary1:"<<endl;
	b1.printLog();
	cout<<"Boundary2: "<<endl;
	b2.printLog();
	
	filterWeatherLogArray(inArray, outArray, size, b1, b2);
	
	cout<<endl<<endl<<"---FILTERED ARRAY HERE:---"<<endl<<endl;
	for(int i = 0; i<size; i++){
		if(!outArray[i].isLogSet()){
			break;
		}
		outArray[i].printLog();
	}
	
	
}


int main(int argc, char** argv) {
	srand(time(0));
	//exampleTest_Tag_and_Measurements();
	//testLog();
	//sortWithArrays();
	filterWithArrays();

	



}
