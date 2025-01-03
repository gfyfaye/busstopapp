/*busstops.cpp*/


#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <limits>

#include "busstops.h"
#include "dist.h"
#include "curl_util.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;


// Given a CSV file, reads through the file and stores all the bus stops into the given vector.
//
BusStops::BusStops(const string& filename) {
    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Error: Unable to open the file " << filename << endl;
        return;
    }

    string line;
    while (getline(input, line)) {
        stringstream parser(line);

        string stopId, busRoute, stopName, direction, location, latitude, longitude;

        getline(parser, stopId, ',');
        getline(parser, busRoute, ',');
        getline(parser, stopName, ',');
        getline(parser, direction, ',');
        getline(parser, location, ',');
        getline(parser, latitude, ',');
        getline(parser, longitude, ',');

        // Create BusStop object and add it to the vector
        BusStop B(stoll(stopId), stoi(busRoute), stopName, direction, location, stod(latitude), stod(longitude));
        this->allBusStops.push_back(B);
    }
}

void BusStops::print() {
    sortID();

    for (const auto& busStop : this->allBusStops) {
        busStop.print();
    }
}

void BusStops::sortID(){
    vector<long long> IDs;
    vector<BusStop> New;
    
    for(auto busstop : this -> allBusStops){
        IDs.emplace_back(busstop.stopId);
    }

    sort(IDs.begin(), IDs.end());

    for(long long ID : IDs){
        const BusStop temp = find(ID);
        New.emplace_back(temp);
    }

    this -> allBusStops = New;
}

const BusStop BusStops::find(long long ID){
    for(auto n : this -> allBusStops){
        if(n.stopId == ID){
            return n;
        }
    }
    return this -> allBusStops[0];
}

void BusStops::findAndPrintClosestStop(double srcLat, double srcLon, CURL* curl){
    BusStop closestSouthbound = allBusStops[0];
    BusStop closestNorthbound = allBusStops[0];
    double closestSouthboundDist = numeric_limits<double>::infinity();
    double closestNorthboundDist = numeric_limits<double>::infinity();

    for(auto n : this -> allBusStops){
        double distance = distBetween2Points(srcLat, srcLon, n.latitude, n.longitude);

        if (n.direction == "Southbound" && distance < closestSouthboundDist){
            closestSouthboundDist = distance;
            closestSouthbound = n;
        }
        else if (n.direction == "Northbound" && distance < closestNorthboundDist) {
            closestNorthboundDist = distance;
            closestNorthbound = n;
        }
    }
    //printing
    cout << "Closest southbound bus stop:" << endl;
    cout<< "  " << closestSouthbound.stopId << ": "
        << closestSouthbound.stopName << ", " 
        << "bus #" << closestSouthbound.busRoute << ", " 
        << closestSouthbound.location << ", "
        << closestSouthboundDist << " miles" << endl;
        string southBoundURL = closestSouthbound.getURL();
        printBuses(curl, southBoundURL);


    cout << "Closest northbound bus stop:" << endl;
    cout<< "  " <<closestNorthbound.stopId << ": "
        << closestNorthbound.stopName << ", " 
        << "bus #" << closestNorthbound.busRoute << ", " 
        << closestNorthbound.location << ", "
        << closestNorthboundDist << " miles" << endl;
        string northBoundURL = closestNorthbound.getURL();
        printBuses(curl, northBoundURL);
}


void BusStops::printBuses(CURL* curl, string& url){

        string response;

        bool temp = callWebServer(curl, url, response);

        if (!temp){
            cout<<"  <<bus predictions unavailable, call failed>>"<<endl;
        }

        else {
            auto jsondata = json::parse(response);
            auto bus_response = jsondata["bustime-response"];
            auto predictions = bus_response["prd"];

            if (predictions.size() == 0) {
                cout<<"  <<no predictions available>>"<<endl;
            }
            else {
            for (auto& M : predictions) {
                cout << "  vehicle #" << stoi(M["vid"].get_ref<std::string&>())
                 << " on route " << stoi(M["rt"].get_ref<std::string&>())
                 << " travelling " << M["rtdir"].get_ref<std::string&>()
                 << " to arrive in " << stoi(M["prdctdn"].get_ref<std::string&>())
                 << " mins" << endl;
            }
            }
        }
}
