#ifndef _LOG_
#define _LOG_

#include "log.h"
using logging::Log;

namespace logging {

	auto myLogger = std::make_shared<Log>("System");

	std::shared_ptr<Log> default_logger() {
		return myLogger;
	}

	void set_default_logger(std::shared_ptr<Log> ptr) {
		myLogger = std::move(ptr);
	}

	String Log::showLevel(Log::Level l) const {
		switch (l) {
		case Level::LevelError:
			return "Error";

		case Level::LevelInfo:
			return "Info";

		case Level::LevelWarning:
			return "Warning";

		default: return "";
		}
	}

	template<typename... T>
	void Log::log(Log::Level l, const T& ...args) const {

		if (m_LogLevel >= l) {
			String str = "Date:- ";
			str.append(m_date.string_rep());
			str.append(" [");
			str.append(l_name);
			str.append("] ");
			str.append("[");
			str.append(showLevel(l));
			str.append("] ");

			logConsole(str);
			printArgs(args...);



			if (isDumpOnFile == true) {
				buffer.append(str);
				getString(args...);
				//std::cout << "1 ";
				bufferCount++;
				
				//std::cout << "2 ";
				if (bufferCount >= 5) {
					flush(buffer);
					buffer = "";
					bufferCount = 0;
				}
			}

		}
	}

	template<typename... Args>
	void Warn(const String& message, Args... args) {
		std::lock_guard<std::mutex> l(m);
		default_logger()->log(Log::Level::LevelWarning, message, args...);
	}

	template<typename... Args>
	void Error(const String& message, Args... args) {
		std::lock_guard<std::mutex> l(m);
		default_logger()->log(Log::Level::LevelError, message, args...);
	}

	template<typename... Args>
	void Info(const String& message, Args... args) {
		std::lock_guard<std::mutex> l(m);
		default_logger()->log(Log::Level::LevelInfo, message, args...);
	}

}


#endif 
