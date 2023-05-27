#pragma once
#include <iostream>
#include<cstring>
#pragma warning(disable:4996)

class MyString
{
	char* _data;
	size_t _length;

	void copyFrom(const MyString& data);
	void free();
	//include the move constructor  IMPORTANT 
	explicit MyString(size_t capacity);
public:

	MyString() = default;
	MyString(const char* data);
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);
	~MyString();

	MyString(MyString&& other) noexcept;
	MyString& operator=(MyString&& other) noexcept;

	size_t length() const;
	MyString& operator+=(const MyString& other);

	MyString substr(size_t begin, size_t howMany) const;

	char& operator[](size_t index);
	char operator[](size_t index) const;
	//MyString& operator+=(char c);
	const char* c_str() const;
	//MyString getline(std::istream& is);
	//MyString mygetline(std::istream& is, char delim = '\n');
	//MyString  mygetline(std::istream& is, char delim);
	void clear();
	friend MyString operator+(const MyString& lhs, const MyString& rhs);
	friend std::istream& operator>>(std::istream&, MyString& str);
};

std::ostream& operator<<(std::ostream& os, const MyString& str);

bool operator<(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);
//std::istream& mygetline(std::istream& is, MyString& str);