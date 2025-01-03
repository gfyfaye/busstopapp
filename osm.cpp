/*osm.cpp*/

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

#include <iostream>
#include <string>
#include <cassert>

#include "osm.h"

using namespace std;
using namespace tinyxml2;


//
// osmLoadMapFile
// 
// Given the filename for an XML doc, tries to open and load
// that file into the given xmldoc variable (which is passed
// by reference).
//
bool osmLoadMapFile(string filename, XMLDocument& xmldoc)
{
  //
  // load the XML document:
  //
  xmldoc.LoadFile(filename.c_str());

  if (xmldoc.ErrorID() != 0)  // failed:
  {
    cout << "**ERROR: unable to open XML file '" << filename << "'." << endl;
    return false;
  }

  //
  // top-level element should be "osm" if the file is a valid open 
  // street map:
  //
  XMLElement* osm = xmldoc.FirstChildElement("osm");

  if (osm == nullptr)
  {
    cout << "**ERROR: unable to find top-level 'osm' XML element." << endl;
    cout << "**ERROR: this file is probably not an Open Street Map." << endl;
    return false;
  }

  //
  // success:
  //
  return true;
}


//
// osmContainsKeyValue
//
// Given a pointer to an XML Element, searches through all 
// the tags associated with this element looking for the 
// given (key, value) pair.
//
bool osmContainsKeyValue(XMLElement* e, string key, string value)
{
  XMLElement* tag = e->FirstChildElement("tag");

  while (tag != nullptr)
  {
    const XMLAttribute* keyAttribute = tag->FindAttribute("k");
    const XMLAttribute* valueAttribute = tag->FindAttribute("v");

    if (keyAttribute != nullptr && valueAttribute != nullptr)
    {
      string elemkey(keyAttribute->Value());
      string elemvalue(valueAttribute->Value());

      if (elemkey == key && elemvalue == value)  // found it:
      {
        return true;
      }
    }
    tag = tag->NextSiblingElement("tag");
  }

  return false;
}


//
// osmGetKeyValue
//
// Given a pointer to an XML Element, searches through all 
// the tags associated with this element looking for the 
// given key.
string osmGetKeyValue(XMLElement* e, string key)
{
  XMLElement* tag = e->FirstChildElement("tag");

  while (tag != nullptr)
  {
    const XMLAttribute* keyAttribute = tag->FindAttribute("k");
    const XMLAttribute* valueAttribute = tag->FindAttribute("v");

    if (keyAttribute != nullptr && valueAttribute != nullptr)
    {
      string elemkey(keyAttribute->Value());
      
      if (elemkey == key)  // found it:
      {
        string elemvalue(valueAttribute->Value());

        return elemvalue;
      }
    }

    tag = tag->NextSiblingElement("tag");
  }

  return "";
}
