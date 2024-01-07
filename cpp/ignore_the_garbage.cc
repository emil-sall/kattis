/*
Problem: Ignore the Garbage - https://open.kattis.com/problems/ignore
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.
*/
#include <iostream>

using namespace std;

void solve(int k){
  int digit;
  int output;
  if (k > 0){
    while(k > 0){
      digit = k % 7;
      if(digit == 3){
        output = 5;
      } else if(digit == 4){
        output = 9;
      } else if(digit == 5){
        output = 8;
      } else if(digit == 6){
        output = 6;
      } else{
        output = digit;
      }
      cout << output;
      k = k/7;
    }
  } else{
    cout << 0;
  }   
  cout << "\n";
}

int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  // Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);

  int k;
  while(cin >> k){
    solve(k);
  }
  return 0;
}