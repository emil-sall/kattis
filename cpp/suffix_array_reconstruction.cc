/*
Problem: Suffix Array Re-construction - https://open.kattis.com/problems/suffixarrayreconstruction
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Suffix{
  string suffix;
  int concat_order;
};

string reconstruct(vector<Suffix> suffixes, int length_of_output){
  string output(length_of_output, '#');
  int pivot = 0;
  int nr_of_suffixes = suffixes.size();
  for(Suffix suffix : suffixes){

    if(suffix.suffix.size() > length_of_output){
      int star_index = suffix.suffix.find('*');
      suffix.suffix.replace(star_index, 1, "");
      return suffix.suffix;
    }

    int letter = suffix.suffix.size();
    bool star_found = false;
    string current_suffix = output.substr(suffix.concat_order - 1, output.size() - (suffix.concat_order - 1));
    //loop from the back of the suffix
    while(letter--){
      if(star_found){
        if(current_suffix[pivot - letter] != suffix.suffix[pivot - letter] && current_suffix[pivot - letter] != '#'){
          return "This aint working my dude";
        } else{
          current_suffix[pivot - letter] = suffix.suffix[pivot - letter];
        }
        continue;
      }
      else{
        if(suffix.suffix[letter] == '*'){     // If a star is found start to loop from the front
          output.replace(letter + output.size() - current_suffix.size() + 1, current_suffix.size() - letter, current_suffix.substr(letter + 1, current_suffix.size() - letter));
          star_found = true;
          pivot = letter - 1;   
          continue;
        } else if(current_suffix[letter + current_suffix.size() - suffix.suffix.size()] != suffix.suffix[letter] && (current_suffix[letter + current_suffix.size() - suffix.suffix.size()] != '#')){
          return "This aint working my dude";
        } else{
          current_suffix[letter + current_suffix.size() - suffix.suffix.size()] = suffix.suffix[letter];
        }
      }
    }
    if(star_found){
      output.replace(suffix.concat_order - 1, pivot + 1, current_suffix.substr(0, pivot+1));
    } else{
      output.replace(suffix.concat_order - 1, current_suffix.size(), current_suffix);
    }
  }
  return output;
}

int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  // Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);

  int t;     // number of test cases
  cin >> t;
  while(t--){
    int length_of_output, nr_of_suffixes;
    cin >> length_of_output >> nr_of_suffixes;
    int pos;
    Suffix suffix;
    vector<Suffix> suffixes;
    while(nr_of_suffixes--){
      cin >> suffix.concat_order >> suffix.suffix;
      suffixes.push_back(suffix);
    }
    string output = reconstruct(suffixes, length_of_output);
    if(output == "This aint working my dude" || output.find("#") != string::npos){
      cout << "IMPOSSIBLE" << "\n";
    } else{
      cout << output << "\n";
    }
  }
  return 0;
}