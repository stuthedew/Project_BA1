// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef data_H_
#define data_H_
#include "Arduino.h"

static const double DEG_TO_RAD = 0.017453292519943295769236907684886;
static const double EARTH_RADIUS_IN_METERS = 6372797.560856;

//add your includes for the project data here

class Data {

public:
	//Constructor
	Data();

	//Methods
	double DistanceInMiles(const Position& from, const Position& to);



private:

	_arcInRadians(const Position& from, const Position& to);
	double _distanceInMeters(const Position& from, const Position& to);

};



class Position {

public:
	//Constructor
	Position(float lat, float lon);



private:



};

//Do not add code below this line
#endif /* data_H_ */
