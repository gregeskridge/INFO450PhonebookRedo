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

void EntryList::showEntryList()
{
	for (int i = 0; i < entryCount; i++)
	{
		myEntries[i]->displayPhoneBook();
	}
}

int EntryList::saveEntryList()
{
	ofstream output(fileName);
	if (!output)
	{
		cout << "You definitely did something wrong." << endl;
		return -1;
	}

	for (int i = 0; i < entryCount; i++)
	{
		output << myEntries[i]->fullName << "|";
		output << myEntries[i]->homePhone << "|";
		output << myEntries[i]->mobilePhone << endl;
	}
	output.close();
	return 0;
}

void EntryList::readEntryList()
{
	ifstream infile(fileName);

	if (!infile)
	{
		return;
	}

	while (!infile.eof())
	{
		PhoneBook *ptr;
		char fName[50];
		char hPhone[20];
		char mPhone[20];

		infile.getline(fName, 50, '|');
		if (strlen(fName))
		{
			infile.getline(hPhone, 20, '|');
			infile.getline(mPhone, 20);
			ptr = new PhoneBook();
			ptr->entryPhoneBook(fName, hPhone, mPhone);
			addEntryToList(ptr);
		}
	}

	infile.close();
}

int main()
{
	char answer = 'y';
	char fullName[50];
	char homePhone[20];
	char mobilePhone[20];
	char fileName[50];

	//Create a new PhoneBook object
	EntryList *eList = new EntryList();

	//Filename Get and Set
	cout << "Please enter the full path filename." << endl;
	gets_s(fileName);
	eList->setFileName(fileName);

	//Read in any existing file
	eList->readEntryList();
	if (eList->getEntryCount() == 0)
	{
		cout << "You've got yourself an empty list.  Commence to recording." << endl;
	}

	else
	{
		cout << "Currently, there are " << eList->getEntryCount() << "entries." << endl;
	}

	cout << "Would you like to add a new entry to your phonebook?" << endl;
	cout << "Y for Yes" << endl;
	cout << "Any other key for Nope" << endl;
	cin >> answer;



    return 0;
}

