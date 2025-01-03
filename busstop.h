/*busstop.h*/

//
// bus stop class

#pragma once

#include <string>
#include <utility> 

using namespace std;

class BusStop {
public:

    long long stopId;
    long long busRoute;
    string stopName;
    string direction;
    string location;
    double latitude;
    double longitude;

    BusStop(long long instopId, long long inbusRoute, const string& instopName,
            const string& indirection, const string& inlocation,
            double inlatitude, double inlongitude);

    void print() const;

    string getURL();

};