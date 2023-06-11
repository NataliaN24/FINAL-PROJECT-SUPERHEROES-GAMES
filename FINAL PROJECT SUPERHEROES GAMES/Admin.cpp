#include "Admin.h"

Admin::Admin(const MyString& name, const MyString& surname, const MyString& email, const MyString& password) :User(name, surname, email, password) {}


void Admin::signUp()const
{
	MyString name, surname, email, password;
	std::cout << "Enter admin name: ";
	std::cin >> name;
	std::cout << "Enter admin surname: ";
	std::cin >> surname;
	std::cout << "Enter admin email: ";
	std::cin >> email;
	std::cout << "Enter admin password(Password must contatin at least one upper_case,one lower_case,one number or it will be invalid): " << std::endl;
	std::cin >> password;

	Admin admin(name.c_str(), surname.c_str(), email.c_str(), password.c_str());
	storeInFile(admin, "admin.txt");
}

void Admin::addAnotherAdmin()const {
	signUp();
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

	return Superhero(name.c_str(), surname.c_str(), nickname.c_str(), power_type, power, purchase, sold);
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
	player.seeInfo("player.txt");

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