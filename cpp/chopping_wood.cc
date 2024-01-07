/*
Problem: Chopping Wood - https://open.kattis.com/problems/chopwood
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

struct node_degree{
  int node;
  int degree;
};

int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  // Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);

  string first_row;
  getline(cin, first_row);
  int nr_of_rows = stoi(first_row);
  vector<int> vertex_vect;
  while(true){
    string vertex_str;
    getline(cin, vertex_str);
    //If the empty line is reached, the whole dictionary is read
    if(vertex_str.size() == 0){
      break;
    }
    int vertex = stoi(vertex_str);
    vertex_vect.push_back(vertex);
  }

  if(vertex_vect.back() != nr_of_rows+1){
    cout << "Error" << "\n";
  } else{
    vector<int> degrees(nr_of_rows+1, 0);
    vector<node_degree> node_degrees_og(nr_of_rows+1);
    map<int, int> zero_degrees;

    for(int node = 0; node < nr_of_rows; node++){
      degrees[vertex_vect[node]-1] += 1;
    }

    for(int i = 0; i < nr_of_rows+1; i++){
      node_degrees_og[i] = {i+1, degrees[i]};
      if(degrees[i] == 0){
        zero_degrees[i+1] = i;
      }
    }
     
    for(int i = 1; i <= nr_of_rows; i++){
      int input = vertex_vect[i-1];
      map<int, int>::iterator it;
      for(it = zero_degrees.begin(); it != zero_degrees.end(); it++){
        // key it->first = node
        // value it->second = index
        if (it->first != input){
          cout << node_degrees_og[it->second].node << "\n";
          node_degrees_og[input-1].degree -= 1;
          zero_degrees.erase(it->first);
          if(node_degrees_og[input-1].degree == 0){
            zero_degrees[node_degrees_og[input-1].node] = node_degrees_og[input-1].node - 1;
          }
          break;
        }
      }
    }
  }
  return 0;
}    
