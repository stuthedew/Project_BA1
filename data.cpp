#include <Arduino.h>
#include "data.h"
#include <Flash.h>




/*---------------Constants for Location Calculations----------------*/
// 0 = PI/180 constant, 1 = Earth's quatratic mean radius for WGS-84,  2 = meters to miles
FLASH_ARRAY(float, calcConsts, 0.01745329251994, 6371, 0.621371);
//6372797.560856






/*------------------------------------------------------------------*/

/*************************************************************************/
/******************************* Position Class **************************/
/*************************************************************************/

/*--------------------------------PUBLIC---------------------------------*/

Position::Position() {

}

void Position::setLocation(float _lat, float _lon) {
	lat = _lat;
	lon = _lon;
}

/*--------------------------------PRIVATE---------------------------------*/







/*************************************************************************/
/******************************* Data Class ******************************/
/*************************************************************************/

/*--------------------------------PUBLIC---------------------------------*/

Data::Data(float _secLat, float _secLon) :
		_secretLocation(), _currentLocation() {

	_secretLocation.setLocation(_secLat, _secLon);

}

float Data::distanceInKilometers() {
	//calcConsts[1] == Earth's quatratic mean radius for WGS-84
	return round(calcConsts[1] * _arcInRadians(_currentLocation, _secretLocation));
}



int Data::distanceInMiles() {
	//calcConsts[2] == meters to miles conversion constant
	return round(calcConsts[2] * distanceInKilometers());
}

void Data::setCurrentLocation(float curLat, char latDir, float curLon, char lonDir){
	float latFloat = _degMinToDec(curLat);

	if(latDir == 'S' || latDir == 's'){
		latFloat *= -1;
	}

	float lonFloat = _degMinToDec(curLon);

	if(lonDir == 'W'|| lonDir == 'w'){
			lonFloat *= -1;
		}

	_currentLocation.setLocation(latFloat, lonFloat);


}


/*--------------------------------PRIVATE---------------------------------*/

double Data::_arcInRadians(const Position& from, const Position& to) {

	//calcConsts[0] == degrees to radian conversion constant
	double latitudeArc = (from.lat - to.lat) * calcConsts[0];
	double longitudeArc = (from.lon - to.lon) * calcConsts[0];
	double latitudeH = sin(latitudeArc * 0.5);
	latitudeH *= latitudeH;
	double lontitudeH = sin(longitudeArc * 0.5);
	lontitudeH *= lontitudeH;
	double tmp = cos(from.lat * calcConsts[0]) * cos(to.lat * calcConsts[0]);
	tmp = latitudeH + tmp * lontitudeH;
	return 2.0 * atan2(sqrt(tmp), sqrt(1 - tmp));
}


// converts degMin format (ddmm.mmmm) from Adafruit Ultimate GPS to Dec format
double Data::_degMinToDec(float degMin) {

	float deg = int(degMin / 100);


	float min = (degMin / 100 - deg) * 100;

	min /= 60;

	deg += min;

	return deg;
}

