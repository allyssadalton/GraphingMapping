/*    @file sandbox.cpp     
      @author < Allyssa Dalton >
      @date < April 13th, 2025 >

			@description Sandbox for MyComplex
*/

#include <iostream>

#include <fstream>
#include <sstream>
#include "MyGraph.h"
#include "MyGraph.cpp"
#include <iomanip> 

using namespace std;

//Man, shoutout to Deepseek because math and getting data off csvs is so difficult for no reason :(
// Create consistent node IDs with 6 decimal places precision (~0.1m)
string makeNodeID(double lat, double lon){
    //return to_string(lat) + "," + to_string(lon);
  stringstream ss;
  ss << fixed << setprecision(7) << lat << "," << lon;
  return ss.str();
}

// Merge nearby intersections (within ~10m)
string getCanonicalNode(double lat, double lon, unordered_map<string, string>& canonical) {
    /*string key = to_string(round(lat * 1000000)/1000000) + "," + to_string(round(lon * 1000000)/1000000); 

  // Store the more precise version
  if (!canonical.count(key)){canonical[key] = makeNodeID(lat, lon);}
  return canonical[key];
  */
 return makeNodeID(lat, lon);
}

int main() {
  unordered_map<string, unordered_map<string, string>> roadNames; 
  MyGraph<string> IndyMapping(undirected);
  ifstream file("indy.csv");
  setprecision(8);
    
  if (!file.is_open()){
    cerr << "Error: Failed to open indy.csv" << endl;
    return 1;
  }

  string line;
  int rows_processed = 0;
  unordered_map<string, string> canonical_nodes;

  // Skip header if exists
  getline(file, line);

  while (getline(file, line)) {
    istringstream iss(line);
    vector<string> tokens;
    string token;

    while (getline(iss, token, ',')){tokens.push_back(token);}

    try {
      // Parse required fields
      double startLat = stod(tokens[0]);
      double startLon = stod(tokens[1]);
      double endLat = stod(tokens[2]);
      double endLon = stod(tokens[3]);
      double distance = stod(tokens[4]);
      string roadName = tokens[5];

      // Get consistent node IDs with intersection merging
      string intersectionA = getCanonicalNode(startLat, startLon, canonical_nodes);
      string intersectionB = getCanonicalNode(endLat, endLon, canonical_nodes);

      if (intersectionA != intersectionB){
        IndyMapping.addEdge(intersectionA, intersectionB, distance);
        // Store road names in both directions for undirected graph
        roadNames[intersectionA][intersectionB] = roadName;
        roadNames[intersectionB][intersectionA] = roadName;
        //cout << "Adding edge between: " << intersectionA << " and " << intersectionB << " with distance " << distance << endl;
        rows_processed++;
      }
    } 
    catch (...){ cout << "Warning: Error processing line: " << line << endl;}
  }

  file.close();


  // Roads & Rows Information
  cout << "Map Information: " << endl;
  cout << "_____________________" << endl;
  cout << "CSV rows:  " << rows_processed << endl;
  cout << "Intersections: " << IndyMapping.numNodes() << endl;
  cout << "Roads:       " << IndyMapping.numEdges() << endl;

  string road = ""; 
  cout << fixed << setprecision(7);
  char comma; //Gemini told  me to do this to use my findNearestNode function after getting input
  double startingLat, startingLong, endingLat, endingLong;
  while(true){
    try{
      cout << "Enter Starting Location Latitude,Longitude: " << endl;
      cin >> startingLat >> comma >> startingLong;
      cout << endl << "Enter Destination Location Latitude,Longitude: " << endl;
      cin >> endingLat >> comma >> endingLong;
      cout << endl; 
        
      //startingLat = 39.7119045;
      //startingLong = -86.1427422;
      //endingLat = 39.7449411;
      //endingLong = -86.1468081;
      string startNode = IndyMapping.findNearestNode(startingLat, startingLong);
      string endNode = IndyMapping.findNearestNode(endingLat, endingLong);
      cout << "Closest Starting Point: " << startNode << endl;
      cout << "Closest Destination Point: " << endNode << endl;
            
      double distance = IndyMapping.dijkstraShortestDistance(startNode, endNode);
      list<string> path = IndyMapping.dijstraShortestPath(startNode, endNode);
      if (path.empty()) {
        cout << "No path found!" << endl;
        return 0;
      }
      cout << "Distance: " << distance << " miles or " << distance * 5280 << " feet." << endl;
      cout << "Number of Intersections: " << path.size() << endl;
      cout << "_____________________" << endl;
        
      auto current = path.begin();
      auto next_node = next(current);
      if (next_node == path.end()){
        cout << "You're already at your destination!" << endl;
        return 0;
      }
        
      string currentRoad = roadNames[*current][*next_node];
      double roadDistance = IndyMapping.getWeight(*current, *next_node);
      int step = 1;
        
      cout << "Directions Starting at: " << *current << endl << endl;
      cout << step++ << ". Take " << currentRoad << " toward " << *next_node;
        
      current = next_node++;
            
      while (next_node != path.end()) {
        string from = *current;
        string to = *next_node;
        string nextRoad = roadNames[from][to];
        double edgeDistance = IndyMapping.getWeight(from, to);

        if (nextRoad == "-"){nextRoad = "Unnamed Road";}
        if (nextRoad != currentRoad){
          cout << " and continue straight for " << roadDistance << " miles or " << roadDistance * 5280 << " feet" << endl;
          cout << "   http://maps.google.com/maps?q=" << to << endl;
          cout << step++ << ". Turn onto " << nextRoad << " toward " << to;
          currentRoad = nextRoad;
          roadDistance = edgeDistance;
        } 
        else {roadDistance += edgeDistance;}
        current = next_node++;
      }
        
      // Print final segment
      cout << step++ << " and continue straight until you've reached your destination" << endl;
    } 
    
    catch(const exception& e){
        cout << "Error: " << e.what() << endl; //Deepseek did this for me because multiple errors could be thrown during the try
        break;
    } 
    
    //return 0;
  }
    return 0;
}
