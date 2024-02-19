#ifndef log_1
#define log_1

#include "./date.h"
#include "fileHelper.h"
#include<vector>
#include<mutex>
using utility::date;
using logging::FileHelper;

extern std::mutex m;

namespace logging {
	
	class Log {
	public:
		enum class Level {
			LevelError = 0, LevelWarning, LevelInfo
		};

		explicit Log(const String& s) : l_name{s} , m_LogLevel { Level::LevelInfo } {}
		explicit Log(const String& s, Level l) : l_name{ s }, m_LogLevel{ l } {}
		explicit Log(const String& s, String name) : l_name{ s }, fName{ name }, m_LogLevel{ Level::LevelInfo } {
			isDumpOnFile = true;
		}
		
		void SetLogLevel(Level level) {
			m_LogLevel = level;
		}

		Level getLogLevel() const {
			return this->m_LogLevel;
		}

		void setFileFlag(bool flag) {
			isDumpOnFile = flag;
		}

		template<typename... T>
		void log(Log::Level, const T& ...args) const;

		void getString() const {
			buffer.append("\n");
			//return buffer;
		}

		template<typename T, typename... Args>
		void getString(T Arg, Args... args) const {

			buffer.append(Arg);
			buffer.append(" ");
			getString(args...);
			//return buffer;
		}

		void flush(const String&) const;
		mutable int bufferCount{ 0 };

		~Log() {
			if (isDumpOnFile) {
				flush(buffer);
				buffer = "";
				bufferCount = 0;
			}
		}

	private:
		String l_name;
		Level m_LogLevel;
		bool isDumpOnFile = false;
		String fName{"default.txt"};
		mutable String buffer{ "" };
		mutable date m_date = date{ 30,1,2024 };

		
		void printArgs() const;

		template<typename T, typename... Args>
		void printArgs(T&& Arg, Args&&... args) const;

		String showLevel(Level) const ;
		void logConsole(String msg)const;
	};

	void Log::logConsole(String msg) const {
		std::cout << msg;
	}

	void Log::printArgs() const{
		std::cout << "\n";
	}

	template<typename T, typename... Args>
	void Log::printArgs(T&& Arg, Args&&... args) const {
		std::cout << Arg << " ";
		printArgs(args...);
	}

	void Log::flush(const String& log) const {
		//std::cout << "3 ";
		FileHelper f{ fName };
		f.writeLine(log);
	}
}

#endif