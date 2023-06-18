#include "Player.h"
#include"Utills.h"

Player::Player() : purchased_superhero(nullptr), money(0) {}

Player::Player(const MyString& name, const MyString& surname, const MyString& email, const MyString& password, unsigned int money) :User(name, surname, email, password)
{
	setMoney(money);
}

void Player::copyFrom(const Player& other)
{

	money = other.money;

	if (other.purchased_superhero)
		purchased_superhero = new Superhero(*other.purchased_superhero);
	else
		purchased_superhero = nullptr;

}

void Player::moveFrom(Player&& other)noexcept
{
	purchased_superhero = other.purchased_superhero;
	other.purchased_superhero = nullptr;
	money = other.money;
	other.money = 0;
}

void Player::free()
{
	delete purchased_superhero;
	purchased_superhero = nullptr;
	money = 0;
}

Player::Player(const Player& other) 
{
	copyFrom(other);
}

Player::Player(Player&& other)noexcept
{
	moveFrom(std::move(other));
}

Player& Player:: operator=(const Player& other)
{
	if (this != &other) 
	{
		free();
		copyFrom(other);
	}
	return*this;
}

Player& Player::operator=(Player&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return*this;
}

Player::~Player()
{
	free();
}

void Player::setMoney(unsigned int money)
{
	this->money = money;
}

const unsigned int Player::getMoney()const
{
	return money;
}

void storeInFilePlayers(const Player& players, const MyString& filename)
{

	std::ofstream file(filename.c_str(), std::ios::app);
	if (!file.is_open()) 
	{
		throw std::runtime_error("Unable to open file for reading.");

	}

	file << players.getName() << "," << players.getSurname() << "," << players.getEmail() << "," << players.getPassword() << "," << players.getMoney() << std::endl;
	file.close();

}

void Player::deleteFromPurchase(const MyString& name) const 
{

	std::cout << "Enter the name of the superhero of the player that you want to delete its profile:" << std::endl;

	MyString superheroName;
	std::cin >> superheroName;

	std::ifstream inFile("purchase.txt");
	if (inFile) {
		std::ofstream tempFile("temp.txt");

		if (tempFile) 
		{
			bool deleted = false;
			char line[256];
			while (inFile.getline(line, 256)) 
			{
				int fieldNum = 0;
				char fields[5][50];
				fieldNum = extractFields(line, fields, 5);
				if (fieldNum == 5 && strcmp(fields[0], name.c_str()) == 0 && strcmp(fields[2], superheroName.c_str()) == 0)
				{
					deleted = true;
					continue;
				}
				tempFile << fields[0] << "," << fields[1] << "," << fields[2] << "," << fields[3] << "," << fields[4] << std::endl;
			}
			inFile.close();
			tempFile.close();

			if (deleted)
			{
				if (remove("purchase.txt") == 0 && rename("temp.txt", "purchase.txt") == 0)
				{
					std::cout << "Player with name " << name << " has been deleted." << std::endl;
				}
				else
				{
					std::cout << "Error: Failed to delete player profile." << std::endl;
				}
			}
			else 
			{
				std::cout << "Incorrect name. Please try again." << std::endl;
				remove("temp.txt");
			}
		}
		else 
		{
			std::cout << "Error: temp.txt could not be opened." << std::endl;
		}
	}
	else
	{
		std::cout << "Error: purchase.txt could not be opened." << std::endl;
	}
}


void Player::deletePlayerProfile(const MyString& email, const MyString& password, const MyString& name)const
{

	bool HasPurchased = checkIfPlayerhasPurchased(name.c_str());
	if (HasPurchased) 
	{
		deleteFromPurchase(name.c_str());
		deleteProfile(email.c_str(), password.c_str());
	}
	else 
	{
		deleteProfile(email.c_str(), password.c_str());
	}

}

