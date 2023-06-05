#pragma once
#include<iostream>
#include<fstream>
#include<cstring>
#include <sstream>
#include"MyString.h"
#include"Superhero.h"
#include"Player.h"
 
class Admin
{
	MyString name;
	MyString surname;
	MyString email;
	MyString password;
	int numOfAdmins;
public:
	Admin() = default;
	Admin(const MyString& name, const MyString& surname, const MyString& email, const MyString& password);

	void setName(const MyString& name);
	void setSurname(const MyString& surname);
	void setEmail(const MyString& email);
	void setPassword(const MyString& password);

	const MyString& getName()const;
	const MyString& getSurname()const;
	const MyString& getEmail()const;
	const MyString& getPassword()const;

	Player& addPlayers(const MyString& name, const  MyString& surname, const  MyString& email, const  MyString& password, const  unsigned int money)const;//DONE

	void signUp()const;//DONE
	bool logIn()const;//DONE

	void addAnotherAdmin()const;//DONE
	void seeInfoOfAdmins()const;//DONE
	Superhero& addSuperhero();//DONE
	void seeInfoOfPlayers()const;//DONE
	void seeInfoOfSoldSuperheroes()const;//DONE
	void deletePlayer(const MyString& email, const MyString& password, const MyString& playerName);
};
void storeInFile(const Admin& admins, const MyString& filename);//DONE
Superhero getSuperheroDetails();//DONE
void addSuperhero1(const Superhero& superhero);//DONE
void addSuperheroes3(int numSuperheroes);//DONE