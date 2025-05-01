/*    @file MyGraph_test.cpp     
      @author < Allyssa Dalton >
      @date < April 13th, 2025 >

			@description Tests for the MyComplex class
*/

#include "gtest/gtest.h"

#include "MyGraph.h"
#include "MyGraph.cpp"


TEST(Nodes, Simple) {
  MyGraph<int> a;
  EXPECT_EQ(a.numNodes(), 0);
  a.addNode(5);
  EXPECT_EQ(a.numNodes(), 1);
  a.addNode(6);
  EXPECT_EQ(a.numNodes(), 2);
  a.addNode(5);
  EXPECT_EQ(a.numNodes(), 2);
}

TEST(Nodes, Simple2) {
  MyGraph<string> a;
  EXPECT_EQ(a.numNodes(), 0);
  a.addNode("hi");
  EXPECT_EQ(a.numNodes(), 1);
  a.addNode("hello");
  EXPECT_EQ(a.numNodes(), 2);
  a.addNode("hi");
  EXPECT_EQ(a.numNodes(), 2);
}

TEST(Nodes, RemoveSimple) {
  MyGraph<int> a;
  EXPECT_EQ(a.numNodes(), 0);
  a.addNode(5);
  EXPECT_EQ(a.numNodes(), 1);
  a.addNode(6);
  EXPECT_EQ(a.numNodes(), 2);
  a.addNode(5);
  EXPECT_EQ(a.numNodes(), 2);
  a.removeNode(5);
  EXPECT_EQ(a.numNodes(), 1);
  a.removeNode(6);
  EXPECT_EQ(a.numNodes(), 0);
  a.removeNode(8);
}

TEST(Edges, Simple) {
  MyGraph<int> a;
  EXPECT_EQ(a.numEdges(), 0);
  a.addEdge(1,2);
  EXPECT_EQ(a.numEdges(), 1);
  a.addEdge(1,3);
  EXPECT_EQ(a.numEdges(), 2);
  a.addEdge(-1,1);
  EXPECT_EQ(a.numEdges(), 3);
  EXPECT_EQ(a.numNodes(), 4);
  a.addEdge(-1, 2);
  EXPECT_EQ(a.numNodes(), 4);
  EXPECT_EQ(a.numEdges(), 4);
}

TEST(Edges, Simple2) {
  MyGraph<int> a;
  EXPECT_EQ(a.numEdges(), 0);
  a.addEdge(1,2);
  EXPECT_EQ(a.numEdges(), 1);
  a.addEdge(2,1);
  EXPECT_EQ(a.numEdges(), 2);
  a.addEdge(-1,1);
  EXPECT_EQ(a.numEdges(), 3);
  EXPECT_EQ(a.numNodes(), 3);
  a.addEdge(-1, 2);
  EXPECT_EQ(a.numNodes(), 3);
  EXPECT_EQ(a.numEdges(), 4);
}

TEST(UnDirected_Edges, Simple2) {
  MyGraph<int> a(undirected);
  EXPECT_EQ(a.numEdges(), 0);
  a.addEdge(1,2);
  EXPECT_EQ(a.numEdges(), 1);
  a.addEdge(2,1);
  EXPECT_EQ(a.numEdges(), 1);
  a.addEdge(-1,1);
  EXPECT_EQ(a.numEdges(), 2);
  EXPECT_EQ(a.numNodes(), 3);
  a.addEdge(-1, 2);
  EXPECT_EQ(a.numNodes(), 3);
  EXPECT_EQ(a.numEdges(), 3);
}

TEST(UnIsNode, Simple) {
  MyGraph<int> a(undirected);
  a.addEdge(1,2);
  a.addEdge(2,1);
  a.addEdge(-1,1);
  a.addEdge(-1, 2);
  EXPECT_TRUE(a.isNode(-1));
  EXPECT_TRUE(a.isNode(1));
  EXPECT_TRUE(a.isNode(2));
  EXPECT_FALSE(a.isNode(3));
}

