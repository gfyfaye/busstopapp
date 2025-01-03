/*building.h*/

//
// A building in the Open Street Map.
// 

#pragma once

#include <string>
#include <vector>

#include "node.h"
#include "nodes.h"
#include "busstops.h"
#include "curl_util.h"

using namespace std;


// Defines a campus building with a name
class Building
{
public:
  long long ID;
  string Name;
  string StreetAddress;
  vector<long long> NodeIDs;

 
  Building(long long id, string name, string streetAddr);

  // prints information about a building --- id, name, etc. -- to
  // the console.
  void print(Nodes& nodes, BusStops& busstops, CURL* curl);

  //
  // adds the given nodeid to the end of the vector.
  //
  void add(long long nodeid);

  //
  // gets the center (lat, lon) of the building based
  // on the nodes that form the perimeter
  //
  pair<double, double> getLocation (const Nodes& nodes);
};
