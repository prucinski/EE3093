#ifndef WeatherMeasurement_h
#define WeatherMeasurement_h

#include<iostream>
#include<random>
using namespace std;

class weatherMeasurement{
	protected:
		bool init_flag;
		float humidity;
		
		
		
	public:

		weatherMeasurement(){
			humidity = -1;
			init_flag = false;
		}
		weatherMeasurement(const weatherMeasurement& other){
			humidity = other.getHumidity();
			init_flag = other.isMeasurementSet();
		}
		bool operator > (const weatherMeasurement& other) const {
			if (getHumidity() > other.getHumidity()){
				return true;
			}
			else{
				return false;
			}
		}
		bool operator < (const weatherMeasurement& other) const {
			if (getHumidity() < other.getHumidity()){
				return true;
			}
			else{
				return false;
			}
		}
		bool operator == (const weatherMeasurement& other) const {
			if (getHumidity() == other.getHumidity()){
				return true;
			}
			else{
				return false;
			}
		}
		weatherMeasurement& operator = (const weatherMeasurement& other){
			if((this != &other) &&(other.isMeasurementSet())&&(!isMeasurementSet())){
				setMeasurement(other.getHumidity());
			}
			return *this;
		}
		bool isMeasurementSet() const {
		return init_flag;
		}
		
		float getHumidity() const{
			return humidity;
		}
		
		void resetMeasurement(){
			if(isMeasurementSet()){
				init_flag = false;
				humidity = -1;
			}
			else{
				cout<<"Error in resetMeasurement() - measurement already uninitialized"<<endl;
			}
			
		}
		bool setMeasurement(float inpHumidity){
			if(!isMeasurementSet()){
				if(0<=inpHumidity && inpHumidity<=100){
					humidity = inpHumidity;
					init_flag = true;
					return true;
				
			
				}
				else{
					cout<<"Error in setMeasurement() - wrong humidity value provided"<<endl;
				}	
			}
			else{
				cout<<"Error in setMeasurement() - measurement already initialized"<<endl;
			}
			return false;
		}
		bool setRandomMeasurement(){
			if(!isMeasurementSet()){
				
				int randomMeasurementWhole = 0;
				//cheating ;)
				float randomMeasurementComma = 0;
				float randomMeasurement = 0;
				//generating a random month in range 1-100
				while(randomMeasurement == 0){
					randomMeasurementWhole = rand()%100;
					randomMeasurementComma = rand()%100;
					randomMeasurement = randomMeasurementWhole + randomMeasurementComma/100;
					}
				setMeasurement(randomMeasurement);
				return true;
			}
			else{
				cout<<"Error in setRandomMeasurement() - measurement already initialized"<<endl;
				return false;
			}	
			return false;
		}
		bool getMeasurement(float &given) const{
			
			if(isMeasurementSet()){
				//by reference
				given = humidity;
				
				return true;
		
			}
			else{
				cout<<"Error in getMeasurement() - measurement not initialized";
				return false;
			}
			
		}
		void printMeasurement() const{
			if(isMeasurementSet()){
				cout<<"The measured humidity is: "<<humidity<<"%"<<endl;
			}
			else{
				cout<<"Error in printMeasurement() - tag not initialized"<<endl;
			}
		
		
		}
		
		
};




#endif