TEST(UnIsNode, Complex) {
  MyGraph<int> a(undirected);
  a.addEdge(1,2);
  a.addEdge(2,1);
  a.addEdge(-1,1);
  a.addEdge(-1, 2);
  EXPECT_TRUE(a.isNode(-1));
  EXPECT_TRUE(a.isNode(1));
  EXPECT_TRUE(a.isNode(2));
  EXPECT_FALSE(a.isNode(3));
  a.removeNode(1);
  EXPECT_FALSE(a.isNode(1));
}

TEST(IsNode, Simple) {
  MyGraph<int> a;
  a.addEdge(1,2);
  a.addEdge(2,1);
  a.addEdge(-1,1);
  a.addEdge(-1, 2);
  EXPECT_TRUE(a.isNode(-1));
  EXPECT_TRUE(a.isNode(1));
  EXPECT_TRUE(a.isNode(2));
  EXPECT_FALSE(a.isNode(3));
}

TEST(IsNode, Complex) {
  MyGraph<int> a;
  a.addEdge(1,2);
  a.addEdge(2,1);
  a.addEdge(-1,1);
  a.addEdge(-1, 2);
  EXPECT_TRUE(a.isNode(-1));
  EXPECT_TRUE(a.isNode(1));
  EXPECT_TRUE(a.isNode(2));
  EXPECT_FALSE(a.isNode(3));
  a.removeNode(1);
  EXPECT_FALSE(a.isNode(1));
}

TEST(UnHasEdge, Simple) {
  MyGraph<int> a(undirected);
  a.addEdge(1,2);
  EXPECT_TRUE(a.hasEdge(1,2));
  EXPECT_TRUE(a.hasEdge(2,1));
  EXPECT_FALSE(a.hasEdge(1,3));
  a.addEdge(1,3);
  EXPECT_TRUE(a.hasEdge(3,1));
  EXPECT_TRUE(a.hasEdge(1,3));
}

TEST(HasEdge, Directed_Simple) {
  MyGraph<int> a;
  a.addEdge(1,2);
  EXPECT_TRUE(a.hasEdge(1,2));
  EXPECT_FALSE(a.hasEdge(2,1));
  EXPECT_FALSE(a.hasEdge(1,3));
  a.addEdge(1,3);
  EXPECT_TRUE(a.hasEdge(1,3));
  EXPECT_FALSE(a.hasEdge(3,1));
}

TEST(HasEdge, Undirected_Complex1) {
  MyGraph<int> a(undirected);
  a.addEdge(1,2);
  a.addEdge(1,3);
  EXPECT_TRUE(a.hasEdge(1,2));
  EXPECT_TRUE(a.hasEdge(2,1));
  EXPECT_TRUE(a.hasEdge(1,3));
  EXPECT_TRUE(a.hasEdge(3,1));
  a.removeEdge(3,1);
  EXPECT_TRUE(a.hasEdge(1,2));
  EXPECT_TRUE(a.hasEdge(2,1));
  EXPECT_FALSE(a.hasEdge(1,3));
  EXPECT_FALSE(a.hasEdge(3,1));
}

TEST(HasEdge, Directed_Complex1) {
  MyGraph<int> a;
  a.addEdge(1,2);
  a.addEdge(1,3);
  EXPECT_TRUE(a.hasEdge(1,2));
  EXPECT_FALSE(a.hasEdge(2,1));
  EXPECT_TRUE(a.hasEdge(1,3));
  EXPECT_FALSE(a.hasEdge(3,1));
  a.removeEdge(3,1);
  EXPECT_TRUE(a.hasEdge(1,2));
  EXPECT_FALSE(a.hasEdge(2,1));
  EXPECT_TRUE(a.hasEdge(1,3));
  EXPECT_FALSE(a.hasEdge(3,1));
}

TEST(HasEdge, Undirected_Complex2) {
  MyGraph<int> a(undirected);
  a.addEdge(1,2);
  a.addEdge(1,3);
  EXPECT_TRUE(a.hasEdge(1,2));
  EXPECT_TRUE(a.hasEdge(2,1));
  EXPECT_TRUE(a.hasEdge(1,3));
  EXPECT_TRUE(a.hasEdge(3,1));
  a.removeNode(1);
  EXPECT_FALSE(a.hasEdge(1,2));
  EXPECT_FALSE(a.hasEdge(2,1));
  EXPECT_FALSE(a.hasEdge(1,3));
  EXPECT_FALSE(a.hasEdge(3,1));
  EXPECT_EQ(a.numEdges(), 0);
  EXPECT_EQ(a.numNodes(), 2);
}

