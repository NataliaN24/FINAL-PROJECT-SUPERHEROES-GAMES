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

	void signUp()const;
	void setMoney(unsigned int money);
	const unsigned int getMoney()const;


	void setAttackingMode(const MyString& name);//DONE WORKS

	void seeSuperheroes();//DONE WORKS

	void seeInfoByPlayers();//DONE WORKS
	void PlayersPLUSSuperheroes();//DONE
	void deleteProfile(const MyString& email, const MyString& password)const;//DONE WORKS
	void deleteFromPurchase(const MyString& name)const;//DONE  WORKS
	void deletePlayerProfile(const MyString& email, const MyString& password, const MyString& name)const;//DONE WORKS

	unsigned showBalance(const MyString& email)const;//DONE WORKS
	unsigned extractBalanceFromFile(const MyString& filename, const  MyString& identifier, unsigned fieldIndex)const; //INCLUDE THIS FC IN UTILLS WORKS 
	unsigned getMoney(const MyString& playername);//DONE WORKS
	bool checkIfPlayerhasPurchased(const MyString& playername)const;//DONE WORKS

	void purchaseASuperhero();//DONE WORKS
	void buySuperhero();//DONE WORKS


	bool upgradeSuperhero(unsigned money, const  MyString& name);//DONE BUT CHECK
	//void storePointsToFile(MyString filename, unsigned points, MyString name, int fieldIndex);//DONE BUT REVIEW TEST THEM

	void storePointsInFileOfAttacker(unsigned points, const MyString& name)const;//DONE
	void storePointsInFileOfAttackerofpurchase(unsigned points, const MyString& name)const;//DONE 
	unsigned playingTheGame(unsigned& pointsToBeDoubled, const MyString& name);//DONE

	void storeMoneyToFile(const MyString& filename, const MyString& name, unsigned money, int fieldIndex)const;//DONE
	void storeMoney(const MyString& name, unsigned money)const;//DONE
	void storeMoneyInPurchase(const MyString& name, unsigned money)const;//DONE

	void attack();
	void wayOfPlayingWhenPowersAreDiff(unsigned power, unsigned powerAttacked, unsigned points, unsigned pointsAttacked, const MyString& nameOfSuperhero, const MyString& attackedSuperhero);
	void wayOfPlayingWhenPowersAreSame();


};

void whoWonTheGame(unsigned pointsOfAttaacker, unsigned pointsOfAttacked);//DONE
void storeInFilePlayers(const Player& players, const  MyString& filename);//DONE