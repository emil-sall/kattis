/*
Problem: Closest sums - https://open.kattis.com/problems/closestsums
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdlib>

using namespace std;

vector<int> all_sums(unsigned n){
  vector<int> vect;
  for(unsigned i = 0; i < n; i++){
    string A;
    getline(cin, A);
    int a = stoi(A);
    vect.push_back(a);
  }
  vector<int> sum_vect; 
  for(unsigned i_1 = 0; i_1 < n; i_1++){
    for(unsigned i_2 = 0; i_2 < n; i_2++){
      if(i_1 == i_2){
        continue;
      } else{
        int sum = vect[i_1] + vect[i_2];
        sum_vect.push_back(sum);
      }
    }
  }
  return sum_vect;
}

void closest_sum(unsigned m, vector<int> sum_vect){
  unsigned closest;
  for(unsigned i = 0; i < m; i++){
    unsigned mindiff = 20000000;
    string A;
    getline(cin, A);
    int query = stoi(A);
    for (unsigned sum:sum_vect){
      int diff = query-sum;
      unsigned absdiff = abs(diff);
      if(absdiff < mindiff){
        mindiff = absdiff;
        closest = sum;
      }
    }
    string current_query = to_string(query);
      cout << "Closest sum to " << current_query << " is " << closest << "." << "\n";
  }
}

int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  // Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);

  unsigned sum_case = 0;
  while (true){
    sum_case = sum_case + 1;
    string N;
    getline(cin, N);
    if(N.size() == 0){
      break;
    }
    unsigned n = stoi(N);
    vector<int> sums = all_sums(n);
    string current_case = to_string(sum_case);
    cout << "Case " << current_case << ":" << "\n";        
    string M;
    getline(cin, M);
    unsigned m = stoi(M);
    closest_sum(m, sums);
  }    
  return 0;
}