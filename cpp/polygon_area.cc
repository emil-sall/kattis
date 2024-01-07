/*
Problem: Polygon Area - https://open.kattis.com/problems/polygonarea
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.

This code is used to compute the area of a simple polygon in which 
its vertices are given.

The time complexity of the program is O(n) where n is the number of 
vertices in the input. All the operators for the Class Coordinate has
constant time complexity. The function polygon_area has the time 
complexity O(n) since it loops through all the given vertices. 

The input could be up to 25 test cases. Every case starts with an 
integer n on the first row.Then follow n vertices of a simple polygon
on each line on the form x y. The points are given in either 
clockwise or counterclockwise order. The input is terminated but a 
row with a single 0.

The output for every polygon (test case) is on the form D A on one 
row. Where D is either CW for clockwise or CCW for counterclockwise 
and A is the area of the polygon given with exactly one digit after 
the decimal point. Below follow examples of input and corresponding 
output.

Input:
3
0 0
10 0
0 10
5
41 -6
-24 -74
-51 -6
73 17
-30 -34
0

Output:	
CCW 50.0
CW 3817.5
*/


#include "point.h"
#include <iomanip>

// The input is a vector of coordinates forming a polygon and the 
// output is the area of that polygon 
double polygon_area(vector<Coordinate> coordinates){
  double area = 0;
  int j = coordinates.size() - 1;
  for (int i = 0; i < coordinates.size(); i++){
    area += (coordinates[j].x + coordinates[i].x) *
              (coordinates[j].y - coordinates[i].y);
    j = i;  
  }
  return round(area*10)/20.0;
};


int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  //Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);
  
  int n;
  while(cin >> n){
    if(n == 0){
      break;
    }
    int x, y;
    vector<Coordinate> corner_coordinates; 
    while(n--){
      cin >> x >> y;
      corner_coordinates.push_back(Coordinate(x, y));
    }
    double area = polygon_area(corner_coordinates);
    string d = "CW";
    if(area < 0){
      d = "CCW";
    }
    cout << fixed << setprecision(1) << d << " " << abs(area) << "\n";
  }
  
  return 0;
}