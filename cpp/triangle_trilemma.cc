/*
Problem: Triangle Trilemma - https://open.kattis.com/problems/trilemma
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.
*/
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <cmath>

using namespace std;

class Coordinate{
  public:
    double x, y, ang, dist;
    Coordinate(int x, int y);
    Coordinate operator+(Coordinate p);
    Coordinate operator-(Coordinate p);
    double scalar_product(Coordinate p);
    double cross_product(Coordinate p);
    double distance(Coordinate p);
    double angle(Coordinate p);
};

Coordinate::Coordinate(int x, int y){
  this->x = x;
  this->y = y;
  this->ang = atan2(y, x);
  dist = sqrt(x*x + y*y);
};

Coordinate Coordinate::operator+(Coordinate p){
  return Coordinate(this->x + p.x, this->y + p.y);
};

Coordinate Coordinate::operator-(Coordinate p){
  return Coordinate(this->x - p.x, this->y - p.y);
};

double Coordinate::scalar_product(Coordinate p){
  return (this->x * p.x) + (this->y * p.y);
};

double Coordinate::cross_product(Coordinate p){
  return (this->x*p.y) - (this->y*p.x);
};

double Coordinate::angle(Coordinate p){
  double a = atan2((p.y - this->y), (p.x - this->x));
  if(a < 0){
    return a + 2 * M_PI;
  } else{
    return a;
  }
};

double Coordinate::distance(Coordinate p){
  return sqrt((p.x - this->x) * (p.x - this->x) + 
              (p.y - this->y) * (p.y - this->y));
};

string triangle_sides(Coordinate p1, Coordinate p2, Coordinate p3){
  double d_12 = floor(p1.distance(p2) * 100000);
  double d_13 = floor(p1.distance(p3) * 100000);
  double d_23 = floor(p2.distance(p3) * 100000);
  if(d_12 != d_13 && d_12 != d_23 && d_13 != d_23){
    return "scalene";
  } else{
    return "isosceles";
  }
}

string triangle_angles(Coordinate p1, Coordinate p2, Coordinate p3){
  double d_12 = p1.distance(p2);
  double d_13 = p1.distance(p3);
  double d_23 = p2.distance(p3);

  double a1 = floor(acos((d_13*d_13 + d_23*d_23 - d_12*d_12) / 
                          (2*d_13*d_23)) * 1000);

  double a2 = floor(acos((d_12*d_12 + d_23*d_23 - d_13*d_13) / 
                          (2*d_12*d_23)) * 1000);

  double a3 = floor(acos((d_12*d_12 + d_13*d_13 - d_23*d_23) / 
                          (2*d_12*d_13)) * 1000);
  
  if(a1 == 1570 || a2 == 1570 || a3 == 1570){
    return "right";
  } else if(a1 > 1570 || a2 > 1570 || a3 > 1570){
    return "obtuse";
  } else{
    return "acute";
  }
}

bool is_triangle(Coordinate p1, Coordinate p2, Coordinate p3){
  double d_12 = floor(p1.distance(p2) * 1000);
  double d_13 = floor(p1.distance(p3) * 1000);
  double d_23 = floor(p2.distance(p3) * 1000);
  if(d_12 + d_13 <= d_23 || d_12 + d_23 <= d_13 || 
                            d_13 + d_23 <= d_12){
    return false;
  } else{
    return true;
  }
}

int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  //Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);

  int nr_cases; 
  cin >> nr_cases;                      // <= 100
  for(int i = 1; i <= nr_cases; i++){
    double x1, y1, x2, y2, x3, y3;    // -1000 <= x1, y1, x2, y2, x3, y3 <= 1000,    -90 < v <= 90
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    Coordinate p1 = Coordinate(x1, y1);
    Coordinate p2 = Coordinate(x2, y2);
    Coordinate p3 = Coordinate(x3, y3);
    
    string type1 = triangle_sides(p1, p2, p3);

    string type2 = triangle_angles(p1, p2, p3);


    if(is_triangle(p1, p2, p3)){
      cout << "Case #" << i << ": " << type1 << " " << type2 << " triangle\n";
    } else{
      cout << "Case #" << i << ": not a triangle\n";
    }
    
  }
  return 0;
}