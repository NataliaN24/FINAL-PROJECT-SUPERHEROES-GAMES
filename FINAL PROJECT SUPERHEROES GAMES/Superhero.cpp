#include "Superhero.h"
#include"Utills.h"

Superhero::Superhero(const MyString& name, const MyString& surname, const MyString& nickname, const PowerType& powertype, unsigned power, unsigned purchase, bool attack_mode) {

	setName(name);
	setSurname(surname);
	setNickname(nickname);
	setPowerType(powertype);
	setPower(power);
	setPurchasePrice(purchase);
	setAttackMode(attack_mode);

}


void Superhero::setPowerType(const PowerType& powertype) {
	this->powerType = powertype;
}
void  Superhero::setPower(unsigned power) {
	this->power = power;

}
void Superhero::setPurchasePrice(unsigned purchase) {
	this->purchase = purchase;
}
void Superhero::setAttackMode(bool attack_mode) {
	this->attackMode = attack_mode;

}

void Superhero::setName(const MyString& name) {
	if (name.length() == 0) {
		return;
	}
	MyString temp(name);
	if (isLower(temp[0])) {
		toUpper(temp[0]);
	}
	this->name = temp;
}

void Superhero::setSurname(const MyString& surname) {
	if (surname.length() == 0) {
		return;
	}
	MyString temp(surname);
	if (isLower(temp[0])) {
		toUpper(temp[0]);
	}
	this->surname = temp;

}
void Superhero::setNickname(const MyString& nickname) {
	this->nickname = nickname;

}

const  MyString& Superhero::getName()const {
	return name;
}
const MyString& Superhero::getSurname()const {
	return surname;
}
const MyString& Superhero::getNickname()const {
	return nickname;
}

const Superhero::PowerType& Superhero::getPowerType() const {
	return powerType;
}

unsigned Superhero::getPower()const {
	return power;

}
unsigned Superhero::getPurchasePrice()const {
	return purchase;

}
bool Superhero::getAttackMode()const {
	return attackMode;
}

void storeInFileSuperheroes(const Superhero& superheroes, const  char* filename) {
	std::ofstream file(filename, std::ios::app);
	if (!file.is_open()) {
		throw std::runtime_error("Unable to open file for reading.");

	}
	file << superheroes.getName() << "," << superheroes.getSurname() << "," << superheroes.getNickname() << "," << superheroes.getPowerType() << ","
		<< superheroes.getPower() << "," << superheroes.getPurchasePrice() << "," << superheroes.getAttackMode() << std::endl;
	file.close();
}

void  Superhero::seeInfoOfSuperheroes() {

	std::ifstream inFile("superheroes.txt");

	if (inFile) {
		std::cout << "List of superheroes:" << std::endl;

		char line[256];
		while (inFile.getline(line, 256)) {
			int fieldNum = 0;
			char fields[7][50];
			fieldNum = extractFields(line, fields, 7);

			if (fieldNum >= 2) {
				std::cout << "Name of superhero: " << fields[0] << std::endl;
				std::cout << "Surname of superhero: " << fields[1] << std::endl;
				std::cout << "Nickname of superhero: " << fields[2] << std::endl;
				std::cout << "Power-type (fire:0,water:1,earth:2) " << fields[3] << std::endl;
				std::cout << "Power: " << fields[4] << std::endl;
				std::cout << "Price: " << fields[5] << std::endl;
				std::cout << "Attack-mode: " << fields[6] << std::endl;

				std::cout << std::endl;
			}
		}

		inFile.close();
	}
	else {
		std::cout << "Error opening the file." << std::endl;
	}

} //DONE

Superhero::PowerType readPowertypefrominput(MyString input) {

	if (input == "fire") {
		return Superhero::fire;
	}
	else if (input == "water") {
		return Superhero::water;
	}
	else
		return Superhero::earth;
}

unsigned Superhero::showPriceOfSuperhero() {  //DONE

	std::cout << "Enter the name of superhero to see its price: " << std::endl;
	char name[50];
	std::cin >> name;


	std::ifstream inFile("superheroes.txt");
	if (!inFile)
	{
		std::cout << "Error: superheroes.txt could not be opened." << std::endl;
		return false;
	}

	char line[256];
	while (inFile.getline(line, 256))
	{
		int fieldNum = 0;
		char fields[7][50];
		fieldNum = extractFields(line, fields, 7);

		if (fieldNum == 7 && strcmp(fields[0], name) == 0)
		{
			inFile.close();
			unsigned balance = 0;
			for (size_t i = 0; i < strlen(fields[5]); i++) {
				balance = balance * 10 + (fields[5][i] - '0');
			}
			return balance;
		}
	}

	std::cout << "Incorrect name. Please try again." << std::endl;
	inFile.close();
	return 0;
}

