/*
Problem: Longest common prefix (Dvaput) - https://liu.kattis.com/courses/AAPS/AAPS23/assignments/umtcb6/problems/dvaput
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.

This code is used to solve the longest common prefix problem using an suffix array. The problem is getting a 
string and to find the longest common prefix of the string and its suffixes.

The time complexity of the program is O(n log(n)) where n is the length of the string. This is because the
suffix array is built in O(n log(n)) and the lcp array is built in O(n).

The input is only one case and starts with an integer L which is the length of the string. The second row is
the string s.

The output is the maximum length of the longest common prefix. An example of input and output is shown below.


Input:
18
trutrutiktiktappop

Output:
4
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

// The function build_suffix_array takes in a string str and builds
// the suffix array of the string str and returns it as a vector<int>
// The time complexity of the function is O(n log(n)) where n is the
// amount of characters in the string str.
vector<int> build_suffix_array(string str){
  str += char(0);
  vector<int> permut = sort_algo(str);
  permut.erase(permut.begin());
  return permut;
}

// The function build_lcp_array takes in a string str and a 
// vector<int> permut which is the suffix array of the string str.
// The function builds the longest common prefix array of the string
// str and returns it as a vector<int>.
// The time complexity of the function is O(n) where n is the amount
// of characters in the string str. This is beacuse the function
// iterates through the string str once.
vector<int> build_lcp_array(string str, vector<int> permut){
  vector<int> suffix_pos_vect(str.size(), 0);
  for(int i = 0; i < str.size(); i++){
    suffix_pos_vect[permut[i]] = i;
  }

  int k = 0;
  vector<int> lcp_vect(str.size() - 1, 0);

  for(int i = 0; i < str.size(); i++){
    // If the suffix is the last one, skip it
    if(suffix_pos_vect[i] == str.size() - 1){
      k = 0;
      continue;
    }

    // j is the position of the next suffix
    int j = permut[suffix_pos_vect[i] + 1];

    // Increase k until the characters are different, i.e. find the 
    // longest common prefix
    while(i + k < str.size() && j + k < str.size() &&
          str[i + k] == str[j + k]){
      k++;
    }

    // Assign the value of k to the lcp array and decrease k 
    lcp_vect[suffix_pos_vect[i]] = k;
    if(k > 0){
      k--;
    }
  }
  return lcp_vect;
}

int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  // Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);

  string L, s;
  cin >> L >> s;
  vector<int> permutation = build_suffix_array(s);
  vector<int> lcp_array = build_lcp_array(s, permutation);

  cout << *max_element(lcp_array.begin(), lcp_array.end());

  return 0;
}