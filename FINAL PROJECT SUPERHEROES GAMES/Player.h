#pragma once
#include<iostream>
#include<fstream>
#include"MyString.h"
#include"Superhero.h"

class Player
{
	MyString name;
	MyString surname;
	MyString email;
	MyString password;
	Superhero* purchased_superhero;
	int numOfPlayers;
	unsigned int money;
	bool LoggedIn;

public:
	Player() = default;
	Player(const MyString& name, const MyString& surname, const MyString& email, const MyString& password, unsigned int money);

	void setName(const MyString& name);
	void setSurname(const MyString& surname);
	void setEmail(const MyString& email);
	void setPassword(const MyString& password);
	void setMoney(unsigned int money);

	const MyString& getName()const;
	const MyString& getSurname()const;
	const MyString& getEmail()const;
	const MyString& getPassword()const;
	const unsigned int getMoney()const;

	void setAttackingMode(const MyString& name);//DONE
	bool logIn(const MyString& email, const  MyString& password)const;//DONE
	void seeSuperheroes();//DONE
	void seeInfo();//DONE
	void seeInfoByPlayers();//DONE
	void PlayersPLUSSuperheroes();//DONE
	void deleteProfile(const MyString& email, const MyString& password)const;//DONE
	void deleteFromPurchase(const MyString& name)const;//DONE
	void deletePlayerProfile(const MyString& email, const MyString& password, const MyString& name)const;//DONE

	unsigned showBalance(const MyString& email)const;//DONE
	unsigned extractBalanceFromFile(const MyString& filename, const  MyString& identifier, unsigned fieldIndex)const;
	unsigned getMoney(const MyString& playername);//DONE WHY DO I HAVE SHOWBALANCE AND GETMONEY FOR THE SAME FC
	bool checkIfPlayerhasPurchased(const MyString& playername)const;//DONE

	void purchaseASuperhero();//DONE
	void buySuperhero();//DONE


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

void storeInFilePlayers(const Player& players, const  MyString& filename);//DONE
void whoWonTheGame(unsigned pointsOfAttaacker, unsigned pointsOfAttacked);//DONE
