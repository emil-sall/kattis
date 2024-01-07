/*
Modular arithmetic: https://open.kattis.com/problems/modulararithmetic
Emil Säll
emisa182
The code is written in C++ and is using the Google C++ style guide.

This code is used to solve a problem of modular arithmetic. The problem is getting a set of expressions
and to calculate the result of the expression modulo a given number.

The time complexity of the program is O(t * log(modulo)) where t is the number of expressions.

The input could be multiple cases and each case starts with two integers modulo and t where modulo is the
number to calculate the result modulo and t is the number of expressions. The next t rows are the expressions
where each row is an expression with the format a op b where a and b are integers and op is one of the
operators +, -, * and /. 

The output is the result of the expression modulo the given number. If the operations is not possible 
(e.g. because of division by zero), the output should be -1. 
An example of input and output is shown below.


Input:
1000 3
1 / 999
1 / 998
578 * 178
13 4
7 / 9
9 * 3
0 - 9
10 + 10
0 0

Output:
999
-1
884
8
1
4
7

*/


#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int gcdExtended(long long int a, long long int b, 
                long long int *x, long long int *y);
long long int mod_invert(long long int b, long long int mod);

// The class Expression is used to store the information about a
// modular expression.
class Expression{
  public:
    Expression(long long int a, string op, long long int b, 
                                           long long int modulo);
    string op;
    long long int a, b, modulo, result{0};
    void perform_calculations();
    void mod_mul();
};

// The constructor of the class Expression. It takes the values, the
// operator and the modulo of the expression as input
// Time complexity: O(1).
Expression::Expression(long long int a, string op, 
                       long long int b, long long int modulo){
  this->op = op;
  this->a = a;
  this->b = b;
  this->modulo = modulo;
};


// The function mod_mul is used to calculate the result of the
// expression modulo the given number.
// The time complexity is O(log(modulo)) because the
// while loop is executed log(modulo) times.
void Expression::mod_mul(){
  this->a %= this->modulo;
  while(this->b > 0){
    if(this->b % 2 == 1){
      this->result = (this->result + this->a) % this->modulo;
    }
    this->a = (this->a * 2) % this->modulo;
    this->b /= 2;
  }
}

// The function perform_calculations is used to calculate the result
// of the expression modulo the given number. 
// The time complexity is O(log(modulo)) for the division and 
// multiplication and O(1) for the addition and subtraction.
void Expression::perform_calculations(){
  if(this->op == "+"){
    this->result = this->a + this->b - this->modulo;
    while(this->result < 0){
      this->result += this->modulo;
    }
  } else if(this->op == "-"){
    this->result = this->a - this->b;
    while(this->result < 0){
      this->result += this->modulo;
    }
  } else if(this->op == "*"){
    this->mod_mul();
  } else if(this->op == "/"){
    if(this->b == 0){
      this->result = -1;
      return;
    }
    this->a %= this->modulo;
    long long int inv = mod_invert(this->b, this->modulo);
    if(inv != -1){
      this->result = (inv * this->a) % this->modulo;
    } else{
      this->result = -1;
    }
  }
}

// The function gcdExtended is used to calculate the greatest common
// divisor of two numbers using the extended Euclidean algorithm.
// The time complexity is O(log(min(a, b))) because the while loop is
// executed log(min(a, b)) times.
int gcdExtended(long long int a, long long int b, 
                long long int *x, long long int *y){
  if (a == 0){
    *x = 0, *y = 1;
    return b;
  }
  long long int x1{0}, y1{0};
  long long int gcd = gcdExtended(b%a, a, &x1, &y1);
  *x = y1 - (b/a) * x1;
  *y = x1;
  return gcd;
}

// The function mod_invert is used to calculate the modular inverse of
// a number. 
// The time complexity is O(log(mod)) because the function gcdExtended
// is executed log(mod) times.
long long int mod_invert(long long int b, long long int mod){
  long long int x{0}, y{0};
  long long int g = gcdExtended(b, mod, &x, &y);
  if (g != 1){
      return -1;
  }
  return (x%mod + mod) % mod;
};

int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  //Decouple activities on cin and cout
  cin.tie(NULL);

  long long int t, modulo;
  long long int a, b;
  string op;
  while(true){
    cin >> modulo >> t;
    if(modulo == 0 && t == 0){
      break;
    }
    while(t--){
      cin >> a >> op >> b;
      Expression expression = Expression(a, op, b, modulo);
      expression.perform_calculations();
      cout << expression.result << "\n";
    }
  }
  return 0;
}