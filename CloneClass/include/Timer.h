#ifndef _TIMER_
#define _TIMER_

#include<iostream>
#include<string>
#include<chrono>

using namespace std::chrono;

namespace utility {
	class myTimer {
	public:
		myTimer() : m_startPoint{ high_resolution_clock::now()} {}
		~myTimer() {
			auto m_endPoint = high_resolution_clock::now();
			auto start = time_point_cast<milliseconds>(m_startPoint).time_since_epoch().count();
			auto end = time_point_cast<milliseconds>(m_endPoint).time_since_epoch().count();
			auto duration = end - start;

			std::cout << duration << " (Miliseconds)\n";
		}

	private:
		time_point<high_resolution_clock> m_startPoint;
	};
}

#endif