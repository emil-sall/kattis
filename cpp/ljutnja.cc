/*
Problem: Ljutnja - https://open.kattis.com/problems/ljutnja
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <math.h>

using namespace std;

int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  // Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);

  string first_row;
  getline(cin, first_row);
  istringstream iss(first_row);
  unsigned long long nr_candies = 0, nr_children = 0;
  iss >> nr_candies >> nr_children;
  vector<unsigned long long> vect;
  unsigned long long leftovers = 0;

  while(true){   
    string want_str;
    //Read the current line
    getline(cin, want_str);

    //If the empty line is reached, the whole dictionary is read
    if(want_str.size() == 0){
      break;
    }

    unsigned want = stoi(want_str);
    vect.push_back(want);
    leftovers += want;
  }

  sort(vect.begin(), vect.end());  //~ O(n log(n))
  leftovers -= nr_candies;
  unsigned long long anger = 0;
  vector<unsigned long long> leftover_vect;

  for(unsigned i = 0; i < nr_children; i++){
    unsigned uniform = leftovers/(nr_children-i);
    if (uniform <= vect[i]){
      leftovers -= uniform;
      leftover_vect.push_back(uniform);
    } else{
      leftovers -= vect[i];
      leftover_vect.push_back(vect[i]);
    }
        
    unsigned long long angerpoint = leftover_vect[i]*leftover_vect[i]; 
    anger += angerpoint;
  }

  cout << anger << "\n";
  cout << flush;
  return 0;
}