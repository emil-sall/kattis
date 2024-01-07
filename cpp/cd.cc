/*
Problem: CD - https://open.kattis.com/problems/cd
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

void cd(const string& row){
  // Read the first line of the file to get N and M ~ O(1)
  istringstream iss(row);
  string m, n;
  iss >> n >> m;
  unsigned N = stoi(n);
  unsigned M = stoi(m);

  // Create a vector of zeros to fill Jacks numbers ~ O(1)
  unordered_map<unsigned, unsigned> dict;

  // Read and fill the vector with Jacks cd-numbers ~ O(N)
  for(unsigned cd = 0; cd < N; cd++){
    string line;
    getline(cin, line);
    unsigned catalog_nr = stoi(line);
    dict[catalog_nr] = catalog_nr;
  }

  // Read and compare Jills cds to Jacks ~ O(M)
  unsigned copies = 0;
  for(unsigned cd = 0; cd < M; cd++){
    string line;
    getline(cin, line);
    unsigned catalog_nr = stoi(line);
    if(dict.find(catalog_nr) != dict.end()){
      copies = copies + 1;
    }        
  }
  cout << copies << "\n";
  cout << flush;
}

int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  // Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);    

  while(true){
    string row;
    getline(cin, row);
    if(row == "0 0"){
      break;
    }
    cd(row);
  }
  return 0;
}

