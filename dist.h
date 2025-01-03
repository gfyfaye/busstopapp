/*dist.h*/

//
// Computes the distance between 2 positions, given in
// (latitude, longitude) coordinates.

#pragma once


//
// DistBetween2Points
//
// Returns the distance in miles between 2 points (lat1, long1) and 
// (lat2, long2). 
double distBetween2Points(double lat1, double lon1, double lat2, double lon2);

