/*    @file MyGraph.cpp   
      @author < Allyssa Dalton >
      @date < April 13th, 2025 >

			@description Implements a class for storing a bi-directional graph.
*/

#include <string>
#include <iostream>
#include <cmath>  // for infinity()
#include <stdexcept>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <iomanip> 
#include "MyGraph.h"

template <typename T> MyGraph<T>::MyGraph(graph_type_t type):type(type){
  unordered_map<T, list<pair<T, float>>> data;
}

template <typename T> void MyGraph<T>::print(){ //double check
  if (data.empty()){
    cout << "Graph is empty." << endl;
    return;
  }
  for (auto& node : data){
    cout << node.first << " -> ";
    for (auto& edge : node.second){cout << "(" << edge.first << ", " << edge.second << ") ";}
    cout << endl;
  }
}

template <typename T> void MyGraph<T>::addEdge(const T &a, const T &b, float weight){
  // Make sure they are nodes
  addNode(a);
  addNode(b);
  if(type == undirected){
    type = directed;
    addEdge(b, a, weight);
    type = undirected;
  }
    
    // See if the destination is already there.
    // Only way is to step down the linked-list. O(n)
    // Could be faster with another unordered_map, but wasteful in space
  for(auto &[dest, w]: data.at(a)){
    if(dest == b){
      // It was already there!
      // Update the weight
      w = weight;
      return;
    }
  }
    // Edge not there already, so add a pair onto the end
  pair<T, float> dest(b, weight);
  data.at(a).push_back(dest);
}

template <typename T> void MyGraph<T>::addNode(const T &a){
  if (!isNode(a)){data[a] = list<pair<T, float>>();} //creates empty list for a to add it
}

template <typename T> void MyGraph<T>::removeEdge(const T &a, const T &b){
  if (isNode(a)){
    data[a].remove_if([&b](const pair<T, float>& edge){return edge.first == b;});

    if (type == undirected && isNode(b)){
      data[b].remove_if([&a](const pair<T, float>& edge){return edge.first == a;});
    }
  }
}

template <typename T> void MyGraph<T>::removeNode(T a){
  if (isNode(a)){
    for (auto& [node, edges] : data){
      edges.remove_if([&a](const pair<T, float>& edge){return edge.first == a;});
    }
    data.erase(a);  
  } 
}

template <typename T> unsigned MyGraph<T>::numNodes(){
  return data.size();
}

template <typename T> unsigned MyGraph<T>::numEdges(){
  unsigned edgeAmount = 0;
  for (auto& [node, edges] : data){edgeAmount += edges.size();}

  if (type == undirected){return edgeAmount / 2;}

  else{return edgeAmount;}
}


template <typename T> bool MyGraph<T>::isNode(T needle){
  return (data.find(needle) != data.end());
}

template <typename T> bool MyGraph<T>::hasEdge(T a, T b){
  if (!isNode(a) || !isNode(b)){return false;}
  for (auto& edge : data[a]){ //looks for b
    if (edge.first == b) {return true;}
  }
  return false;
}


template <typename T> float MyGraph<T>::getWeight(T a, T b){
  if (!isNode(a) || !isNode(b)){throw invalid_argument("One or both nodes don't exist");} //Deepseek helped me with this line

  for (auto& edge : data[a]) {
    if (edge.first == b){return edge.second;}
  }

  throw invalid_argument("Edge between nodes doesn't exist"); //Deepseek helped me with this line
}

/* **** Distance functions */

// Change if needed
template <typename T>
class MyCompare{
  public:
  bool operator()(const pair<T,float> &a, const pair<T,float> &b){
    if(a.second > b.second){
      return true;
    }else{
      return false;
    }
  }
};

template <typename T> float MyGraph<T>::dijkstraShortestDistance(T a, T b){
  float bigNum = 1e9; //Allows for distance to be bigger than what's necessary  
  unordered_map<T, float> distance;
  unordered_map<T, T> previous;
  unordered_map<T, bool> visited;
  priority_queue<pair<T, float>, vector<pair<T,float>>, MyCompare<T>> priorityQ;

  for (auto& [node, _] : data){distance[node] = bigNum;} //deepseek helped me with this
  distance[a] = 0.0;
  priorityQ.push({a, 0.0});

  while(!priorityQ.empty()){
    T current = priorityQ.top().first;
    priorityQ.pop();
    if (visited[current]){continue;} //if current node has already been touched, go to the next
    visited[current] = true;
    if (current == b){break;} //if current node is destination then quit

    for (auto& [neighbor, weight] : data[current]){
      float newDistance = distance[current] + weight; 
      if (newDistance < distance[neighbor]){
        distance[neighbor] = newDistance;
        previous[neighbor] = current;
        priorityQ.push({neighbor, newDistance});
      }
    }
  }

  if (distance[b] == bigNum){throw runtime_error("No path exists between the specified nodes.");}
  return distance[b];
}


