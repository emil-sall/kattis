/*
Problem: Babelfish - https://open.kattis.com/problems/babelfish
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  // Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);

  unordered_map<string, string> dict;
  while(true){
    string line, a, b;
    getline(cin, line);

    //If the empty line is reached, the whole dictionary is read
    if(line.size() == 0){
        break;
    }

    istringstream iss(line);
    iss >> a >> b;

    //Set the value in map as a (english) and b as key (unknown language)
    dict[b] = a;
  }

  //Define the word in the message
  string c;
  while(cin >> c){
    //If the current word does not exist in the dictionary, send "eh" instead
    if(dict.find(c) == dict.end()){
      cout << "eh" << "\n";
    } else{
      cout << dict[c] << "\n";
    }
  }
  // Flush the buffer ~ make the stream clean
  cout << flush;

  return 0;
}
