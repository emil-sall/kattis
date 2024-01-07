/*
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.
*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

// A class for 2-dimensional points which can also be interpreted as 
// mathematical vectors. 

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
  return atan2((p.y - this->y), (p.x - this->x));
};

double Coordinate::distance(Coordinate p){
  return sqrt((p.x - this->x) * (p.x - this->x) + (p.y - this->y) *
              (p.y - this->y));
};