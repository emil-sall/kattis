/*
Problem: Logo - https://open.kattis.com/problems/logo
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.
*/
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

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
    void move_fd(int dist, int direction);
    void move_bk(int dist, int direction);
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
  return sqrt((p.x - this->x) * (p.x - this->x) + (p.y - this->y) * (p.y - this->y));
};

void Coordinate::move_fd(int dist, int direction){
  this->x += dist * cos(direction * M_PI / 180);
  this->y += dist * sin(direction * M_PI / 180);
};

void Coordinate::move_bk(int dist, int direction){
  this->x -= dist * cos(direction * M_PI / 180);
  this->y -= dist * sin(direction * M_PI / 180);
};

int end_dist(vector<string> cmds, vector<int> dgs){
  /*
  cmds:
        fd: go forward this length
        lt: turn left these degrees
        bk: go backward this length
        rt: turn right these degrees
  */ 
  Coordinate start_point{0, 0}, end_point{0, 0};
  int direction{0};
  for(int i = 0; i < dgs.size(); i++){
    if(cmds[i] == "fd"){
      end_point.move_fd(dgs[i], direction);
    } else if(cmds[i] == "bk"){
      end_point.move_bk(dgs[i], direction);
    } else if(cmds[i] == "lt"){
      direction += dgs[i];
    } else{
      direction -= dgs[i];
    }
  }
  return round(start_point.distance(end_point));
}

int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  //Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);

  int nr_testcases, nr_cmds, dg;
  cin >> nr_testcases;
  string cmd;
  while(nr_testcases--){
    cin >> nr_cmds;
    vector<string> cmds;
    vector<int> dgs;
    while(nr_cmds--){
      cin >> cmd >> dg;
      cmds.push_back(cmd);
      dgs.push_back(dg);
    }
    int x = 0;
    cout << end_dist(cmds, dgs) << "\n";

  }
  return 0;
}