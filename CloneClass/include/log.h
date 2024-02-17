#ifndef log_1
#define log_1

#include "./date.h"
#include<mutex>
using utility::date;

extern std::mutex m;

namespace logging {
	
	class Log {
	public:
		enum class Level {
			LevelError = 0, LevelWarning, LevelInfo
		};

	public:
		Log() {
			m_LogLevel = Level::LevelInfo;
		}

		explicit Log(Level l) {
			m_LogLevel = l;
		}

		void SetLogLevel(Level level) {
			m_LogLevel = level;
		}

		Level getLogLevel() const {
			return m_LogLevel;
		}

		template<typename... Args>
		void Warn(const String& message , Args... args)const;

		template<typename... Args>
		void Error(const String& message, Args... args)const;

		template<typename... Args>
		void Info(const String& message, Args... args) const;

	private:
		Level m_LogLevel;
		mutable date m_date = date{ 30,1,2024 };

		void printArgs() const;

		template<typename T, typename... Args>
		void printArgs(T&& Arg, Args&&... args) const;
	};

	void Log::printArgs() const{
		std::cout << "\n";
	}

	template<typename T, typename... Args>
	void Log::printArgs(T&& Arg, Args&&... args) const {
		std::cout << Arg << " ";
		printArgs(args...);
	}

	template<typename... Args>
	void Log::Warn(const String& message , Args... args)const {
		std::lock_guard<std::mutex> l(m);
		if (m_LogLevel >= Level::LevelWarning) {
			std::cout << "Date: " << m_date.string_rep() << "  [Warning]: " << message << " " ;
			printArgs(args...);
		}
	}

	template<typename... Args>
	void Log::Error(const String& message, Args... args)const {
		std::lock_guard<std::mutex> l(m);
		if (m_LogLevel >= Level::LevelError) {
			std::cout << "Date: " << m_date.string_rep() << "  [Error]: " << message << " " ;
			printArgs(args...);
		}
	}

	template<typename... Args>
	void Log::Info(const String& message, Args... args) const {
		std::lock_guard<std::mutex> l(m);
		if (m_LogLevel >= Level::LevelInfo) {
			std::cout << "Date: " << m_date.string_rep() << "  [Info]: " << message << " ";
			printArgs(args...);
		}
	}
}

#endif