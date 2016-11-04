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
	strcpy_s(fullName, "");
	strcpy_s(homePhone, "");
	strcpy_s(mobilePhone, "");

}

void PhoneBook::entryPhoneBook(char fn[], char hp[], char mp[])
{
	strcpy_s(fullName, fn);
	strcpy_s(homePhone, hp);
	strcpy_s(mobilePhone, mp);
}

void PhoneBook::displayPhoneBook()
{
	printf("-------------\n");
	printf("Full Name:\n%s\n", fullName);
	printf("Home Phone:\n%s\n", homePhone);
	printf("Mobile Phone:\n%s\n", mobilePhone);
	printf("-------------\n");
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
	delete myEntries;
}

void EntryList::setFileName(char f[])
{
	strcpy_s(fileName, f);
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
		cout << "Entry Number: " << i + 1 << endl;
		myEntries[i]->displayPhoneBook();

		if ((i + 1) % 5 == 0)
		{
			char answer;
			cout << "Type any character and press Enter to continue" << endl;
			cin >> answer;
			cin.ignore();
		}
	}
}

int EntryList::saveEntryList()
{
	//ios::trunc by default, so this will make the string compare much easier.
	ofstream output(fileName);
	if (!output)
	{
		cout << "You definitely did something wrong." << endl;
		return -1;
	}
	
	for (int i = 0; i < entryCount; i++)
	{
		//// Does not print duplicate entries to the phone book
		//if (i > 0)
		//{
		//	for (int j = 0; j < entryCount && j < i; j++)
		//	{
		//		if (strcmp(myEntries[i]->fullName, myEntries[j]->fullName) == 0)
		//		{
		//			++i;
		//		}
		//	}
		//}

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
	EntryList *entryCount;

	//Create a new PhoneBook object
	EntryList *eList = new EntryList();

	//Filename Get and Set
	cout << "Please enter the full path filename." << endl;
	gets_s(fileName);
	eList->setFileName(fileName);

	//Read in any existing file
	eList->readEntryList();
	if (eList->getEntryCount() == 0 || eList->getEntryCount() < 100)
	{
		cout << "Currently, there are " << eList->getEntryCount() << " entries in your phone book!" << endl;

		cout << "Would you like to add a new entry to your phonebook?" << endl;
		cout << "Y for Yes" << endl;
		cout << "Any other key for Nope" << endl;
		cin >> answer;

		while (answer == 'Y' || answer == 'y')
		{
			cin.ignore();
			cin.clear();

			cout << "Enter a full name." << endl;
			gets_s(fullName);
			cout << "Enter " << fullName << "'s home phone number." << endl;
			cout << "Please use the format (555) 555-5555.  Thank you." << endl;
			gets_s(homePhone);
			cout << "Enter " << fullName << "'s mobile phone number." << endl;
			cout << "Please use the format (555) 555-5555.  Thank you." << endl;
			gets_s(mobilePhone);

			PhoneBook *myPhoneBook = new PhoneBook();
			myPhoneBook->entryPhoneBook(fullName, homePhone, mobilePhone);
			eList->addEntryToList(myPhoneBook);

			cout << "Would you like to enter another wonderful person?" << endl;
			cout << "Y for Yes or any other key for Nope." << endl;
			cin >> answer;
		}
	}
	
	else
	{
		cout << "I'm sorry, but this Phone Book is full.  Please create a new Phone Book file." << endl;
		cout << "For your viewing pleasure, I will display the contents of the Phone Book that you requested." << endl;
	}

	// This shows the list
	eList->showEntryList();
	eList->saveEntryList();

    return 0;
}

