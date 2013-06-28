// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef data_H_
#define data_H_


//add your includes for the project data here


class Position {

public:
	//Constructor
	Position();
	void setLocation(float, float);
	float lat;
	float lon;





private:



};

class Data {

public:
	//Constructor
	Data();

	//Methods
	int distanceInMiles();
	float distanceInKilometers();

	void setCurrentLocation(float, char, float, char);


private:

	//Methods
	double _arcInRadians(const Position& from, const Position& to);

	double _degMinToDec(float);



	//Members
	Position _secretLocation;
	Position _currentLocation;

};









//Do not add code below this line
#endif /* data_H_ */
