/*
Problem: Prime Sieve - https://open.kattis.com/problems/primesieve
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.

This code is used to find all prime numbers up to a given number n. The code uses the sieve of
eratosthenes algorithm to find all prime numbers up to n. 

The time complexity of the program is O(n log( log(n) )) where n is the number it checks prime numbers to.

The input starts with 2 integers seperated by a space. The first integer is n which is the number that the
program checks prime numbers to. The second integer is q which is the number of queries that the program
will answer. The next q lines contains a query of an integer that is to be checked if it is a prime or not.

The output starts with the number of prime numbers up to n. The next q lines contains the answer to the
queries. If the number is a prime the output is 1, otherwise the output is 0.
An example of the input and output is shown below.


Input:
9973 6
1
2
3
4
9972
9973

Output:
1229
0
1
1
0
0
1

*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// The function sieve_of_eratosthenes uses the sieve of Eratosthenes
// algorithm to find a set of prime numbers up to a given number n. 
// The function returns a vector of booleans where the index i says
// if the number i is a prime or not. 
// The time complexity of the algorithm is O(n log( log(n) )) because
// it iterates over all the numbers up to n and for each number it
// iterates over all the numbers up to sqrt(n).
vector<bool> sieve_of_eratosthenes(int n){
  vector<bool> primes(n + 1, true);
  primes[0] = false;
  primes[1] = false;
  for (int p = 2; p * p <= n; p++){
    if (primes[p] == true){
      for (int i = p * p; i <= n; i += p)
        primes[i] = false;
    }
  }
  return primes;
}

int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  //Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);

  int n, q, p;
  cin >> n >> q;
  vector<bool> primes = sieve_of_eratosthenes(n);
  cout << count(primes.begin(), primes.end(), true) << "\n";
  while(q--){
    cin >> p;
    cout << primes[p] << "\n";
  }
  return 0;
}