#include "Utills.h"
#include <iostream>
#include<cstring>

bool isLower(char ch) { return ch >= 'a' && ch <= 'z'; }

bool isSymbol(char ch)
{
	return ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z';
}


void toUpper(char& ch)
{
	if (!isSymbol(ch))
		throw std::invalid_argument("The given character is not a letter");

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
	char balanceStr[50]{};//added new
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
unsigned extractBalance(const char* balanceStr) {
	unsigned balance = 0;
	for (size_t i = 0; i < strlen(balanceStr); i++) {
		balance = balance * 10 + (balanceStr[i] - '0');
	}
	return balance;
}


void updateFile(const MyString& inputFileName, const MyString& outputFileName, const MyString& name, unsigned money, int index) {
	try {
		std::ifstream infile(inputFileName.c_str());
		std::ofstream outfile(outputFileName.c_str());

		if (!infile || !outfile)
			throw std::runtime_error("Error file  could not be opened.");

		char line[256];
		while (infile.getline(line, 256)) {
			char fields[5][50];
			extractFields(line, fields, 5);

			if (strcmp(fields[0], name.c_str()) == 0) {
				// Update the money/balance field
				if (money == 0) {
					strcpy(fields[index], "0");
				}
				else {
					MyString reversedPointsStr = reverseBalance(money);
					strcpy(fields[index], reversedPointsStr.c_str());
				}
				//strcpy(fields[index], reverseBalance(money).c_str());
			}

			outfile << fields[0] << "," << fields[1] << "," << fields[2] << "," << fields[3] << "," << fields[4] << std::endl;
		}

		infile.close();
		outfile.close();


		if (remove(inputFileName.c_str()) != 0 || rename(outputFileName.c_str(), inputFileName.c_str()) != 0) {
			std::cout << "Error: Failed to update file." << std::endl;
		}


	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}

void updatePointsInFile(const MyString& inputFileName, const MyString& outputFileName, const MyString& name, unsigned points, int fieldNum, int fieldIndex) {
	std::ifstream infile(inputFileName.c_str());
	std::ofstream outfile(outputFileName.c_str());

	if (!infile || !outfile) {
		std::cerr << "Error: File could not be opened." << std::endl;
		return;
	}

	char line[256];
	while (infile.getline(line, 256)) {
		int currFieldNum = 0;
		char fields[7][50];
		currFieldNum = extractFields(line, fields, fieldNum);
		if (currFieldNum == fieldNum && strcmp(fields[fieldIndex], name.c_str()) == 0) {
			MyString reversedPointsStr = reverseBalance(points);
			strcpy(fields[4], reversedPointsStr.c_str());
		}
		for (int i = 0; i < currFieldNum; i++) {
			outfile << fields[i];
			if (i != currFieldNum - 1) {
				outfile << ",";
			}
		}
		outfile << std::endl;
	}

	infile.close();
	outfile.close();

	if (remove(inputFileName.c_str()) == 0 && rename(outputFileName.c_str(), inputFileName.c_str()) == 0) {
		std::cout << " " << std::endl;
	}
	else {
		std::cout << "Error: Failed to update file." << std::endl;
	}
}


unsigned getFieldValue(const MyString& filename, const MyString& name, int fieldIndex) {
	std::ifstream inFile(filename.c_str());
	if (!inFile) {
		std::cout << "Error: " << filename << " could not be opened." << std::endl;
		return 0;
	}

	char line[256];
	while (inFile.getline(line, 256)) {
		int fieldNum = 0;
		char fields[7][50];
		fieldNum = extractFields(line, fields, 7);

		if (fieldNum == 7 && strcmp(fields[0], name.c_str()) == 0) {
			inFile.close();
			return extractBalance(fields[fieldIndex]);
		}
	}

	std::cout << "Incorrect name. Please try again." << std::endl;
	inFile.close();
	return 0;
}