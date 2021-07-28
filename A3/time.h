#include <iostream>
#include <climits>

#define MAXIMUM_TIME_LIMIT INT_MAX

/*
 * TimeUnit: seconds, minutes, hours, days and so on  
 */
class TimeUnit {

private:
	int val;
	/*
	 * maximum possible val for current unit of time
	 * 60 for seconds, 24 hours and so on
	 */
	int valLimit;									
	/**********************************************
	 * nextBiggerTimeUnit:						  *
	 * 					for second: 	minutes   *
	 * 					for minutes: 	hours     *
	 * 					for hours:		days      *
	 * 					for days:		NULL      *
	 **********************************************/
	TimeUnit *nextBiggerTimeUnit;
	std::string unitName;

public:
	TimeUnit();
	~TimeUnit();
	int GetVal() const;
	void SetVal(int units);										// prevents overflow
	void Reset();
	void SetLimit(int _valLimit);
	int GetLimit() const;
	void SetUnitName(const std:: string& _unitName);
	void SetNextBiggerUnit(TimeUnit& _nextBiggerTimeUnit);
	void Increment(int units);									// prevents overflow above valLimit
	
	int operator+(const TimeUnit& t2) const;
	int operator-(const TimeUnit& t2) const;
	int operator*(const int n) const;
	bool operator==(const TimeUnit& t2) const;
	bool operator<(const TimeUnit& t2) const;
	bool operator>(const TimeUnit& t2) const;

private:
	void AdjustOverflow();

};

class Time {

private:
	TimeUnit days, hours, minutes, seconds;
public:
	Time();
	Time(int _seconds);
	Time(int _days, int _hours, 								\
		 int _minutes, int _seconds);
	~Time();
	
	Time operator+(const Time& t2) const;
	Time operator-(const Time& t2) const;
	Time operator*(const int n) const;
	bool operator==(const Time& t2) const;
	bool operator!=(const Time& t2) const;
	bool operator<(const Time& t2) const;
	bool operator>(const Time& t2) const;
	bool operator<=(const Time& t2) const;
	bool operator>=(const Time& t2) const;
	Time& operator++();
	Time& operator--();
	Time operator++(int);
	Time operator--(int);

	friend std::ostream& operator<<(std::ostream& out, 
									const Time& time);
	friend std::istream& operator>>(std::istream& in, 
									Time& time);

private:										
	void init();													// for all units
	void SetDefaultDate();											// all set to zeros
	void SetTime(int _seconds, int _minutes=0, 						\
				 int _hours=0, int _days=0);
	/*
 	 * Used as utility function by Time::operator>>()
 	 * Format: 10~12:23:48, no error checking, assumes correct format
	 */
	void ExtractTimeFromString(const std::string& s, int& _days,	\
							   int& _hours, int& _minutes,			\
							   int&_seconds) const;
	// Used by Time::ExtractTimeFromString
	void FindCharIdx(const std::string& s, char ch, 				\
					 int& idx) const;
};
