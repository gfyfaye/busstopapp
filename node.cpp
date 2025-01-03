/*node.cpp*/

//
// A node / position in the Open Street Map.

#include "node.h"

using namespace std;

Node::Node(long long id, double lat, double lon, bool entrance)
  : ID(id), Lat(lat), Lon(lon), IsEntrance(entrance)
{

  Node::Created++;
}

Node::Node(const Node& other)
{
  this->ID = other.ID;
  this->Lat = other.Lat;
  this->Lon = other.Lon;
  this->IsEntrance = other.IsEntrance;

  Node::Copied++;
}

long long Node::getID() const {

  Node::CallsToGetID++;

  return this->ID;
}

double Node::getLat() const {
  return this->Lat;
}

double Node::getLon() const {
  return this->Lon;
}

bool Node::getIsEntrance() const {
  return this->IsEntrance;
}

int Node::getCallsToGetID() {
  return Node::CallsToGetID;
}

int Node::getCreated() {
  return Node::Created;
}

int Node::getCopied() {
  return Node::Copied;
}