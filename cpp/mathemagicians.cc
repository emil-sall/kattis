/*
Problem: Mathemagicians - https://open.kattis.com/problems/mathemagicians
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<int> fields(unsigned n){
  char c;
  vector<char> hat_sequence;
  int nr_fields = 1;
  for(unsigned i = 0; i < n; i++){
    cin >> c;
    hat_sequence.push_back(c);
  }

  int checker = 0;
  for(unsigned i = 0; i < n-1; i++){
    if(hat_sequence[i] != hat_sequence[i+1]){
      nr_fields = nr_fields +1;
      checker = checker + 1;
    }
  }

  if((hat_sequence[0] == hat_sequence.back()) && (checker != 0)){
    nr_fields = nr_fields - 1;
  }

  vector<int> return_vect;
  return_vect.push_back(nr_fields);
  char first_letter = hat_sequence[0];
  char blue = 'B';
  if(first_letter == blue){
    return_vect.push_back(0);       // If first letter is "B" (blue), return 0
  } else{
    return_vect.push_back(1);       //else (red) return 1
  }

  return return_vect;
}

int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  //Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);

  while(true){
    string N;
    getline(cin, N);
    if(N.size() == 0){
      break;
    }
    
    unsigned n = stoi(N);
    vector<int> wear_fields = fields(n);
    vector<int> want_fields = fields(n);
    string A;
    getline(cin, A);

    if(((want_fields[0] > wear_fields[0]) || 
        ((wear_fields[1] != want_fields[1]) &&
         (wear_fields[0] == 1) && (want_fields[0] == 1)) ||         // (BBB)    (RRR)
        ((want_fields[0] == n) && (wear_fields[0] == n) &&
         (wear_fields[1] != want_fields[1])))){      // (BRBR)   (RBRB)  
                                      
      cout << "no" << "\n";
    } else{
      cout << "yes" << "\n";
    }
  }
  return 0;
}