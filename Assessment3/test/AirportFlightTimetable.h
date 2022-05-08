#ifndef AirportFlightTimetable_h


#define AirportFlightTimetable_h

#include<iostream>
#include<random>
#include<cmath>
#include<string>
#include "FlightTimetableEntry.h"


//enumerators for choosing which one to print
enum tmtblCaseEnum { blankEntry = 0, Arrival, Departure, Both, stopEntry};

using namespace std;

class AirportFlightTimetable {
private:
	//defining rules for this class.
	//Making them static is actually necessary so that the compiler knows
	//their values during compile time, otherwise it will refuse to create
	//the arrays.
	static const int maxDayDep = 38;
	static const int maxDayArr = 34;
	const int maxHourDep = 4;
	const unsigned char minSep = 12;
	const int maxHourIntDep= 2;
	const int maxHourIntArr = 2;
	AirportEnum thisAirport = Copenhagen;
	//I dont want to check the length of the array every time
	//I'm adding an entry. Therefore, I will just keep track of 
	//how many flights have arrived and departed in total per day.
	int howManyFlightsArrive;
	int howManyFlightsDepart;
	FlightTimetableEntry arrivingFlights[maxDayArr];
	FlightTimetableEntry departingFlights[maxDayDep];
	//have an arrays for counting how many flights are
	//leaving each hour. We will then access this array
	//and add one if a flight is added that specific hour.
	//very useful way for not having to go over the array
	//every single time. 24 entries: from 00:.. to 23:..
	int howManyDepartingFlightsThisHour[24] = {};
	int howManyDepartingIntFlightsThisHour[24] = {};
	int howManyArrivingIntFlightsThisHour[24] = {};
public:
	AirportFlightTimetable(){
		howManyFlightsArrive = 0;
		howManyFlightsDepart = 0;
	}

