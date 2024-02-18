#ifndef string1
#define string1 

#include<iostream>
#include<cstring>
#include<string.h>

namespace utility {

	class String {
	
	public:
		String(const char* string = "");
		String(const String& other);
		String(String&& other) noexcept;
		String& operator=(const String& other) noexcept;
		String& operator=(String&& other)noexcept;

		~String() {

		}

		char& operator[](unsigned int index);

		int length() const {
			return m_size;
		}

		String& append(const String& other);
		friend String operator+(const  String& first, const  String& second);
		static String toString(int num);
		String& to_lower() noexcept;
		String& to_upper() noexcept;

		char* getRaw() {
			char* raw = new char[m_size+1];
			memcpy(raw, buffer.get(), m_size);
			raw[m_size] = '\0';
			return raw;
		}

		friend std::ostream& operator<<(std::ostream& stream, const String& string) noexcept;

	private:
		//char* buffer{ nullptr };
		std::unique_ptr<char[]> buffer;
		unsigned int m_size{ 0 };
	};
}

#endif