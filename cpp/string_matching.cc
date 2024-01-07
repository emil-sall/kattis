/*
Problem: String matching - https://open.kattis.com/problems/stringmatching
Author: Emil Säll
emisa182
The code is written in C++ and is using the Google C++ style guide.

This code is used to solve a string matching problem using the prefix function. The problem is to get a
string and a pattern and to find all the indices of the string where the pattern starts.

The time complexity of the program is O(n + m) where n is the length of the string and m is the length
of the pattern.

The input can be multiple test cases and each test case is row dependent, the first row in each test
case is a pattern (string) p. The second row is a string s. The input ends when there is no more test
cases.

The output for each test case is one row per test case that is a list of integers which are the indices
where the pattern starts in the string. An example of input and output is shown below.


Input:
a
aaaaa
p
Popup
helo
Hello there!
peek a boo
you speek a bootiful language
anas
bananananaspaj

Output:
0 1 2 3 4 
2 4 
 
5 
7 

*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;


// The prefix function takes a string as input and returns a vector
// of integers where the i'th element is the length of the longest
// prefix of the string that is also a suffix of the string up to
// the i'th character.
// The time complexity of the function is O(n) where n is the length
// of the string. This is because the function iterates over the string
// once and each iteration is O(1).
vector<int> prefix_func(string str){
  vector<int> prefix_func_result(str.size());
  for(int i = 1; i < str.size(); i++){
    int j = prefix_func_result[i-1];
    while(j > 0 && str[i] != str[j]){
      j = prefix_func_result[j-1];
    }
    if(str[i] == str[j]){
      j++;
    }
    prefix_func_result[i] = j;
  }
  return prefix_func_result;
}

// The function find takes two strings as input, the first one is a 
// pattern and the second one is a string which we want to find the
// pattern in. The function returns a vector of integers where each
// integer is the index of a match of the start of the pattern in 
// the string.
// The Time complexity of the function is O(n + m) where n is the 
// length of the string and m is the length of the pattern. This is
// because the function calls the prefix function which has a time
// complexity of O(n + m) and then iterates over the result of the
// prefix function which is O(n + m).
vector<int> find(string pattern, string str){
  string text = pattern + char(0) + str;
  vector<int> prefix_func_result = prefix_func(text);

  prefix_func_result.erase(prefix_func_result.begin(), prefix_func_result.begin() + pattern.size() + 1);

  vector<int> indices;
  for(int i = 0; i < prefix_func_result.size(); i++){
    if(prefix_func_result[i] == pattern.size()){
      indices.push_back(i - pattern.size() + 1);
    }   
  }
  return indices;
}


int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  // Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);


  string s, p;
  while(!cin.eof()){
    getline(cin, p);
    if(p.size() == 0){
      break;
    }
    getline(cin, s);
      
    vector<int> indices = find(p, s);

    if(indices.size() == 0){
      cout << " ";
    } else{
      for(int i = 0; i < indices.size(); i++){
        cout << indices[i] << " ";
      }
    }
    cout << "\n";
  }

  return 0;
}