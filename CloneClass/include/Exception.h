#ifndef exce
#define exce

#include"./string.h"
#include<string>
//using utility::String;


namespace exception {

	class Exception {
	

	public:
		Exception() : message{ "There is Some Error" } {}
		Exception(std::string s) : message{ s } {
		}

		std::string getMessage() const {
			return message;
		}

	private:
		std::string message;
	};
}

#endif