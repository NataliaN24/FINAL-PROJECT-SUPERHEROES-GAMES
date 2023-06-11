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


//Superhero* Superhero::clone()const {
//	return new Superhero(*this);
//}

Superhero::PowerType readPowertypefrominput(const MyString& input) {

	if (input == "fire") {
		return Superhero::fire;
	}
	else if (input == "water") {
		return Superhero::water;
	}
	else
		return Superhero::earth;
}