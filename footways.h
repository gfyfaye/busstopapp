/*footways.h*/

//
// A collection of pedestrian footways in the Open Street Map.
// 
#pragma once

#include <vector>
#include <iostream>

#include "footway.h"
#include "tinyxml2.h"


using namespace std;
using namespace tinyxml2;

class Footways
{
public:
  vector<Footway> MapFootways;

  //
  // Reads footways from the given XML document
  //
  void readMapFootways(XMLDocument& xmldoc);

  //
  // Returns the number of footways.
  //
  int getNumMapFootways() const;
};