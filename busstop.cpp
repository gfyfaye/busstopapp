/*busstop.cpp*/

//
// bus stop class function definitions
//

#include <iostream>
#include <utility>
#include <algorithm>
#include "busstop.h"

using namespace std;


BusStop::BusStop(long long instopId, long long inbusRoute, const string& instopName,
                 const string& indirection, const string& inlocation,
                 double inlatitude, double inlongitude)

    : stopId(instopId), busRoute(inbusRoute), stopName(instopName),
      direction(indirection), location(inlocation),
      latitude(inlatitude), longitude(inlongitude) 
      {}

void BusStop::print() const {
    cout<< this-> stopId << ": bus "
        << this-> busRoute << ", " 
        << this-> stopName << ", " 
        << this-> direction << ", " 
        << this-> location << ", location ("
        << this-> latitude << ", " 
        << this-> longitude << ")" << endl;
}

string BusStop::getURL() {
    string url = "http://ctabustracker.com/bustime/api/v2/getpredictions?key=zNJqgJLKZ8QFrxUXyu6ygcWTe&rt=" 
                + to_string(this->busRoute) +
                 "&stpid=" + to_string(this->stopId) +
                 "&format=json";

    return url;
}