TEST(HasEdge, Directed_Complex2) {
  MyGraph<int> a;
  a.addEdge(1,2);
  a.addEdge(1,3);
  EXPECT_TRUE(a.hasEdge(1,2));
  EXPECT_FALSE(a.hasEdge(2,1));
  EXPECT_TRUE(a.hasEdge(1,3));
  EXPECT_FALSE(a.hasEdge(3,1));
  EXPECT_EQ(a.numEdges(), 2);
  EXPECT_EQ(a.numNodes(), 3);
  a.removeNode(1);
  EXPECT_FALSE(a.hasEdge(1,2));
  EXPECT_FALSE(a.hasEdge(2,1));
  EXPECT_FALSE(a.hasEdge(1,3));
  EXPECT_FALSE(a.hasEdge(3,1));
  EXPECT_EQ(a.numEdges(), 0);
  EXPECT_EQ(a.numNodes(), 2);
}

TEST(Weight, Directed) {
  MyGraph<int> a;
  a.addEdge(1,2, 5);
  EXPECT_EQ(a.getWeight(1,2), 5);
  EXPECT_ANY_THROW(a.getWeight(2,1));
  a.addEdge(2,1,10);
  EXPECT_EQ(a.getWeight(2,1), 10);
  a.addEdge(1,2,15);
  EXPECT_EQ(a.getWeight(1,2), 15);
}

TEST(Weight, Undirected) {
  MyGraph<int> a(undirected);
  a.addEdge(1,2, 5);
  EXPECT_EQ(a.getWeight(1,2), 5);
  EXPECT_EQ(a.getWeight(2,1), 5);
  EXPECT_ANY_THROW(a.getWeight(3,1));
  a.addEdge(2,1,10);
  EXPECT_EQ(a.getWeight(2,1), 10);
  EXPECT_EQ(a.getWeight(1,2), 10);
  a.addEdge(1,2,15);
  EXPECT_EQ(a.getWeight(1,2), 15);
  EXPECT_EQ(a.getWeight(2,1), 15);
}

TEST(Weight, Error) {
  MyGraph<int> a(undirected);
  a.addNode(1);
  a.addNode(2);
  EXPECT_ANY_THROW(a.getWeight(1,2));
}

/*******    Dykstras Shortest Path *******/
TEST(Dykstras, ShortestDistance1) {
  MyGraph<char> a(undirected);
  a.addEdge('A','B', 10);
  a.addEdge('A','C', 2);
  a.addEdge('A','D', 7);
  a.addEdge('C','D', 2);
  a.addEdge('D','B', 2);
  EXPECT_EQ(a.dijkstraShortestDistance('A','D'), 4);
}

TEST(Dykstras, ShortestDistance2) {
  MyGraph<char> a(undirected);
  a.addEdge('A','B', 10);
  a.addEdge('A','C', 2);
  a.addEdge('A','D', 7);
  a.addEdge('C','D', 2);
  a.addEdge('D','B', 2);
  EXPECT_EQ(a.dijkstraShortestDistance('A','B'), 6);
}

TEST(Dykstras, ShortestDistance3) {
  MyGraph<char> a(undirected);
  a.addEdge('A','B', 10);
  a.addEdge('A','C', 2);
  a.addEdge('A','D', 7);
  a.addEdge('C','D', 2);
  a.addEdge('D','B', 2);
  EXPECT_EQ(a.dijkstraShortestDistance('B','C'), 4);
}

TEST(Dykstras, ShortestDistance4_Directed) {
  MyGraph<char> a;
  a.addEdge('A','B', 10);
  a.addEdge('A','C', 2);
  a.addEdge('A','D', 7);
  a.addEdge('C','D', 2);
  a.addEdge('D','B', 2);
  EXPECT_ANY_THROW(a.dijkstraShortestDistance('B','C'));
  a.addEdge('B','A', 1);
  EXPECT_EQ(a.dijkstraShortestDistance('B','C'), 3);
}