void Player::deleteProfile(const MyString& email, const MyString& password)const 
{
	std::ifstream inFile("player.txt");

	if (inFile) {

		std::ofstream tempFile("temp.txt");
		if (tempFile) 
		{
			bool deleted = false;
			char line[256];
			while (inFile.getline(line, 256))
			{
				int fieldNum = 0;
				char fields[5][50];
				fieldNum = extractFields(line, fields, 5);
				if (fieldNum == 5 && strcmp(fields[2], email.c_str()) == 0 && strcmp(fields[3], password.c_str()) == 0)
				{
					deleted = true;
					continue;
				}
				tempFile << fields[0] << "," << fields[1] << "," << fields[2] << "," << fields[3] << "," << fields[4] << std::endl;
			}
			inFile.close();
			tempFile.close();
			if (deleted)
			{

				if (remove("player.txt") == 0 && rename("temp.txt", "player.txt") == 0) 
				{
					std::cout << "Player with email " << email << " has been deleted." << std::endl;
				}
				else 
				{
					std::cout << "Error: Failed to delete player profile." << std::endl;
				}
			}
			else 
			{
				std::cout << "Incorrect email or password. Please try again." << std::endl;
				remove("temp.txt");
			}
		}
		else
		{
			std::cout << "Error: temp.txt could not be opened." << std::endl;
		}
	}
	else
	{
		std::cout << "Error: player.txt could not be opened." << std::endl;
	}
}


void Player::seeInfoByPlayers() 
{
	std::ifstream inFile("player.txt");

	if (inFile)
	{
		std::cout << "List of players:" << std::endl;

		char line[256];
		while (inFile.getline(line, 256))
		{
			int fieldNum = 0;
			char fields[5][50];
			fieldNum = extractFields(line, fields, 5);

			if (fieldNum >= 2)
			{
				std::cout << "Name of player: " << fields[0] << std::endl;
				std::cout << "Surname of player: " << fields[1] << std::endl;
				std::cout << "Money of player $: " << fields[4] << std::endl;
				std::cout << std::endl;
			}
		}
		inFile.close();
	}
	else 
	{
		std::cout << "Error opening the file." << std::endl;
	}
}

void  Player::seeSuperheroes()
{
	SuperheroesCollection sup;
	sup.seeInfoOfSuperheroes("superheroes.txt");
}


void Player::PlayersPLUSSuperheroes()
{
	std::ifstream inFile("purchase.txt");
	if (inFile) 
	{
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
	else 
	{
		std::cout << "Error opening this file." << std::endl;
	}
}

unsigned Player::extractBalanceFromFile(const MyString& filename, const  MyString& identifier, unsigned fieldIndex)const
{
	
	std::ifstream inFile(filename.c_str());
	if (inFile)
	{
		char line[256];
		while (inFile.getline(line, 256))
		{
			int fieldNum = 0;
			char fields[5][50];
			fieldNum = extractFields(line, fields, 5);
			if (fieldNum == 5 && strcmp(fields[fieldIndex], identifier.c_str()) == 0)
			{
				inFile.close();
				return extractBalance(fields[4]);
			}
		}
		std::cout << "Incorrect identifier. Please try again." << std::endl;
		inFile.close();
		return 0;
	}
	else 
	{
		std::cout << "Error: " << filename << " could not be opened." << std::endl;
		return 0;
	}
}

unsigned Player::showBalance(const MyString& email)const
{
	return extractBalanceFromFile("player.txt", email.c_str(), 2);
}

unsigned Player::getMoney(const MyString& playername) 
{
	return extractBalanceFromFile("player.txt", playername.c_str(), 0);
}

void Player::purchaseASuperhero() 
{
	MyString  nameOfSuperhero;
	std::cout << "enter the name of superhero you just bought to finish purchase :" << std::endl;
	std::cin >> nameOfSuperhero;

	std::ifstream inFile("superheroes.txt");
	std::ofstream outFile("purchased_superheroes.txt", std::ios::app);
	std::ofstream tempFile("temp.txt");
	std::ofstream purchasefile("purchase.txt", std::ios::app);

	bool found = false;
	if (inFile)
	{

		char line[256];
		while (inFile.getline(line, 256))
		{
			int fieldNum = 0;
			char fields[7][50];
			fieldNum = extractFields(line, fields, 7);
			if (fieldNum == 7 && strcmp(fields[0], nameOfSuperhero.c_str()) == 0) 
			{
				found = true;
				outFile << fields[0] << "," << fields[1] << "," << fields[2] << "," << fields[3] << "," << fields[4] << "," << fields[5] << "," << fields[6] << std::endl;
				purchasefile << fields[0] << "," << fields[3] << "," << fields[4] << std::endl;
			}
			else 
			{
				tempFile << fields[0] << "," << fields[1] << "," << fields[2] << "," << fields[3] << "," << fields[4] << "," << fields[5] << "," << fields[6] << std::endl;
			}
		}
		inFile.close();
		outFile.close();
		tempFile.close();
		purchasefile.close();
		if (found) 
		{
			if (remove("superheroes.txt") == 0 && rename("temp.txt", "superheroes.txt") == 0) 
			{
				std::cout << "Superhero purchased successfully!" << std::endl;
			}
			else
			{
				std::cout << "Error: Failed to update superhero file." << std::endl;
			}
		}
		else 
		{
			std::cout << "Superhero not found!" << std::endl;
		}
	}
	else 
	{
		std::cout << "Error: could not open files." << std::endl;
	}

}

void Player::buySuperhero() 
{
	std::cout << "Choose the superhero to buy :" << std::endl;

	
	SuperheroesCollection superhero;
	unsigned  price = superhero.showPriceOfSuperhero();
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

		if (!infile.is_open()) 
		{
			std::cerr << "Error: player.txt could not be opened." << std::endl; 
			return;
		}

		if (!outfile.is_open() || !purchasefile.is_open())
		{
			std::cerr << "Error: file could not be created." << std::endl;
			infile.close();
			return;
		}

		char line[256];
		while (infile.getline(line, 256))
		{
			int fieldNum = 0;
			char fields[5][50];
			fieldNum = extractFields(line, fields, 5);

			if (fieldNum == 5 && strcmp(fields[2], email.c_str()) == 0)
			{
				MyString reversedBalanceStr = reverseBalance(balance);
				strcpy(fields[4], reversedBalanceStr.c_str());
				purchasefile << fields[0] << "," << fields[4] << ",";
			}
			outfile << fields[0] << "," << fields[1] << "," << fields[2] << "," << fields[3] << "," << fields[4] << std::endl;
		}

		infile.close();
		outfile.close();
		purchasefile.close();

		if (remove("player.txt") == 0 && rename("temp.txt", "player.txt") == 0) {
			std::cout << "You have successfully bought the desired superhero." << std::endl;
			purchaseASuperhero();
		}
		else {
			std::cout << "Error: Failed to update player file." << std::endl;
		}

	}
}

