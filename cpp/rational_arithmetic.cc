/*
Problem: Rational arithmetic - https://open.kattis.com/problems/rationalarithmetic
Author: Emil Säll
emisa182
The code is written in C++ and is using the Google C++ style guide.

This code is used to apply an operator to two fractions. This operator could be any of the following:
+, -, /, *, <, >, <=, >=, == or !=. 

The time complexity of the program is O( log(numerator + denominator) ) 

The input can be multiple test cases and each test case is row dependent, the first row in the input tells 
how many test cases that are to be processed. The test cases arrive on one row on the format: a b op c d, 
where it is interpreted that one fraction is a/b and the other is c/d. These fractions are separated by an
operator. The program assumes that non of b, c, or d are zero.

The output for each test case is one row per test case that is the result of applying the operator. For a
comparing operator the output is either 0 or 1 and if the operator is calculatory the output is the new
fraction. An exapmle of input and its output is shown below.


Input:
14
1 3 + 1 2
1 3 - 1 2
123 287 / 81 -82
12 -3 * -1 -1
-1 3 + 1 2
1 -3 + 1 2
1 3 + -1 2
1 3 + 1 -2
1 3 < 1 -2
1 3 > 1 -2
1 3 <= 1 -2
1 3 >= 1 -2
1 3 == 1 -2
1 3 != 1 -2

Output:
5 / 6
-1 / 6
-82 / 189
-4 / 1
1 / 6
1 / 6
-1 / 6
-1 / 6
0
1
0
1
0
1
*/
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// The class Fraction stores a fraction through a nominator and a
// denominator. The practicallity of the function is that it can use
// the operations: +, -, /, *, <, >, <=, >=, == and != when used with
// another fraction. 
class Fraction{
  public:
    long long int numerator;
    long long int denominator;
    Fraction(long long int numerator, long long int denominator);
    Fraction();
    long long int greatest_common_divisor(long long int num, 
                                          long long int denom);
    void format_fraction(long long int numerator, 
                         long long int denominator);
    operator double();
    Fraction operator + (Fraction frac);
    Fraction operator - (Fraction frac);
    Fraction operator / (Fraction frac);
    Fraction operator * (Fraction frac);
    bool operator < (Fraction frac);
    bool operator > (Fraction frac);
    bool operator <= (Fraction frac);
    bool operator >= (Fraction frac);
    bool operator == (Fraction frac);
    bool operator != (Fraction frac);
};


// The class Expression has got a left fraction and a right fraction,
// they are separated by an operator op. The fractions are 
// initialized through the variables a, b, c, and d, and the 
// fractions is interpreted as a/b and c/d. The operator can be any
// of the following: +, -, /, *, <, >, <=, >=, == and !=, all as 
// strings. The function can be used to merge fractions or
// compare the fractions depending on the operator. If the operator
// is comparing, the result is stored in the boolean yes and if the 
// operator is merging the two fractions the result is stored in a
// merged fraction. 
class Expression{
  public:
    Expression(long long int a, long long int b, string op,
               long long int c, long long int d);
    string op;
    Fraction left_frac, right_frac, merged_frac;
    bool yes;
    void merge_fractions();
    void compare_fractions();
    void apply_operator();
};


// The constructor of an expression. 
// Time Complexity O(1)
Expression::Expression(long long int a, long long int b, string op, 
                       long long int c, long long int d){
  this->left_frac = Fraction(a, b);
  this->op = op;
  this->right_frac = Fraction(c, d);
};

// The function merge_fractions is applied when the operator is a 
// type of calculation. It uses the operations defined for fractions.
// Time complexity ~ O(1)
void Expression::merge_fractions(){ 
  if(this->op == "+"){
    this->merged_frac = this->left_frac + this->right_frac;
  } else if(this->op == "-"){
    this->merged_frac = this->left_frac - this->right_frac;
  } else if(this->op == "/"){
    this->merged_frac = this->left_frac / this->right_frac;
  } else if(this->op == "*"){
    this->merged_frac = this->left_frac * this->right_frac;
  }
};

// The function compare_fractions is applied when the operator is a 
// type of comparison. It uses the operations defined for fractions.
// Time complexity ~ O(1)
void Expression::compare_fractions(){ 
  if(this->op == "<"){
    this->yes = (this->left_frac < this->right_frac);
  } else if(this->op == ">"){
    this->yes = (this->left_frac > this->right_frac);
  } else if(this->op == "<="){
    this->yes = (this->left_frac <= this->right_frac);
  } else if(this->op == ">="){
    this->yes = (this->left_frac >= this->right_frac);
  } else if(this->op == "=="){
    this->yes = (this->left_frac == this->right_frac);
  } else if(this->op == "!="){
    this->yes = (this->left_frac != this->right_frac);
  }
};

// The function apply_operator is used to apply the operator in the
// expression. To do so it determines what kind of operator it is. 
// Time complexity ~ O(1)
void Expression::apply_operator(){
  int res;
  if(this->op == "+" || this->op == "-" ||
     this->op == "/" || this->op == "*"){
    this->merge_fractions();
  } else{
    this->compare_fractions();
  }
}

// The default constructor for a Fraction which initializes the 
// numerator and the denominator.
// Time complexity ~ O(1)
Fraction::Fraction(){
  this->numerator;
  this->denominator;
}

// A constructor for the class Fraction. It takes a numerator and a 
// denominator and uses the function format_fraction to make sure 
// that the fraction is in the right format. 
// Time complexity ~ O(1)
Fraction::Fraction(long long int numerator, 
                   long long int denominator){
  format_fraction(numerator, denominator);
};

