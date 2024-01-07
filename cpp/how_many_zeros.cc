/*
Problem: How many 0's? - https://open.kattis.com/problems/howmanyzeros
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.
*/
#include <iostream>
#include <cmath>

using namespace std;

long long int nr_zeros(long long int x){
  long long int count = x;
  long long int nr_zeros{0}, length{0}, local_nr{0}, local_zeros{0};
  while(count){
    count /= 10;
    length += 1;
  }

  // loop over all digits, left to right.
  for (long long int i = length-1; i >= 0; --i){ 
    long long int digit = (long long int)(x / pow(10,i)) % 10;

    // main formula. the count of each digit is periodic
    nr_zeros = 10*nr_zeros + local_nr - local_zeros*(9-digit); 
    if (digit == 0){
      local_zeros += 1;
    }
    local_nr = (10*local_nr + digit);
  }
  return nr_zeros + 1;
}

int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  //Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);

  long long int n, m;
  while(cin >> m >> n){
    if(m == -1 && n == -1){
      break;
    }
    long long int m_zeros = 0;
    if(m != 0){
      m_zeros = nr_zeros(m-1);
    }
    long long int n_zeros = nr_zeros(n);
    long long int zeros = n_zeros - m_zeros;
    cout << zeros << "\n";
  }

  return 0;
}