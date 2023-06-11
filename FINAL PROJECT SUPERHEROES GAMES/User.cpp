#include "User.h"

User::User() :name(), surname(), email(), password() {}
User::User(const MyString& name, const MyString& surname, const MyString& email, const MyString& password) {
	setName(name);
	setSurname(surname);
	setEmail(email);
	setPassword(password);
}
void User::setName(const MyString& name) {
	if (name.length() == 0) {
		return;
	}
	MyString temp(name);
	if (isLower(temp[0])) {
		toUpper(temp[0]);
	}
	this->name = temp;
}
void User::setSurname(const MyString& surname) {
	if (surname.length() == 0) {
		return;
	}
	MyString temp(surname);
	if (isLower(temp[0])) {
		toUpper(temp[0]);
	}
	this->surname = temp;

}
void User::setEmail(const MyString& email) {
	this->email = email;

}
void  User::setPassword(const MyString& password) {
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

const MyString& User::getName()const {
	return name;
}
const MyString& User::getSurname()const {
	return surname;
}
const MyString& User::getEmail()const {
	return email;
}
const MyString& User::getPassword()const {
	return password;
}

bool User::logIn(const MyString& email, const  MyString& password, const MyString& filename)const {

	std::ifstream inFile(filename.c_str());
	if (!inFile)
	{
		std::cout << "Error: file could not be opened." << std::endl;
		return false;
	}
	char line[256];
	while (inFile.getline(line, 256))
	{
		int fieldNum = 0;
		char fields[4][50];
		fieldNum = extractFields(line, fields, 4);

		if (fieldNum == 4 && strcmp(fields[2], email.c_str()) == 0 && strcmp(fields[3], password.c_str()) == 0)
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

void User::seeInfo(const MyString& filename)const {
	std::ifstream inFile(filename.c_str());

	if (inFile) {
		if (filename == "admin.txt") {
			std::cout << "List of administrators:" << std::endl;
		}
		else if (filename == "player.txt") {
			std::cout << "List of players:" << std::endl;
		}

		char line[256];
		while (inFile.getline(line, 256)) {
			int fieldNum = 0;
			char fields[5][50];
			fieldNum = extractFields(line, fields, 5);

			if (fieldNum >= 2) {
				if (filename == "admin.txt") {
					std::cout << "Name of administrator: " << fields[0] << std::endl;
					std::cout << "Email of administrator: " << fields[2] << std::endl;
				}
				else if (filename == "player.txt") {
					std::cout << "Name of player: " << fields[0] << std::endl;
					std::cout << "Surname of player: " << fields[1] << std::endl;
					std::cout << "Email of player: " << fields[2] << std::endl;
					std::cout << "Password of player: " << fields[3] << std::endl;
					std::cout << "Money of player $: " << fields[4] << std::endl;
				}
				std::cout << std::endl;
			}
		}

		inFile.close();
	}
	else {
		std::cout << "Error opening the file." << std::endl;
	}
}
