#pragma once
#include"MyString.h"
#include"User.h"
#include"Player.h"
#include"Superhero.h"
#include"Utills.h"
#include<fstream>
#include<cstring>
#include <sstream>
#include"SuperheroesCollection.h"
#include<iostream>
#include <stdexcept> 

class Admin :public User
{

public:
	Admin() = default;
	Admin(const MyString& name, const MyString& surname, const MyString& email, const MyString& password);

	Player& addPlayers(const MyString& name, const  MyString& surname, const  MyString& email, const  MyString& password, const  unsigned int money)const;

	void signUp()const;
	void addAnotherAdmin()const;

	Superhero& addSuperhero();
	void seeInfoOfPlayers()const;
	void seeInfoOfSoldSuperheroes()const; 
	void deletePlayer(const MyString& email, const MyString& password, const MyString& playerName);
};
Superhero getSuperheroDetails();
void addSuperhero1(const Superhero& superhero);
void addSuperheroes3(int numSuperheroes);
void storeInFile(const Admin& admins, const MyString& filename);