	bool checkEntryIsValid(const FlightTimetableEntry& test_entry, bool verbose = false) const {
		bool a = isArriving(test_entry);
		bool d = isDeparting(test_entry);
		bool domestic = FlightTimetableEntry::isDomestic(test_entry.getOrigin(), test_entry.getDest());
		unsigned char arrHour = test_entry.getArrHour();
		unsigned char arrMin = test_entry.getArrMin();
		unsigned char deptHour = test_entry.getDeptHour();
		unsigned char deptMin = test_entry.getDeptMin();

		//first, check if can be added.
		if (isTimetableFull(verbose)) {
			return false;
		}
		//check if is either arriving or departing.
		if (!(a || d)) {
			if (verbose) {
				cout << "Error - this entry does not relate to the Copenhagen airport." << endl;
			}
			return false;
		}

		//rules if arrival.
		if (a) {
			//check if arrival is specifically full.
			if (howManyFlightsArrive == maxDayArr) {
				return false;
			}
			//basic rules check.
			for (int i = 0; i < maxDayArr; i++) {
				FlightTimetableEntry temp = arrivingFlights[i];
				//if same airline...
				if (temp.getAirline() == test_entry.getAirline()) {
					//1st or: if same destination...
					if (temp.getDest() == test_entry.getDest()) {
						//and if same arrival hour.
						if (temp.getArrHour() == arrHour && temp.getArrMin() == arrMin) {
							if (verbose) {
								cout << "Error. There exists an entry with the same arrival time from this airline." << endl;
							}
						return false;
						}
					}
					//2nd or: if same flight code.
					if (temp.getFlightcode() == test_entry.getFlightcode()) {
						if (verbose) {
							cout << "Error. Flight with this flight code already exists" << endl;
							return false;
						}
					}
				}
				//advances rules check
				//12 minute separation between two flights from same origin.
				if (temp.getOrigin() == test_entry.getOrigin()) {
					int tempHourMinute = 60*(int)temp.getArrHour() + (int)temp.getArrMin();
					int flightHourMinute = 60 * (int)arrHour + (int)arrMin;
					if (abs(flightHourMinute - tempHourMinute) < 12) {
						if (verbose) {
							cout << "Error. There needs to be a 12 minute flight separation between arrivals." << endl;
						}
						return false;
					}


				}
			}
			//advanced rules check cont
			if (howManyFlightsArrive == maxDayArr) {
				if (verbose) {
					cout << "Error - maximum arrival capacity reached." << endl;
				}
				return false;
			}
			//checking for arriving international arriving flights.
			if (!domestic) {
				if (howManyArrivingIntFlightsThisHour[arrHour] == maxHourIntArr) {
					if (verbose) {
						cout << "Error - maximum arriving international flights per hour reached at hour " << (int)arrHour << endl;
					}
					return false;
				}
			}
			

		}
		//rules if departure.
		if (d) {
			//check if departure timetable full. Verbose in checkTimetableFull().
			if (howManyFlightsDepart == maxDayDep) {
				return false;
			}
			//basic rules check.
			for (int i = 0; i < maxDayDep; i++) {
				FlightTimetableEntry temp = departingFlights[i];
				//if same airline...
				if (temp.getAirline() == test_entry.getAirline()) {
					//1st or: if same origin...
					if (temp.getOrigin() == test_entry.getOrigin()) {
						//and if same departure hour.
						if (temp.getDeptHour() == deptHour && temp.getDeptMin() == deptMin) {
							if (verbose) {
								cout << "Error. There exists an entry with the same departure time from this airline." << endl;
							}
							return false;
						}
					}
					//2nd or: if same flight code.
					if (temp.getFlightcode() == test_entry.getFlightcode()) {
						if (verbose) {
							cout << "Error. Flight with this flight code already exists." << endl;
						}
						return false;
					}
				}
			}


			if (howManyFlightsDepart == maxDayDep) {
				if (verbose) {
					cout << "Error - maximum departure capacity reached." << endl;
				}
				return false;
			}
			if (howManyDepartingFlightsThisHour[deptHour] == maxHourDep) {
				if (verbose) {

					cout << "Error - maximum departing flights per hour reached at hour " << (int)deptHour << endl;
				}
				return false;
			}
			//checking for arriving international arriving flights.

			if (!domestic) {
				if (howManyDepartingIntFlightsThisHour[deptHour] == maxHourIntDep) {
					if (verbose) {
						cout << "Error - maximum departing international flights per hour reached at hour " << (int)deptHour << endl;
					}
					return false;
				}
			}
		}
		if (verbose) {
			cout << "All checks passed." << endl;
		}
		return true;
	}
	bool checkAndAddEntry(const FlightTimetableEntry& test_entry, bool verbose = false) {
		if (!checkEntryIsValid(test_entry, verbose)) {
			return false;
		}
		//this is kind of a bad practice since I'm repeating code from the other function, but I don't have any better ideas.
		bool a = isArriving(test_entry);
		bool d = isDeparting(test_entry);
		bool domestic = FlightTimetableEntry::isDomestic(test_entry.getOrigin(), test_entry.getDest());
		unsigned char arrHour = test_entry.getArrHour();
		unsigned char depHour = test_entry.getDeptHour();
		//add to arrival timetable.
		if (a) {
			arrivingFlights[howManyFlightsArrive] = test_entry;
			howManyFlightsArrive += 1;
			if (!domestic) {
				howManyArrivingIntFlightsThisHour[arrHour] += 1;
			}
			sortArrival();
		}
		//add to departure timetable
		if (d) {
			departingFlights[howManyFlightsDepart] = test_entry;
			howManyFlightsDepart += 1;
			howManyDepartingFlightsThisHour[depHour] += 1;
			if (!domestic) {
				howManyDepartingIntFlightsThisHour[depHour] += 1;
			}
			sortDeparture();
		}
		
		return true;
	}

