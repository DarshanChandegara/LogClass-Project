#ifndef date_1 
#define date_1 

#include "./string.h"
#include "./Exception.h"

using utility::String;
using exception::Exception;

namespace utility {

	class date {

	public:
		date(int dd, int mm, int yy) : day{ dd }, month{ mm }, year{ yy } {
			if (mm > 12) throw Exception{ "Months can not be greater than 12 \n" };

			auto check{ isLeapYear(yy) };
			auto month{ daysInMonth(mm, yy) };

			if (dd > month) throw Exception{ "Days are more than the respective Month" };

		}

		String string_rep();
		bool compare() const;

		static date getCurrDate();
		date& addYear(int years);
		date& addMonth(int months);
		date& addDay(int days);
		void print() const;
		void updateCache();

	private:
		int day;
		int month;
		int year;
		mutable bool cacheValid = false;
		mutable String cache = "12/12/1541";

		bool isLeapYear(int year) const;
		int daysInMonth(int m, int y) const;
	};
}

#endif
