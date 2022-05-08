#ifndef WeatherLog_h
#define WeatherLog_h

#include "WeatherTag.h"
#include "WeatherMeasurement.h"

class weatherLog{
	public:
		weatherTag wtag;
		weatherMeasurement wmes;
		
	//empty constructor	
	weatherLog(){	}
		
	//constructor when weathertag and weathermesaurement are provided
	weatherLog(weatherTag t, weatherMeasurement m){
		wtag = t;
		wmes = m;
	}
	weatherLog(const weatherLog& other){
		wtag = other.getWeatherTag();
		wmes = other.getWeatherMeasurement();
		
	}
	
	bool operator == (const weatherLog& other) const {
		if(isLogSet() && other.isLogSet() && getWeatherTag() == other.getWeatherTag() && getWeatherMeasurement() == other.getWeatherMeasurement()){	
				return true;	
			}
		
		else{
			return false;
		}				
	}
	bool operator < (const weatherLog& other) const {
		if(getWeatherMeasurement() < other.getWeatherMeasurement()){	
				return true;	
			}
		else if(getWeatherMeasurement() == other.getWeatherMeasurement()){
			if(getWeatherTag()>other.getWeatherTag()){
				return true;
			}
		}
		else{
			return false;
		}				
	}

	bool operator > (const weatherLog& other) const {
		if(getWeatherMeasurement() > other.getWeatherMeasurement()){	
				return true;	
			}
		else if(getWeatherMeasurement() == other.getWeatherMeasurement()){
			if(getWeatherTag()<other.getWeatherTag()){
				return true;
			}
		}
		else{
			return false;
		}				
	}
	
	weatherLog& operator = (const weatherLog& other){
			if((this != &other) &&(other.isLogSet())&&(!isLogSet())){
				wtag = other.getWeatherTag();
				wmes = other.getWeatherMeasurement();
			}
			return *this;
		}
	
	weatherTag getWeatherTag() const{
		return wtag;
	}
	weatherMeasurement getWeatherMeasurement() const{
		return wmes;
	}
	bool isLogSet() const{
		return (wtag.isTagSet() && wmes.isMeasurementSet());
	}
	void reset(){
		if(isLogSet()){
		wtag.resetTag();
		wmes.resetMeasurement();
		}
	}
	
	bool setRandomLog(){
		//these are forced to succeed.
		if(!isLogSet()){
			wtag.setRandomTag();
			wmes.setRandomMeasurement();
			return true;
		}
		else{
			cout<<"Error in setRandomLog() - log already initialized"<<endl;
			return false;
		}
		
	}
	void printLog() const{
		if(isLogSet()){
			wtag.printTag();
			wmes.printMeasurement();
			cout<<endl;
		}
		else{
			cout<<"Error in printLog() - log is not initialized"<<endl;
		}
	}
	
	
		
		
};

void sortWeatherLogArray(weatherLog in[], weatherLog out[], int size){
	int currentIndex = 0;
	//employing counting sort -  works and is very elegant.
	for(int i = 0; i<size; i++){
		int lowerThan = 0;
		for(int j = 0; j<size; j++){
			if(in[i]>in[j]){
				lowerThan++;
			}
		}
		//when two entries are equal - move to the next empty spot in array
		while(out[lowerThan].isLogSet()){
			cout<<"Wow! If randomly generated, then a super rare thing is happening at this index: "<< i<<endl;
			lowerThan++;
		}
		out[lowerThan] = in[i];

		
		
	}
}

void filterWeatherLogArray(weatherLog in[], weatherLog out[], int size, weatherLog bound1, weatherLog bound2){
	weatherLog sorted[size];
	//sorting the input array for immedieate filtering;
	sortWeatherLogArray(in, sorted, size);
	//creating an average weather log. Probably not the best way of doing it but no instructions were provided.
	weatherMeasurement m;
	weatherTag t;
	float theHumidity = (bound1.getWeatherMeasurement().getHumidity()+bound2.getWeatherMeasurement().getHumidity())/2;
	m.setMeasurement(theHumidity);
	int theMonth = (bound1.getWeatherTag().getMonth() + bound2.getWeatherTag().getMonth())/2;
	int theDay = (bound1.getWeatherTag().getDay() + bound2.getWeatherTag().getDay())/2;
	t.setTag(theMonth, theDay);
	weatherLog avgLog(t,m);
	cout<<"the following average log has been produced: "<<endl;
	avgLog.printLog();
	
	int j = 0;
	//now the actual code.
	for(int i = 0; i<size; i++){
		if(sorted[i]>avgLog){
			out[j] = sorted[i];
			j++;
		}
	}
	
	
	
	
	
	
	
	
	
}


#endif