#include "Utills.h"
#include <iostream>
#include<cstring>

//we don't make them static, because we want to use the in other cpp files.

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

int extractFields(const char* line, char fields[][50], int maxFields) {
	char* field = strtok(const_cast<char*>(line), ",");
	int fieldNum = 0;
	while (field != NULL && fieldNum < maxFields) {
		strcpy(fields[fieldNum], field);
		fieldNum++;
		field = strtok(NULL, ",");
	}
	return fieldNum;
}

void reverseString(char* str, int length) {
	int start = 0;
	int end = length - 1;
	while (start < end) {
		char temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}

MyString reverseBalance(int balance) {
	int n = 0, temp = balance;
	char balanceStr[50];
	while (temp != 0) {
		balanceStr[n++] = (temp % 10) + '0';
		temp /= 10;
	}
	balanceStr[n] = '\0';

	for (int i = 0, j = n - 1; i < j; i++, j--) {
		char temp = balanceStr[i];
		balanceStr[i] = balanceStr[j];
		balanceStr[j] = temp;
	}

	return MyString(balanceStr);
}

void showPowerType(unsigned power) {
	if (power == 0) {
		std::cout << "This superhero's power type is fire.:" << std::endl;
	}
	else if (power == 1) {
		std::cout << "This superhero's power type is water.:" << std::endl;
	}
	else if (power == 2) {
		std::cout << "This  superhero's power type is earth.:" << std::endl;
	}
	else {
		std::cout << "This superhero's has no valid power type.:" << std::endl;
	}
}

void showAttack(unsigned attackMode)
{
	if (attackMode == 0) {
		std::cout << "This superhero is set in defense mode." << std::endl;
	}
	else if (attackMode == 1) {
		std::cout << "This superhero is set in attacking mode." << std::endl;
	}
	else
	{
		std::cout << "This superhero is not set in any mode" << std::endl;
	}

}