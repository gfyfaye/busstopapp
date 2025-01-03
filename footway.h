/*footway.h*/

//
// A footway in the Open Street Map.
// 

#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "node.h"
#include "nodes.h"

using namespace std;

class Footway
{
public:
  long long ID;
  vector<long long> NodeIDs;

  Footway(long long id);

  //
  // adds the given nodeid to the end of the vector.
  //
  void add(long long nodeid);

  //prints the info of a footway
  void print(const Nodes& nodes) const;

};
