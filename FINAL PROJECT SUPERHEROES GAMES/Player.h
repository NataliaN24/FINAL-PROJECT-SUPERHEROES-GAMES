#pragma once
#include<iostream>
#include<fstream>
#include"MyString.h"
#include"Superhero.h"
#include"User.h"
#include"SuperheroesCollection.h"

class Player :public User
{
	Superhero* purchased_superhero;
	unsigned int money;

	void copyFrom(const Player& other);
	void moveFrom(Player&& other)noexcept;
	void free();

public:

	Player();
	Player(const MyString& name, const MyString& surname, const MyString& email, const MyString& password, unsigned int money);
	Player(const Player& other);
	Player(Player&& other)noexcept;
	Player& operator=(const Player& other);
	Player& operator=(Player&& other) noexcept;
	~Player();

	void signUp()const override ;
	void setMoney(unsigned int money);
	const unsigned int getMoney()const;

	void setAttackingMode(const MyString& name);

	void seeSuperheroes();

	void seeInfoByPlayers();
	void PlayersPLUSSuperheroes();
	void deleteProfile(const MyString& email, const MyString& password)const;
	void deleteFromPurchase(const MyString& name)const;
	void deletePlayerProfile(const MyString& email, const MyString& password, const MyString& name)const;

	unsigned showBalance(const MyString& email)const;
	unsigned extractBalanceFromFile(const MyString& filename, const  MyString& identifier, unsigned fieldIndex)const; 
	unsigned getMoney(const MyString& playername);
	bool checkIfPlayerhasPurchased(const MyString& playername)const;

	void purchaseASuperhero();
	void buySuperhero();

	bool upgradeSuperhero(unsigned money, const  MyString& name); 
	
	void storePointsInFileOfAttacker(unsigned points, const MyString& name)const;
	void storePointsInFileOfAttackerofpurchase(unsigned points, const MyString& name)const; 
	unsigned playingTheGame(unsigned& pointsToBeDoubled, const MyString& name);

	void storeMoney(const MyString& name, unsigned money)const;
	void storeMoneyInPurchase(const MyString& name, unsigned money)const;

	void attack();
	
};

void whoWonTheGame(unsigned pointsOfAttaacker, unsigned pointsOfAttacked);
void storeInFilePlayers(const Player& players, const  MyString& filename);