TEST(Dykstras, ShortestDistance_NotPossible) {
  MyGraph<char> a(undirected);
  a.addEdge('A','C', 2);
  a.addEdge('A','D', 7);
  a.addEdge('C','D', 2);
  EXPECT_ANY_THROW(a.dijkstraShortestDistance('B','C'));
  a.addNode('B');
  EXPECT_ANY_THROW(a.dijkstraShortestDistance('B','C'));
  a.addEdge('D','B', 1);
  EXPECT_EQ(a.dijkstraShortestDistance('A','B'), 5);
}

TEST(Dykstras, ShortestPath) {
  MyGraph<char> a(undirected);
  a.addEdge('A','B', 10);
  a.addEdge('A','C', 2);
  a.addEdge('A','D', 7);
  a.addEdge('C','D', 2);
  a.addEdge('D','B', 2);
  list<char> ans;
  ans.push_back('A');
  ans.push_back('C');
  ans.push_back('D');
  ans.push_back('B');
  list<char> ret = a.dijstraShortestPath('A','B');
  EXPECT_EQ(ans.size(), ret.size());
  auto it = ans.begin();
  auto r = ret.begin();
  while(it != ans.end() && r != ret.end()){
    EXPECT_EQ(*it, *r);
    it++;
    r++;
  }
}

TEST(Dykstras, ShortestPath_NotPossible) {
  MyGraph<char> a(undirected);
  a.addEdge('A','B', 10);
  a.addEdge('A','C', 2);
  a.addEdge('A','D', 7);
  a.addEdge('C','D', 2);
  a.addEdge('D','B', 2);
  EXPECT_ANY_THROW(a.dijstraShortestPath('A','Z'));
  EXPECT_ANY_THROW(a.dijstraShortestPath('Z','A'));
  a.addEdge('Z', 'B', 1);
  list<char> ans;
  ans.push_back('Z');
  ans.push_back('B');
  ans.push_back('D');
  ans.push_back('C');
  ans.push_back('A');
  list<char> ret = a.dijstraShortestPath('Z','A');
  EXPECT_EQ(ans.size(), ret.size());
  auto it = ans.begin();
  auto r = ret.begin();
  while(it != ans.end() && r != ret.end()){
    EXPECT_EQ(*it, *r);
    it++;
    r++;
  }
}

TEST(Dykstras, NegativeBreak1) {
  MyGraph<char> a(undirected);
  a.addEdge('A','B', -10);
  a.addEdge('A','C', 2);
  a.addEdge('A','D', 7);
  a.addEdge('C','D', 2);
  a.addEdge('D','B', 2);
  // Going from B to A to D should be -3
  EXPECT_EQ(a.dijkstraShortestDistance('D','B'), 2);
}

/*******    Bellman-Ford Shortest Path *******/
TEST(BellmanFord, ShortestDistance1) {
  MyGraph<char> a(undirected);
  a.addEdge('A','B', 10);
  a.addEdge('A','C', 2);
  a.addEdge('A','D', 7);
  a.addEdge('C','D', 2);
  a.addEdge('D','B', 2);
  EXPECT_EQ(a.bellmanFordShortestDistance('A','D'), 4);
}

TEST(BellmanFord, ShortestDistance2) {
  MyGraph<char> a(undirected);
  a.addEdge('A','B', 10);
  a.addEdge('A','C', 2);
  a.addEdge('A','D', 7);
  a.addEdge('C','D', 2);
  a.addEdge('D','B', 2);
  EXPECT_EQ(a.bellmanFordShortestDistance('A','B'), 6);
}

TEST(BellmanFord, ShortestDistance3) {
  MyGraph<char> a(undirected);
  a.addEdge('A','B', 10);
  a.addEdge('A','C', 2);
  a.addEdge('A','D', 7);
  a.addEdge('C','D', 2);
  a.addEdge('D','B', 2);
  EXPECT_EQ(a.bellmanFordShortestDistance('B','C'), 4);
}

TEST(BellmanFord, ShortestDistance_NotPossible) {
  MyGraph<char> a(undirected);
  a.addEdge('A','C', 2);
  a.addEdge('A','D', 7);
  a.addEdge('C','D', 2);
  EXPECT_ANY_THROW(a.bellmanFordShortestDistance('B','C'));
  a.addNode('B');
  EXPECT_ANY_THROW(a.bellmanFordShortestDistance('B','C'));
  a.addEdge('D','B', 1);
  EXPECT_EQ(a.bellmanFordShortestDistance('A','B'), 5);
}

