/*
Problem: Suffix sorting - https://open.kattis.com/problems/suffixsorting
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.

This code is used to solve the suffix sorting problem using a suffix array. The problem is to sort 
all possible suffixes of a string in lexicographical order. 

The time complexity of the program is O(n log(n)) where n is the amount of characters in the input.

The input can be multiple test cases and each test case is row dependent, the first row in each test
case is a string s. The second row is multiple integers separated by a space, the first integer is the
amount of queries q there is and the next q integers are the indices of the non-sorted suffixes that 
we want to find. The input ends when there is no more test cases. 

The output for each test case is one row per test case that has q integers which are the indices of the
sorted suffixes. An example of input and output is shown below.


Input:
popup
5 0 1 2 3 4
Popup
5 0 1 2 3 4
Suffixes are jolly fun, eh old chap?
7 35 3 18 33 26 6 2

Output:
1 4 0 2 3
0 1 4 2 3
17 18 19 20 21 22 23

*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// The function sort_algo takes in a string s which it performs the
// suffix sorting algorithm on and it returns a vector<int> which is
// the sorted suffix array of the string s.
// The time complexity of the function is O(n log(n)) where n is the
// amount of characters in the string s.
vector<int> sort_algo(string const& s){
  int len = s.size();
  const int char_amount = 256;
  int cnt_size = max(char_amount, len);

  vector<int> permut(len);
  vector<int> equv_class(len); 
  vector<int> cnt(cnt_size, 0);

  // Count the amount of each character in the string
  for(int i = 0; i < len; i++){
    cnt[s[i]]++;    
  }

  // Count the amount of characters smaller than i
  for(int i = 1; i < char_amount; i++){
    cnt[i] += cnt[i-1]; 
  }

  // Permutate the string
  for(int i = 0; i < len; i++){
    permut[--cnt[s[i]]] = i; 
  }

  equv_class[permut[0]] = 0;
  int classes = 1;


  for(int i = 1; i < len; i++){
    // If the character is different from the previous one, increase
    // the amount of classes
    if(s[permut[i]] != s[permut[i-1]]){ 
      classes++;
    }
    // Assign the class to the character
    equv_class[permut[i]] = classes - 1; 
  }

  vector<int> new_permut(len);
  vector<int> new_equv_class(len);
  
  for(int i = 0; (1 << i) < len; ++i){

    // Shift the permutation
    for(int j = 0; j < len; j++){
      new_permut[j] = permut[j] - (1 << i); 

      // If the shift is negative, add the length of the string
      if(new_permut[j] < 0){
        new_permut[j] += len;   
      }
    }

    // Reset the counter
    fill(cnt.begin(), cnt.begin() + classes, 0); 
    
    // Count the amount of each class
    for(int j = 0; j < len; j++){
      cnt[equv_class[new_permut[j]]]++; 
    }

    // Count the amount of classes smaller than j
    for(int j = 1; j < classes; j++){
      cnt[j] += cnt[j-1]; 
    }

    // Permutate the string
    for(int j = len-1; j >= 0; j--){
      permut[--cnt[equv_class[new_permut[j]]]] = new_permut[j]; 
    }

    new_equv_class[permut[0]] = 0; 
    classes = 1;

    for(int j = 1; j < len; j++){
      pair<int, int> current = {equv_class[permut[j]], 
                                equv_class[(permut[j] + 
                                (1 << i)) % len]}; 
      pair<int, int> previous = {equv_class[permut[j-1]], 
                                  equv_class[(permut[j-1] + 
                                  (1 << i)) % len]}; 

      // If the class is different from the previous one, increase
      // the amount of classes
      if(current != previous){  
        ++classes;
      }

      // Assign the class to the character
      new_equv_class[permut[j]] = classes - 1; 
    }
    equv_class.swap(new_equv_class); 
  }
  return permut;
};

// The constructor will construct the suffix array for the input 
// string s and return the suffix array as a vector<int>.
// The time complexity of the constructor is O(n*log(n)). Because
// of the sorting algorithm used.
vector<int> constructor(string s){
  s += char(0);
  vector<int> permut = sort_algo(s);
  permut.erase(permut.begin());
  return permut;
};



int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  // Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);

  string s;
  while(true){
    getline(cin, s);
    if(s.size() == 0){
      break;
    }
    vector<int> suffixes = constructor(s);  // O(n log(n))
    int n, query;
    cin >> n;
    for(int i = 0; i < n; i++){
      cin >> query;
      cout << suffixes[query] << " ";       // O(1)
    }
    cin.ignore();
    cout << "\n";
  }
}