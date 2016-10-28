// INFO450PhonebookRedo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;

class PhoneBook
{
	char fullName[50];
	char homePhone[20];
	char mobilePhone[20];

public:
	PhoneBook();
	void entryPhoneBook(char fn[], char hp[], char mp[]);
	void displayPhoneBook();
	friend class EntryList;
};

PhoneBook::PhoneBook()
{
	strcpy(fullName, "");
	strcpy(homePhone, "");
	strcpy(mobilePhone, "");

}

void PhoneBook::entryPhoneBook(char fn[], char hp[], char mp[])
{
	strcpy(fullName, fn);
	strcpy(homePhone, hp);
	strcpy(mobilePhone, mp);
}

void PhoneBook::displayPhoneBook()
{
	printf("----------------------------------------\n");
	printf("Full Name:\n%s\n", fullName);
	printf("Home Phone:\n%s\n", homePhone);
	printf("Mobile Phone:\n%s\n", mobilePhone);
	printf("----------------------------------------\n");
}

class EntryList
{
	char fileName[100];
	int entryCount;
	PhoneBook **myEntries;

public:
	EntryList();
	~EntryList();
	void setFileName(char f[]);
	int getEntryCount();
	void addEntryToList(PhoneBook *p);
	void showEntryList();
	int saveEntryList();
	void readEntryList();
};

EntryList::EntryList()
{
	myEntries = new PhoneBook*[100];
	entryCount = 0;
}

EntryList::~EntryList()
{
	delete EntryList;
}

void EntryList::setFileName(char f[])
{
	strcpy_s(filename, f);
}

void EntryList::addEntryToList(PhoneBook *p)
{
	myEntries[entryCount] = p;
	entryCount++;
}

int EntryList::getEntryCount()
{
	return entryCount;
}

int main()
{
    return 0;
}

