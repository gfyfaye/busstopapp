/*building.cpp*/

//
// A building in the Open Street Map.
// 

#include <iostream>
#include <utility>
#include <algorithm>

#include "building.h"
#include "busstops.h"
#include "dist.h"
#include "curl_util.h"

using namespace std;

Building::Building(long long id, string name, string streetAddr)
  : ID(id), Name(name), StreetAddress(streetAddr)
{
}

// prints information about a building --- id, name, etc. -- to
// the console.
void Building::print(Nodes& nodes, BusStops& busstops, CURL* curl)
{
  cout << this->Name << endl;
  cout << "Address: " << this->StreetAddress << endl;
  cout << "Building ID: " << this->ID << endl;
  /*
  cout << "Nodes:" << endl;
  for (long long nodeid : this->NodeIDs)
  {
    cout << "  " << nodeid << ": ";

    double lat = 0.0;
    double lon = 0.0;
    bool entrance = false;

    bool found = nodes.find(nodeid, lat, lon, entrance);

    if (found) {
      cout << "(" << lat << ", " << lon << ")";

      if (entrance)
        cout << ", is entrance";

      cout << endl;
    }
    else {
      cout << "**NOT FOUND**" << endl;
    }

  }//for*/

  //output num of perimeter nodes and building's location
  pair<double, double> location = getLocation(nodes);
  cout << "# perimeter nodes: " << this->NodeIDs.size() << endl;
  cout << "Location: (" << location.first << ", " << location.second << ")" << endl;

  //call from bus stops class, findAndprintClosestStop to a location
  busstops.findAndPrintClosestStop(location.first, location.second, curl);

}

//
// adds the given nodeid to the end of the vector.
//
void Building::add(long long nodeid)
{
  this->NodeIDs.push_back(nodeid);
}

//
// gets the center (lat, lon) of the building based
// on the nodes that form the perimeter
//

pair<double, double> Building::getLocation(const Nodes& nodes) {
  //if building has no nodes
  if (this->NodeIDs.empty()) {
    cerr << "Error: Building has no nodes." << endl;

    return make_pair(0.0, 0.0);  //default loc
  }

  double sumLat = 0.0;
  double sumLon = 0.0;

  //add to sumLat sumLon
  auto accumulateLocation = [&](const long long nodeId) {
    double lat = 0.0;
    double lon = 0.0;
    bool entrance = false;

    bool found = nodes.find(nodeId, lat, lon, entrance);

    if (found) {
      sumLat += lat;
      sumLon += lon;
    }
  };
  for_each(this->NodeIDs.begin(), this->NodeIDs.end(), accumulateLocation);
  //find average lat and lon
  double avgLat = sumLat / this->NodeIDs.size();
  double avgLon = sumLon / this->NodeIDs.size();

  //return average loc
  return make_pair(avgLat, avgLon);
}