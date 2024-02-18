#ifndef _FILE_HELPER_
#define _FILE_HELPER_

#include<fstream>
#include "string.h"

using utility::String;

namespace logging {

	class FileHelper {
		
	public:
		FileHelper(String name) : fName{name} , out{name.getRaw() , std::ios::app} {
			//std::cout << "4 ";
		}

		void writeLine(const String& log) {
			//std::cout << "5 ";
			out << log;
		}

	private :
		String fName{ "" };
		std::ofstream out{};
	}; 
}

#endif