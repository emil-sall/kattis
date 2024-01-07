/*
Problem: Evil Straw Warts Live - https://open.kattis.com/problems/evilstraw
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.
*/
#include <iostream>
#include <string>
#include <map>

using namespace std;

map<string, int> dp;

int palin(string s){
  int i;
  for(i = 0; s[i] == s[s.size()-1-i] && i < s.size()/2; i++);
  if(i){
    s = s.substr(i, s.size()-2*i);
  }
  if(s.size() <= 1){
    return 0;
  }
  int n = s.size();
  int &nr_swaps = dp[s];
  if(nr_swaps){
    return nr_swaps;
  }
  nr_swaps = 10001;
  for(i = 0; i < n-1; i++){  //find first occurence of s[n-1]
    if(s[i] == s[n-1]){
      break;
    }
  }
  if(i < n-1){ //if found check if it is better than the previous one
    //cut the string to the non-palindromic part
    nr_swaps = min(nr_swaps, i + palin(s.substr(0, i) +
                   s.substr(i+1, n-i-2)));     
  }
  if(!i){
    return nr_swaps;
  }
  for(i = n-1; i > 0; i--){ //find last occurence of s[0]
    if(s[i] == s[0]){
      break;
    }
  }
  if(i > 0){ //if found check if it is better than the previous one
    //cut the string to the non-palindromic part
    nr_swaps = min(nr_swaps, n-i-1 + palin(s.substr(1, i-1) +
                   s.substr(i+1, n-i-1)));   
  }
  return nr_swaps;
}

int main() {
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  // Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);

  int n;
  cin >> n;
  string s;
  while(n--){
    cin >> s;
    int nr_swaps = palin(s);
    if(nr_swaps == 10001){
      cout << "Impossible" << "\n";
    } else{
      cout << nr_swaps << "\n";
    }
  }
  return 0;
}
