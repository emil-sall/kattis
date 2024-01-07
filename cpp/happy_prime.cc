/*
Problem: Happy Happy Prime Prime - https://open.kattis.com/problems/happyprime
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.
*/
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

bool is_happy_prime(long long int n){
  if(n == 1){
    return true;
  }
  if(n == 2){
    return false;
  }

  //SUCH A BAD SOLUTION BUT IT WORKS
  if(log2(n) == (int)log2(n) && n != 32){   
    return false;
  }

  long long int sum = 0;
  while(n > 0){
    long long int digit = n % 10;
    sum += digit * digit;
    n /= 10;
  }
  return is_happy_prime(sum);
}

bool is_prime(int n){
  if(n == 1){
    return false;
  }
  if(n == 2){
    return true;
  }
  if(n % 2 == 0){
    return false;
  }
  for(int i = 3; i * i <= n; i += 2){
    if(n % i == 0){
      return false;
    }
  }
  return true;
}



int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  // Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);

  int cases;
  cin >> cases;
  while(cases--){
    int K; 
    long long int m;
    cin >> K >> m;
    bool happy_prime = false; 
    if(is_prime(m)){
      happy_prime = is_happy_prime(m);
    }
    if(happy_prime){
      cout << K << " " << m << " YES\n";
    } else{
      cout << K << " " << m << " NO\n";
    }
  }

  return 0;

}