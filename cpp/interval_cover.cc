/*
Interval cover: https://open.kattis.com/problems/intervalcover
Emil Säll
The code is written in C++ and is using the Google C++ style guide.

This code is used to solve the interval cover problem. The problem is to find the minimal number of 
intervals that covers a target interval. The input is a set of intervals and a target interval. The 
output is the minimal number of intervals that covers the target interval and which intervals that are
used. 

The time complexity of the program is O(n log n) where n is the number of intervals.

The input is row dependent, the first row are two floats separated by a space, the first float is
the lower bound of the interval and the second float is the upper bound of the interval. The second 
row is an integer n, which are the number of intervals in the set of intervals that are checked to 
cover the target interval. The next n rows are two floats separated by a space which similarily as 
the target interval are the lower and upper bound of the intervals. The output is the minimal number
of intervals that covers the target interval and which intervals that are used indexed as they were
input in the program. If the target interval cannot be covered the output is "impossible". The 
program can take multiple testcases as input. as long as they follow eachother directly. A example of
input and output is shown below.

Input:
-0.5 1
3
-0.9 -0.1
-0.2 2
-0.7 1
0 1
3
0 0.25
0.25 0.75
0.75 0.999

Output:
1
2
impossible

*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>

using namespace std;

// Defines a struct for representing an interval.
struct bounds{
  double lower_bound;
  double upper_bound;
  short int index;
};

//The input is a vector of the intervals that are used and a new interval
//with startingpoint to the right of the currently used intervals 
//startingpoints and endingpoint to the right of the used intervals 
//endingpoints.

//The output is an updated vector of used intervals.

//The function takes the new interval and adds it to the vector of used
//intervals and the unneccesary intervals, that is not needed to cover the 
//whole interval anymore, are removed from the vector.

//The time complexity is O(n) where n is the number of used intervals.
vector<bounds> MinimalCover(bounds& interval, 
                            vector<bounds>& used_intervals){
  vector<bounds> new_used_intervals;
  for(int j = 0; j < used_intervals.size(); j++){
    new_used_intervals.push_back(used_intervals[j]);
    if (interval.lower_bound <= used_intervals[j].upper_bound){
      break;
    }
  }
    new_used_intervals.push_back(interval);
    return new_used_intervals;
};

//The input is two intervals. 

//The output is a boolean returning true if the first interval has a lower 
//lower bound than the second interval and false otherwise. If the first 
//interval has the same lower bound as the second interval the function
//returns true if the first interval has a higher upper bound than the
//second interval and false otherwise.

//The function is used in sorting a vector of intervals. 

//The time complexity is O(1).
bool IntervalSort(bounds& interval1, bounds& interval2){
  if(interval1.lower_bound == interval2.lower_bound)
  {
    return interval1.upper_bound > interval2.upper_bound;
  }
  return interval1.lower_bound < interval2.lower_bound; 
};


//The input is a vector of a set of intervals, a target interval and the number
//of intervals of the vector. The intevals are of the struct bounds, it has a 
//lower bound, an upper bound and an index. 

//The output is a vector of the intervals that are used to cover the target, if
//the target can not be covered the vector is empty.

//The function solves the problem of finding the minimal number of intervals
//that covers the target interval and finds which intervals that are used.
//It sorts the vector increasingly based on the lower bound of the intervals
//and if it is a tie it sorts decreasingly based on the upper bound of the 
//intervals. It then iterates through the vector and finds the minimal number
//of intervals that covers the target.

//The time complexity is O(n log n) where n is the number of intervals. The 
//sorting takes O(n log n) and the iteration takes O(n). 
vector<bounds> Solve(vector<bounds>& intervals, 
                          bounds& target_bounds, 
                          short int&  nr_of_intervals){
  vector<bounds> used_intervals;
  sort(intervals.begin(), intervals.end(), IntervalSort);
  bounds current_bounds = {intervals[0].lower_bound, 
                           target_bounds.lower_bound};
  for (short int i = 0; i < nr_of_intervals; i++)  
  {
    if (intervals[i].lower_bound <= current_bounds.upper_bound && 
        intervals[i].upper_bound >= current_bounds.upper_bound){
      if (used_intervals.size() == 0){
        used_intervals.push_back(intervals[i]);
        current_bounds.lower_bound = used_intervals[0].lower_bound;
      } else if(intervals[i].lower_bound <= target_bounds.lower_bound){
        used_intervals.clear();
        used_intervals.push_back(intervals[i]);
      } else{
        used_intervals = MinimalCover(intervals[i], used_intervals);
      }
      current_bounds.upper_bound = used_intervals.back().upper_bound;
      if(intervals[i].upper_bound >= target_bounds.upper_bound){
        break;
      }
    }    
  }
  if(current_bounds.upper_bound < target_bounds.upper_bound |
     current_bounds.lower_bound > target_bounds.lower_bound){
    used_intervals.clear();
  }
  return used_intervals;
};



int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  // Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);

  bounds target_bounds;
  short int nr_of_intervals;
  while (cin >> target_bounds.lower_bound >>
         target_bounds.upper_bound >> nr_of_intervals){ 
    vector<bounds> intervals(nr_of_intervals, {0,0});
    for (short int i = 0; i < nr_of_intervals; i++){ 
      cin >> intervals[i].lower_bound >> intervals[i].upper_bound;
      intervals[i].index = i;
    }
    vector<bounds> used_intervals = Solve(intervals, target_bounds, nr_of_intervals);
    if(used_intervals.size() == 0)
    {
      cout << "impossible";
    } else{
      cout << used_intervals.size() << "\n";
      for (short int i = 0; i < used_intervals.size(); i++){
        cout << used_intervals[i].index << " ";
      }
    }
    cout << "\n";
  }
};