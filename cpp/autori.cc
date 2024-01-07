/*
Problem: Autori - https://open.kattis.com/problems/autori
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  // Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);

  string s;
  vector<string> v;

  while(getline(cin, s, '-')){
    cout << s[0];
  }
  return 0;
}