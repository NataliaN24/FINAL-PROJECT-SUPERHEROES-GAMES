#pragma once
#include"MyString.h"
#include"Superhero.h"
#include<iostream>
#include<fstream>

class SuperheroesCollection
{
	Superhero** superheroes;

	size_t size;
	size_t capacity;

	void copyFrom(const  SuperheroesCollection& other);
	void moveFrom(SuperheroesCollection&& other)noexcept;
	void resize();
	void free();

public:

	SuperheroesCollection() = default;
	~SuperheroesCollection();
	SuperheroesCollection(const SuperheroesCollection& other);
	SuperheroesCollection(SuperheroesCollection&& other)noexcept;
	SuperheroesCollection& operator=(SuperheroesCollection&& other)noexcept;
	SuperheroesCollection& operator=(const SuperheroesCollection& other);

	void seeInfoOfSuperheroes(const MyString& filename)const;
	unsigned   getPowerTypeOfSuperhero(const MyString& name)const;
	unsigned  showPriceOfSuperhero();
	unsigned showPointsOfSuperhero(const MyString& name)const;
	unsigned showAttackMode(const MyString& name)const;

	void storeAttackMode(const MyString& name, unsigned input)const;

};

void storeInFileSuperheroes(const Superhero& superheroes, const  MyString& filename);