//#include <iostream>
//#include "../include/log.h"
//#include"../include/date.h"
//#include<mutex>
//
//using utility::date;
//using logging::Log;
//
//extern std::mutex m;
//
//void Log::Warn(const String& message)const {
//	std::lock_guard<std::mutex> l(m);
//	if (m_LogLevel >= Level::LevelWarning)
//		std::cout << "[Warning]: " << message << " " << " Date: " << m_date.string_rep() << std::endl;
//}
//
//void Log::Error(const String& message)const {
//	std::lock_guard<std::mutex> l(m);
//	if (m_LogLevel >= Level::LevelError)
//		std::cout << "[Error]: " << message << " " << " Date: " << m_date.string_rep() << std::endl;
//}
//
//void Log::Info(const String& message) const {
//	std::lock_guard<std::mutex> l(m);
//	if (m_LogLevel >= Level::LevelInfo)
//		std::cout << "[Info]: " << message << " " << " Date: " << m_date.string_rep() << std::endl;
//}
