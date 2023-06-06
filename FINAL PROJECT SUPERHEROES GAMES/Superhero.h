#pragma once
#include<iostream>
#include<fstream>
#include"MyString.h"
class Superhero
{
	MyString name;
	MyString surname;
	MyString nickname;

	unsigned power;
	unsigned purchase;
	bool attackMode;

public:

	enum PowerType { fire, water, earth, none }powerType;
	Superhero() = default;
	Superhero(const MyString& name, const MyString& surname, const MyString& nickname,
		const PowerType& powertype, unsigned power, unsigned purchase, bool attack_mode);

	void setName(const MyString& name);
	void setSurname(const MyString& surname);
	void setNickname(const MyString& nickname);
	void setPowerType(const PowerType& powertype);
	void setPower(unsigned power);
	void setPurchasePrice(unsigned purchase);
	void setAttackMode(bool attack_mode);

	const MyString& getName()const;
	const MyString& getSurname()const;
	const MyString& getNickname()const;
	const PowerType& getPowerType()const;
	unsigned getPower()const;
	unsigned getPurchasePrice()const;
	bool getAttackMode()const;
	void seeInfoOfSuperheroes();
	PowerType readPowertypefrominput();
	unsigned   getPowerTypeOfSuperhero(const MyString& name)const;

	unsigned  showPriceOfSuperhero();
	unsigned showPointsOfSuperhero(const MyString& name)const;
	unsigned showAttackMode(const MyString& name)const;

	void storeAttackMode(const MyString& name, unsigned input)const;
	/*void setAttackMode(bool attackMode);
	bool getAttackMode() const;*/




};

void storeInFileSuperheroes(const Superhero& superheroes, const  MyString& filename);

