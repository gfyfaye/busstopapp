/*main.cpp*/

//
// Program to input Nodes (positions) and Buildings from
// an Open Street Map file.
// 
#include <iostream>
#include <string>

#include "building.h"
#include "buildings.h"
#include "node.h"
#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"
#include "curl_util.h"
#include "busstop.h"
#include "busstops.h"

using namespace std;
using namespace tinyxml2;

//
// main
//
int main()
{
  XMLDocument xmldoc;
  Nodes nodes;
  Buildings buildings;
  BusStops busstops("bus-stops.txt");

  //
  //init curl library
  //
  CURL* curl = curl_easy_init();

  if (curl == nullptr) {
    cout << "**ERROR:" << endl;
    cout << "**ERROR: unable to initialize curl library" << endl;
    cout << "**ERROR:" << endl;
  return 0;
  }

  
  cout << "** NU open street map **" << endl;

  string filename;

  cout << endl;
  cout << "Enter map filename> " << endl;
  getline(cin, filename);

  if (!osmLoadMapFile(filename, xmldoc))
  {
    // failed, error message already output
    return 0;
  }
  
  nodes.readMapNodes(xmldoc);

  buildings.readMapBuildings(xmldoc);

  cout << "# of nodes: " << nodes.getNumMapNodes() << endl;
  cout << "# of buildings: " << buildings.getNumMapBuildings() << endl;
  cout <<"# of bus stops: " <<busstops.allBusStops.size()<<endl;

  while (true)
  {
    string name;

    cout << endl;
    cout << "Enter building name (partial or complete), or * to list, or @ for bus stops, or $ to end> " << endl;

    getline(cin, name);

    if (name == "$") {
      break;
    }
    else if (name == "*") {
      buildings.print();
    }
    else if (name == "@") {
      busstops.print();
    }
    else {
      buildings.findAndPrint(name, nodes, busstops, curl);
    }

  }//while
  curl_easy_cleanup(curl);
  cout << endl;


  cout << "** Done **" << endl;
  return 0;
}
