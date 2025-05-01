#ifndef MYGRAPH_H
#define MYGRAPH_H  

/*    @file MyGraph.cpp   
      @author < Allyssa Dalton >
      @date < April 13th, 2025 >

			@description Implements a class for storing a bi-directional graph.
*/

#include <string>
#include <unordered_map>
#include <list>

using namespace std;

enum graph_type_t {
  directed,
  undirected
};

template <typename T>
class MyGraph{
  public:
  MyGraph(graph_type_t type = directed);
  void print();   
      // Prints the current graph to the screen
  void addEdge(const T &a,const T &b, float weight = 1.0);
      // Add an edge from 
      // node a to node b, with optional weight.  If a or b doesn't exist as nodes,
      // this will create them.
      // Will overwrite the edge if it already exists
  void addNode(const T &a);
      // Adds a node a to the graph (with no edges)
  void removeEdge(const T &a, const T &b);
      // Removes the edge from a to b, if it exists
  void removeNode(T a);
      // Removes node a if it exists and removes all edges associated with it

  unsigned numNodes();
      // Returns the number of nodes in the graph
  unsigned numEdges();
      // Returns the number of edges in the graph

  bool isNode(T a);
      // Returns true if a is a node, false otherwise
  bool hasEdge(T a, T b);
      // Returns true if there is an edge from a to b, false otherwise
  float getWeight(T a, T b);
      // Returns the weight of the edge from a to b, or throws an exception
      // if there isn't an edge or a or b aren't nodes.

  /* *****  Shortest Path using Dyjstra's Algorithm ***** */
  float dijkstraShortestDistance(T a, T b);
      // Returns the total shortest distance from a to b.
  list<T> dijstraShortestPath(T a, T b);
      // Returns a list of
  /* *****  Shortest Path using Bellman-Ford Algorithm ***** */
  float bellmanFordShortestDistance(T a, T b);
      // Returns the total shortest distance from a to b.
  list<T> bellmanFordShortestPath(T a, T b);
      // Returns a list of

  //template <typename T> findNearestNode(float lat, float lon);
  T findNearestNode(double lat, double lon);
  private:
  unordered_map<T, list< pair<T, float> > > data;

  graph_type_t type;
};


#endif