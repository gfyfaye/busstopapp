/*nodes.cpp*/

//
// A collection of nodes in the Open Street Map.

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

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <algorithm>
#include <cassert>

#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;


//
// readMapNodes
//
// Given an XML document, reads through the document and 
// stores all the nodes into the given vector. 
void Nodes::readMapNodes(XMLDocument& xmldoc)
{
  XMLElement* osm = xmldoc.FirstChildElement("osm");
  assert(osm != nullptr);

  //
  // Parse the XML document node by node: 
  //
  XMLElement* node = osm->FirstChildElement("node");

  while (node != nullptr)
  {
    const XMLAttribute* attrId = node->FindAttribute("id");
    const XMLAttribute* attrLat = node->FindAttribute("lat");
    const XMLAttribute* attrLon = node->FindAttribute("lon");

    assert(attrId != nullptr);
    assert(attrLat != nullptr);
    assert(attrLon != nullptr);

    long long id = attrId->Int64Value();
    double latitude = attrLat->DoubleValue();
    double longitude = attrLon->DoubleValue();

    bool entrance = false;

    if (osmContainsKeyValue(node, "entrance", "yes") ||
      osmContainsKeyValue(node, "entrance", "main") ||
      osmContainsKeyValue(node, "entrance", "entrance"))
    {
      entrance = true;
    }

    //
    // Add node to vector:
    //
    this->MapNodes.emplace(id, Node(id, latitude, longitude, entrance));

    //
    // next node element in the XML doc:
    //
    node = node->NextSiblingElement("node");
  }
}

//
// find
// 
// Searches the nodes for the one with the matching ID, returning
// true if found and false if not.
bool Nodes::find(long long id, double& lat, double& lon, bool& isEntrance) const
{
  auto ptr = this->MapNodes.find(id);

  if (ptr == this->MapNodes.end()) {  // not found:
    return false;
  }
  else {  // found:
    lat = ptr->second.getLat();
    lon = ptr->second.getLon();
    isEntrance = ptr->second.getIsEntrance();

    return true;
  }
}

int Nodes::getNumMapNodes() {
  return (int) this->MapNodes.size();
}
