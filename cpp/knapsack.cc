/*
Knapsack: https://open.kattis.com/problems/knapsack
Emil Säll
The code is written in C++ and is using the Google C++ style guide.

This code is used to solve the knapsack problem. The problem is to find the maximal value from items, 
which have a value and a weight to them, that can be put in a knapsack with a given weight capacity C.
The input is a knapsack capacity and a set of items which each have a value and a weight. The output 
is two rows where the first row is the maximum number of items that can be put in the knapsack given 
the capacity and the second row is the indexes of the items that are put in the knapsack.

The time capacity for the program is O(n * C) where n is the number of items and C is the capacity of
the knapsack.

The input is row dependent, the first row are two integers separated by a space, the first integer C 
is the capacity of the knapsack and the second integer n is the number of items. The next n rows are 
two integers separated by a space which are the value and weight of the items. The program can take 
multiple testcases as input, as long as they follow eachother directly. An example of input and 
output is shown below.

Input:
5 3
1 5
10 5
100 5
6 4
5 4
4 3
3 2
2 1

Output:
1
2
3
1 2 3

*/
#include <iostream>
#include <vector>

using namespace std;

// Defines a struct for representing an item.
struct Item{
  int value;
  int weight;
  int index;
};

//The input is a capacity and a vector of items. The items are of the struct
//Items, it has a value, a weight and an index.

//The output is a vector of the items that are used to fill the knapsack.

//The function solves the classic knapsack problem. It creates a table of
//zeros with the dimension (nr of items + 1 x capacity + 1) and then iterates
//through the items and the possible weights. If the weight of the item is
//less than or equal to the current weight that is checked, the maximum of
//either {the previous items entry for the same weight} or {the value of this
//item + the value of the previous item for the weight (this.weight - 
//previous.weight)} is put in the table. If the weight of the item is greater
//than the current weight that is checked, the value of the previous item for
//the same weight is put in the table.
//The function then iterates through the table and finds the items that are 
//used to fill the knapsack.

//The time complexity is O(n * C) where n is the number of items and C is the
//capacity of the knapsack. The iteration through the items takes O(n) and the
//iteration in that loop through the possible weights takes O(C). Therefore the
//time complexity is O(n * C).
vector<Item> solve(int C, vector<Item> items){
  vector<vector<int>> table(items.size() + 1, vector<int>(C + 1, 0)); // (4x7) table of zeros
  for(int i = 0; i < items.size(); i++){        //loop over the items (3) ~ O(n * C)
    for(int j = 1; j <= C; j++){             //loop over the possible capacities assuming all are lower than the total capacity (7)
      if(items[i].weight <= j){
        table[i+1][j] = max(table[i][j], items[i].value + table[i][j - items[i].weight]);
      }else{
        table[i+1][j] = table[i][j];
      }
    }
  }
  vector<Item> used_items;
  int i = items.size();
  int w = C;
  while(i > 0 && w > 0){
    if(table[i][w] != table[i - 1][w]){
      used_items.push_back(items[i - 1]);
      w -= items[i - 1].weight;
    }
    i--;
  }
  return used_items;
}

int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  // Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);
    
  int C, n;

  while(cin >> C >> n){
    vector<Item> items(n);
    for(int i = 0; i < n; i++){
      cin >> items[i].value >> items[i].weight;
      items[i].index = i; 
    }

    vector<Item> used_items = solve(C, items);
    cout << used_items.size() << "\n";
    for(int i = 0; i < used_items.size(); i++){
      cout << used_items[i].index << " ";
    }
    cout << "\n";
  }
  return 0;
}