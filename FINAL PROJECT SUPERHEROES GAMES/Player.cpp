#include "Player.h"
#include"Utills.h"


Player::Player(const MyString& name, const MyString& surname, const MyString& email, const MyString& password, unsigned int money) {

	setName(name);
	setSurname(surname);
	setEmail(email);
	setPassword(password);
	setMoney(money);

}

void Player::setName(const MyString& name) {
	if (name.length() == 0) {
		return;
	}
	MyString temp(name);
	if (isLower(temp[0])) {
		toUpper(temp[0]);
	}
	this->name = temp;
}
void Player::setSurname(const MyString& surname) {
	if (surname.length() == 0) {
		return;
	}
	MyString temp(surname);
	if (isLower(temp[0])) {
		toUpper(temp[0]);
	}
	this->surname = temp;

}
void Player::setEmail(const MyString& email) {
	this->email = email;

}
void  Player::setPassword(const MyString& password) {
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
void Player::setMoney(unsigned int money) {
	this->money = money;
}

const MyString& Player::getName()const {
	return name;
}
const MyString& Player::getSurname()const {
	return surname;
}
const MyString& Player::getEmail()const {
	return email;
}
const MyString& Player::getPassword()const {
	return password;
}
const unsigned int Player::getMoney()const {
	return money;
}

void storeInFilePlayers(const Player& players, const MyString& filename) {

	std::ofstream file(filename.c_str(), std::ios::app);
	if (!file.is_open()) {
		throw std::runtime_error("Unable to open file for reading.");

	}
	file << players.getName() << "," << players.getSurname() << "," << players.getEmail() << "," << players.getPassword() << "," << players.getMoney() << std::endl;
	file.close();


}
bool Player::logIn(const MyString& email, const MyString& password)const {

	std::ifstream inFile("player.txt");
	if (!inFile)
	{
		std::cout << "Error: player.txt could not be opened." << std::endl;
		return false;
	}
	char line[256];
	while (inFile.getline(line, 256))
	{
		int fieldNum = 0;
		char fields[5][50];
		fieldNum = extractFields(line, fields, 5);

		if (fieldNum == 5 && strcmp(fields[2], email.c_str()) == 0 && strcmp(fields[3], password.c_str()) == 0)
		{
			std::cout << "Login successful!" << std::endl;
			inFile.close();
			return true;
		}
	}
	std::cout << "Incorrect email or password. Please try again." << std::endl;
	inFile.close();
	return false;
}//DONE
void Player::deleteFromPurchase(const MyString& name) const {
	std::cout << "Enter the name of superhero of the player that you want to delete its profile:" << std::endl;
	MyString superheroName;
	std::cin >> superheroName;
	std::ifstream inFile("purchase.txt");
	if (inFile) {
		std::ofstream tempFile("temp.txt");
		if (tempFile) {
			bool deleted = false;
			char line[256];
			while (inFile.getline(line, 256)) {
				int fieldNum = 0;
				char fields[5][50];
				fieldNum = extractFields(line, fields, 5);
				if (fieldNum == 5 && strcmp(fields[0], name.c_str()) == 0 && strcmp(fields[2], superheroName.c_str()) == 0) {
					deleted = true;
					continue;
				}
				tempFile << fields[0] << "," << fields[1] << "," << fields[2] << "," << fields[3] << "," << fields[4] << std::endl;
			}
			inFile.close();
			tempFile.close();
			if (deleted) {
				remove("purchase.txt");
				rename("temp.txt", "purchase.txt");
				std::cout << "Player with name " << name << " has been deleted." << std::endl;
			}
			else {
				std::cout << "Incorrect  name . Please try again." << std::endl;
				remove("temp.txt");
			}
		}
		else {
			std::cout << "Error: temp.txt could not be opened." << std::endl;
		}
	}
	else {
		std::cout << "Error: purchase.txt could not be opened." << std::endl;
	}


}
void Player::deletePlayerProfile(const MyString& email, const MyString& password, const MyString& name)const
{

	bool HasPurchased = checkIfPlayerhasPurchased(name.c_str());
	if (HasPurchased) {
		deleteFromPurchase(name.c_str());
		deleteProfile(email.c_str(), password.c_str());
	}
	else {
		deleteProfile(email.c_str(), password.c_str());
	}

}
void Player::deleteProfile(const MyString& email, const MyString& password)const {

	std::ifstream inFile("player.txt");
	if (inFile) {
		std::ofstream tempFile("temp.txt");
		if (tempFile) {
			bool deleted = false;
			char line[256];
			while (inFile.getline(line, 256)) {
				int fieldNum = 0;
				char fields[5][50];
				fieldNum = extractFields(line, fields, 5);
				if (fieldNum == 5 && strcmp(fields[2], email.c_str()) == 0 && strcmp(fields[3], password.c_str()) == 0) {
					deleted = true;
					continue;
				}
				tempFile << fields[0] << "," << fields[1] << "," << fields[2] << "," << fields[3] << "," << fields[4] << std::endl;
			}
			inFile.close();
			tempFile.close();
			if (deleted) {
				remove("player.txt");
				rename("temp.txt", "player.txt");
				std::cout << "Player with email " << email << " has been deleted." << std::endl;
			}
			else {
				std::cout << "Incorrect email or password. Please try again." << std::endl;
				remove("temp.txt");
			}
		}
		else {
			std::cout << "Error: temp.txt could not be opened." << std::endl;
		}
	}
	else {
		std::cout << "Error: player.txt could not be opened." << std::endl;
	}
}//DONE
void Player::seeInfo() { //DONE

	std::ifstream inFile("player.txt");

	if (inFile) {
		std::cout << "List of players:" << std::endl;

		char line[256];
		while (inFile.getline(line, 256)) {
			int fieldNum = 0;
			char fields[5][50];
			fieldNum = extractFields(line, fields, 5);

			if (fieldNum >= 2) {
				std::cout << "Name of player: " << fields[0] << std::endl;
				std::cout << "Surname of player: " << fields[1] << std::endl;
				std::cout << "Email of player: " << fields[2] << std::endl;
				std::cout << "Password of player: " << fields[3] << std::endl;
				std::cout << "Money of player $: " << fields[4] << std::endl;
				std::cout << std::endl;
			}
		}
		inFile.close();
	}
	else {
		std::cout << "Error opening the file." << std::endl;
	}

}
void Player::seeInfoByPlayers() {//this will be seen just by players 
	std::ifstream inFile("player.txt");

	if (inFile) {
		std::cout << "List of players:" << std::endl;

		char line[256];
		while (inFile.getline(line, 256)) {
			int fieldNum = 0;
			char fields[5][50];
			fieldNum = extractFields(line, fields, 5);

			if (fieldNum >= 2) {
				std::cout << "Name of player: " << fields[0] << std::endl;
				std::cout << "Surname of player: " << fields[1] << std::endl;
				std::cout << "Money of player $: " << fields[4] << std::endl;
				std::cout << std::endl;
			}
		}
		inFile.close();
	}
	else {
		std::cout << "Error opening the file." << std::endl;
	}
}
void  Player::seeSuperheroes() {
	Superhero sup;
	sup.seeInfoOfSuperheroes();
}//DONE
void Player::PlayersPLUSSuperheroes() {
	std::ifstream inFile("purchase.txt");
	if (inFile) {
		std::cout << "List of players and their superheroes:" << std::endl;

		char line[256];
		while (inFile.getline(line, 256))
		{

			int fieldNum = 0;
			char fields[5][50];
			fieldNum = extractFields(line, fields, 5);
			std::cout << "Name  of player :" << fields[0] << std::endl;
			std::cout << "Money of player :" << fields[1] << "$" << std::endl;
			std::cout << "Superhero's name of the player:" << fields[2] << std::endl;
			std::cout << "Power - type(0 fire, 1 water, 2 earth, 3 none) :" << fields[3] << std::endl;
			std::cout << std::endl;
		}
		inFile.close();
	}
	else {
		std::cout << "Error opening this file." << std::endl;
	}
}//DONE
unsigned Player::extractBalanceFromFile(const MyString& filename, const  MyString& identifier, unsigned fieldIndex)const {
	std::ifstream inFile(filename.c_str());
	if (inFile) {
		char line[256];
		while (inFile.getline(line, 256)) {
			int fieldNum = 0;
			char fields[5][50];
			fieldNum = extractFields(line, fields, 5);
			if (fieldNum == 5 && strcmp(fields[fieldIndex], identifier.c_str()) == 0) {
				inFile.close();
				return extractBalance(fields[4]);
			}
		}
		std::cout << "Incorrect identifier. Please try again." << std::endl;
		inFile.close();
		return 0;
	}
	else {
		std::cout << "Error: " << filename << " could not be opened." << std::endl;
		return 0;
	}
}

unsigned Player::showBalance(const MyString& email)const {
	return extractBalanceFromFile("player.txt", email.c_str(), 2);
}
unsigned Player::getMoney(const MyString& playername) {
	return extractBalanceFromFile("player.txt", playername.c_str(), 0);
}
void Player::purchaseASuperhero() {
	//char nameOfSuperhero[50];
	MyString  nameOfSuperhero;
	std::cout << "enter the name of superhero you just bought to finish purchase :" << std::endl;
	std::cin >> nameOfSuperhero;

	std::ifstream inFile("superheroes.txt");
	std::ofstream outFile("purchased_superheroes.txt", std::ios::app);
	std::ofstream tempFile("temp.txt");
	std::ofstream purchasefile("purchase.txt", std::ios::app);

	bool found = false;
	if (inFile) {

		char line[256];
		while (inFile.getline(line, 256))
		{
			int fieldNum = 0;
			char fields[7][50];
			fieldNum = extractFields(line, fields, 7);
			if (fieldNum == 7 && strcmp(fields[0], nameOfSuperhero.c_str()) == 0) {
				found = true;
				outFile << fields[0] << "," << fields[1] << "," << fields[2] << "," << fields[3] << "," << fields[4] << "," << fields[5] << "," << fields[6] << std::endl;
				purchasefile << fields[0] << "," << fields[3] << "," << fields[4] << std::endl;
			}
			else {
				tempFile << fields[0] << "," << fields[1] << "," << fields[2] << "," << fields[3] << "," << fields[4] << "," << fields[5] << "," << fields[6] << std::endl;
			}
		}
		inFile.close();
		outFile.close();
		tempFile.close();
		purchasefile.close();
		if (found) {
			remove("superheroes.txt");
			rename("temp.txt", "superheroes.txt");
			std::cout << "Superhero purchased successfully!" << std::endl;
		}
		else {
			std::cout << "Superhero not found!" << std::endl;
		}
	}
	else {
		std::cout << "Error: could not open files." << std::endl;
	}

}//DONE
void Player::buySuperhero() {
	std::cout << "Choose the superhero to buy :" << std::endl;

	Superhero superhero;
	int price = superhero.showPriceOfSuperhero();
	std::cout << "Price of this superhero is:" << price << std::endl;

	MyString email;
	std::cout << "enter your email" << std::endl;
	std::cin >> email;

	std::cout << "View the amount of money that you have:" << std::endl;
	unsigned  balance = showBalance(email);

	std::cout << "Your balance is :" << balance << std::endl;

	if (balance < price) {
		std::cout << "You do not have the right amount of money to buy this superhero." << std::endl;
	}
	else {
		balance -= price;
		std::ifstream infile("player.txt");
		std::ofstream outfile("temp.txt");
		std::ofstream purchasefile("purchase.txt", std::ios::app);
		if (!infile.is_open()) {
			std::cerr << "Error: player.txt could not be opened." << std::endl; //do the same thing in other fc
			return;
		}
		if (!outfile.is_open()) {
			std::cerr << "Error: temp.txt could not be created." << std::endl;
			infile.close();
			return;
		}
		if (!purchasefile.is_open()) {
			std::cerr << "Error: purchase.txt could not be created." << std::endl;
			infile.close();
			return;
		}

		char line[256];
		while (infile.getline(line, 256)) {
			int fieldNum = 0;
			char fields[5][50];
			fieldNum = extractFields(line, fields, 5);
			if (fieldNum == 5 && strcmp(fields[2], email.c_str()) == 0) {
				MyString reversedBalanceStr = reverseBalance(balance);
				strcpy(fields[4], reversedBalanceStr.c_str());
				purchasefile << fields[0] << "," << fields[4] << ",";
			}
			outfile << fields[0] << "," << fields[1] << "," << fields[2] << "," << fields[3] << "," << fields[4] << std::endl;
		}
		infile.close();
		outfile.close();
		purchasefile.close();
		remove("player.txt");
		rename("temp.txt", "player.txt");
		std::cout << "You just bought the desired superhero" << std::endl;
		purchaseASuperhero();
	}
}//DONE//DONE

bool Player::checkIfPlayerhasPurchased(const MyString& playerName)const {

	std::ifstream inFile("purchase.txt");
	if (inFile) {
		char line[256];
		while (inFile.getline(line, 256)) {

			int fieldNum = 0;
			char fields[5][50];
			fieldNum = extractFields(line, fields, 5);
			if (fieldNum == 5 && strcmp(fields[0], playerName.c_str()) == 0) {
				inFile.close();
				std::cout << "Name of superhero of this player is:" << fields[2] << std::endl;
				return true;
			}

		}
		return false;//////new added
		std::cout << " ....." << std::endl;
		inFile.close();

	}
	else {
		std::cout << "Error: purchase.txt could not be opened." << std::endl;
	}

	return false;

}//DONE
void Player::setAttackingMode(const MyString& name) {

	std::cout << "SET ATTACK MODE:1 FOR ATTACK MODE| 0 FOR DEFENSE MODE " << std::endl;
	unsigned input;
	std::cin >> input;
	Superhero sup;
	if (input == 1) {

		sup.storeAttackMode(name.c_str(), input);

	}
	else if (input == 0) {

		sup.storeAttackMode(name.c_str(), input);

	}

}//DONE
bool Player::upgradeSuperhero(unsigned money, const  MyString& name)
{

	if (checkIfPlayerhasPurchased(name)) {

		unsigned playerMoney = getMoney(name.c_str());
		if (playerMoney >= money) {
			std::cout << "Your money are:" << playerMoney << " $" << std::endl;
			playerMoney -= money;
			storeMoney(name, playerMoney);
			storeMoneyInPurchase(name, playerMoney);
			std::cout << "Superhero upgraded!" << std::endl;
			return true;
		}
		else {
			std::cout << "Insufficient funds to upgrade superhero." << std::endl;
			return false;

		}

	}
	return false;

}
//void  Player::storeMoneyToFile(MyString filename, MyString name, unsigned money, int fieldIndex) {
//	std::ifstream infile(filename.c_str());
//	std::ofstream outfile("temp.txt");
//	if (!infile.is_open()) {
//		std::cerr << "Error: " << filename << " could not be opened." << std::endl;
//		return;
//	}
//	if (!outfile.is_open()) {
//		std::cerr << "Error: temp.txt could not be created." << std::endl;
//		infile.close();
//		return;
//	}
//
//	char line[256];
//	while (infile.getline(line, 256)) {
//		int fieldNum = 0;
//		char fields[5][50];
//		fieldNum = extractFields(line, fields, 5);
//		if (fieldNum == 5 && strcmp(fields[0], name.c_str()) == 0) {
//			if (money == 0) {
//				strcpy(fields[fieldIndex], "0");
//			}
//			MyString reversedPointsStr = reverseBalance(money);
//			strcpy(fields[fieldIndex], reversedPointsStr.c_str());
//		}
//		for (int i = 0; i < fieldNum; i++) {
//			outfile << fields[i];
//			if (i != fieldNum - 1) {
//				outfile << ",";
//			}
//		}
//		outfile << std::endl;
//	}
//	infile.close();
//	outfile.close();
//	remove(filename.c_str());
//	rename("temp.txt", filename.c_str());
//
//}
//void Player::storeMoney(MyString name, unsigned money) {
//
//	storeMoneyToFile("player.txt", name, money, 4);
//
//}
//void Player::storeMoneyInPurchase(MyString name, unsigned money) {
//	storeMoneyToFile("purchase.txt", name, money, 1);
//}
//void Player::storePointsToFile(MyString filename, unsigned points, MyString name, int fieldIndex) {
//	std::ifstream infile(filename.c_str());
//	std::ofstream outfile("temp.txt");
//	if (!infile.is_open()) {
//		std::cerr << "Error: " << filename << " could not be opened." << std::endl;
//		return;
//	}
//	if (!outfile.is_open()) {
//		std::cerr << "Error: temp.txt could not be created." << std::endl;
//		infile.close();
//		return;
//	}
//
//	char line[256];
//	while (infile.getline(line, 256)) {
//		int fieldNum = 0;
//		char fields[7][50];
//		fieldNum = extractFields(line, fields, 7);
//		if (fieldNum == 7 && strcmp(fields[2], name.c_str()) == 0) {
//			MyString reversedPointsStr = reverseBalance(points);
//			strcpy(fields[fieldIndex], reversedPointsStr.c_str());
//		}
//		for (int i = 0; i < fieldNum; i++) {
//			outfile << fields[i];
//			if (i != fieldNum - 1) {
//				outfile << ",";
//			}
//		}
//		outfile << std::endl;
//	}
//	infile.close();
//	outfile.close();
//	remove(filename.c_str());
//	rename("temp.txt", filename.c_str());
//}
//void Player::storePointsInFileOfAttacker(unsigned points, MyString name) {
//	storePointsToFile("purchase.txt", points, name, 4);
//}
//void  Player::storePointsInFileOfAttackerofpurchase(unsigned points, MyString name) {
//	storePointsToFile("purchased_superheroes.txt", points, name, 4);
//}
void Player::storeMoneyInPurchase(const MyString& name, unsigned money)const {
	std::ifstream infile("purchase.txt");
	std::ofstream outfile("temp.txt");
	if (!infile.is_open()) {
		std::cerr << "Error: purchase.txt could not be opened." << std::endl;
		return;
	}
	if (!outfile.is_open()) {
		std::cerr << "Error: temp.txt could not be created." << std::endl;
		infile.close();
		return;
	}

	char line[256];
	while (infile.getline(line, 256)) {

		int fieldNum = 0;
		char fields[5][50];
		fieldNum = extractFields(line, fields, 5);
		if (fieldNum == 5 && strcmp(fields[0], name.c_str()) == 0) {
			if (money == 0) {
				strcpy(fields[1], "0");
			}
			MyString reversedPointsStr = reverseBalance(money);
			strcpy(fields[1], reversedPointsStr.c_str());

			/*int n = 0, temp = money;
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
			}*/
		}
		outfile << fields[0] << "," << fields[1] << "," << fields[2] << "," << fields[3] << "," << fields[4] << std::endl;


	}
	infile.close();
	outfile.close();
	remove("purchase.txt");
	rename("temp.txt", "purchase.txt");

}



void Player::storeMoney(const MyString& name, unsigned money)const {

	std::ifstream infile("player.txt");
	std::ofstream outfile("temp.txt");
	if (!infile.is_open()) {
		std::cerr << "Error: player.txt could not be opened." << std::endl; //do the same thing in other fc
		return;
	}
	if (!outfile.is_open()) {
		std::cerr << "Error: temp.txt could not be created." << std::endl;
		infile.close();
		return;
	}

	char line[256];
	while (infile.getline(line, 256)) {
		int fieldNum = 0;
		char fields[5][50];
		fieldNum = extractFields(line, fields, 5);
		if (fieldNum == 5 && strcmp(fields[0], name.c_str()) == 0) {
			//newwww....
			if (money == 0) {
				strcpy(fields[4], "0");
			}
			MyString reversedPointsStr = reverseBalance(money);
			strcpy(fields[4], reversedPointsStr.c_str());

		}
		outfile << fields[0] << "," << fields[1] << "," << fields[2] << "," << fields[3] << "," << fields[4] << std::endl;


	}
	infile.close();
	outfile.close();
	remove("player.txt");
	rename("temp.txt", "player.txt");

}



void Player::storePointsInFileOfAttacker(unsigned points, const  MyString& name)const {

	std::ifstream infile("purchase.txt");
	std::ofstream outfile("temp.txt");
	if (!infile.is_open()) {
		std::cerr << "Error: purchase.txt could not be opened." << std::endl; //do the same thing in other fc
		return;
	}
	if (!outfile.is_open()) {
		std::cerr << "Error: temp.txt could not be created." << std::endl;
		infile.close();
		return;
	}

	char line[256];
	while (infile.getline(line, 256)) {
		int fieldNum = 0;
		char fields[5][50];
		fieldNum = extractFields(line, fields, 5);
		if (fieldNum == 5 && strcmp(fields[2], name.c_str()) == 0) {
			MyString reversedPointsStr = reverseBalance(points);
			strcpy(fields[4], reversedPointsStr.c_str());
		}
		outfile << fields[0] << "," << fields[1] << "," << fields[2] << "," << fields[3] << "," << fields[4] << std::endl;


	}
	infile.close();
	outfile.close();
	remove("purchase.txt");
	rename("temp.txt", "purchase.txt");


}
void  Player::storePointsInFileOfAttackerofpurchase(unsigned points, const MyString& name)const {


	std::ifstream infile("purchased_superheroes.txt");
	std::ofstream outfile("temp.txt");
	if (!infile.is_open()) {
		std::cerr << "Error: purchased_superheroestxt could not be opened." << std::endl; //do the same thing in other fc
		return;
	}
	if (!outfile.is_open()) {
		std::cerr << "Error: temp.txt could not be created." << std::endl;
		infile.close();
		return;
	}

	char line[256];
	while (infile.getline(line, 256)) {
		int fieldNum = 0;
		char fields[7][50];
		fieldNum = extractFields(line, fields, 7);
		if (fieldNum == 7 && strcmp(fields[0], name.c_str()) == 0) {

			MyString reversedPointsStr = reverseBalance(points);
			strcpy(fields[4], reversedPointsStr.c_str());

			/*int n = 0, temp = points;
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
			strcpy(fields[4], pointsStr);*/
		}
		outfile << fields[0] << "," << fields[1] << "," << fields[2] << "," << fields[3] << "," << fields[4] << "," << fields[5] << "," << fields[6] << std::endl;


	}
	infile.close();
	outfile.close();
	remove("purchased_superheroes.txt");
	rename("temp.txt", "purchased_superheroes.txt");
}


void whoWonTheGame(unsigned pointsOfAttaacker, unsigned pointsOfAttacked) {
	if (pointsOfAttaacker > pointsOfAttacked)
	{
		std::cout << "WELL DONE.ATTACKER WON THIS GAME!" << std::endl;
	}
	else if (pointsOfAttaacker < pointsOfAttacked) {
		std::cout << "ATTACKED  WON THIS GAME!" << std::endl;
	}
	else {
		std::cout << "NO ONE WON THIS GAME.TRY ONE MORE TIME !" << std::endl;
	}

}
unsigned Player::playingTheGame(unsigned& pointsToBeDoubled, const MyString& name)
{
	pointsToBeDoubled *= 2;
	std::cout << pointsToBeDoubled << std::endl;
	storePointsInFileOfAttacker(pointsToBeDoubled, name.c_str());
	storePointsInFileOfAttackerofpurchase(pointsToBeDoubled, name.c_str());
	return pointsToBeDoubled;
}


//void Player::attack() {
//	Superhero superhero;
//	MyString nameOfSuperhero;
//	MyString name;
//
//	std::cout << "Hello ATTACKER .Enter your name ...:" << std::endl;//attacker s name
//	std::cin >> name;
//
//	std::cout << "Enter the name of SUPERHERO you will attack with:" << std::endl;//superhero of attacker
//	std::cin >> nameOfSuperhero;
//
//	bool AttackerhasPurchased = checkIfPlayerhasPurchased(name);
//	if (!AttackerhasPurchased)
//	{
//		std::cout << "You do not have a superhero to attack.Go buy it !" << std::endl;
//	}
//	else {
//
//		//--------------------------------------------------------------------------ATTACKER PLAYER
//		setAttackingMode(nameOfSuperhero);
//
//		unsigned power = superhero.getPowerTypeOfSuperhero(nameOfSuperhero);
//		showPowerType(power);
//		
//		unsigned points = superhero.showPointsOfSuperhero(nameOfSuperhero);
//		std::cout << "ATTACKER,your superhero has:" << points <<"points." << std::endl;
//
//		unsigned attack = superhero.showAttackMode(nameOfSuperhero);
//		showAttack(attack);
//		//--------------------------------------------------------------------------ATTACKED PLAYER
//
//		seeInfoByPlayers();
//		std::cout << "---CHOOSE ONE  PLAYER FROM THE LIST TO ATTACK:---" << std::endl;
//		MyString playerName;
//		std::cin >> playerName;
//
//		unsigned moneyOfAttackedPlayer = getMoney(playerName);//MONEY OF ATTACKED
//		unsigned moneyOfAttacker = getMoney(name);//MONEY OF ATTACKER
//
//		bool hasPurchased = checkIfPlayerhasPurchased(playerName);
//
//		if (hasPurchased) {
//			MyString attackedSuperhero;//name of superhero that will be attacked
//			std::cout << "Type the name of this superhero to finish the attack:" << std::endl;
//			std::cin >> attackedSuperhero;
//
//			unsigned powerAttacked = superhero.getPowerTypeOfSuperhero(attackedSuperhero);
//			showPowerType(powerAttacked);
//			
//			unsigned pointsAttacked = superhero.showPointsOfSuperhero(attackedSuperhero);//ATTACKED
//			std::cout << "The RIVAL has :" << pointsAttacked << "  points." << std::endl;
//			unsigned attackModeOfAttacked = superhero.showAttackMode(attackedSuperhero);
//			showAttack(attackModeOfAttacked);
//
//			
//			if (power == 0 && powerAttacked == 2|| power == 2 && powerAttacked == 1|| power == 1 && powerAttacked == 0) { //fire earth  //earth water //water fire
//				std::cout << "Congratulations ATTACKER ,your points are doubled.Now they  are:" << std::endl;
//				points=playingTheGame(points, nameOfSuperhero);
//				whoWonTheGame(points, pointsAttacked);
//			}
//
//			else if (power == 2 && powerAttacked == 0 || power == 1 && powerAttacked == 2|| power == 0 && powerAttacked == 1)
//			{ //earth fire  //water earth
//				std::cout << "ATTACKED PLAYER  just got his points doubled.Now his points  are:" << std::endl;
//				pointsAttacked=playingTheGame(pointsAttacked,  attackedSuperhero);
//				whoWonTheGame(points, pointsAttacked);
//			}
//			else if (power == powerAttacked) {
//				if (attackModeOfAttacked == 0) {
//					if (points > pointsAttacked) {
//						unsigned difference = points - pointsAttacked;
//						moneyOfAttacker += difference;
//
//						std::cout << "CONGRATULATIONS,ATTACKER WON THE GAME!" << std::endl;
//					}
//					else if (points < pointsAttacked) {
//						unsigned difference = pointsAttacked - points;
//						difference *= 2;
//						moneyOfAttacker -= difference;
//						std::cout << "ATTACKED WON THE GAME!" << std::endl;
//					}
//					else {//when they are equal
//
//						moneyOfAttacker -= 50;
//						std::cout << "ATTACKED WON THE GAME!" << std::endl;//review who won the game
//
//					}
//					storeMoney(name, moneyOfAttacker);
//					storeMoneyInPurchase(name, moneyOfAttacker);
//
//				}
//				else {
//					if (points > pointsAttacked) {
//						unsigned difference = points - pointsAttacked;
//						moneyOfAttackedPlayer -= difference;
//						moneyOfAttacker += difference;
//						storeMoney(playerName, moneyOfAttackedPlayer);
//						storeMoney(name, moneyOfAttacker);
//						storeMoneyInPurchase(name, moneyOfAttacker);
//						storeMoneyInPurchase(playerName, moneyOfAttackedPlayer);
//						std::cout << "CONGRATULATIONS,ATTACKER WON THE GAME!" << std::endl;
//					}
//					else if (points < pointsAttacked) {
//						unsigned difference = pointsAttacked - points;//i think i have to declare above
//						difference *= 2;
//						moneyOfAttackedPlayer += 50;//X money gained const i think
//						moneyOfAttacker -= difference;
//						storeMoney(playerName, moneyOfAttackedPlayer);
//						storeMoney(name, moneyOfAttacker);
//						storeMoneyInPurchase(name, moneyOfAttacker);
//						storeMoneyInPurchase(playerName, moneyOfAttackedPlayer);
//						std::cout << "ATTACKED WON THE GAME!" << std::endl;
//
//					}
//					else {//when they are equal
//						moneyOfAttacker -= 50;
//						std::cout << "CONGRATULATIONS,ATTACKER WON THE GAME!" << std::endl;
//						storeMoney(name, moneyOfAttacker);
//						storeMoneyInPurchase(name, moneyOfAttacker);
//
//					}
//				}
//			}
//		}
//
//		else   {//when he attacks a player that has no superheroes
//
//			//std::cout << moneyOfAttackedPlayer << std::endl;
//			if (moneyOfAttackedPlayer <= points) { ///this part doesn work correct it
//				moneyOfAttackedPlayer -= 50;
//				moneyOfAttacker += 50;//make this a constant value
//				/*storeMoney(playerName, moneyOfAttackedPlayer);
//				storeMoney(name, moneyOfAttacker);
//				storeMoneyInPurchase(name, moneyOfAttacker);*/
//				std::cout << "ATTACKER WON GAME...." << std::endl;
//			}
//			else {
//				moneyOfAttackedPlayer -= points;
//				moneyOfAttacker += 50;
//				/*storeMoney(playerName, moneyOfAttackedPlayer);
//				storeMoney(name, moneyOfAttacker);
//				storeMoneyInPurchase(name, moneyOfAttacker);*/
//				std::cout << "ATTACKER WON GAME...." << std::endl;
//			}
//			storeMoney(playerName, moneyOfAttackedPlayer);
//			storeMoney(name, moneyOfAttacker);
//			storeMoneyInPurchase(name, moneyOfAttacker);
//
//		}
//	}
//}

void Player::attack() {
	Superhero superhero;
	MyString nameOfSuperhero;
	MyString name;

	std::cout << "Hello ATTACKER .Enter your name ...:" << std::endl;//attacker s name
	std::cin >> name;

	std::cout << "Enter the name of SUPERHERO you will attack with:" << std::endl;//superhero of attacker
	std::cin >> nameOfSuperhero;

	bool AttackerhasPurchased = checkIfPlayerhasPurchased(name);
	if (!AttackerhasPurchased)
	{
		std::cout << "You do not have a superhero to attack.Go buy it !" << std::endl;
	}
	else {

		//--------------------------------------------------------------------------ATTACKER PLAYER
		setAttackingMode(nameOfSuperhero.c_str());

		unsigned power = superhero.getPowerTypeOfSuperhero(nameOfSuperhero.c_str());///ADDED NEY .CSTR
		showPowerType(power);

		unsigned points = superhero.showPointsOfSuperhero(nameOfSuperhero.c_str());
		std::cout << "ATTACKER,your superhero has:" << points << "points." << std::endl;

		unsigned attack = superhero.showAttackMode(nameOfSuperhero.c_str());
		showAttack(attack);
		//--------------------------------------------------------------------------ATTACKED PLAYER

		seeInfoByPlayers();
		std::cout << "---CHOOSE ONE  PLAYER FROM THE LIST TO ATTACK:---" << std::endl;
		MyString playerName;
		std::cin >> playerName;

		unsigned moneyOfAttackedPlayer = getMoney(playerName);//MONEY OF ATTACKED
		unsigned moneyOfAttacker = getMoney(name);//MONEY OF ATTACKER

		bool hasPurchased = checkIfPlayerhasPurchased(playerName);

		if (hasPurchased) {
			MyString attackedSuperhero;//name of superhero that will be attacked
			std::cout << "Type the name of this superhero to finish the attack:" << std::endl;
			std::cin >> attackedSuperhero;

			unsigned powerAttacked = superhero.getPowerTypeOfSuperhero(attackedSuperhero.c_str());
			showPowerType(powerAttacked);

			unsigned pointsAttacked = superhero.showPointsOfSuperhero(attackedSuperhero.c_str());//ATTACKED
			std::cout << "The RIVAL has :" << pointsAttacked << "  points." << std::endl;
			unsigned attackModeOfAttacked = superhero.showAttackMode(attackedSuperhero.c_str());
			showAttack(attackModeOfAttacked);


			if (power == 0 && powerAttacked == 2) { //fire earth
				std::cout << "Congratulations ATTACKER ,your points are doubled.Now they  are:" << std::endl;
				points = playingTheGame(points, nameOfSuperhero);
				whoWonTheGame(points, pointsAttacked);
			}

			else if (power == 2 && powerAttacked == 0)
			{ //earth fire
				std::cout << "ATTACKED PLAYER  just got his points doubled.Now his points  are:" << std::endl;
				pointsAttacked = playingTheGame(pointsAttacked, attackedSuperhero.c_str());
				whoWonTheGame(points, pointsAttacked);
			}
			else if (power == 2 && powerAttacked == 1) { //earth water 
				std::cout << "Congratulations ATTACKER ,your points are doubled.Now they  are:" << std::endl;
				points = playingTheGame(points, nameOfSuperhero.c_str());
				whoWonTheGame(points, pointsAttacked);
			}
			else if (power == 1 && powerAttacked == 2)
			{ //water earth
				std::cout << "ATTACKED PLAYER  just got his points doubled.Now his points  are:" << std::endl;
				pointsAttacked = playingTheGame(pointsAttacked, attackedSuperhero.c_str());
				whoWonTheGame(points, pointsAttacked); std::cout << "attacked won the game" << std::endl;
			}
			else if (power == 1 && powerAttacked == 0) {   //water fire
				std::cout << "Congratulations ATTACKER ,your points are doubled.Now they  are:" << std::endl;

				points = playingTheGame(points, nameOfSuperhero.c_str());
				whoWonTheGame(points, pointsAttacked);
			}
			else if (power == 0 && powerAttacked == 1) { //fire water 
				std::cout << "ATTACKED PLAYER  just got his points doubled.Now his points  are:" << std::endl;
				pointsAttacked = playingTheGame(pointsAttacked, attackedSuperhero.c_str());//WORKS 
				whoWonTheGame(points, pointsAttacked);
			}

			else if (power == powerAttacked) {
				if (attackModeOfAttacked == 0) {
					if (points > pointsAttacked) {
						unsigned difference = points - pointsAttacked;
						moneyOfAttacker += difference;
						storeMoney(name.c_str(), moneyOfAttacker);
						storeMoneyInPurchase(name.c_str(), moneyOfAttacker);
						std::cout << "CONGRATULATIONS,ATTACKER WON THE GAME!" << std::endl;
					}
					else if (points < pointsAttacked) {
						unsigned difference = pointsAttacked - points;
						difference *= 2;
						if (moneyOfAttacker > difference) {
							moneyOfAttacker -= difference;
						}
						else {
							moneyOfAttacker = 1;
						}
						//moneyOfAttacker -= difference;
						storeMoney(name.c_str(), moneyOfAttacker);
						storeMoneyInPurchase(name.c_str(), moneyOfAttacker);
						std::cout << "ATTACKED WON THE GAME!" << std::endl;
					}
					else {//when they are equal
						if (moneyOfAttacker < 50) {
							moneyOfAttacker = 1;
						}
						else {
							moneyOfAttacker -= 50;
						}
						std::cout << "ATTACKED WON THE GAME!" << std::endl;//review who won the game
						storeMoney(name.c_str(), moneyOfAttacker);
						storeMoneyInPurchase(name.c_str(), moneyOfAttacker);

					}

				}
				else {
					if (points > pointsAttacked) {
						unsigned difference = points - pointsAttacked;
						moneyOfAttacker += difference;
						if (moneyOfAttackedPlayer > difference) {
							moneyOfAttackedPlayer -= difference;

						}
						else {
							moneyOfAttackedPlayer = 1;
						}

						storeMoney(name.c_str(), moneyOfAttacker);
						storeMoneyInPurchase(name.c_str(), moneyOfAttacker);
						storeMoney(playerName.c_str(), moneyOfAttackedPlayer);
						storeMoneyInPurchase(playerName.c_str(), moneyOfAttackedPlayer);
						//review these doesnt work

						std::cout << "CONGRATULATIONS,ATTACKER WON THE GAME!" << std::endl;
					}
					else if (points < pointsAttacked) {
						unsigned difference = pointsAttacked - points;
						//moneyOfAttackedPlayer += 50;
						difference *= 2;
						if (moneyOfAttacker > difference) {
							moneyOfAttacker -= difference;
						}
						else {
							moneyOfAttacker = 1;
						}
						moneyOfAttackedPlayer += 50;
						//moneyOfAttacker -= difference;
						storeMoney(name.c_str(), moneyOfAttacker);
						storeMoneyInPurchase(name.c_str(), moneyOfAttacker);
						storeMoney(playerName.c_str(), moneyOfAttackedPlayer);
						storeMoneyInPurchase(playerName.c_str(), moneyOfAttackedPlayer);
						std::cout << "ATTACKED WON THE GAME!" << std::endl;
					}
					else {//when they are equal
						if (moneyOfAttacker < 50) {
							moneyOfAttacker = 1;
						}
						else {
							moneyOfAttacker -= 50;
						}
						std::cout << "ATTACKED WON THE GAME!" << std::endl;//review who won the game
						storeMoney(name.c_str(), moneyOfAttacker);
						storeMoneyInPurchase(name.c_str(), moneyOfAttacker);
					}
				}
			}
		}

		else {

			//std::cout << moneyOfAttackedPlayer << std::endl;
			if (moneyOfAttackedPlayer <= points) { ///this part doesn work correct it
				moneyOfAttackedPlayer = 1;
				moneyOfAttacker += 50;//make this a constant value
				storeMoney(playerName.c_str(), moneyOfAttackedPlayer);
				storeMoney(name.c_str(), moneyOfAttacker);
				storeMoneyInPurchase(name.c_str(), moneyOfAttacker);
				storeMoneyInPurchase(playerName.c_str(), moneyOfAttackedPlayer);
				std::cout << "ATTACKER WON GAME...." << std::endl;
			}
			else {
				moneyOfAttackedPlayer -= points;
				moneyOfAttacker += 50;
				storeMoney(playerName.c_str(), moneyOfAttackedPlayer);
				storeMoney(name.c_str(), moneyOfAttacker);
				storeMoneyInPurchase(name.c_str(), moneyOfAttacker);
				storeMoneyInPurchase(playerName.c_str(), moneyOfAttackedPlayer);
				std::cout << "ATTACKER WON GAME...." << std::endl;
			}

		}
	}
}







