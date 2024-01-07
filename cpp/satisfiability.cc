/*
Problem: Yet Satisfiability Again! - https://open.kattis.com/problems/satisfiability
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> split(string str){
  vector<string> ret = {""};
  for(auto i : str){
    if(i == ' ') continue;
      else if(i == 'v'){
        ret.push_back("");
      }else{
        ret.back().push_back(i);
      }
  }
  return ret;
}

string getbits(int bits, int n){
  string ret;
  for(int i = 0; i < bits; i++) {
    ret.push_back((n%2)+'0');
    n /= 2;
  }
  reverse((ret).begin(), (ret).end());
  return ret;
}

bool solve(){
  int n, m;
  cin >> n >> m;
  cin.ignore();
  vector<vector<int>> clauses;
  for(int i = 0; i < m; i++) {
    string s;
    getline(cin, s);
    vector<int> local(21,0);
    vector<string> bits = split(s);
    bool yes = false;
    for(auto i : bits){
      int value = 1;
      if(i[0] == '~'){
        value = -1;
        i.erase(0,1);
      }
      i.erase(0,1);
      int index = stoi(i)-1;
      if(local[index] * value == -1){
        yes = true;
      }
      local[index] = value;
    }
    if(!yes) {
      clauses.push_back(local);
    }
  }

  bool works = false;
  for(int i = 0; i < 1<<n; i++){
    bool good_global = true;
    for(auto j : clauses){
      bool good_local = false;
      for(int k = 0; k < n; k++) {
        if((i&(1<<k)) >= 1 && j[k] == 1){
          good_local = true;
        }
        if((i&(1<<k)) == 0 && j[k] == -1){
          good_local = true;
        }
      }
      if(!good_local){
        good_global = false;
        break;
      }
    }
    if(good_global){
      works = true;
      break;
    }
  }

  return works;
}

int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  //Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);

  int cases;
  cin >> cases;
  while(cases--) {
    if(solve()) {
      cout << "satisfiable" << endl;
    }else{
      cout << "unsatisfiable" << endl;
    }
  }
  return 0;
}