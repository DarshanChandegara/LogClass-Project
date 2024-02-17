#include<iostream>
#include<thread>
#include "./include/log.h"
#include "./include/date.h"
#include "./include/string.h"
#include "./include/Exception.h"
#include<mutex>

using logging::Log;
using utility::date;
using exception::Exception;
using utility::String;

std::mutex m;

int main() {
	Log log;
	log.SetLogLevel(Log::Level::LevelWarning);
	/*std::thread t1{ &Log::Info , &log , "Fine!" };
	std::thread t2{ &Log::Warn  , &log,  "Carefull!" };
	std::thread t3{ &Log::Error , &log ,  "Stop!" };*/
	log.Info("Fine!" , 65 , "Extra" , 45.214);
	log.Warn("Carefull!" , "Message" , 4612 , 32.15);
	log.Error("Stop!");
	/*t1.join();
	t2.join();
	t3.join();*/
}