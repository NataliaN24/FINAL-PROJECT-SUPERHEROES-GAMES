#include "Admin.h"
#include<iostream>
#include<cstring>
#include"Utills.h"
#include <sstream> 
#include <stdexcept> 
const int max = 1024;


Admin::Admin(const MyString& name, const MyString& surname, const MyString& email, const MyString& password) {

	setName(name);
	setSurname(surname);
	setEmail(email);
	setPassword(password);


}

void Admin::setName(const MyString& name) {
	if (name.length() == 0) {
		return;
	}
	MyString temp(name);
	if (isLower(temp[0])) {
		toUpper(temp[0]);
	}
	this->name = temp;
}


void Admin::setSurname(const MyString& surname) {
	if (surname.length() == 0) {
		return;
	}
	MyString temp(surname);
	if (isLower(temp[0])) {
		toUpper(temp[0]);
	}
	this->surname = temp;

}
void Admin::setEmail(const MyString& email) {
	this->email = email;

}
void  Admin::setPassword(const MyString& password) {
	bool has_upper = false;
	bool has_lower = false;
	bool has_digit = false;
	for (size_t i = 0; i < password.length(); ++i) {
		if (isupper(password[i])) {
			has_upper = true;
		}
		if (islower(password[i])) {
			has_lower = true;
		}
		if (isdigit(password[i])) {
			has_digit = true;
		}
	}
	if (has_upper && has_lower && has_digit) {
		this->password = password;

	}
	else {
		throw std::invalid_argument("Password must contain at least one uppercase letter, one lowercase letter, and one number.");

	}

}

const MyString& Admin::getName()const {
	return name;
}
const MyString& Admin::getSurname()const {
	return surname;
}
const MyString& Admin::getEmail()const {
	return email;
}
const MyString& Admin::getPassword()const {
	return password;
}


void Admin::signUp() {

	MyString name, surname, email, password;
	std::cout << "Enter your name: ";
	std::cin >> name;
	std::cout << "Enter your surname: ";
	std::cin >> surname;
	std::cout << "Enter your email: ";
	std::cin >> email;
	std::cout << "Enter your password: ";
	std::cin >> password;

	Admin admin(name, surname, email, password);
	storeInFile(admin, "admin.txt");

	//// Read in existing admins from file and check for duplicates
	//	std::ifstream inFile("admin.txt");
	//MyString existingEmail;
	//bool duplicateFound = false;

	//while (inFile >> existingEmail) {
	//	// Compare existing email to new email
	//	if (existingEmail == email) {
	//		duplicateFound = true;
	//		break;
	//	}
	//}
	//inFile.close();
	//// Add new admin if no duplicates found
	//if (!duplicateFound) {
	//	storeInFile(admin, "admin.txt");
	//	std::cout << "Admin added successfully\n";
	//}
	//else {
	//	std::cout << "Admin already exists\n";
	//}

}
bool  Admin::logIn() {

	std::cout << "Enter your email: ";
	char email[50];
	std::cin >> email;

	std::cout << "Enter your password: ";
	char password[50];
	std::cin >> password;

	std::ifstream inFile("admin.txt");
	if (inFile)
	{
		char line[256]; //include this in a separate function
		while (inFile.getline(line, 256))
		{
			char* field = strtok(line, ",");
			int fieldNum = 0;
			char fields[4][50];
			while (field != NULL && fieldNum < 4)
			{
				strcpy(fields[fieldNum], field);
				fieldNum++;
				field = strtok(NULL, ",");
			}
			if (fieldNum == 4 && strcmp(fields[2], email) == 0 && strcmp(fields[3], password) == 0)
			{
				std::cout << "Login successful!" << std::endl;
				inFile.close();
				return true;
			}
		}
		std::cout << "Incorrect email or password. Please try again." << std::endl;
		inFile.close();
		return false;
	}
	else
	{
		std::cout << "Error: admin.txt could not be opened." << std::endl;
		return false;
	}



}
void Admin::addAnotherAdmin() {
	signUp();
}
void Admin::seeInfoOfAdmins() {
	std::ifstream inFile("admin.txt");
	if (inFile) {
		std::cout << "List of administrators:" << std::endl;

		char line[256];
		while (inFile.getline(line, 256))
		{
			char* field = strtok(line, ",");
			int fieldNum = 0;
			char fields[4][50];
			while (field != NULL && fieldNum < 4)
			{
				strcpy(fields[fieldNum], field);
				fieldNum++;
				field = strtok(NULL, ",");
			}
			std::cout << "name od amdinistrator:" << fields[0] << "   email of administrators:" << " " << fields[2] << std::endl;
		}
		inFile.close();
	}
	else {
		std::cout << "Error opening this file." << std::endl;
	}

}

void storeInFile(const Admin& admins, const  char* filename) {
	std::ofstream file(filename, std::ios::app);
	if (!file.is_open()) {
		throw std::runtime_error("Unable to open file for reading.");

	}
	file << admins.getName() << "," << admins.getSurname() << "," << admins.getEmail() << "," << admins.getPassword() << std::endl;
	file.close();


}