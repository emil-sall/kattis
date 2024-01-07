/*
Problem: Polynomial Multiplication 2 - https://open.kattis.com/problems/polymul2
Author: Emil Säll
The code is written in C++ and is using the Google C++ style guide.

This code is used to do a Polynomial multiplication with FFT. The input is 2 polynomials and the output
is the product of the two polynomials. 

The time complexity of the program is O(n log n) where n is the degree of the polynomial.

The first row of the input cointains how many test cases that are to be solved. Then the test cases start.
The first row of a test case is an integer n1, which is the degree of the first polynomial. The next row
contains n1 + 1 integers which are the coefficients of the first polynomial. The next row is an integer
n2, which is the degree of the second polynomial. The next row contains n2 + 1 integers which are the
coefficients of the second polynomial. THis repeats for every test case. The output are two lines for 
every test case. The first line is the degree of the product of the two polynomials. The second line
contains the coefficients of the product of the two polynomials. A example of input and output is shown
below.

Input:
1
2
1 0 5
1
0 -2


Output:	
3
0 -2 0 -10

*/

#include <iostream>
#include <string>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;
using cd = complex<double>;

//The input is a vector of complex numbers and a boolean which is true if the
//function should use the inverse DFT and false if it should use only DFT.

//The output is a vector of complex numbers which is the result of the DFT or
//the inverse DFT.

//The function uses the divide and conquer method to calculate the DFT or the
//inverse DFT. It divides the vector into two vectors of half the size and
//calls itself on those two vectors. Which it repeatedly does until it is only
//one element left. It then uses the formula for the DFT or the inverse DFT to
//calculate the DFT or the inverse DFT of the original vector. 

//Because of the breakdown to single elements, the time complexity is 
//O(n log n) where n is the size of the vector. 
vector<cd> convert(vector<cd> pol, bool invert){
  int n = pol.size();
  if (n == 1){
    return pol;
  }
  int half_size = (pol.size() + 1)/2;
  vector<cd> pol_even(half_size, 0), pol_odd(half_size, 0);
  for (int i = 0; 2 * i < n; i++){
    pol_even[i] = pol[2*i];
    pol_odd[i] = pol[2*i+1];
  }
  if(n % 2 == 1){
    pol_odd.back() = 0;
  }   
  pol_even = convert(pol_even, invert);
  pol_odd = convert(pol_odd, invert);
  vector<cd> dft_vector(n, 0);
  double ang = 2 * M_PI / n * (invert ? -1 : 1);
  cd w(1), wn(cos(ang), sin(ang));
  for (int i = 0; 2 * i < n; i++){
    dft_vector[i] = pol_even[i] + w * pol_odd[i];
    dft_vector[i + n/2] = pol_even[i] - w * pol_odd[i];
    if (invert){
      dft_vector[i] /= 2;
      dft_vector[i + n/2] /= 2;
    }
    w *= wn;
  }
  return dft_vector;
};

//The input is two vectors of integers interpreted as complex numbers. 
//The integers repressent coefficients of two polynomials which polmul is used
//to multiply. 

//The output is a vector of integers which is the resulting polynomials
//coefficients after the multiplication.

//The function uses the function convert() to convert the polynomials to
//their DFT representation and then multiplies them more efficiently in that
//domain and then converts the result back to the polynomial domain.

//The time complexity of the function is O(n log n) where n is the size of
//the input vectors. Since the function uses convert() which has a time
//complexity of O(n log n) the time complexity of the function is O(n log n).
vector<int> polmul(vector<cd> pol1, vector<cd> pol2){    
  int n = 1;
  while (n < pol1.size() + pol2.size()){
    n <<= 1;
  }
  pol1.resize(n, 0);
  pol2.resize(n, 0);
  vector<cd> dft_pol1 = convert(pol1, false);
  vector<cd> dft_pol2 = convert(pol2, false);
  for (int i = 0; i < n; i++){
    dft_pol1[i] *= dft_pol2[i];
  }
  dft_pol1 = convert(dft_pol1, true);
  vector<int> pol3(n, 0);
  for (int i = 0; i < n; i++){
    pol3[i] = round(dft_pol1[i].real());
  }
  return pol3;
};


int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  //Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  cin >> T;
  for(int i = 0; i < T; i++){
    int n1, n2;

    cin >> n1;
    vector<cd> pol1(n1+1, 0);
    for(int i = 0; i <= n1; i++){
      cin >> pol1[i];
    }

    cin >> n2;
    vector<cd> pol2(n2+1, 0);
    for(int i = 0; i <= n2; i++){
      cin >> pol2[i];
    }

    vector<int> pol3 = polmul(pol1, pol2);
      
    cout << n1+n2 << "\n";
    for(int i = 0; i <= n1+n2; i++){
      cout << pol3[i] << " ";
    }
    cout << "\n";
  }
  return 0;
}