#ifndef WeatherTag_h
#define WeatherTag_h

#include<iostream>
#include<random>
using namespace std;

class weatherTag{
	protected:
		bool init_flag;
		int month;
		int day;
		//a bootleg version of declaring how many days in a month - initialized in main
		static int dayNumberList[13];
		
		
	public:

		weatherTag(){
			month = -1;
			day = -1;
			init_flag = false;
		}
		weatherTag(const weatherTag& other){
			month = other.getMonth();
			day = other.getDay();
			init_flag = other.isTagSet();
			
		}
		bool operator > (const weatherTag& other) const {
			if(getMonth() > other.getMonth()){
				return true;	
			}
			else if (getMonth() == other.getMonth()){
				if(getDay() > other.getDay()){
					return true;
				}
				else{
					return false;
				}
			}
			else{
				return false;
			}
			
		}
		bool operator < (const weatherTag& other) const {
			if(getMonth() < other.getMonth()){
				return true;	
			}
			else if (getMonth() == other.getMonth()){
				if(getDay() < other.getDay()){
					return true;
				}
				else{
					return false;
				}
			}
			else{
				return false;
			}
			
		}
		bool operator == (const weatherTag& other) const {
			if(getMonth() == other.getMonth()){
				if(getDay() == other.getDay()){
					return true;	
				}
			}
			
			else{
				return false;
			}
				
		}
		weatherTag& operator = (const weatherTag& other){
			if((this != &other) &&(other.isTagSet())&&(!isTagSet())){
				setTag(other.getMonth(), other.getDay());
			}
			return *this;
		}
		
		
		bool isTagSet() const {
		return init_flag;
		}
		
		int getMonth() const{
			return month;
		}
		int getDay()const{
			return day;
		}
		
		void resetTag(){
			if(isTagSet()){
				init_flag = false;
				month = -1;
				day = -1;
			}
			else{
				cout<<"Error in resetTag() - tag already uninitialized"<<endl;
			}
			
		}
		bool setTag(int inpMonth, int inpDay){
			if(!isTagSet()){
				if(1<=inpMonth && inpMonth<=12){
					if(1<= inpDay && inpDay <= dayNumberList[inpMonth]){
						init_flag = true;
						month = inpMonth;
						day = inpDay;
						return true;
					}
					else{
						cout<<"Error in setTag() - wrong day value provided"<<endl;
					}
				}
				else{
					cout<<"Error in setTag() - wrong month value provided"<<endl;
				}
				
			}
			else{
				cout<<"Error in setTag() - tag already initialized"<<endl;
			}
			return false;
		}
		bool setRandomTag(){
			if(!isTagSet()){
				
				int randomMonth = 0;
				int randomDay = 0;
				//generating a random month in range 1-12
				while(randomMonth == 0){
					randomMonth = rand() % 13;
				}
				while(randomDay ==0){
					randomDay = rand() % (dayNumberList[randomMonth]+1);
				}
				setTag(randomMonth, randomDay);
				return true;
			}
			else{
				cout<<"Error in setRandomTag() - tag already initialized"<<endl;
				return false;
			}
			return false;	
		}
		bool getTag(int &givenMonth, int &givenDay) const{
			
			if(isTagSet()){
				//by reference
				givenMonth = month;
				givenDay = day;
				return true;
		
			}
			else{
				cout<<"Error in getTag() - tag not initialized";
				return false;
			}
			
		}
		void printTag() const{
			if(isTagSet()){
				cout<<"The tag was taken on this month: "<<getMonth()<< ", on this day: "<<getDay()<<endl;
			}
			else{
				cout<<"Error in printTag() - tag not initialized"<<endl;
			}
		
		
		}
		
		
};








#endif