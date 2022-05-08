#ifndef FlightTimetableEntry_h
#define FlightTimetableEntry_h

#include<iostream>
#include<random>
#include<string>


//enumerators for cities and airline ids
enum AirportEnum { blankPort = 0, Aberdeen, London, Manchester, Copenhagen, Esbjerg, stopPort };
enum AirlinesEnum { blankLine = 0, BA, SK, KL, EZY, LM, stopLine };

using namespace std;

class FlightTimetableEntry {

private:
	AirportEnum origin;
	AirportEnum destination;
	AirlinesEnum airlineID;
	int fCode;
	bool init_flag;
	unsigned char dept_hour;
	unsigned char dept_min;
	//these will be implicit - figure it out
	unsigned char arr_hour;
	unsigned char arr_min;
	unsigned char flight_hour;
	unsigned char flight_min;

public:
	bool domestic;
	static std::string flightDurations[6][6];
	bool isInit() const {
		return init_flag;
	}
	
	//used for comparing arrival times for sorting...
	bool operator > (const FlightTimetableEntry& other) const {
		if (getArrHour() > other.getArrHour()) {
			return true;
		}
		else if (getArrHour() == other.getArrHour()) {
			if (getArrMin() > other.getArrMin()) {
				return true;
			}
			return false;
		}
		else {
			return false;
		}
	}
	//used for comparing departure times for sorting...
	//I'm actually cheating and using it the opposite way.
	bool operator < (const FlightTimetableEntry& other) const {
		if (getDeptHour() > other.getDeptHour()) {
			return true;
		}
		else if (getDeptHour() == other.getDeptHour()) {
			if (getDeptMin() > other.getDeptMin()) {
				return true;
			}
			return false;
		}
		else {
			return false;
		}
	}

	FlightTimetableEntry() {
		init_flag = false;
		origin = blankPort;
		destination = blankPort;
		airlineID = blankLine;
		fCode = -1;
		dept_hour = 99;
		dept_min = 999;
	}
	//these getters are used in AirportFlightTimetable.h. They're not really meant to be used as public, but it's the easiest way.
	AirportEnum getOrigin() const{
		//not putting into an else-if statement because it will return a blank one either way.
		return origin;
	}
	AirportEnum getDest() const{
		return destination;
	}
	AirlinesEnum getAirline() const {
		return airlineID;
	}
	unsigned char getArrHour() const {
		return arr_hour;
	}
	unsigned char getDeptHour() const {
		return dept_hour;
	}
	unsigned char getArrMin() const {
		return arr_min;
	}
	unsigned char getDeptMin() const {
		return dept_min;
	}
	int getFlightcode() const {
		return fCode;
	}
	bool checkAndSetFTE(AirportEnum orig, AirportEnum dest, AirlinesEnum airID, int flCode, unsigned char dept_hr, unsigned char dept_mn) {
		if (!isInit()) {
			if (!checkEntryVals(orig, dest, airID, flCode, dept_hr, dept_mn)) {
				return false;
			}
			origin = orig;
			destination = dest;
			airlineID = airID;
			fCode = flCode;
			dept_hour = dept_hr;
			dept_min = dept_mn;
			getFlightDurationTime(origin, destination, flight_hour, flight_min);
			getFlightArrivalTime(origin, destination, dept_hour, dept_min, arr_hour, arr_min);
			init_flag = true;
			return true;
		}
		else {
			cout << "Error (checkAndSetFTE) -  FTE is already checked" << endl;
			return false;
		}
	}
	bool setRandomFTE() {
		if (!isInit()) {
			//creating random origin, destination and provider.
			int theOrigin = RandomValInBounds(1, 6);
			AirportEnum o = (AirportEnum)theOrigin;
			int theDest = RandomValInBounds(1,6);
			int airlineID = RandomValInBounds(1, 6);
			AirlinesEnum ai = (AirlinesEnum)airlineID;
			while (theOrigin == theDest) {
				theDest = RandomValInBounds(1, 6);
			}
			AirportEnum d = (AirportEnum)theDest;
			//cheating by creating random date within all airports departures
			int theDepartureHr = RandomValInBounds(6, 21);
			int theDepartureMin = RandomValInBounds(0, 60);
			unsigned char dh = theDepartureHr;
			unsigned char dm = theDepartureMin;
			unsigned char ah, am;
			//check if domestic. Get provider. 2nd digit is the hardest. 
			int firstDigit = 0;
			int secondDigit = 300;
			if (!isDomestic(o, d)) {
				firstDigit = 5000;
			}
			getFlightArrivalTime(o, d, dh, dm, ah, am);
			if (ah < 12) {
				secondDigit = 100;
			}
			else if (dh >= 18) {
				secondDigit = 600;
			}
			int thirdDigit = RandomValInBounds(20 * (airlineID - 1), 20 * airlineID);
			int flightNo = firstDigit + secondDigit + thirdDigit;
			//finally, create entry. I think I might have overcomplicated the process.
			checkAndSetFTE(o, d, ai, flightNo, dh, dm);
			return true;
		}
		else {
			cout<<"Error (setRandomFTE) - FTE is already set"<<endl;
			return false;
		}
	}
	//my reset is lazy. It only gives a heads up that values can be overwritten.
	//But that is how hard drives work anyway.
	void reset() {
		init_flag = false;
	}
	bool getFTE(AirportEnum& orig, AirportEnum& dest, AirlinesEnum& airID, int&
	flCode, unsigned char& dept_hr, unsigned char& dept_mins, unsigned char& arriv_hr,
	unsigned char& arriv_min, unsigned char& durat_hr, unsigned char& durat_min) const {
		if (isInit()) {
			orig = origin;
			dest = destination;
			airID = airlineID;
			flCode = fCode;
			dept_hr = dept_hour;
			dept_mins = dept_min;
			arriv_hr = arr_hour;
			arriv_min = arr_min;
			durat_hr = flight_hour;
			durat_min = flight_min;
			return true;
		}
		return false;
	}

