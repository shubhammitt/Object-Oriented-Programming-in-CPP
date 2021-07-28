// Sample main program to test the Time class
// Author:  Bob Myers

#include <iostream>
#include "time.h"

using namespace std;

void test1() {
   Time t1, t2, t3(123456), t4(987654321);
   cout << "t1 = " << t1 << '\n';
   cout << "t2 = " << t2 << '\n';
   cout << "t3 = " << t3 << '\n';
   cout << "t4 = " << t4 << '\n';

   cout << "Enter first Time object (DAYS~HH:MM:SS):  ";
   cin >> t1;

   cout << "Enter second Time object (DAYS~HH:MM:SS):  ";
   cin >> t2;

   cout << "\n\n"; 
   cout << t1 << " + " << t2 << " = " << t1 + t2 << '\n';
   cout << t1 << " - " << t2 << " = " << t1 - t2 << "\n\n";

   cout << "t1 * 2 = " << t1 * 2 << "\n";      
   cout << "t1 * 5 = " << t1 * 5 << "\n\n";      

   if (t1 < t2)   cout << t1 << " <  " << t2 << " is TRUE\n";
   if (t1 > t2)   cout << t1 << " >  " << t2 << " is TRUE\n";
   if (t1 <= t2)  cout << t1 << " <= " << t2 << " is TRUE\n";
   if (t1 >= t2)  cout << t1 << " >= " << t2 << " is TRUE\n";
   if (t1 == t2)  cout << t1 << " == " << t2 << " is TRUE\n";
   if (t1 != t2)  cout << t1 << " != " << t2 << " is TRUE\n\n";

   cout << t1 << " + 654321 = " << t1 + 654321 << '\n';
   cout << t2 << " + 15263748 = " << t2 + 15263748 << '\n';
   cout << "t1++ = " << t1++ << "\n";            
   cout << "++t1 = " << ++t1 << "\n";            
   cout << "t1-- = " << t1-- << "\n";            
   cout << "--t1 = " << --t1 << "\n";            
   cout << "--t1 = " << --t1 << "\n";       
}

void test2() {
   Time t1, t2, t3(59), t4(60);
   int x; cin >> x;
   Time t5(x);
   cout << t5;
   // t3.print();
   // t4.print();
}
int main()
{
   test1();
   // test2();
}

