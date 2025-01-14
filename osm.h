/*osm.h*/

//
// Functions for working with an Open Street Map file.
// TinyXML: 
//   files: https://github.com/leethomason/tinyxml2
//   docs:  http://leethomason.github.io/tinyxml2/
// 
// OpenStreetMap: https://www.openstreetmap.org
// OpenStreetMap docs:  
//   https://wiki.openstreetmap.org/wiki/Main_Page
//   https://wiki.openstreetmap.org/wiki/Map_Features
//   https://wiki.openstreetmap.org/wiki/Node
//   https://wiki.openstreetmap.org/wiki/Way
//   https://wiki.openstreetmap.org/wiki/Relation
//

#pragma once

#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

bool osmLoadMapFile(string filename, XMLDocument& xmldoc);
bool osmContainsKeyValue(XMLElement* e, string key, string value);
string osmGetKeyValue(XMLElement* e, string key);
