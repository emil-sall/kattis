/*
Problem: The Uxuhul Voting System - https://open.kattis.com/problems/uxuhulvoting
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.
*/
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

string output(int vote){
  switch(vote){
    case 0: return "NNN";
    case 1: return "NNY";
    case 2: return "NYN";
    case 3: return "NYY";
    case 4: return "YNN";
    case 5: return "YNY";
    case 6: return "YYN";
    case 7: return "YYY";
  }
};


string Solve(vector<vector<short int>> table, 
             vector<vector<short int>> parents){

  vector<vector<short int>> backtrack_table(table.size(), 
                                            vector<short int>(8, 0));
  for(int prio = 0; prio < 8; prio++){
    vector<short int> local_vect;
    local_vect.push_back(table[table.size() - 1][parents[prio][0]]);
    local_vect.push_back(table[table.size() - 1][parents[prio][1]]);
    local_vect.push_back(table[table.size() - 1][parents[prio][2]]);

    auto pointer = min_element(local_vect.begin(), local_vect.end());
    auto index = distance(local_vect.begin(), pointer);
    backtrack_table[table.size() - 1][prio] = parents[prio][index];
  }

  for(int priest = 1; priest < table.size(); priest++){
    for(int prio = 0; prio < 8; prio++){
      vector<short int> local_vect;
      local_vect.push_back(table[table.size() - priest - 1]
        [backtrack_table[table.size() - priest][parents[prio][0]]]);

      local_vect.push_back(table[table.size() - priest - 1]
        [backtrack_table[table.size() - priest][parents[prio][1]]]);

      local_vect.push_back(table[table.size() - priest - 1]
        [backtrack_table[table.size() - priest][parents[prio][2]]]);

          
      auto pointer = min_element(local_vect.begin(), local_vect.end());
      auto index = distance(local_vect.begin(), pointer);
      backtrack_table[table.size() - priest - 1][prio] = 
          backtrack_table[table.size() - priest][parents[prio][index]];
    }
  }
  return output(backtrack_table[0][0]);
}

int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  // Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);

  int n, m;
  vector<vector<short int>> parents{{1,2,4}, {0,3,5}, {0,3,6}, 
                                    {1,2,7}, {0,5,6}, {1,4,7}, 
                                    {2,4,7}, {3,5,6}};
  cin >> n;
  while(cin >> m){
    vector<vector<short int>> table(m, vector<short int>(8, 0));
    for(int priest = 0; priest < m; priest++){
      for(int prio = 0; prio < 8; prio++){
        cin >> table[priest][prio];
      }
    }
    string answer = Solve(table, parents);

    cout << answer << "\n";
  }
  return 0;
}