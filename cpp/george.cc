/*
Problem: George - https://open.kattis.com/problems/george
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.
*/
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;


int min(int x, int y){ 
    return x < y ? x : y; 
}

int max(int x, int y){ 
    return x > y ? x : y; 
}


int solve(int nr_intersections, int nr_streets, int start_point, 
          int end_point, int start_time, 
          vector<int> mr_george_intersections, 
          vector<vector<int>> adjacency_matrix){
            
  vector<vector<int>> george_matrix(adjacency_matrix[0].size(), 
                        vector<int>(adjacency_matrix[0].size(), 
                                    1000001));

  for(int i = 0, t = 0; i < mr_george_intersections.size() - 1; i++){
    george_matrix[mr_george_intersections[i]]
                  [mr_george_intersections[i+1]] = t;

    george_matrix[mr_george_intersections[i+1]]
                  [mr_george_intersections[i]] = t;

    t += adjacency_matrix[mr_george_intersections[i]]
                          [mr_george_intersections[i+1]];
  }
  vector<int> time_stamps(nr_intersections, 1000001);
  vector<int> visited(nr_intersections, 0);
  time_stamps[start_point] = start_time;
    
  for(int i = 0; i < nr_intersections; i++){
    int m = -1;
    for(int j = 0; j < nr_intersections; j++){
      if(visited[j]){
        continue;
      }
      if(m == -1 || time_stamps[j] < time_stamps[m]){
        m = j;
      }
    }
    visited[m] = 1;

    for( int j = 0; j < nr_intersections; j++){
      if(time_stamps[m] < george_matrix[m][j]){
        time_stamps[j] = min(time_stamps[j], time_stamps[m] + 
                             adjacency_matrix[m][j]);
      } else{
        time_stamps[j] = min(time_stamps[j], max(george_matrix[m][j] +
                             adjacency_matrix[m][j], time_stamps[m]) +
                             adjacency_matrix[m][j]);
      }
    }
  }
  return time_stamps[end_point] - time_stamps[start_point];
}


int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  // Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);

  int N, M;
  cin >> N >> M;

  int  A, B, K, G;
  cin >> A >> B >> K >> G;


  vector<int> mr_george_intersections(G, 0); 
  int x;
  for(int i = 0; i < G; i++){
    cin >> x;
    mr_george_intersections[i] = x - 1;
  }
  vector<vector<int>> adjacency_matrix(N, vector<int>(N, 1000001));
  int total_time = 0;
  int a, b;
  for(int i = 0; i < M; i++){
    cin >> a >> b >> x;
    adjacency_matrix[a - 1][b - 1] = x;
    adjacency_matrix[b - 1][a - 1] = adjacency_matrix[a - 1][b - 1];
  }

  cout << solve(N, M, A-1, B-1, K, mr_george_intersections, 
                adjacency_matrix);
  return 0;
}