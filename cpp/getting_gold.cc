/*
Problem: Getting Gold - https://open.kattis.com/problems/gold
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstdio>
#include <cstdlib>

using namespace std;

struct point{
    short int x;
    short int y;
};

void search(point position, int& gold, 
            const vector<vector<char>>& map, 
            vector<vector<char>>& visited_map){

  point left = {position.x - 1, position.y};
  point right = {position.x + 1, position.y};
  point up = {position.x, position.y - 1};
  point down = {position.x, position.y + 1};

  if(visited_map[position.y][position.x] == 1 ||
     map[position.y][position.x] == '#'){
        return;
  } else if(map[position.y][position.x] == 'G'){
    gold += 1;
  }

  if(map[left.y][left.x] == 'T' || map[right.y][right.x] == 'T' ||
     map[up.y][up.x] == 'T' || map[down.y][down.x] == 'T'){
    visited_map[position.y][position.x] = 1;
    return;
  }
  visited_map[position.y][position.x] = 1;
  search(left, gold, map, visited_map);
  search(right, gold, map, visited_map);
  search(up, gold, map, visited_map);
  search(down, gold, map, visited_map);
}

int solve(vector<vector<char>> map, point start){
  int gold = 0;
  vector<char> visited_map_rows(map[0].size(), 0);
  vector<vector<char>> visited_map(map.size(), visited_map_rows);
  search(start, gold, map, visited_map);

  return gold;
}


int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  // Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);

  int w, h;
  cin >> w >> h;

  vector<char> map_rows(w, 0);
  vector<vector<char>> map(h, map_rows);
  point start;
  for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++){
      cin >> map[i][j];
      if(map[i][j] == 'P'){
        start.x = j;
        start.y = i;
      }
    }
  }

  cout << solve(map, start) << '\n';
  return 0;
}