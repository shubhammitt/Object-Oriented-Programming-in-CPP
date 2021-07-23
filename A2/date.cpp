#include "date.h"

Date::Date() {
	SetDefaultDate();
	SetDefaultDateFormat();
}

Date::Date(int _month, int _day, int _year) {
	if (IsDateValid(_month, _day, _year)) 
		SetDateWithoutValidation(_month, _day, _year);
	else {
		std::cout << "Invalid Date! Setting to default...\n";
		SetDefaultDate();
	}
	SetDefaultDateFormat();
}

void Date::Input() {
	std::cout << "Enter a valid date:\n";
	// loop until valid date is entered by user
	while (true) {
		std::string inputDate;
		std::cin >> inputDate;
		int m, d, y;
		ExtractDateFromString(inputDate, m, d, y);
		if (IsDateValid(m, d, y)) {
			SetDateWithoutValidation(m, d, y);
			return;
		}
		std::cout << "Invalid date. Try again:\n";
	}
}

void Date::Show() const {
	switch(dateFormat) {
		case 'D':
		PrintInDefaultFormat();
		break;
		case 'T':
		PrintInTwoDigitFormat();
		break;
		case 'L':
		PrintInLongFormat();
	}
}

bool Date::Set(int _month, int _day, int _year) {
	if (IsDateValid(_month, _day, _year)) {
		SetDateWithoutValidation(_month, _day, _year);
		return true;
	}
	return false;
}

int Date::GetMonth() const {
	return month;
}

int Date::GetDay() const {
	return day;
}

int Date::GetYear() const {
	return year;
}

bool Date::SetFormat(char f) {
	for (auto& format: validFormats) {
		if (format == f) {
			dateFormat = f;
			return true;
		}
	}
	return false;
}

void Date::Increment(int numDays) {

	int numYears = numDays / 365;
	int _year = GetYear() + numYears;
	numDays = numDays - 365 * numYears;

	int leftDaysInCurrentMonth = numDaysInMonth[GetMonth()] - day;

	if (leftDaysInCurrentMonth >= numDays) {
		SetDateWithoutValidation(GetMonth(), GetDay() + numDays, _year);
	}
	else {
		numDays -= leftDaysInCurrentMonth;
		int _day;
		int _month = GetMonth() + 1;
		AddMonths(numDays, _month, _day, _year);
		SetDateWithoutValidation(_month, _day, _year);
	}
}

/****************************************************************
 * returns: 													*
 * 		-1 if the calling object comes first chronologically, 	*
 * 		 0 if the objects are the same date, and 				*
 * 		 1 if the parameter object comes first chronologically. *
 * 																*
 * **************************************************************/
int Date::Compare(const Date &d) const {
	if (year < d.year) 	return -1;
	if (year > d.year) 	return  1;

	if (month < d.month) return -1;
	if (month > d.month) return  1;

	if (day < d.day) 	return -1;
	if (day > d.day) 	return  1;

	return 0;
}

bool Date::IsDateValid(int _month, int _day, int _year) const {

	return _year > 0 										&&			\
		   _month >= 1 && _month <= 12 						&&			\
		   _day >= 1 &&	_day <= numDaysInMonth[_month];
}

// January 1, 2000
void Date::SetDefaultDate() {
	SetDateWithoutValidation(1, 1, 2000);
}
												
void Date::SetDefaultDateFormat() {
	dateFormat = 'D';
}

void Date::SetDateWithoutValidation(int _month, int _day, int _year) {
	month = _month;
	day = _day;
	year = _year;
}

// inputDate format: M/D/Y
void Date::ExtractDateFromString(const std::string& inputDate, 			\
								 int& m, int& d, int& y) const {
	int slash_idx1, slash_idx2;
	for (slash_idx1 = 1 ; ; slash_idx1++)				// no condition since valid format expected
		if (inputDate[slash_idx1] == '/')
			break;

	for (slash_idx2 = slash_idx1 + 1 ; ; slash_idx2++)	// no condition since valid format expected
		if (inputDate[slash_idx2] == '/')
			break;

	m = stoi(inputDate.substr(0, slash_idx1));
	d = stoi(inputDate.substr(slash_idx1 + 1, slash_idx2 - slash_idx1 - 1));
	y = stoi(inputDate.substr(slash_idx2 + 1, inputDate.size() - slash_idx2 - 1));
}

void Date::AddMonths(int& numDays, int& _month, int& _day, int& _year) const {
	while(_month <= 12) {
		if(numDaysInMonth[_month]  >= numDays) {
			_day = numDays;
			break;
		}
		numDays -= numDaysInMonth[_month];
		_month++;
	}
	if(_month == 13) {
		_month = 1;
		_year += 1;
		AddMonths(numDays, _month, _day, _year);
	}
}

// Format: M/D/Y; 		Example: 10/4/1998
void Date::PrintInDefaultFormat() const {
	std::cout << GetMonth() << "/" << GetDay() << "/" << GetYear() << "\n";
}

// Format: mm/dd/yy; 	Example: 10/04/98
void Date::PrintInTwoDigitFormat() const {
	char oldfill = std::cout.fill();
	std::cout.fill('0');
	std::cout.width(2);
	std::cout << GetMonth() << "/";
	std::cout.width(2);
	std::cout << GetDay() << "/";
	std::cout.width(2);
	std::cout << GetYear() % 100 << "\n";
	std::cout.fill(oldfill);
}

// Format: month D, Y; 	Example: Oct 4, 1998
void Date::PrintInLongFormat() const {
	std::cout << monthsName[GetMonth()] << " " 
			  << GetDay() << ", " << GetYear() << "\n";
}
