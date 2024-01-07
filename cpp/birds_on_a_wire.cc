/*
Problem: Birds on a Wire - https://open.kattis.com/problems/birds
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solve(int l, int d, vector<int> birds){
  if(l < 12){
    return 0;
  } else if(birds.empty()){
    int new_birds = ((l - 12) / d) + 1;
    return new_birds;
  }
  sort(birds.begin(), birds.end());
  int new_birds = (birds[0] - 6) / d;

  for(int i = 1; i < birds.size(); i++){
    new_birds += (birds[i] - birds[i-1] - d) / d;
  }

  new_birds += (l - 6 - birds.back()) / d;
    return new_birds;
}

int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  // Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);
    
  int l, d, n;
  cin >> l >> d >> n;
  vector<int> birds(n);
  for(int i = 0; i < n; i++){
    cin >> birds[i];
  }

  cout << solve(l, d, birds) << "\n";
  return 0;
}