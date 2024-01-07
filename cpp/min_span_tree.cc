/*
Minimum spanning tree: https://open.kattis.com/problems/minspantree
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.

This code is used to solve the minimum spanning tree problem. The problem is to find the 
minimum-weighted tree that connects all the vertices in a graph. The input is several 
test cases and each test case input is the edges of the graph.

The time complexity of the program is O(E * log(E)) where E is the number of edges in the graph.
This is because the program is sorting the edges based on the weights and the sorting takes O(E * log(E)).
The sorting is done with the standard library function std::sort which is using the algorithm introsort
which is a combination of quicksort, heapsort and insertion sort. The rest of the operations have a lower
time complexity, parts as the union-find operations and actually constructing the tree.


The input of each test case is row dependent, the first row are two integers separated by a space, 
the first integer is the number of nodes n in the graph and the second integer is the number of edges m.
The next m rows are three integers separated by a space, the first integer is the first node of the edge,
the second integer is the second node of the edge and the third integer is the weight of the edge.

The output for each test case is first a row with one integer which is the cost of the minimum spanning
tree. The next n-1 rows are all the edges in the minimum spanning tree, each row is two integers separated
by a space, the first integer is the first node of the edge and the second integer is the second node of
the edge. If there is no minium spanning tree, the output should be "Impossible". An example of input and
output is shown below.

Input:
4 4
0 1 1
1 2 2
1 3 3
2 3 0
2 1
0 1 100
3 0
0 0

Output:
3
0 1
1 2
2 3
100
0 1
Impossible

*/

#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;


//Defines a struct for an edge that always has the smaller node as u
//and the larger as v. The weight as w.
struct Edge{
  int u;
  int v;
  int w;
  Edge(int u, int v, int w){
    if(u > v){
      this->u = v;
      this->v = u;
    } else{
      this->u = u;
      this->v = v;
    }
    this->w = w;
  }
};


//Sorts edges by weight.
bool edge_sort(Edge edge1, Edge edge2){
  return edge1.w < edge2.w;
}

//Sorts edges by u and then by v. 
bool node_sort(Edge edge1, Edge edge2){
  if(edge1.u == edge2.u){
    return edge1.v < edge2.v;
  }
  return edge1.u < edge2.u;
}

//Struct for returning the minimum spanning tree. 
struct Return{
  vector<Edge> min_span_tree;
  int cost;
};

//A class for treating disjoint sets and finding out which set a node
//belongs to. Initiates with the number of nodes as input.
class UnionFind{ 
  private: 
    vector<int> parent, rank;
  public:
      UnionFind(int N);
      int findSet(int i);
      bool isSameSet(int i, int j);
      void unionSet(int i, int j);
};

//Constructor for the UnionFind class.
//The time complexity is O(n) where n is the number of nodes.
UnionFind::UnionFind(int N){ 
  rank.assign(N, 0);
  parent.assign(N, 0); 
  for (int i = 0; i < N; i++){
    parent[i] = i;
  } 
};

//Finds the set that a node belongs to.
//The time complexity is O(log n) where n is the number of nodes.
int UnionFind::findSet(int node){ 
  return (parent[node] == node) ? node : (parent[node] =
      findSet(parent[node])); 
};

//Checks if two nodes belong to the same set.
//The time complexity is O(1).
bool UnionFind::isSameSet(int u, int v){ 
  return findSet(u) == findSet(v); 
};

//Unions two disjoint sets. The input is two nodes. 
//The time complexity is O(1).
void UnionFind::unionSet(int u, int v){
  if (!isSameSet(u, v)){ 
    int set1 = findSet(u), set2 = findSet(v);
    if (rank[set1] > rank[set2]){
      parent[set2] = set1; 
    } else{ 
      parent[set1] = set2;
      if (rank[set1] == rank[set2]){
        rank[set2]++;
      } 
    }
  } 
}; 

//Solves the minimum spanning tree problem. The input is a vector of
//edges, the number of nodes and the number of edges.
//The time complexity is O(E log E) where E is the number of edges.
Return solve(vector<Edge> adj_list, int nr_nodes, int nr_edges){
  sort(adj_list.begin(), adj_list.end(), edge_sort); 
  int cost = 0;
  vector<Edge> min_span_tree;
  UnionFind UF(nr_nodes); 
  for (int i = 0; i < nr_edges; i++){ 
    Edge edge = adj_list[i];
    if (!UF.isSameSet(edge.u, edge.v)){ 
      cost += edge.w; 
      UF.unionSet(edge.u, edge.v); 
      min_span_tree.push_back(edge);
    } 
  } 
    
  sort(min_span_tree.begin(), min_span_tree.end(), node_sort); 
  Return ret = {min_span_tree, cost};
  return ret;
}



int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  //Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);

  int nr_nodes, nr_edges;
  while(cin >> nr_nodes >> nr_edges){
    if(nr_nodes == 0 && nr_edges == 0){
      break;
    }

    int u, v, w, start_node; 
    vector<Edge> adj_list; 
    for(int i = 0; i < nr_edges; i++){
      cin >> u >> v >> w;
      adj_list.push_back({u, v, w});
    }

    if(nr_nodes == 0 || nr_edges == 0 || nr_edges < nr_nodes-1){
      cout << "Impossible \n";
      continue;
    }

    Return min_span_tree = solve(adj_list, nr_nodes, nr_edges);

    if(min_span_tree.min_span_tree.size() == nr_nodes-1){    
      cout << min_span_tree.cost << "\n";
      for(int i = 0; i < min_span_tree.min_span_tree.size(); i++){
        cout << min_span_tree.min_span_tree[i].u << " " << 
            min_span_tree.min_span_tree[i].v << "\n";
      }
    } else{
      cout << "Impossible \n";
    }
  }
  return 0;
}