/*
Problem: Hiding Places - https://open.kattis.com/problems/hidingplaces
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct position{
  int x;
  int y;
};

struct output{
  int nr_jumps;
  vector<string> coordinates;
};

void fill_board(vector<position> next_points, 
                vector<vector<int>>& chess_board, 
                int& filled_squares, int& jump_nr){

  if(filled_squares == 64){
    return;
  }
  vector<position> new_next_points;
  vector<position> moves = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, 
                            {1, -2}, {1, 2}, {2, -1}, {2, 1}};
  for(int i = 0; i < next_points.size(); i++){
    for(int j = 0; j < moves.size(); j++){
      if(next_points[i].x + moves[j].x >= 0 && 
         next_points[i].x + moves[j].x < 8 && 
         next_points[i].y + moves[j].y >= 0 && 
         next_points[i].y + moves[j].y < 8){
        
        if(chess_board[next_points[i].x + moves[j].x]
                       [next_points[i].y + moves[j].y] == 0){

          chess_board[next_points[i].x + moves[j].x]
                      [next_points[i].y + moves[j].y] = jump_nr;

          filled_squares++;
          new_next_points.push_back({next_points[i].x + moves[j].x, 
                                     next_points[i].y + moves[j].y});
        }
      }
    }
  }
  jump_nr += 1;
  fill_board(new_next_points, chess_board, filled_squares, jump_nr);
}

string coordinates(int j, int k){
  string coordinate;
  switch(j){
    case 0:
      coordinate += 'a';
      break;
    case 1:
      coordinate += 'b';
      break;
    case 2:
      coordinate += 'c';
      break;
    case 3:
      coordinate += 'd';
      break;
    case 4:
      coordinate += 'e';
      break;
    case 5:
      coordinate += 'f';
      break;
    case 6:
      coordinate += 'g';
      break;
    case 7:
      coordinate += 'h';
      break;
  }
  coordinate += to_string(k + 1);
  return coordinate;
}

vector<output> solve(int n, vector<string> starting_positions){
  vector<position> positions(n, {0, 0});
  vector<output> hidden_places(n);
  for(int i = 0; i < n; i++){
    switch(starting_positions[i][0]){
      case 'a':
        positions[i].x = 0;
        break;
      case 'b':
        positions[i].x = 1;
        break;
      case 'c':
        positions[i].x = 2;
        break;
      case 'd':
        positions[i].x = 3;
        break;
      case 'e':
        positions[i].x = 4;
        break;
      case 'f':
        positions[i].x = 5;
        break;
      case 'g':
        positions[i].x = 6;
        break;
      case 'h':
        positions[i].x = 7;
        break;
    }
    switch(starting_positions[i][1]){
      case '1':
        positions[i].y = 0;
        break;
      case '2':
        positions[i].y = 1;
        break;
      case '3':
        positions[i].y = 2;
        break;
      case '4':
        positions[i].y = 3;
        break;
      case '5':
        positions[i].y = 4;
        break;
      case '6':
        positions[i].y = 5;
        break;
      case '7':
        positions[i].y = 6;
        break;
      case '8':
        positions[i].y = 7;
        break;
    }
  }

  for(int i = 0; i < n; i++){
    vector<vector<int>> chess_board(8, vector<int>(8, 0));
    chess_board[positions[i].x][positions[i].y] = 1;
    int filled_squares = 1;
    vector<position> next_points;
    next_points.push_back(positions[i]);
    int jump_nr = 2;
    fill_board(next_points, chess_board, filled_squares, jump_nr);
    hidden_places[i].nr_jumps = jump_nr-2;
    for(int k = 7; k > -1; k--){
      for(int j = 0; j < 8; j++){
        if(chess_board[j][k] == jump_nr-1){
          hidden_places[i].coordinates.push_back(coordinates(j, k));
        }
      }
    }
  }
  return hidden_places;
}

int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  // Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);

  int nr_cases;
  cin >> nr_cases;

  vector<string> starting_positions(nr_cases, "");
  for(int i = 0; i < nr_cases; i++){
    cin >> starting_positions[i];
  }

  vector<output> hidden_places = solve(nr_cases, starting_positions);
  for(int i = 0; i < nr_cases; i++){
    cout << hidden_places[i].nr_jumps << " ";
    for(int j = 0; j < hidden_places[i].coordinates.size(); j++){
      cout << hidden_places[i].coordinates[j] << " ";
    }
    cout << "\n";
  }
  return 0;
}