TEST(BellmanFord, ShortestDistance4_Directed) {
  MyGraph<char> a;
  a.addEdge('A','B', 10);
  a.addEdge('A','C', 2);
  a.addEdge('A','D', 7);
  a.addEdge('C','D', 2);
  a.addEdge('D','B', 2);
  EXPECT_ANY_THROW(a.bellmanFordShortestDistance('B','C'));
  a.addEdge('B','A', 1);
  EXPECT_EQ(a.bellmanFordShortestDistance('B','C'), 3);
}

TEST(BellmanFord, NegativeCycle) {
  MyGraph<char> a(undirected);
  a.addEdge('A','B', -10);
  a.addEdge('A','C', 2);
  a.addEdge('A','D', 7);
  a.addEdge('C','D', 2);
  a.addEdge('D','B', 2);
  // Going from B to A to D should be -3, which is a negative cycle
  EXPECT_ANY_THROW(a.bellmanFordShortestDistance('D','B'));
}


TEST(BellmanFord, ShortestPath) {
  MyGraph<char> a(undirected);
  a.addEdge('A','B', 10);
  a.addEdge('A','C', 2);
  a.addEdge('A','D', 7);
  a.addEdge('C','D', 2);
  a.addEdge('D','B', 2);
  list<char> ans;
  ans.push_back('A');
  ans.push_back('C');
  ans.push_back('D');
  ans.push_back('B');
  list<char> ret = a.bellmanFordShortestPath('A','B');
  EXPECT_EQ(ans.size(), ret.size());
  auto it = ans.begin();
  auto r = ret.begin();
  while(it != ans.end() && r != ret.end()){
    EXPECT_EQ(*it, *r);
    it++;
    r++;
  }
}

TEST(BellmanFord, ShortestPath_Directed) {
  MyGraph<char> a;
  a.addEdge('A','B', 10);
  a.addEdge('A','C', 2);
  a.addEdge('A','D', 7);
  a.addEdge('C','D', 2);
  a.addEdge('D','B', 2);
  a.addEdge('B','A', 1);
  list<char> ans;
  ans.push_back('B');
  ans.push_back('A');
  ans.push_back('C');
  ans.push_back('D');
  list<char> ret = a.bellmanFordShortestPath('B','D');
  EXPECT_EQ(ans.size(), ret.size());
  auto it = ans.begin();
  auto r = ret.begin();
  while(it != ans.end() && r != ret.end()){
    EXPECT_EQ(*it, *r);
    it++;
    r++;
  }
}

TEST(BellmanFord, ShortestPath_NotPossible) {
  MyGraph<char> a(undirected);
  a.addEdge('A','B', 10);
  a.addEdge('A','C', 2);
  a.addEdge('A','D', 7);
  a.addEdge('C','D', 2);
  a.addEdge('D','B', 2);
  EXPECT_ANY_THROW(a.bellmanFordShortestPath('A','Z'));
  EXPECT_ANY_THROW(a.bellmanFordShortestPath('Z','A'));
  a.addEdge('Z', 'B', 1);
  list<char> ans;
  ans.push_back('Z');
  ans.push_back('B');
  ans.push_back('D');
  ans.push_back('C');
  ans.push_back('A');
  list<char> ret = a.bellmanFordShortestPath('Z','A');
  EXPECT_EQ(ans.size(), ret.size());
  auto it = ans.begin();
  auto r = ret.begin();
  while(it != ans.end() && r != ret.end()){
    EXPECT_EQ(*it, *r);
    it++;
    r++;
  }
}

TEST(BellmanFord, NegativePath) {
  MyGraph<char> a(undirected);
  a.addEdge('A','B', -10);
  a.addEdge('A','C', 2);
  a.addEdge('A','D', 7);
  a.addEdge('C','D', 2);
  a.addEdge('D','B', 2);
  EXPECT_ANY_THROW(a.bellmanFordShortestPath('C','D'));
}