	void printEntry()const {
		if (isInit()) {
			cout << "Flight from " << value2string(origin) << " to " << value2string(destination) << endl;
			cout << "The provider for the flight is " << value2string(airlineID) << " with flight code " << value2string(fCode) << endl;
			cout << "It departs at " << value2string(dept_hour, dept_min) << " and flies for " << value2string(flight_hour, flight_min) << endl;
			cout << "It will happily arrive at it's destination at local time " << value2string(arr_hour, arr_min) << endl;
		}
		else {
			cout << "Error - obj not initialized" << endl;
		}
	}
	void printEntryForArrival()const {
		if (isInit()) {
			cout << value2string(origin)<<std::string(15-value2string(origin).size(), ' ')<< value2string(arr_hour, arr_min) << std::string(8 - value2string(arr_hour, arr_min).size(), ' ') <<value2string(airlineID)<< value2string(fCode) << endl;
		}
		else {
			cout << "Error - obj not initialized" << endl;
		}
	}
	void printEntryForDeparture()const {
		if (isInit()) {
			cout << value2string(destination) << std::string(15 - value2string(destination).size(), ' ') << value2string(dept_hour, dept_min)<< std::string(8 - value2string(arr_hour, arr_min).size(), ' ') << value2string(airlineID)<<value2string(fCode)<< endl;
		}
		else {
			cout << "Error - obj not initialized" << endl;
		}
	}


	//static functions.
	static bool getFlightDurationTime(AirportEnum orig, AirportEnum dest, unsigned char& out_hrs, unsigned char& out_mins) {
		if(isOriginDestValid(orig, dest)){
			std::string tableEntry = flightDurations[orig][dest];
			int out_hrs_temp = extractHour(tableEntry);
			int out_mins_temp = extractMinute(tableEntry);
			out_hrs = (unsigned char)out_hrs_temp;
			out_mins = (unsigned char)out_mins_temp;
			return true;
			
		}
		else {
			return false;
		}
	}
	static bool isOriginDestValid(AirportEnum orig, AirportEnum dest) {
		if (orig > blankPort && orig < stopPort) {
			if (orig != dest && dest > blankPort && dest < stopPort) {
			return true;
			}
			else {
				cout << "Error with destination: " << dest<< endl;
			}
		}
		else {
			cout << "Error with origin" << endl;
		}
		
		return false;
	}
	static bool isDomestic(AirportEnum orig, AirportEnum dest) {
		if (((orig == 1 || orig == 2 || orig == 3) && (dest == 4 || dest == 5)) || ((orig == 4 || orig == 5) && (dest == 1 || dest == 2 || dest == 3))) {
			return false;
		}
		return true;
	}
	static bool getFlightArrivalTime(AirportEnum orig, AirportEnum dest, unsigned char dpt_hrs_loc, unsigned char dpt_min_loc, unsigned char& arr_hrs_loc, unsigned char& arr_min_loc) {
		if (isOriginDestValid(orig, dest)) {
			int timeForward;
			//checking whether we need to push the time back, forward or not. This isn't a good programatical solution but it works for this small data set.
			if (orig == 1 || orig == 2 || orig == 3) {
				if (dest == 4 || dest == 5) {
					timeForward = 1;
				}
				else {
					timeForward = 0;
				}
			}
			else {
				if (dest == 4 || dest == 5) {
					timeForward = 0;
				}
				else {
					timeForward = -1;
				}
			}
			//we have now computed whether to push time forward or not. Let's calculate the time of arrival now.
			unsigned char a, b;
			getFlightDurationTime(orig, dest, a, b);
			int tempMinute = (int)b + (int)dpt_min_loc;
			if (tempMinute >= 60) {
				tempMinute -= 60;
				timeForward += 1;
			}
			int tempHour = int(a) + int(dpt_hrs_loc) + timeForward;
			arr_hrs_loc = tempHour;
			arr_min_loc = tempMinute;
			return true;

		}
		return false;
	}

