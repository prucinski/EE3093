
#define AirportFlightTimetable

#include<iostream>
#include<random>
#include<string>
#include "FlightTimetableEntry.h"


//enumerators for choosing which one to print
enum tmtblCaseEnum { blankEntry = 0, Arrival, Departure, Both, stopEntry};

using namespace std;

class AirportFlightTimetable {
private:
	//defining rules for this class.
	const int maxDayDep = 38;
	const int maxDayArr = 34;
	const int maxHourDep = 4;
	const unsigned char minSep = 12;
	const int maxHourIntDep = 2;
	const int maxHourIntArr = 2;
	AirportEnum thisAirport = Copenhagen;
	FlightTimetableEntry arrivingFlights[];
public:
	AirportFlightTimetable(){
		arrivingFlights[maxDayDep];
	}
};

