#include <iostream>

using namespace std;

int main()
{
const int monthsInYear = 12;
double Principal = 0.0;
cout << "Enter the principal amount:";
cin >> Principal;

double interest = 0.0;
cout << "Enter the interest rate:";
cin >> interest;

int yearsOfLoan = 0;
cout << "Enter the years of loan";
cin >> yearsOfLoan;

double monthInterest = interest / monthsInYear;
long monthsOfLoan = yearsOfLoan * monthsInYear;

cout << Principal << " " < <interest << " "<< yearsOfLoan << " " << monthInterest << " " << monthsOfLoan << " " << endl;

return 0;
}