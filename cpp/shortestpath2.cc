/*
Problem: Single source shortest path, non-negative weights - https://open.kattis.com/problems/shortestpath2
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.

This code is used to solve the single source shortest path problem. The problem is to find the 
shortest path where the problems are restricted to have only one source. The input is several 
test cases.

The time complexity of the program is O(n^2) where n is the number of nodes in the graph.

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
4 4 4 0
0 1 15 10 5
1 2 15 10 5
0 2 5 5 30
3 0 0 1 1
0
1
2
3
2 1 1 0
0 1 100 0 5
1
0 0 0 0

Output:
0
20
30
Impossible

105
*/
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

//Defines a struct for a node that has a number and a time from 
//source.
struct Node{
  int nr;
  int time;
};

//Defines a struct for a weighted pointer to a neighbor node.
struct WeightedPointer{
  int weight;
  int node;
};

//Sorts nodes by time.
struct NodeSort{
  bool operator()(Node node1, Node node2){
    return node1.time < node2.time;
  }
};

//Defines a class for edges with nodes u, v, weight w, 
//start_time t_0 and period P.
class Edge{
  public:
    Edge(int u, int v, int t_0, int P, int w);
    int u;
    int v;
    int t_0;
    int P;
    int w;
};

//Constructor for edges.
//Time complexity: O(1)
Edge::Edge(int u, int v, int t_0, int P, int w){
  this->u = u;
  this->v = v;
  this->t_0 = t_0;
  this->P = P;
  this->w = w;
};

//Defines a struct for the return value of the function 
//find_shortest_paths.
struct Return{
  vector<vector<int>> shortest_paths;
  vector<int> length;
};

//Defines a class for graphs with the input number of edges, nodes
//and a start node.
class Graph{
  public:
    Graph(int nr_edges, int nr_nodes, int start_node);
    int nr_edges;
    int nr_nodes;
    int start_node;
    vector<vector<Edge>> neighbor_lists;
    void add_edge(int u, int v, int t_0, int P, int w);
    vector<WeightedPointer> current_neighbors(int u, int t);
    Return timed_shortest_paths(int limit);
};

//Constructor for graphs.
//Time complexity: O(1)
Graph::Graph(int nr_edges, int nr_nodes, int start_node){
  this->nr_edges = nr_edges;
  this->nr_nodes = nr_nodes;
  this->neighbor_lists = vector<vector<Edge>>(nr_nodes);
  this->start_node = start_node;
};    

//Adds an edge to the graph.
//Time complexity: O(1)
void Graph::add_edge(int u, int v, int t_0, int P, int w){
  Edge e = Edge(u, v, t_0, P, w);
  this->neighbor_lists[u].push_back(e);
};

//Returns a vector of weighted pointers to the current neighbors of 
//node u at time t.
//Time complexity: O(n) where n is the number of 
//nodes(neighbors of u) (worst case)
vector<WeightedPointer> Graph::current_neighbors(int u, int t){
  vector<WeightedPointer> neighbors;
  for(int i = 0; i < this->neighbor_lists[u].size(); i++){
    Edge edge = this->neighbor_lists[u][i];
    if(t <= edge.t_0){
      neighbors.push_back({edge.w + edge.t_0 - t, edge.v});
    } else if(edge.P){
      neighbors.push_back({edge.w + (edge.P - (t - edge.t_0) %
          edge.P) % edge.P, edge.v});
    }
  }

  return neighbors;
};

//Returns a vector of distances from the start node to all other 
//nodes.
//Time complexity: O(n^2) where n is the number of nodes (worst case)
Return Graph::timed_shortest_paths(int limit){
  priority_queue<Node, vector<Node>, NodeSort> pq;
  vector<int> distances(this->nr_nodes, limit); 
  Return ret{vector<vector<int>>(nr_nodes, 
      vector<int>(nr_nodes, 0)), distances};
  ret.length[this->start_node] = 0;
  pq.push({this->start_node, 0});

  while(!pq.empty()){
    Node node = pq.top();
    pq.pop();
    vector<WeightedPointer> neighbors = 
        current_neighbors(node.nr, node.time);

    for(int i = 0; i < neighbors.size(); i++){
      WeightedPointer neighbor = neighbors[i];
      int distance = node.time + neighbor.weight;

      if(ret.length[neighbor.node] > distance){
        ret.length[neighbor.node] = distance;
        ret.shortest_paths[neighbor.node][node.nr] = 1;
        pq.push({neighbor.node, distance});
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
    int u, v, t_0, P, w;
    for(int i = 0; i < nr_edges; i++){
      cin >> u >> v >> t_0 >> P >> w;
      G.add_edge(u, v, t_0, P, w);
    }

    int limit = nr_edges * 1000 + 1;
    Return shortest_paths = G.timed_shortest_paths(limit);
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