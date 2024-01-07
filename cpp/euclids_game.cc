/*
Problem: Euclids game - https://open.kattis.com/problems/euclidsgame
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.
*/
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;


bool game(long long int nr_1, long long int nr_2){
  if(nr_1 < nr_2){ 
    long long int exchange = nr_1;
    nr_1 = nr_2;
    nr_2 = exchange;
  }
  if(nr_2 == 0){ 
    return false;
  } else if(nr_1 % nr_2 == 0){ 
    return true;
  }
  long long int optimal_move = (nr_1 / nr_2) * nr_2;
  if(!game(nr_1 - optimal_move, nr_2) || nr_1 - optimal_move + nr_2 < nr_1){
    return true;
  }
  return false;
};

int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  //Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);
  
  long long int nr_1, nr_2;
  while(cin >> nr_1 >> nr_2){
    if(nr_1 == 0 && nr_2 == 0){
      break;
    }
    bool winner = game(nr_1, nr_2);
    if(winner){
      cout << "Stan wins\n";
    } else{
      cout << "Ollie wins\n";
    }
  }
  

  return 0;
}