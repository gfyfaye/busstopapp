/*busstops.h*/

#pragma once

#include <vector>
#include <iostream>
#include <string>

#include "busstop.h"
#include "curl_util.h"

using namespace std;

class BusStops {
public:
    vector<BusStop> allBusStops;

    BusStops(const string& filename);

    void print();

    void sortID();

    const BusStop find(long long ID);

    CURL* curl = curl_easy_init();

    void findAndPrintClosestStop(double srcLat, double srcLon, CURL* curl);

    string getURL(int busRoute, long long busStopId);

    void printBuses(CURL* curl, string& url);
};