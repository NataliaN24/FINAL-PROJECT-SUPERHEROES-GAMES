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