// The function format_fraction is used to make sure that the 
// fraction is in the right format. The right format is that a 
// denominator should never be negative and the numerator should
// only be negative if the whole fraction is negative. The fraction 
// should also be on the shortest possible form, i.e. no common 
// divisor between the numerator and denominator.  
// Time complexity ~ O( log(numerator + denominator) )
void Fraction::format_fraction(long long int numerator, 
                               long long int denominator){
  // Assuming that denom is never 0. Minus sign in the numerator always.
  long long int divisor;
  if(denominator > 0){
    this->numerator = numerator;
    this->denominator = denominator;
  } else{
    this->numerator = -numerator;
    this->denominator = -denominator;
  } 

  // Every time a fraction is created, the fraction should have the
  // shortest term.
  if(this->numerator >= 0){
    divisor = greatest_common_divisor(this->numerator, this->denominator);
  } else{
    divisor = greatest_common_divisor(-this->numerator, this->denominator);
  }
  this->numerator /= divisor;
  this->denominator /= divisor;
};

// The function greatest common divisor is used to find the greatest
// common divisor between two integers. 
// Time complexity ~ O( log(num + denom) )
long long int Fraction::greatest_common_divisor(long long int num, 
                                                long long int denom){
  if(denom == 0){
    return num;
  }
  return greatest_common_divisor(denom, num % denom);
}

// An operator to make a fraction to a double. 
// Time complexity ~ O(1)
Fraction::operator double(){
  return double(this->numerator) / double(this->denominator);
};

// An operator to add two fractions. 
// Time complexity ~ O(1)
Fraction Fraction::operator + (Fraction frac){
  Fraction merged_frac;
  long long int a = this->numerator;
  long long int b = this->denominator;
  long long int c = frac.numerator;
  long long int d = frac.denominator;
  merged_frac.format_fraction(a*d + b*c, b*d);
  return merged_frac;
};

// An operator to subtract two fractions. 
// Time complexity ~ O(1)
Fraction Fraction::operator - (Fraction frac){
  Fraction merged_frac;
  long long int a = this->numerator;
  long long int b = this->denominator;
  long long int c = frac.numerator;
  long long int d = frac.denominator;
  merged_frac.format_fraction(a*d - b*c, b*d);
  return merged_frac;
};

// An operator to divide two fractions. 
// Time complexity ~ O(1)
Fraction Fraction::operator / (Fraction frac){
  Fraction merged_frac;
  long long int a = this->numerator;
  long long int b = this->denominator;
  long long int c = frac.numerator;
  long long int d = frac.denominator;
  merged_frac.format_fraction(a*d, c*b);
  return merged_frac;
};

// An operator to multiply two fractions. 
// Time complexity ~ O(1)
Fraction Fraction::operator * (Fraction frac){
  Fraction merged_frac;
  long long int a = this->numerator;
  long long int b = this->denominator;
  long long int c = frac.numerator;
  long long int d = frac.denominator;
  merged_frac.format_fraction(a*c, b*d);
  return merged_frac;
};

// An operator to see if the left fraction is smaller than the right.
// Time complexity ~ O(1)
bool Fraction::operator < (Fraction frac){
  return (double(this->numerator) / double(this->denominator)) < 
         (double(frac.numerator) / double(frac.denominator));
};

// An operator to see if the left fraction is bigger than the right.
// Time complexity ~ O(1)
bool Fraction::operator > (Fraction frac){
  return (double(this->numerator) / double(this->denominator)) >  
         (double(frac.numerator) / double(frac.denominator));
};

// An operator to see if the left fraction is smaller than or equal 
// to the right. 
// Time complexity ~ O(1)
bool Fraction::operator <= (Fraction frac){
  return (double(this->numerator) / double(this->denominator)) <=
         (double(frac.numerator) / double(frac.denominator));
};

// An operator to see if the left fraction is bigger than or equal 
// to the right. 
// Time complexity ~ O(1)
bool Fraction::operator >= (Fraction frac){
  return (double(this->numerator) / double(this->denominator)) >=
         (double(frac.numerator) / double(frac.denominator));
};

// An operator to see if the left fraction is equal to the right.
// Time complexity ~ O(1)
bool Fraction::operator == (Fraction frac){
  return (double(this->numerator) / double(this->denominator)) == 
         (double(frac.numerator) / double(frac.denominator));
};

// An operator to see if the left fraction is not equal to the right.
// Time complexity ~ O(1)
bool Fraction::operator != (Fraction frac){
  return (double(this->numerator) / double(this->denominator)) !=
         (double(frac.numerator) / double(frac.denominator));
};


int main(){
  // Disable the syncronization between C and C++ standard streams
  // which leads ta an improved IO speed.
  ios_base::sync_with_stdio(false);

  // Decouple activities on cin and cout
  cin.tie(NULL);
  cout.tie(NULL);

  int nr_operations;
  cin >> nr_operations;

  for(int i = 0; i < nr_operations; i++){
    long long int a, b, c, d;
    string op;
    cin >> a >> b >> op >> c >> d;
    Expression expression = Expression(a, b, op, c, d);
    expression.apply_operator();
    if(op == "+" || op == "-" || op == "/" || op == "*"){
    cout << expression.merged_frac.numerator << " / " <<  expression.merged_frac.denominator << "\n";
    } else{
      cout << expression.yes << "\n";
    }
  }
  return 0;
}
