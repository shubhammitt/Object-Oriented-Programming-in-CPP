#include "time.h"

TimeUnit::TimeUnit() {
	val = 0;
	nextBiggerTimeUnit = NULL;
}

TimeUnit::~TimeUnit() {
	nextBiggerTimeUnit = NULL;
}

int TimeUnit::GetVal() const {
	return val;
}

void TimeUnit::SetVal(int units) {
	val = units;
	AdjustOverflow();
}

void TimeUnit::Reset() {
	SetVal(0);
}

void TimeUnit::SetLimit(int _valLimit) {
	valLimit = _valLimit;
}

int TimeUnit::GetLimit() const {
	return valLimit;
}

void TimeUnit::SetUnitName(const std:: string& _unitName) {
	unitName = _unitName;
}

void TimeUnit::SetNextBiggerUnit(TimeUnit& _nextBiggerTimeUnit) {
	nextBiggerTimeUnit = &_nextBiggerTimeUnit;
}

void TimeUnit::Increment(int units) {
	val += units;
	AdjustOverflow();
}

void TimeUnit::AdjustOverflow() {
	if (val >= valLimit) {
		int nextUnitVal = val / valLimit;
		val = val - (nextUnitVal * valLimit);
		if (nextBiggerTimeUnit != NULL)
			nextBiggerTimeUnit -> Increment(nextUnitVal);
	}
}

int TimeUnit::operator+(const TimeUnit& t2) const {
	return val + t2.val;
}

int TimeUnit::operator-(const TimeUnit& t2) const {
	return val - t2.val;
}

int TimeUnit::operator*(const int n) const {
	return val * n;
}

bool TimeUnit::operator==(const TimeUnit& t2) const {
	return val == t2.val;
}

bool TimeUnit::operator<(const TimeUnit& t2) const {
	return val < t2.val;
}


bool TimeUnit::operator>(const TimeUnit& t2) const {
	return val > t2.val;
}


/**************************************Time class*********************************************/

Time::Time() {
	init();
}

Time::Time(int _seconds) {
	init();
	SetTime(_seconds);
}

Time::Time(int _days, int _hours, int _minutes, int _seconds) {
	init();
	SetTime(_seconds, _minutes, _hours, _days);
}

Time::~Time() {

}

Time Time::operator+(const Time& t2) const {
	return Time(seconds + t2.seconds,						\
				minutes + t2.minutes,						\
				hours + t2.hours, 							\
				days + t2.days);
}

Time Time::operator-(const Time& t2) const {
	int _seconds = seconds - t2.seconds;
	int _minutes = minutes - t2.minutes;
	int _hours = hours - t2.hours;
	int _days = days - t2.days;

	// adjust negative value
	if (_seconds < 0) {
		_seconds += seconds.GetLimit();
		_minutes--;
	}

	if (_minutes < 0) {
		_minutes += minutes.GetLimit();
		_hours--;
	}

	if(_hours < 0) {
		_hours += hours.GetLimit();
		_days--;
	}

	return Time(_seconds, _minutes, _hours, _days);
}

Time Time::operator*(const int n) const {
	return Time(days * n, hours * n, minutes * n, seconds * n);
}

bool Time::operator==(const Time& t2) const {
	return seconds == t2.seconds 	&&
		   minutes == t2.minutes 	&&
		   hours == t2.hours 		&&
		   days == days;
}

bool Time::operator!=(const Time& t2) const {
	return not(*(this) == t2);
}

bool Time::operator<(const Time& t2) const {
	if (days < t2.days)
		return true;
	if (days > t2.days)
		return false;

	if (hours < t2.hours)
		return true;
	if (hours > t2.hours)
		return false;

	if (minutes < t2.minutes)
		return true;
	if (minutes > t2.minutes)
		return false;

	if (seconds < t2.seconds)
		return true;
	if (seconds > t2.seconds)
		return false;

	return false;
}

