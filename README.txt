Open Street Maps - Nearest Bus Stops

Overview
This project integrates CTA bus stop data with Northwestern University’s Evanston campus Open Street Maps, 
allowing users to locate the nearest southbound and northbound bus stops for a selected building. 
The program also fetches real-time bus arrival predictions using the CTA Bus Tracker API.

Features
- Building Location Calculation: Calculates the latitude and longitude of a building based on its perimeter nodes.
- Bus Stop Integration: Reads bus stop data from a CSV file and organizes it into a structured format.
- Closest Bus Stops: Identifies the nearest northbound and southbound bus stops for a given building.
- Real-time Bus Predictions: Queries the CTA Bus Tracker API to fetch bus arrival times.
- Exception Handling: Ensures robust error management during API queries and data processing.

Input Format
- Enter a building name to find its closest bus stops.
- Use * to list all buildings or @ to list all bus stops.

Dependencies
- C++17 or later.
- CURL library for API communication.
- nlohmann/json library for JSON parsing.

Testing
- Test with real-time data using an API key.
- Test offline using provided mock data files in the /mock directory.

Example Output
Enter building name (* to list, @ for stops): University Library
Closest southbound stop: Sheridan & Foster (0.2 miles)
Closest northbound stop: Sheridan & Emerson (0.3 miles)
Bus Predictions:
  Vehicle #2092, Route #20, Direction: Westbound, ETA: 8 minutes
  Vehicle #2103, Route #20, Direction: Westbound, ETA: 12 minutes

Contributors
- Northwestern University CS 211 Team
- Professor Joseph Hummel