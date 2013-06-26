
#include <data.h>
#include <Flash.h>

/**********************************SECRET LOCATION*********************************/
/*		 +	-
 *------------
 * lat | N	S
 * lon | E  W
*/

// lat, lon
FLASH_ARRAY(float, Secretlocation, 43.691708, -114.35051);

/**********************************SECRET LOCATION*********************************/
FLASH_ARRAY(float, calcConsts, 0.017453292519943295769236907684886, 6372797.560856, 0.000621371);
double Data::_arcInRadians(const Position& from, const Position& to) {
	//calcConsts[0] == degrees to radian conversion constant
    double latitudeArc  = (from.lat - to.lat) * calcConsts[0];
    double longitudeArc = (from.lon - to.lon) * calcConsts[0];
    double latitudeH = sin(latitudeArc * 0.5);
    latitudeH *= latitudeH;
    double lontitudeH = sin(longitudeArc * 0.5);
    lontitudeH *= lontitudeH;
    double tmp = cos(from.lat*calcConsts[0]) * cos(to.lat*calcConsts[0]);
    return 2.0 * asin(sqrt(latitudeH + tmp*lontitudeH));
}


double Data::_distanceInMeters(const Position& current, const Position& secret) {
	//calcConsts[1] == Earth's quatratic mean radius for WGS-84
    return calcConsts[1]*_ArcInRadians(current, secret);
}

double Data::distanceInMiles(const Position& current, const Position& secret) {
	//calcConsts[2] == meters to miles conversion constant
    return calcConsts[2]*_distanceinMeters(current, secret);
}
