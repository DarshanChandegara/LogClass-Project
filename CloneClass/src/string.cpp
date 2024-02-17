#include<iostream>
#include<cstring>
#include "../include/string.h"
#include "../include/Exception.h"

using utility::String;
using exception::Exception;

String::String(const char* string) {
	//std::cout << "Default";
	m_size = static_cast<unsigned int>(strlen(string));
	//if (!buffer) delete[] buffer;
	try {
		//buffer = new char[m_size + 1];
		buffer = std::make_unique<char[]>(m_size + 1);
	}
	catch (std::bad_alloc) {
		throw Exception{ "Dynamic memory is not available \n" };
	}
	/*memcpy(buffer, string, m_size);
	buffer[m_size] = '\0';*/

	memcpy(buffer.get(), string, m_size);
	buffer.get()[m_size] = '\0';
}

String::String(const String& other) : m_size(other.m_size) {
	//std::cout << "Copy\n";
	try {
		//buffer = new char[other.m_size + 1];
		buffer = std::make_unique<char[]>(other.m_size + 1);
	}
	catch (std::bad_alloc) {
		throw Exception{ "Dynamic memory is not available \n" };
	}
	/*memcpy(buffer, other.buffer, other.m_size);
	buffer[other.m_size] = '\0';*/
	memcpy(buffer.get(), other.buffer.get(), other.m_size);
	buffer.get()[other.m_size] = '\0';
}

String::String(String&& other) noexcept {
	//std::cout << "Move\n";
	//delete[] buffer;

	buffer = std::move(other.buffer);
	m_size = other.m_size;

	other.buffer = nullptr;
	other.m_size = 0;
}

String& String::operator=(const String& other)noexcept {
	//std::cout << "Cpoy =\n";
	m_size = other.m_size;
	try {
		buffer = std::make_unique<char[]>(m_size + 1);
	}
	catch (std::bad_alloc) {
		throw Exception{ "Dynamic memory is not available \n" };
	}
	memcpy(buffer.get(), other.buffer.get(), m_size);

	return *this;
}

String& String::operator=(String&& other) noexcept
{

	//std::cout << "Move =\n";
	//delete[] buffer;

	buffer = std::move(other.buffer);
	m_size = other.m_size;

	other.buffer = nullptr;
	other.m_size = 0;

	return *this;
};

char& String::operator[](unsigned int index) {

	if (index >= m_size || index < 0) {
		throw Exception{ "Out of Bound Exception :: Invalid access from string" };
	}
	return buffer.get()[index];
}

String String::toString(int num) {
	if (num == 0) {
		auto str = std::make_unique<char[]>(2);
		str[0] = '0';
		str[1] = '\0';
		return String{ str.get() };
	}
	else {
		auto cnt{ 0 };
		auto tmp{ num };
		while (tmp > 0) {
			tmp = tmp / 10;
			cnt++;
		}

		auto index{ 0 };
		auto str = std::make_unique<char[]>(cnt + 1);
		while (index < cnt) {
			auto digit{ num % 10 };
			str.get()[index] = '0' + digit;
			index++;
			num /= 10;
		}
		str[cnt] = '\0';

		auto start{ 0 };
		auto end{ cnt - 1 };
		while (start < end) {
			auto temp = str.get()[start];
			str.get()[start] = str.get()[end];
			str.get()[end] = temp;

			start++;
			end--;
		}
		return String{ str.get() };
	}
}

String& String::append(const String& other) {
	auto len{ other.m_size };
	try {
		auto len = m_size + other.m_size;
		auto str = std::make_unique<char[]>(len + 1);
		memcpy(str.get(), buffer.get(), m_size);
		memcpy(str.get() + m_size, other.buffer.get(), other.m_size);
		str.get()[len] = '\0';
		this->m_size = len;
		this->buffer = std::move(str);
		return *this;
	}
	catch (std::bad_alloc) {
		throw "Dynamic memory is not available \n";
	}

	return *this;
}

String utility::operator+(const String& first, const String& second) {
	auto len{ first.m_size };
	String tmp;
	try {
		auto len{ first.m_size };
		auto str = std::make_unique<char[]>(second.m_size + len + 1);
		memcpy(str.get(), first.buffer.get(), first.m_size);
		memcpy(str.get() + first.m_size, second.buffer.get(), second.m_size);
		str.get()[first.m_size + second.m_size] = '\0';
		String tmp{ str.get() };
		return tmp;
	}
	catch (std::bad_alloc) {
		throw "Dynamic memory is not available \n";
	}

	return tmp;
}

String& String::to_lower() noexcept {
	// 65 - 90
	for (auto i{ 0u }; i < m_size; i++) {
		if ((buffer.get()[i] >= 65) && (buffer.get()[i] <= 90))
			buffer.get()[i] += 32;
	}
	return *this;
}

String& String::to_upper() noexcept {
	// 97 - 122
	for (auto i{ 0u }; i < m_size; i++) {
		if ((buffer.get()[i] >= 97) && (buffer.get()[i] <= 122))
			buffer.get()[i] -= 32;
	}
	return *this;
}

std::ostream& utility::operator<<(std::ostream& stream, const String& string) noexcept
{
	stream << string.String::buffer.get();
	return stream;
}