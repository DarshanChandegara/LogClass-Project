#include<iostream> 
#include "../include/date.h"
#include "../include/string.h"
using utility::date;
using utility::String;

bool date::isLeapYear(int year) const {
	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) return true;
	else return false;
}

int date::daysInMonth(int m, int y) const {
	switch (m) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;

	case 4: case 6: case 9: case 11:
		return 30;


	case 2:
		return isLeapYear(y) ? 29 : 28;
	}
}

date& date::addMonth(int months) {
	if (months > 12) {
		year = year + (months / 12);
		months = months % 12;
	}
	if (month + month > 12) {
		month = (month + months) - 12;
		year += 1;
		auto DIM = daysInMonth(month, year);
		if (DIM < day) {
			auto temp = day - DIM;
			month++;
			day = temp;
		}
	}

	else {
		month++;
		auto DIM = daysInMonth(month, year);
		if (DIM < day) {
			auto temp = day - DIM;
			month++;
			day = temp;
		}
	}

	return *this;
}

date& date::addYear(int years) {
	this->year += years;
	return *this;
}

date& date::addDay(int days) {
	while (days != 0) {
		auto dayinMonth = daysInMonth(month, year);
		if (days > dayinMonth) {
			days = days - (dayinMonth - day + 1);
			if (month == 12) {
				month = 1;
				year++;
				day = 1;
			}
			else {
				month++;
				day = 1;
			}
		}
		else {
			if ((day + days) > dayinMonth) {
				day = ((day + days) - dayinMonth);
				if (month == 12) {
					month = 1;
					year++;
					days = 0;
				}
				else {
					month++;
					days = 0;
				}
			}
			else {
				day = day + days;
				days = 0;
			}

		}
	}

	return *this;
}

void date::print() const {
	std::cout << "Current date is: " << this->day << " / " << this->month << " / " << this->year << "\n";
}

date date::getCurrDate() {
	return date{ 2,2,2024 };
}

bool date::compare() const {
	auto dd{ (cache[0] - '0') * 10 + (cache[1] - '0') };
	auto mm{ (cache[3] - '0') * 10 + (cache[4] - '0') };
	auto yy{ ((cache[6] - '0') * 1000) + ((cache[7] - '0') * 100) + ((cache[8] - '0') * 10) + ((cache[9] - '0')) };
	if ((dd == this->day) && (mm == this->month) && (yy == this->year)) return true;
	return false;

	/*date curDate = date::getCurrDate();
	if ((curDate.d == d) && (curDate.m == m) && (curDate.y == y)) return true;
	return false;*/
}

void date::updateCache() {

	cache = "";
	if (this->day < 10) {
		cache.append("0");
	}
	cache.append(String::toString(this->day));
	cache.append("/");
	if (this->month < 10) {
		cache.append("0");
	}
	cache.append(String::toString(this->month));
	cache.append("/");
	if (this->year < 10) {
		cache.append("000");
	}
	else if (this->year < 100) {
		cache.append("00");
	}
	else if (this->year < 1000) {
		cache.append("0");
	}
	cache.append(String::toString(this->year));
}

String date::string_rep() {

	//cacheValid = this->compare();

	if (!cacheValid) {

		auto curDate{ date::getCurrDate() };
		this->day = curDate.day;
		this->month = curDate.month;
		this->year = curDate.year;

		updateCache();

		cacheValid = true;
		//std::cout << "Cache Miss\n";
		return cache;
	}
	//std::cout << "Cache Hit\n";
	return cache;
}

