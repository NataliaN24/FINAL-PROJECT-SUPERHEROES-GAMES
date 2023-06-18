#pragma once
#include"MyString.h"
#include"Utills.h"
#include <fstream>

class User
{
	MyString name;
	MyString surname;
	MyString email;
	MyString password;

public:

	User();
	User(const MyString& name, const MyString& surname, const MyString& email, const MyString& password);

	bool logIn(const MyString& email, const  MyString& password, const MyString& filename)const;

	void setName(const MyString& name);
	void setSurname(const MyString& surname);
	void setEmail(const MyString& email);
	void setPassword(const MyString& password);

	const MyString& getName()const;
	const MyString& getSurname()const;
	const MyString& getEmail()const;
	const MyString& getPassword()const;

	void seeInfo(const MyString& filename)const;
	virtual void signUp()const = 0;

	virtual ~User() = default;

};