#include<iostream>
#include<thread>
#include "./include/log.h"
#include "./include/Exception.h"
#include "./include/logger.h"
#include "./include/Timer.h"
#include<mutex>

using logging::Log;
//using logging::Log;
using exception::Exception;
using utility::myTimer;

std::mutex m;

int main() {
	//Log log{"Darshan"};
	//log.SetLogLevel(Log::Level::LevelWarning);
	/*std::thread t1{ &Log::Info , &log , "Fine!" };
	std::thread t2{ &Log::Warn  , &log,  "Carefull!" };
	std::thread t3{ &Log::Error , &log ,  "Stop!" };*/
	myTimer t1;
	logging::Info("Fine!", "65", "Extra", "45.214");
	logging::Warn("Carefull!", "Message", "4612", "32.15");
	logging::Error("Stop!");

	logging::default_logger()->setFileFlag(true);
	auto nLog = std::make_shared<Log>("Deep");
	//logging::set_default_logger(nLog);
	logging::Warn("This is new logger");
	logging::Info("This is new Info");
	logging::Info("This is new Info");
	nLog->log(Log::Level::LevelError, "This is Error");

	auto logger = std::make_shared<Log>("Darshan" , "error.txt");
	logger->setFileFlag(true);
	logger->log(Log::Level::LevelWarning, "This is new warning");
	logger->log(Log::Level::LevelInfo, "This is new Info");
	logger->log(Log::Level::LevelWarning, "This is new warning");
	logger->log(Log::Level::LevelError, "This is new Error");
	logger->log(Log::Level::LevelWarning, "This is new warning");
	logger->log(Log::Level::LevelWarning, "This is new warning");
	//logging::default_logger()->flush();
	/*t1.join();
	t2.join();
	t3.join();*/
}