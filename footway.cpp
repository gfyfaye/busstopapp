/*footway.cpp*/

//
// A footway in the Open Street Map.
// 


#include "footway.h"

using namespace std;


Footway::Footway(long long id) : ID(id) {
}


//
//adds the given nodeid to the end of the vector.
void Footway::add(long long nodeid) {
    NodeIDs.push_back(nodeid);
}

//
//prints the info about a footway
//
void Footway::print(const Nodes& nodes) const {
    cout << "Footway ID: " << ID << endl;
    cout << "Nodes: ";
    for (long long nodeId : NodeIDs) {
        double lat = 0.0;
        double lon = 0.0;
        bool isEntrance = false;

        bool found = nodes.find(nodeId, lat, lon, isEntrance);

        if (found) {
            cout << nodeId << " (" << lat << ", " << lon << ")";
            if (isEntrance) {
                cout << ", is entrance";
            }
            cout << " ";
        } else {
            cout << nodeId << ": **NOT FOUND** ";
        }
    }
    cout << endl;
}