	static bool checkEntryVals(AirportEnum orig, AirportEnum dest, AirlinesEnum airID, int flCode, unsigned char dept_hour, unsigned char dept_min) {
		int dept_hr = (int)dept_hour;
		int dept_m = (int)dept_min;
		if (!(0 <= dept_hr && dept_hr <= 23 && 0 <= dept_m && dept_m <= 59)) {
			cout << "Error - check whether hour and minutes are in normal format (00:00-23:59)"<<endl;
			return false;
		}
		bool timeInside = false;
		if (isOriginDestValid(orig, dest)) {
			//check if departure time is fine.
			switch (orig) {
			case 1:	//Aberdeen
				if ((6 <= dept_hour && dept_hour <= 20) || (dept_hour == 5 && dept_min >= 30)) {
					timeInside = true;
				}
				break;
			case 2:	//London
				if ((5 <= dept_hour && dept_hour <= 20) || (dept_hour == 4 && dept_min >= 30) || (dept_hour == 21 && dept_min <= 10)) {
					timeInside = true;
				}
				break;
			case 3:	//Manchester
				if ((5 <= dept_hour && dept_hour <= 20) ||  (dept_hour == 21 && dept_min <= 5)) {
					timeInside = true;
				}
				break;
			case 4:	//Copenhagen
				if ((5 <= dept_hour && dept_hour <= 20) || (dept_hour == 21 && dept_min <= 45)) {
					timeInside = true;
				}
				break;
			case 5:	//Esbjerg
				if ((6 <= dept_hour && dept_hour <= 20)) {
					timeInside = true;
				}
				break;
			default:
				cout << "This should be unreachable as the check for the enum has been already done. Inspect!" << endl;
				return false;
			}
			//check if flight code is fine - is it domestic or not?
			std::string flightCode = value2string(flCode);
			if (isDomestic(orig, dest)) {
				if (flightCode.substr(0, 1) != "0") {
					cout << "Error. Flight is domestic but it doesn't have the domestic code." << endl;
					
					return false;
				}
			}
			else {
				if (flightCode.substr(0, 1) != "5") {
					cout << "Error. Flight is international but it doesn't have the international code." << endl;
					return false;
				}
			}
			//First digit has been checked. Now check the second digit...
			unsigned char arrivalHour, arrivalMinute;
			getFlightArrivalTime(orig, dest, dept_hour, dept_min, arrivalHour, arrivalMinute);
			arrivalHour = (int)arrivalHour;
			arrivalMinute = (int)arrivalMinute;
			if (arrivalHour < 12) {
				if (flightCode.substr(1, 1) != "1") {
					cout << "Error. Flight arrives before noon but it's second digit isn't 1." << endl;
					return false;
				}
			}
			else if (dept_hour >= 18) {
				if (flightCode.substr(1, 1) != "6") {
					cout << "Error. Flight departs and arrives after 6pm, but it's second digit isn't 6." << endl;
					return false;
				}
			}
			else {
				if (flightCode.substr(1, 1) != "3") {
					cout << "Error. This flight is expected to have 3 as it's second digit (as it's not 2 or 6)." << endl;
					return false;
				}
			}
			
			//now check the third and fourth digit...
			int lastTwo = std::stoi(flightCode.substr(2, 2));
			//check based on each case of Airlines Enum
			if (!(20* ((int)airID-1) <= lastTwo && lastTwo < 20 * int(airID))) {
				cout << "Error. Last two digits of the flight ID does not match the airline" << endl;
				return false;
			}
			//if passed all the checks, return true;
			return true;
		}		
		return false;
	}
	static std::string value2string(AirlinesEnum airlineID) {
		switch (airlineID) {
		case 1:
			return "BA";
		case 2:
			return "SK";
		case 3:
			return "KL";
		case 4:
			return "EZY";
		case 5:
			return "LM";
		default:
			return "Error (airlineID) - not initialized";
		}
	}

	static std::string value2string(AirportEnum airport) {
		switch (airport) {
		case 1:
			return "Aberdeen";
		case 2:
			return "London";
		case 3:
			return "Manchester";
		case 4:
			return "Copenhagen";
		case 5:
			return "Esbjerg";
		default:
			return  "Error (airportID) - not initialized";
		}
	}
	static std::string value2string(unsigned char hour, unsigned char minute) {
		std::string tempHour = std::to_string((int)hour);
		std::string tempMinute = std::to_string((int)minute);
		if (tempHour.length() == 1) {
			tempHour = "0" + tempHour;
		}
		if (tempMinute.length() == 1) {
			tempMinute = "0" + tempMinute;
		}
		return tempHour + ":" + tempMinute;

	}
	static std::string value2string(int flCode) {
		std::string flCodeStr = std::to_string(flCode);
		if (flCodeStr.length() == 3) {
			flCodeStr = "0" + flCodeStr;
		}
		return flCodeStr;
	}
	//because returning arrays is dark arts in C++, I have two separate functions.
	static int extractHour(std::string tableEntry) {
		std::string hourStr = tableEntry.substr(0, 1);
		return std::stoi(hourStr);
	}
	static int extractMinute(std::string tableEntry) {
		std::string minuteStr = tableEntry.substr(2, 2);
		return std::stoi(minuteStr);
	}
	static int RandomValInBounds(int min_val, int max_val) {
		//first inclusive, second non-inclusive
		int myRange = max_val - min_val;
		int randomValue = rand() % myRange;
		return randomValue + min_val;

	}
};

#endif