bool Player::checkIfPlayerhasPurchased(const MyString& playerName)const
{

	std::ifstream inFile("purchase.txt");
	if (inFile) 
	{
		char line[256];
		while (inFile.getline(line, 256))
		{
			int fieldNum = 0;
			char fields[5][50];
			fieldNum = extractFields(line, fields, 5);
			if (fieldNum == 5 && strcmp(fields[0], playerName.c_str()) == 0) 
			{
				inFile.close();
				std::cout << "Name of superhero of this player is:" << fields[2] << std::endl;
				return true;
			}

		}
		return false;
		std::cout << " ....." << std::endl;
		inFile.close();

	}
	else {
		std::cout << "Error: purchase.txt could not be opened." << std::endl;
	}

	return false;

}

void Player::setAttackingMode(const MyString& name)
{

	std::cout << "SET ATTACK MODE:1 FOR ATTACK MODE| 0 FOR DEFENSE MODE " << std::endl;
	unsigned input;
	std::cin >> input;
	SuperheroesCollection sup;
	if (input == 1) 
	{
		sup.storeAttackMode(name.c_str(), input);
	}

	else if (input == 0)
	{
		sup.storeAttackMode(name.c_str(), input);
	}
}

bool Player::upgradeSuperhero(unsigned money, const  MyString& name)
{

	if (checkIfPlayerhasPurchased(name)) 
	{

		unsigned playerMoney = getMoney(name.c_str());
		if (playerMoney >= money)
		{
			std::cout << "Your money are:" << playerMoney << " $" << std::endl;
			playerMoney -= money;
			storeMoney(name, playerMoney);
			storeMoneyInPurchase(name, playerMoney);
			std::cout << "Superhero upgraded!" << std::endl;
			return true;
		}
		else 
		{
			std::cout << "Insufficient funds to upgrade superhero." << std::endl;
			return false;
		}
	}
	return false;
}

