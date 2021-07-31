#include <iostream>
#include <iomanip>
#include <cstring>
#include "book.h"

Book::Book() {
	price = 0;
	type = COMPUTER;
	for(int i = 0 ; i < 31 ; i++)
		title[i] = ' ';
	for(int i = 0 ; i < 21 ; i++)
		author[i] = ' ';
}

void Book::Set(const char* t, const char* a, Genre g, double p) {
	// copy title
	for(int i = 0 ; i < 31 ; i++)
		title[i] = t[i];
	// copy author name
	for(int i = 0 ; i < 21 ; i++)
		author[i] = a[i];
	type = g;
	price = p;
}

const char* Book::GetTitle() const {
	return title;
}

const char* Book::GetAuthor() const {
	return author;
}

double Book::GetPrice() const {
	return price;
}

Genre Book::GetGenre() const {
	return type;
}

// Format: Mutant Space Weasels				Bob Myers				Sci-Fi		 $	 5.95
void Book::Display() const {
	char *typeName = new char[10];
	if (type == FICTION)
		typeName = strcpy(typeName, "FICTION");
	else if(type == MYSTERY)
		typeName = strcpy(typeName, "MYSTERY");
	else if(type == COMPUTER)
		typeName = strcpy(typeName, "COMPUTER");
	else
		typeName = strcpy(typeName, "SCIFI");

	std::cout.width(30);
	std::cout << title << "\t\t\t\t";
	std::cout.width(20);
	std::cout << author << "\t\t\t";
	std::cout.width(8);
	std::cout << typeName << "\t\t";
	std::cout << "$  " << std::fixed << std::setprecision(2);
	std::cout.width(8);
	std::cout << price << "\n";
	delete [] typeName;
}
