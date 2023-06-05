#include "Admin.h"
#include<iostream>
#include<cstring>
#include"Utills.h"
#include <sstream> 
#include <stdexcept> 

Admin::Admin(const MyString& name, const MyString& surname, const MyString& email, const MyString& password) {

	setName(name);
	setSurname(surname);
	setEmail(email);
	setPassword(password);

}

void Admin::setName(const MyString& name) {
	if (name.length() == 0)
	{
		return;
	}
	MyString temp(name);
	if (isLower(temp[0]))
	{
		toUpper(temp[0]);
	}
	this->name = temp;
}

void Admin::setSurname(const MyString& surname) {
	if (surname.length() == 0)
	{
		return;
	}
	MyString temp(surname);
	if (isLower(temp[0]))
	{
		toUpper(temp[0]);
	}
	this->surname = temp;
}

void Admin::setEmail(const MyString& email)
{
	this->email = email;
}

void  Admin::setPassword(const MyString& password)
{
	bool has_upper = false;
	bool has_lower = false;
	bool has_digit = false;
	for (size_t i = 0; i < password.length(); ++i)
	{
		if (isupper(password[i]))
		{
			has_upper = true;
		}
		if (islower(password[i]))
		{
			has_lower = true;
		}
		if (isdigit(password[i]))
		{
			has_digit = true;
		}
	}
	if (has_upper && has_lower && has_digit)
	{
		this->password = password;

	}
	else
	{
		throw std::invalid_argument("Password must contain at least one uppercase letter, one lowercase letter, and one number.");
	}

}

const MyString& Admin::getName()const
{
	return name;
}
const MyString& Admin::getSurname()const
{
	return surname;
}
const MyString& Admin::getEmail()const
{
	return email;
}
const MyString& Admin::getPassword()const
{
	return password;
}

void Admin::signUp()const
{
	MyString name, surname, email, password;
	std::cout << "Enter admin name: ";
	std::cin >> name;
	std::cout << "Enter admin surname: ";
	std::cin >> surname;
	std::cout << "Enter admin email: ";
	std::cin >> email;
	std::cout << "Enter admin password(Password must contatin at least one upper_case,one lower_case,one number or it will be invalid): ";
	std::cin >> password;

	Admin admin(name, surname, email, password);
	storeInFile(admin, "admin.txt");
}

void Admin::addAnotherAdmin()const {
	signUp();
}


bool Admin::logIn()const
{
	std::cout << "Enter your email: ";
	//char email[50];
	MyString email;
	std::cin >> email;

	std::cout << "Enter your password: ";
	//char password[50];
	MyString password;
	std::cin >> password;

	std::ifstream inFile("admin.txt");
	if (!inFile)
	{
		std::cout << "Error: admin.txt could not be opened." << std::endl;
		return false;
	}

	char line[256];
	while (inFile.getline(line, 256))
	{
		int fieldNum = 0;
		char fields[4][50];
		fieldNum = extractFields(line, fields, 4);  // Update fieldNum with the number of fields extracted

		if (fieldNum == 4 && strcmp(fields[2], email.c_str()) == 0 && strcmp(fields[3], password.c_str()) == 0)
		{
			std::cout << "Login successful!" << std::endl;
			std::cout << std::endl;
			inFile.close();
			return true;
		}
	}

	std::cout << "Incorrect email or password. Please try again." << std::endl;
	inFile.close();
	return false;
}//DONE


void Admin::seeInfoOfAdmins()const {
	std::ifstream inFile("admin.txt");

	if (inFile) {
		std::cout << "List of administrators:" << std::endl;

		char line[256];
		while (inFile.getline(line, 256)) {
			int fieldNum = 0;
			char fields[4][50];
			fieldNum = extractFields(line, fields, 4);

			if (fieldNum >= 2) {
				std::cout << "Name of administrator: " << fields[0] << std::endl;
				std::cout << "Email of administrator: " << fields[2] << std::endl;
				std::cout << std::endl;
			}
		}

		inFile.close();
	}
	else {
		std::cout << "Error opening the file." << std::endl;
	}
}