template <typename T> list<T> MyGraph<T>::dijstraShortestPath(T a, T b){
  float bigNum = 1e9;
  unordered_map<T, float> distance;
  unordered_map<T, T> previous;
  unordered_map<T, bool> visited;
  priority_queue<pair<T, float>, vector<pair<T,float>>, MyCompare<T>> priorityQ;

  for (auto& [node, _] : data){distance[node] = bigNum;}
  distance[a] = 0.0;
  priorityQ.push({a, 0.0});

  while(!priorityQ.empty()){
    T current = priorityQ.top().first;
    priorityQ.pop();

    if (visited[current]){continue;}
    visited[current] = true;
    if (current == b){break;}

    for (auto& [neighbor, weight] : data[current]){
      float newDistance = distance[current] + weight;
      if (newDistance < distance[neighbor]){
        distance[neighbor] = newDistance;
        previous[neighbor] = current;
        priorityQ.push({neighbor, newDistance});
      }
    }
  }

  list<T> path;
  T at = b;

  // if no path exists
  if (previous.find(at) == previous.end() && a != b){throw runtime_error("No path exists between the specified nodes.");}

  while (at != a){
    path.push_front(at);
    at = previous[at];
  }

  path.push_front(a);
  return path;
}


template <typename T> float MyGraph<T>::bellmanFordShortestDistance(T a, T b){
  float bigNum = 1e9;
  unordered_map<T, float> distance;

  for (auto& [node, _] : data){distance[node] = bigNum;}
  distance[a] = 0.0;
  unsigned int N = data.size(); //number of nodes
  for (unsigned i = 0; i < N - 1; i++){
    for (auto& [from, edges] : data){
      for (auto& [to, weight] : edges){
        if ((distance[from] + weight) < distance[to]){
          distance[to] = distance[from] + weight;
        }
      }
    }
  }

  for (auto& [from, edges] : data){
    for (auto& [to, weight] : edges){
      if ((distance[from] + weight) < distance[to]){throw runtime_error("A negative cycle exists.");}
    }
  }

  if (distance[b] == bigNum){throw runtime_error("A path does not exist between locations");}

  return distance[b];
}

template <typename T> list<T>  MyGraph<T>::bellmanFordShortestPath(T a, T b){
  float bigNum = 1e9;
  unordered_map<T, float> distance;
  unordered_map<T,T> previous;

  for (auto& [node, _] : data){distance[node] = bigNum;}
  distance[a] = 0.0;
  unsigned int N = data.size(); //number of nodes

  for (unsigned i = 0; i < N - 1; i++){
    for (auto& [from, edges] : data){
      for (auto& [to, weight] : edges){
        if ((distance[from] + weight) < distance[to]){
          distance[to] = distance[from] + weight;
          previous[to] = from;
        }
      }
    }
  }

  for (auto& [from, edges] : data){
    for (auto& [to, weight] : edges){
      if ((distance[from] + weight) < distance[to]){throw runtime_error("A negative cycle exists.");}
    }
  }

  list<T> path;

  if (previous.find(b) == previous.end() && a != b){throw runtime_error("A path does not exist between locations");}
 
  T current = b;

  while(current != a){
    path.push_front(current);
    if (previous.find(current) == previous.end()){throw runtime_error("A path does not exist between locations");}
    current = previous[current];
  }
  path.push_front(current);
  return path;
}

//Deepseek & Chatgpt did this because I had no idea
template <typename T>  T MyGraph<T>::findNearestNode(double lat, double lon) {
    if (data.empty()) {
        throw runtime_error("Graph is empty");
    }

    T nearestNode;
    double minDistance = numeric_limits<double>::max();
    const double EARTH_RADIUS = 6371000; // meters

    for (const auto& [node, edges] : data) {
    if (edges.empty()){continue;}
        size_t commaPos = node.find(',');
        if (commaPos == string::npos) continue;

        try {
            double nodeLat = stod(node.substr(0, commaPos));
            double nodeLon = stod(node.substr(commaPos + 1));

            // Haversine formula
            double dLat = (lat - nodeLat) * M_PI / 180.0;
            double dLon = (lon - nodeLon) * M_PI / 180.0;
            double a = sin(dLat / 2) * sin(dLat / 2) +
                       cos(nodeLat * M_PI / 180.0) * cos(lat * M_PI / 180.0) *
                       sin(dLon / 2) * sin(dLon / 2);
            double distance = EARTH_RADIUS * 2 * atan2(sqrt(a), sqrt(1 - a));

            if (distance < minDistance) {
                minDistance = distance;
                nearestNode = node;
            }
        } catch (...) {
            cerr << "Warning: Failed to parse node " << node << endl;
            continue;
        }
    }

    if (minDistance == numeric_limits<double>::max()) {
        throw runtime_error("No valid nodes found within search range");
    }

    
    return nearestNode;
}
