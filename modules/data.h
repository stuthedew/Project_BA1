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
class Position {

public:
	//Constructor
Position();

private:


};



class Data {

public:
	//Constructor
	Data();

	//Methods
	double DistanceInMeters(const Position& from, const Position& to)


private:

	_ArcInRadians(const Position& from, const Position& to);



};






//Do not add code below this line
#endif /* data_H_ */
