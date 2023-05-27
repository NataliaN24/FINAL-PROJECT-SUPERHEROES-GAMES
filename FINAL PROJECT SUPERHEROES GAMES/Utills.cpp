#include <iostream>
#include"Utills.h"
bool isLower(char ch) { return ch >= 'a' && ch <= 'z'; }

bool isSymbol(char ch)
{
	return ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z';
}

//void toUpper(char* str)
//{
//	if (str == nullptr)
//		throw std::invalid_argument("The given string does not exist");
//
//	static int diff = 'a' - 'A';
//	while (*str)
//	{
//		if (!isSymbol(*str))
//			throw std::bad_cast();
//		if (isLower(*str))
//			*str = *str - diff;
//		str++;
//	}
//}
void toUpper(char& ch)
{
	if (!isSymbol(ch))
		throw std::invalid_argument("The given character is not a letter");

	/*static int diff = 'a' - 'A';
	if (isLower(ch))
		ch = ch - diff;*/
	if (isLower(ch)) {
		ch = ch - ('a' - 'A');
	}
}

unsigned charToDigit(char ch)
{
	if (ch < '0' || ch > '9')
		throw std::bad_cast();

	return ch - '0';
}

unsigned convertToNumber(const char* str)
{
	if (!str)
		throw std::invalid_argument("The given string does not exist");

	unsigned result = 0;
	while (*str)
	{
		result *= 10;
		result += charToDigit(*str);
		str++;
	}
	return result;
}