	void printTimetable(tmtblCaseEnum ArrOrDepOrBoth = tmtblCaseEnum::Both) {
		cout << "This is the timetable. " << endl;
		int j = 0;
		switch (ArrOrDepOrBoth) {
		case 1:	//arrivals
			cout << "=======Arrivals to Copenhagen=======:" << endl;
			while(j<maxDayArr) {
				//running it with for loop was breaking it and I had no idea why.
				FlightTimetableEntry tempFlight = arrivingFlights[j];
				//cout << tempFlight.isInit() << endl;
				if (!tempFlight.isInit()) {
					break;
				}
				if (isArriving(tempFlight)) {
					cout << "Pos " << j<<":"<< std::string(4 -to_string(j).size(), ' ');
					tempFlight.printEntryForArrival();

				}
				j++;
			}
			cout << "======================================" << endl;
			break;

		case 2:	//departures
			cout << "======Departures from Copenhagen======:" << endl;
			while(j<maxDayDep) {
				FlightTimetableEntry tempFlight = departingFlights[j];
				if (!tempFlight.isInit()) {
					break;
				}
				if (isDeparting(tempFlight)) {
					cout << "Pos " << j << ":"<< std::string(4 -to_string(j).size(), ' ');
					tempFlight.printEntryForDeparture();
				}
				j++;
			}
			cout << "=====================================" << endl;
			break;
		case 3:
			cout << "========Arrivals to Copenhagen========:" << endl;
			while(j<maxDayArr) {
				FlightTimetableEntry tempFlight = arrivingFlights[j];
				if (!tempFlight.isInit()) {
					break;
				}
				if (isArriving(tempFlight)) {
					cout << "Pos " << j << ":" << std::string(4 - to_string(j).size(), ' ');;
					tempFlight.printEntryForArrival();

				}
				j++;
			}
			cout << "=======================================" << endl;
			cout << "======Departures from Copenhagen======:" << endl;
			j = 0;
			while(j<maxDayDep) {
				FlightTimetableEntry tempFlight = departingFlights[j];
				if (!tempFlight.isInit()) {
					break; 
				}
				if (isDeparting(tempFlight)) {
					cout << "Pos " << j << ":" << std::string(4 - to_string(j).size(), ' ');;
					tempFlight.printEntryForDeparture();
				}
				j++;
			}
			cout << "=======================================" << endl;
			break;
		default:
			cout << "Error: try 1, 2 or 3" << endl;
			break;
		}
	}
	//the reason why this is two functions is to be able to check whether 
	//a timetable entry is neither.
	bool isArriving(FlightTimetableEntry t) const{
		if (t.getDest() == thisAirport) {
			return true;
		}
		return false;
	}
	bool isDeparting(FlightTimetableEntry t) const{
		if (t.getOrigin() == thisAirport) {
			return true;
		}
		return false;
	}
	bool isTimetableFull(bool verbose = false) const {
		bool a = howManyFlightsArrive == maxDayArr;
		bool b = howManyFlightsDepart == maxDayDep;
		if (a && verbose) {
			cout << "Arrival timetable is full" << endl;
		}
		if (b && verbose) {
			cout << "Departure timetable is full" << endl;
		}
		//task is not clear enough. Is it when both are full or either?
		if (a && b) {
			if (verbose) {
				cout << "Aborting..." << endl;
			}
			return true;
		}
		return false;

	}
	//functions for sorting. Snatching my own code from previous assessment.
	void sortDeparture(){
		int currentIndex = 0;
		int stopHere = maxDayDep;
		FlightTimetableEntry sorted[maxDayDep];
		//employing counting sort -  works and is very elegant.
		//finding how many elements to go through.
		for (int i = 0; i < maxDayDep; i++) {
			if (!departingFlights[i].isInit()) {
				stopHere = i;
				break;
			}
		}
		//going through found no of elements
		for (int i = 0; i < stopHere; i++) {
			int lowerThan = 0; 
			for (int j = 0; j < stopHere; j++) {
				if (departingFlights[i] < departingFlights[j]) {
					lowerThan++;
				}
			}
			//when two entries are equal - move to the next empty spot in array
			while (sorted[lowerThan].isInit()) {
				lowerThan++;
			}
			sorted[lowerThan] = departingFlights[i];	
		}
		for (int i = 0; i < stopHere; i++) {
			departingFlights[i] = sorted[i];
		}

	}
	void sortArrival(){
		int currentIndex = 0;
		int stopHere = maxDayArr;
		FlightTimetableEntry sorted[maxDayArr];
		for (int i = 0; i < maxDayDep; i++) {
			if (!arrivingFlights[i].isInit()) {
				stopHere = i;
				break;
			}
		}
		for (int i = 0; i < stopHere; i++) {
			int lowerThan = 0;
			for (int j = 0; j < stopHere; j++) {
				if (arrivingFlights[i] > arrivingFlights[j]) {
					lowerThan++;
				}
			}

			while (sorted[lowerThan].isInit()) {
				lowerThan++;
			}
			sorted[lowerThan] = arrivingFlights[i];
		}
		for (int i = 0; i < stopHere; i++) {
			arrivingFlights[i] = sorted[i];
		}
		
	}
};
#endif // !AirportFlightTimetable_h