void Player::storeMoneyInPurchase(const MyString& name, unsigned money)const
{
	updateFile("purchase.txt", "temp.txt", name, money, 1);
}

void Player::storeMoney(const MyString& name, unsigned money)const
{
	updateFile("player.txt", "temp.txt", name, money, 4);
}

void Player::storePointsInFileOfAttacker(unsigned points, const MyString& name) const
{
	updatePointsInFile("purchase.txt", "temp.txt", name, points, 5, 2);
}

void Player::storePointsInFileOfAttackerofpurchase(unsigned points, const MyString& name) const 
{
	updatePointsInFile("purchased_superheroes.txt", "temp.txt", name, points, 7, 0);
}


void whoWonTheGame(unsigned pointsOfAttaacker, unsigned pointsOfAttacked)
{
	if (pointsOfAttaacker > pointsOfAttacked)
	{
		std::cout << "WELL DONE.ATTACKER WON THIS GAME!" << std::endl;
	}
	else if (pointsOfAttaacker < pointsOfAttacked) 
	{
		std::cout << "ATTACKED  WON THIS GAME!" << std::endl;
	}
	else
	{
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

void Player::attack() 
{
	Superhero superhero;
	SuperheroesCollection sup;
	MyString nameOfSuperhero;
	MyString name;

	std::cout << "Hello ATTACKER .Enter your name ...:" << std::endl;
	std::cin >> name;

	std::cout << "Enter the name of SUPERHERO you will attack with:" << std::endl;
	std::cin >> nameOfSuperhero;

	bool AttackerhasPurchased = checkIfPlayerhasPurchased(name);
	if (!AttackerhasPurchased)
	{
		std::cout << "You do not have a superhero to attack.Go buy it !" << std::endl;
	}
	else 
	{

		setAttackingMode(nameOfSuperhero.c_str());

		unsigned power = sup.getPowerTypeOfSuperhero(nameOfSuperhero.c_str());
		showPowerType(power);

		unsigned points = sup.showPointsOfSuperhero(nameOfSuperhero.c_str());
		std::cout << "ATTACKER,your superhero has:" << points << "points." << std::endl;

		unsigned attack = sup.showAttackMode(nameOfSuperhero.c_str());
		showAttack(attack);

		seeInfoByPlayers();
		std::cout << "---CHOOSE ONE  PLAYER FROM THE LIST TO ATTACK:---" << std::endl;
		MyString playerName;
		std::cin >> playerName;

		unsigned moneyOfAttackedPlayer = getMoney(playerName);
		unsigned moneyOfAttacker = getMoney(name);

		bool hasPurchased = checkIfPlayerhasPurchased(playerName);

		if (hasPurchased) {
			MyString attackedSuperhero;
			std::cout << "Type the name of this superhero to finish the attack:" << std::endl;
			std::cin >> attackedSuperhero;

			unsigned powerAttacked = sup.getPowerTypeOfSuperhero(attackedSuperhero.c_str());
			showPowerType(powerAttacked);

			unsigned pointsAttacked = sup.showPointsOfSuperhero(attackedSuperhero.c_str());
			std::cout << "The RIVAL has :" << pointsAttacked << "  points." << std::endl;
			unsigned attackModeOfAttacked = sup.showAttackMode(attackedSuperhero.c_str());
			showAttack(attackModeOfAttacked);


			if (power == 0 && powerAttacked == 2 || power == 2 && powerAttacked == 1 || power == 1 && powerAttacked == 0) 
			{ 
				std::cout << "Congratulations ATTACKER ,your points are doubled.Now they  are:" << std::endl;
				points = playingTheGame(points, nameOfSuperhero.c_str());
				whoWonTheGame(points, pointsAttacked);
			}

			else if (power == 0 && powerAttacked == 1 || power == 2 && powerAttacked == 0 || power == 1 && powerAttacked == 2)
			{ 
				std::cout << "ATTACKED PLAYER  just got his points doubled.Now his points  are:" << std::endl;
				pointsAttacked = playingTheGame(pointsAttacked, attackedSuperhero.c_str());
				whoWonTheGame(points, pointsAttacked);
			}

			else if (power == powerAttacked)
			{
				if (attackModeOfAttacked == 0) 
				{
					if (points > pointsAttacked)
					{
						unsigned difference = points - pointsAttacked;
						moneyOfAttacker += difference;
						storeMoney(name.c_str(), moneyOfAttacker);
						storeMoneyInPurchase(name.c_str(), moneyOfAttacker);
						std::cout << "CONGRATULATIONS,ATTACKER WON THE GAME!" << std::endl;
					}
					else if (points < pointsAttacked)
					{
						unsigned difference = pointsAttacked - points;
						difference *= 2;
						if (moneyOfAttacker > difference) 
						{
							moneyOfAttacker -= difference;
						}
						else
						{
							moneyOfAttacker = 1;
						}
						storeMoney(name.c_str(), moneyOfAttacker);
						storeMoneyInPurchase(name.c_str(), moneyOfAttacker);
						std::cout << "ATTACKED WON THE GAME!" << std::endl;
					}
					else {
						if (moneyOfAttacker < 50)
						{
							moneyOfAttacker = 1;
						}
						else 
						{
							moneyOfAttacker -= 50;
						}
						std::cout << "ATTACKED WON THE GAME!" << std::endl;
						storeMoney(name.c_str(), moneyOfAttacker);
						storeMoneyInPurchase(name.c_str(), moneyOfAttacker);

					}
				}
				else 
				{
					if (points > pointsAttacked) 
					{
						unsigned difference = points - pointsAttacked;
						moneyOfAttacker += difference;

						if (moneyOfAttackedPlayer > difference) 
						{
							moneyOfAttackedPlayer -= difference;
						}
						else 
						{
							moneyOfAttackedPlayer = 1;
						}

						storeMoney(name.c_str(), moneyOfAttacker);
						storeMoneyInPurchase(name.c_str(), moneyOfAttacker);
						storeMoney(playerName.c_str(), moneyOfAttackedPlayer);
						storeMoneyInPurchase(playerName.c_str(), moneyOfAttackedPlayer);

						std::cout << "CONGRATULATIONS,ATTACKER WON THE GAME!" << std::endl;
					}
					else if (points < pointsAttacked) 
					{
						unsigned difference = pointsAttacked - points;

						difference *= 2;
						if (moneyOfAttacker > difference) 
						{
							moneyOfAttacker -= difference;
						}
						else
						{
							moneyOfAttacker = 1;
						}
						moneyOfAttackedPlayer += 50;

						storeMoney(name.c_str(), moneyOfAttacker);
						storeMoneyInPurchase(name.c_str(), moneyOfAttacker);
						storeMoney(playerName.c_str(), moneyOfAttackedPlayer);
						storeMoneyInPurchase(playerName.c_str(), moneyOfAttackedPlayer);
						std::cout << "ATTACKED WON THE GAME!" << std::endl;
					}
					else 
					{
						if (moneyOfAttacker < 50)
						{
							moneyOfAttacker = 1;
						}
						else 
						{
							moneyOfAttacker -= 50;
						}
						std::cout << "ATTACKED WON THE GAME!" << std::endl;
						storeMoney(name.c_str(), moneyOfAttacker);
						storeMoneyInPurchase(name.c_str(), moneyOfAttacker);
					}
				}
			}
		}

		else{
			if (moneyOfAttackedPlayer <= points)
			{
				moneyOfAttackedPlayer = 1;
				moneyOfAttacker += 50;
				storeMoney(playerName.c_str(), moneyOfAttackedPlayer);
				storeMoney(name.c_str(), moneyOfAttacker);
				storeMoneyInPurchase(name.c_str(), moneyOfAttacker);
				storeMoneyInPurchase(playerName.c_str(), moneyOfAttackedPlayer);
				std::cout << "ATTACKER WON GAME...." << std::endl;
			}
			else 
			{
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




void Player::signUp()const
{
	MyString name, surname, email, password;
	std::cout << "Enter player name: ";
	std::cin >> name;
	std::cout << "Enter player surname: ";
	std::cin >> surname;
	std::cout << "Enter player email: ";
	std::cin >> email;
	std::cout << "Enter  player password(Password must contatin at least one upper_case,one lower_case,one number or it will be invalid): " << std::endl;
	std::cin >> password;

	Player pl(name.c_str(), surname.c_str(), email.c_str(), password.c_str(), 150);
	storeInFilePlayers(pl, "player.txt");
}
