#include <iostream>

const static std::string monthsName[] = {""  , "Jan", "Feb", "Mar", "Apr", 		\
										"May", "Jun", "Jul", "Aug", "Sep",		\
										"Oct", "Nov", "Dec"}; 					// 1-indexed

const static int numDaysInMonth[] = {0, 31, 28, 31, 30,							\
									31, 30, 31, 31, 30,							\
									31, 30, 31};								// 1-indexed

const static char validFormats[] = {'D' /*Default format*/		,				\
								    'T' /*Two-Digit format*/	,				\
								    'L' /*Long format*/};

// No Leap year handled, 1 year = 365 days with 28days in Feb
class Date {

private:
	int day, month, year;
	char dateFormat;

public:
	Date();
	Date(int _month, int _day, int _year);
	void Input();
	void Show() const;														// display with format
	bool Set(int _month, int _day, int _year);								// aborts if invalid
	int GetMonth() const;
	int GetDay() const;
	int GetYear() const;
	bool SetFormat(char f);
	void Increment(int numDays = 1);										// add numDays in Date
	/****************************************************************
	 * returns: 													*
	 * 		-1 if the calling object comes first chronologically, 	*
	 * 		 0 if the objects are the same date, and 				*
	 * 		 1 if the parameter object comes first chronologically. *
	 * 																*
	 * **************************************************************/
	int Compare(const Date& d) const;	

private:
	bool IsDateValid(int _month, int _day, int _year) const;
	void SetDefaultDate();													// January 1, 2000
	void SetDefaultDateFormat();
	void SetDateWithoutValidation(int _month, int _day, int _year);			// Without Date Validation
	void ExtractDateFromString(const std::string& inputDate, int& m, 		\
							   int& d, int& y) const;
	void AddMonths(int& numDays, int& _month, int& _day, int& _year) const;
	void PrintInDefaultFormat() const;
	void PrintInTwoDigitFormat() const;
	void PrintInLongFormat() const;
};
