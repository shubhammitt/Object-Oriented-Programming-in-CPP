#include <iostream>
#include "date.h"
using namespace std;

void test1() {
cout << "d1 using default constructor..." << endl;
	Date d1;             // initializes to Jan 1, 2000 
	d1.Show();
	cout << "d2 using paramatrised constructor..." << endl;
	Date d2(3,4,1992);   // initializes to March 4, 1992 
	d2.Show();
	cout << "d3 using paramatrised constructor..." << endl;
	Date d3(13,30,1990); // invalid month, initializes to Jan 1, 2000 instead. 
	d3.Show();
	cout << "Enter d1..." << endl;
	d1.Input();
	d1.Show();
	cout << "Enter d3..." << endl;
	d3.Input();
	d3.Show();
	d3.SetFormat('L');
	d3.Show();
	d3.SetFormat('T');
	d3.Show();
	d3.SetFormat('A');
	d3.Show();
	int c = 10;int inc; 
	while(c--) {
		cout << "Enter increment value in d3 date: ";
		cin >> inc;
		d3.Increment(inc);
		d3.SetFormat('T');
		d3.Show();
	}
	cout << "Enter increment value in d3 date: ";
	cin >> inc;
	d3.Increment(inc);
	d3.Show();
	cout << d2.Compare(d3) << endl;
	cout << d2.Compare(d2) << endl;
	cout << d3.Compare(d2) << endl;
	cout << "Setting d1 date... " <<  d1.Set(123, 4, 444) << endl;
	cout << "Setting d1 date... " <<  d1.Set(12, 4, 444) << endl;
	d1.SetFormat('T');
	d1.Show();
}

void test2() {
	Date d1(12,25,2003);		// Dec 25, 2003
	Date d2(5,18,2002);		// May 18, 2002

	cout << d1.Compare(d2);		// returns 1  (since d2 comes first)
	cout << d2.Compare(d1);		// returns -1 (calling object is d2, comes first)
}
int main(int argc, char *argv[]) {
	test2();
}