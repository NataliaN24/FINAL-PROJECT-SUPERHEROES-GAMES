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

	Player& addPlayers(const MyString& name, const  MyString& surname, const  MyString& email, const  MyString& password, const  unsigned int money)const;//DONE YES

	void signUp()const;//DONE YES
	void addAnotherAdmin()const;//DONE YES

	Superhero& addSuperhero();//DONE YES
	void seeInfoOfPlayers()const;//DONE YES
	void seeInfoOfSoldSuperheroes()const;//DONE 
	void deletePlayer(const MyString& email, const MyString& password, const MyString& playerName);//DONE YES
};
Superhero getSuperheroDetails();//DONE
void addSuperhero1(const Superhero& superhero);//DONE
void addSuperheroes3(int numSuperheroes);//DONE
void storeInFile(const Admin& admins, const MyString& filename);//DONE