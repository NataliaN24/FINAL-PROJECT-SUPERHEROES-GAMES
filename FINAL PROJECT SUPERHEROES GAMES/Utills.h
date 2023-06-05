#pragma once
#include<iostream>
#include<cstring>
#include"MyString.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)


bool isLower(char ch);
bool isSymbol(char ch);
void toUpper(char& str);
unsigned charToDigit(char ch);
unsigned convertToNumber(const char* str);
int extractFields(const char* line, char fields[][50], int maxFields);
void reverseString(char* str, int length);
MyString reverseBalance(int balance);
void showPowerType(unsigned power);
void showAttack(unsigned attackMode);
unsigned extractBalance(const char* balanceStr);