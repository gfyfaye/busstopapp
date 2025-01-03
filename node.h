/*node.h*/

//
// A node / position in the Open Street Map.
#pragma once

//
// Node:
//
// A node is a point on the map, with a unique ID and the position
// in GPS (lat, lon) terms. 
class Node
{
private:
  long long ID;
  double Lat;
  double Lon;
  bool   IsEntrance;

  inline static int CallsToGetID = 0;
  inline static int Created = 0;
  inline static int Copied = 0;

public:
  Node(long long id, double lat, double lon, bool entrance);
  
  Node(const Node& other);
  long long getID() const;
  double getLat() const;
  double getLon() const;
  bool getIsEntrance() const;

  static int getCallsToGetID();
  static int getCreated();
  static int getCopied();

};
