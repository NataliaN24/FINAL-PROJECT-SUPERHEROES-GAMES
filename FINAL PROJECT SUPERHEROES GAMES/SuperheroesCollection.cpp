#include"SuperheroesCollection.h"


void storeInFileSuperheroes(const Superhero& superheroes, const  MyString& filename) {
	std::ofstream file(filename.c_str(), std::ios::app);
	if (!file.is_open()) {
		throw std::runtime_error("Unable to open file for reading.");

	}
	file << superheroes.getName() << "," << superheroes.getSurname() << "," << superheroes.getNickname() << "," << superheroes.getPowerType() << ","
		<< superheroes.getPower() << "," << superheroes.getPurchasePrice() << "," << superheroes.getAttackMode() << std::endl;
	file.close();
}

void  SuperheroesCollection::seeInfoOfSuperheroes(const MyString& filename)const {

	std::ifstream inFile(filename.c_str());

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

unsigned SuperheroesCollection::showPriceOfSuperhero() {
	std::cout << "Enter the name of superhero to see its price: " << std::endl;
	MyString name;
	std::cin >> name;
	return getFieldValue("superheroes.txt", name, 5);
}

unsigned SuperheroesCollection::getPowerTypeOfSuperhero(const MyString& name) const {
	return getFieldValue("purchased_superheroes.txt", name, 3);
}

unsigned SuperheroesCollection::showPointsOfSuperhero(const MyString& name) const {
	return getFieldValue("purchased_superheroes.txt", name, 4);
}

unsigned SuperheroesCollection::showAttackMode(const MyString& name) const {
	return getFieldValue("purchased_superheroes.txt", name, 6);
}



void SuperheroesCollection::storeAttackMode(const MyString& name, unsigned input)const {
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

		if (fieldNum == 7 && strcmp(fields[0], name.c_str()) == 0) {
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

	if (remove("purchased_superheroes.txt") == 0 && rename("temp.txt", "purchased_superheroes.txt") == 0) {
		std::cout << "You just updated the attack mode of the superhero." << std::endl;
	}
	else {
		std::cout << "Error: Failed to update player file." << std::endl;
	}


}


void SuperheroesCollection::copyFrom(const  SuperheroesCollection& other) {
	superheroes = new Superhero * [other.capacity];
	size = other.size;
	capacity = other.capacity;
	//for (size_t i = 0; i < size; i++) {
	//	//superheroes[i] = new Superhero(*other.superheroes[i]); // Create new Superhero objects and copy the contents buffer overruns?
	//}
	superheroes = other.superheroes;

}
void  SuperheroesCollection::moveFrom(SuperheroesCollection&& other)noexcept {
	superheroes = other.superheroes;
	size = other.size;
	capacity = other.capacity;
	other.superheroes = nullptr;
	other.size = 0;
	other.capacity = 0;
}

void SuperheroesCollection::resize() {
	Superhero** newCollection = new Superhero * [capacity *= 2];
	for (size_t i = 0; i < size; i++)
		newCollection[i] = superheroes[i];
	delete[] superheroes;
	superheroes = newCollection;
}
void SuperheroesCollection::free() {

	for (size_t i = 0; i < size; i++) {
		delete superheroes[i];
	}
	delete[]superheroes;
}



SuperheroesCollection::~SuperheroesCollection() {
	free();
}
SuperheroesCollection::SuperheroesCollection(const SuperheroesCollection& other) {
	copyFrom(other);
}
SuperheroesCollection::SuperheroesCollection(SuperheroesCollection&& other)noexcept {
	moveFrom(std::move(other));
}
SuperheroesCollection& SuperheroesCollection:: operator=(SuperheroesCollection&& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}
SuperheroesCollection& SuperheroesCollection:: operator=(const SuperheroesCollection& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}