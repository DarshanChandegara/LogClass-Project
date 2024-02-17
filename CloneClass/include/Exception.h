#ifndef exce
#define exce

#include"./string.h"
using utility::String;


namespace exception {

	class Exception {
	

	public:
		Exception() : message{ "There is Some Error" } {}
		Exception(String s) : message{ s } {
		}

		String getMessage() const {
			return message;
		}

	private:
		String message;
	};
}

#endif