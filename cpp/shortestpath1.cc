/*
Problem: Single source shortest path, non-negative weights - https://open.kattis.com/problems/shortestpath1
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.

This code is used to solve the single source shortest path problem. The problem is to find the 
shortest path where the problems are restricted to have only one source. The input is several 
test cases.

The time complexity of the program is O(E log(V)) where E is the number of edges and V is the 
number of vertices.  

The input of each test case is row dependent, the first row are four integers separated by a space, 
the first integer is the number of nodes n in the graph, the second integer is the number of edges m, 
the third is the number of queries q and the fourth is the source node s. The next m rows are three
integers separated by a space, the first integer is the first node of the edge, the second integer is
the second node of the edge and the third integer is the weight of the edge. The next q rows are one
integer which is the node that we want to find the shortest path to from the source node.

The output for each test case is one row per test case that has one integer which is the shortest path
to the node from the source node. If there is no path to the node, the output should be "Impossible".
Between test cases the output should be an empty row. An example of input and output is shown below.

Input:
4 3 4 0
0 1 2
1 2 2
3 0 2
0
1
2
3
2 1 1 0
0 1 100
1
0 0 0 0

Output:
0
2
4
Impossible

100

*/
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

//Defines a struct for a node that has a number and a distance from 
//source.
struct Node{
  int nr;
  int distance;
};

//Sorts nodes by distance.
struct NodeSort{
  bool operator()(Node node1, Node node2){
    return node1.distance < node2.distance;
  }
};

//Defines a class for edges with nodes u, v and weight w.
class Edge{
  public:
    Edge(int u, int v, int w);
    int u;
    int v;
    int w;
};

//Defines a struct for the return value of the function 
//find_shortest_paths.
struct Return{
  vector<vector<int>> shortest_paths;
  vector<int> length;
};

//Defines a class for graphs with the input number of edges, nodes 
//and a start node. The graph is repressented as a vector of vectors
//of edges. Each inner vector has got edges to the neighbor nodes, 
//and the outer vectors indexes are the nodes.
class Graph{
  public:
    Graph(int nr_edges, int nr_nodes, int start_node);
    int nr_edges;
    int nr_nodes;
    int start_node;
    vector<vector<Edge>> neighbor_lists;
    void add_edge(int u, int v, int w);
    Return find_shortest_paths(int limit);
};

//Constructor for edges.
//Time complexity: O(1)
Edge::Edge (int u, int v, int w){
  this->u = u;
  this->v = v;
  this->w = w;
};

//Constructor for graphs. It initializes the graph with the input 
//number of edges, nodes and start node.
//Time complexity: O(1)
Graph::Graph(int nr_edges, int nr_nodes, int start_node){
  this->nr_edges = nr_edges;
  this->nr_nodes = nr_nodes;
  this->neighbor_lists = vector<vector<Edge>>(nr_nodes);
  this->start_node = start_node;
};

//Adds an edge from node u to node v with the weigth w to the graph.
//Time complexity: O(1)
void Graph::add_edge(int u, int v, int w){
    Edge e = Edge(u, v, w);
    this->neighbor_lists[u].push_back(e);
};

//Finds the shortest paths from the start node to all other nodes.
//The input limit is the maximum distance that is allowed + 1.
//Time complexity: O(E log V)
Return Graph::find_shortest_paths(int limit){
  priority_queue<Node, vector<Node>, NodeSort> pq;
  vector<int> distances(this->nr_nodes, limit);
  Return ret{vector<vector<int>>(nr_nodes, 
      vector<int>(nr_nodes, 0)), distances};
  ret.length[this->start_node] = 0;
  pq.push(Node{this->start_node, 0});

  while(!pq.empty()){
    Node node = pq.top();
    pq.pop();
    vector<Edge> root = this->neighbor_lists[node.nr]; 
    for(int i = 0; i < root.size(); i++){
      Edge edge = root[i];
      int l_v = ret.length[edge.v];
      int l_u = ret.length[edge.u];
      if(l_v > l_u + edge.w){
        ret.length[edge.v] = l_u + edge.w;
        ret.shortest_paths[edge.u][edge.v] = 1;
        pq.push(Node{edge.v, l_v});
      }
    }
  }
  
  return ret;
};

int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  // Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);


  int nr_nodes, nr_edges, nr_queries, start_node;
  while(cin >> nr_nodes >> nr_edges >> nr_queries >> start_node){
    if(nr_nodes == 0 && nr_edges == 0 && nr_queries == 0){
      continue;
    }

    Graph G(nr_edges, nr_nodes, start_node);
    int u, v, w;
    for(int i = 0; i < nr_edges; i++){
      cin >> u >> v >> w;
      G.add_edge(u, v, w);
    }

    int limit = nr_edges * 1000 + 1;
    Return shortest_paths = G.find_shortest_paths(limit);
    int q;
    for(int i = 0; i < nr_queries; i++){
      cin >> q;
      if(shortest_paths.length[q] == limit){
        cout << "Impossible \n";
      } else{
        cout << shortest_paths.length[q] << "\n";
      }
    }
    
    cout << "\n";
  }
  return 0;
}