bool Time::operator>(const Time& t2) const {
	return ( *(this) != t2 and not(*(this) < t2 ) );
}

bool Time::operator<=(const Time& t2) const {
	return ( *(this) == t2 or (*(this) < t2 ));
}

bool Time::operator>=(const Time& t2) const {
	return ( *(this) == t2 or (*(this) > t2 ));
}

Time& Time::operator++() {
	seconds.Increment(1);
	return *this;
}

Time& Time::operator--() {
	Time t = *this - 1;
	this -> SetTime(t.seconds.GetVal(), t.minutes.GetVal(), 	\
					t.hours.GetVal(), t.days.GetVal());
	return *this;
}

Time Time::operator++(int) {
	Time temp = *this;
	seconds.Increment(1);
	return temp;
}

Time Time::operator--(int) {
	Time temp = *this;
	Time t = *this - 1;
	this -> SetTime(t.seconds.GetVal(), t.minutes.GetVal(), t.hours.GetVal(), t.days.GetVal());
	return temp;
}

// Format: 10~12:23:48
std::ostream& operator<<(std::ostream& out, const Time& time) {
	char oldfill = out.fill();
	out.fill('0');
	out << time.days.GetVal() << "~";
	out.width(2);
	out << time.hours.GetVal() << ":";
	out.width(2);
	out << time.minutes.GetVal() << ":";
	out.width(2);
	out << time.seconds.GetVal();
	out.fill(oldfill);
	return out;
}

// Format: 10~12:23:48
std::istream& operator>>(std::istream& in, Time& time) {
	std::string inputTime;
	in >> inputTime;
	int _days, _hours, _minutes, _seconds;
	time.ExtractTimeFromString(inputTime, _days, _hours, _minutes, _seconds);
	time.SetTime(_seconds, _minutes, _hours, _days);
	return in;
}

void Time::init() {
	seconds.SetLimit(60);
	minutes.SetLimit(60);
	hours.SetLimit(24);
	days.SetLimit(MAXIMUM_TIME_LIMIT);

	seconds.SetNextBiggerUnit(minutes);
	minutes.SetNextBiggerUnit(hours);
	hours.SetNextBiggerUnit(days);

	seconds.SetUnitName("seconds");
	minutes.SetUnitName("minutes");
	hours.SetUnitName("hours");
	days.SetUnitName("days");
}

void Time::SetDefaultDate() {
	seconds.Reset();
	minutes.Reset();
	hours.Reset();
	days.Reset();
}

void Time::SetTime(int _seconds, int _minutes, int _hours, int _days) {
	SetDefaultDate();
	if (_days >= 0 && _hours >= 0 && _minutes >= 0 && _seconds >= 0) {
		seconds.Increment(_seconds);
		minutes.Increment(_minutes);
		hours.Increment(_hours);
		days.Increment(_days);
	}
}

/*
 * Used as utility function by Time::operator>>()
 * Format: 10~12:23:48, no error checking, assumes correct format
 */
void Time::ExtractTimeFromString(const std::string& s, int& _days,		\
							     int& _hours, int& _minutes,			\
							     int& _seconds) const {
	int tildeIdx = 1;
	FindCharIdx(s, '~', tildeIdx);

	int colonIdx1 = tildeIdx + 1;
	FindCharIdx(s, ':', colonIdx1);

	int colonIdx2 = colonIdx1 + 1;
	FindCharIdx(s, ':', colonIdx2);

	_days = stoi(s.substr(0, tildeIdx));
	_hours = stoi(s.substr(tildeIdx + 1, colonIdx1 - tildeIdx - 1));
	_minutes = stoi(s.substr(colonIdx1 + 1, colonIdx2 - colonIdx1 - 1));
	_seconds = stoi(s.substr(colonIdx2 + 1, s.size()));
}

// Used by Time::ExtractTimeFromString
void Time::FindCharIdx(const std::string& s, char ch, int& idx) const {
	while (idx) {
		if (s[idx] == ch)
			break;
		idx++;
	}
}
