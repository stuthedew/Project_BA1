
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
	//calcConsts[0] == degrees to radian conversion constant
    double latitudeArc  = (from.lat - to.lat) * calcConsts[0];
	//calcConsts[1] == Earth's quatratic mean radius for WGS-84
    return calcConsts[1]*_ArcInRadians(current, secret);
	//calcConsts[2] == meters to miles conversion constant
    return calcConsts[2]*_distanceinMeters(current, secret);