void storeInFile(const Admin& admins, const  MyString& filename)
{
	std::ofstream file(filename.c_str(), std::ios::app);
	if (!file.is_open())
	{
		throw std::runtime_error("Unable to open file for reading.");

	}
	file << admins.getName() << "," << admins.getSurname() << "," << admins.getEmail() << "," << admins.getPassword() << std::endl;
	file.close();
}


Superhero getSuperheroDetails() {
	std::cout << std::endl;
	std::cout << "Name of superhero:" << std::endl;
	MyString name;
	std::cin >> name;

	std::cout << "Surname of superhero:" << std::endl;
	MyString surname;
	std::cin >> surname;


	std::cout << "Nickname of superhero:" << std::endl;
	MyString nickname;
	std::cin >> nickname;

	std::cout << "Power type:FIRE,WATER,EARTH:" << std::endl;
	MyString pwt;
	std::cin >> pwt;


	std::cout << "Power points of superhero:" << std::endl;
	unsigned power;
	std::cin >> power;


	std::cout << "Purchase price $:" << std::endl;
	unsigned purchase;
	std::cin >> purchase;


	std::cout << "Attack mode(0 in defense mode, 1 in attack mode):" << std::endl;
	bool sold;
	std::cin >> sold;


	Superhero::PowerType power_type;
	if (pwt == "fire") {
		power_type = Superhero::PowerType::fire;
	}
	else if (pwt == "water") {
		power_type = Superhero::PowerType::water;
	}
	else {
		power_type = Superhero::PowerType::earth;
	}

	return Superhero(name, surname, nickname, power_type, power, purchase, sold);
}

void addSuperhero1(const  Superhero& superhero) {
	storeInFileSuperheroes(superhero, "superheroes.txt");
}

void addSuperheroes3(int numSuperheroes) {
	for (int i = 0; i < numSuperheroes; i++) {
		Superhero superhero = getSuperheroDetails();
		addSuperhero1(superhero);
	}
}

Superhero& Admin::addSuperhero() {
	std::ifstream infile("superheroes.txt");
	bool emptyfile = infile.peek() == std::ifstream::traits_type::eof();

	if (emptyfile) {
		addSuperheroes3(3);
	}

	Superhero superhero = getSuperheroDetails();
	addSuperhero1(superhero);

	Superhero* superheroes = new Superhero(superhero);
	return *superheroes;
}//DONE


Player& Admin::addPlayers(const MyString& name, const  MyString& surname, const  MyString& email, const MyString& password, const  unsigned int money)const { //DONE
	Player* player = new Player(name, surname, email, password, money);
	storeInFilePlayers(*player, "player.txt");
	return *player;
}

void Admin::seeInfoOfPlayers()const { //DONE
	Player player;
	player.seeInfo();

}

void Admin::deletePlayer(const MyString& email, const MyString& password, const MyString& playerName) {
	Player player;
	player.deletePlayerProfile(email, password, playerName);
}

void Admin::seeInfoOfSoldSuperheroes()const {
	std::ifstream inFile("purchased_superheroes.txt");
	if (inFile) {
		std::cout << "List of sold superheroes:" << std::endl;

		char line[256];
		while (inFile.getline(line, 256))
		{

			int fieldNum = 0;
			char fields[7][50];
			fieldNum = extractFields(line, fields, 7);
			std::cout << "Name of superhero :" << fields[0] << std::endl;
			std::cout << "Surname of superhero:" << fields[1] << std::endl;
			std::cout << "Nickname:" << fields[2] << std::endl;
			std::cout << "Power type(0-fire,1-water,2-earth):" << fields[3] << std::endl;
			std::cout << "Points:" << fields[4] << std::endl;
			std::cout << "Price :" << fields[5] << "$" << std::endl;
			std::cout << "Attack mode(0-deffensive,1-attacking):" << fields[6] << std::endl;
			std::cout << std::endl;
		}
		inFile.close();
	}
	else {
		std::cout << "Error opening this file." << std::endl;
	}
}