unsigned  Superhero::getPowerTypeOfSuperhero(const char* name)
{

	std::ifstream inFile("purchased_superheroes.txt");
	if (!inFile)
	{
		std::cout << "Error: purchased_superheroes.txt could not be opened." << std::endl;
		return false;
	}

	char line[256];
	while (inFile.getline(line, 256))
	{
		int fieldNum = 0;
		char fields[7][50];
		fieldNum = extractFields(line, fields, 7);

		if (fieldNum == 7 && strcmp(fields[0], name) == 0)
		{
			inFile.close();
			unsigned powertype = 0;
			for (size_t i = 0; i < strlen(fields[3]); i++) {
				powertype = powertype * 10 + (fields[3][i] - '0');
			}
			return powertype;
		}
	}

	std::cout << "Superhero not found. Please try again." << std::endl;
	inFile.close();
	return Superhero::none;
}

unsigned Superhero::showPointsOfSuperhero(const char* name) {


	std::ifstream inFile("purchased_superheroes.txt");
	if (!inFile)
	{
		std::cout << "Error: purchased_superheroes.txt could not be opened." << std::endl;
		return false;
	}

	char line[256];
	while (inFile.getline(line, 256))
	{
		int fieldNum = 0;
		char fields[7][50];
		fieldNum = extractFields(line, fields, 7);

		if (fieldNum == 7 && strcmp(fields[0], name) == 0)
		{
			inFile.close();
			unsigned points = 0;
			for (size_t i = 0; i < strlen(fields[4]); i++) {
				points = points * 10 + (fields[4][i] - '0');
			}
			return points;
		}
	}
	std::cout << "Incorrect name. Please try again." << std::endl;
	inFile.close();
	return 0;
}

void Superhero::storeAttackMode(const char* name, unsigned input) {
	std::ifstream infile("purchased_superheroes.txt");
	std::ofstream outfile("temp.txt");
	if (!infile.is_open()) {
		std::cerr << "Error: purchased_superheroes.txt could not be opened." << std::endl;
		return;
	}
	if (!outfile.is_open()) {
		std::cerr << "Error: temp.txt could not be created." << std::endl;
		infile.close();
		return;
	}

	char line[256];
	while (infile.getline(line, 256)) {
		char fields[7][50];
		int fieldNum = extractFields(line, fields, 7);

		if (fieldNum == 7 && strcmp(fields[0], name) == 0) {
			if (input == 0) {
				strcpy(fields[6], "0");
			}
			else {
				MyString reversedPointsStr = reverseBalance(input);
				strcpy(fields[6], reversedPointsStr.c_str());
			}
		}

		for (int i = 0; i < fieldNum; i++) {
			outfile << fields[i];
			if (i < fieldNum - 1) {
				outfile << ",";
			}
		}
		outfile << std::endl;
	}

	infile.close();
	outfile.close();
	remove("purchased_superheroes.txt");
	rename("temp.txt", "purchased_superheroes.txt");
}

unsigned Superhero::showAttackMode(const char* name) {
	std::ifstream inFile("purchased_superheroes.txt");
	if (inFile) {
		char line[256];
		while (inFile.getline(line, 256)) {
			char fields[7][50];
			int fieldNum = extractFields(line, fields, 7);

			if (fieldNum == 7 && strcmp(fields[0], name) == 0) {
				inFile.close();
				unsigned points = atoi(fields[6]);
				/*unsigned points = 0;
				for (size_t i = 0; i < strlen(fields[6]); i++) {
					points = points * 10 + (fields[6][i] - '0');
				}*/
				return points;
			}
		}
		std::cout << "Incorrect name. Please try again." << std::endl;
		inFile.close();
		return 0;
	}
	else {
		std::cout << "Error: purchased_superheroes.txt could not be opened." << std::endl;
		return 0;
	}
}


MyString convertToPointsStr(int input) {
	int n = 0, temp = input;
	char pointsStr[50];
	while (temp != 0) {
		pointsStr[n++] = (temp % 10) + '0';
		temp /= 10;
	}
	pointsStr[n] = '\0';
	for (int i = 0, j = n - 1; i < j; i++, j--) {
		char temp = pointsStr[i];
		pointsStr[i] = pointsStr[j];
		pointsStr[j] = temp;
	}
	return MyString(pointsStr);
}


//if (fieldNum == 7 && strcmp(fields[0], name) == 0) {
//	if (input == 0) {
//		strcpy(fields[6], "0");
//	}
//	else {
//		std::string pointsStr = convertToPointsStr(input);
//		strcpy(fields[6], pointsStr.c_str());
//	}
//}
