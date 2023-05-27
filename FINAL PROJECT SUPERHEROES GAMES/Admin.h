#pragma once
#include<iostream>
#include<fstream>
#include<cstring>
#include <sstream>

#include"MyString.h" 
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

	void signUp();
	bool logIn();
	void addAnotherAdmin();
	void seeInfoOfAdmins();

};
void storeInFile(const Admin& admins, const  char* filename);

