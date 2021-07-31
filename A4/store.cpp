#include <cstddef>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "store.h"

Store::Store() {
	amount = 0;
	capacityBookList = 0;
	sizeBookList = 0;
	bookList = NULL;
}

Store::~Store() {
	std::cout << "**Calling From Destructor\n";
	DeleteBookList();
}

bool Store::SetAmount(const double _a) {
	if (_a > 0) {
		amount = _a;
		return true;
	}
	std::cout << "Must enter a positive price.  Please re-enter: ";
	return false;
}

void Store::AddBook(const char* t, const char* a, Genre g, double p) {
	ExpandBookList();							// ignore if not required
	bookList[sizeBookList++].Set(t, a, g, p);
	if (DEBUG)
		std::cout << "**Book Added....\n\n";
}

void Store::ExpandBookList() {
	if (capacityBookList == sizeBookList)
		ChangeListCapacity(capacityBookList + 5);
}

void Store::ShrinkBookList() {
	if (capacityBookList - sizeBookList > 5)
		ChangeListCapacity(capacityBookList - 5);
}

void Store::SearchBookByAuthor(const char* author) const {
	if (DEBUG)
		std::cout << "**Searching Store based on author...\n\n";
	bool header = false;
	for (int idx = 0 ; idx < sizeBookList ; idx++) {
		if (strcmp(bookList[idx].GetAuthor(), author) == 0) {
			if (not header){
				PrintHeader();
				header = true;
			}
			bookList[idx].Display();
		}
	}
}

void Store::SearchBookByTitle(const char* title) const {
	if (DEBUG)
		std::cout << "**Searching Store based on title...\n\n";
	for (int idx = 0 ; idx < sizeBookList ; idx++) {
		if (strcmp(bookList[idx].GetTitle(), title) == 0) {
			PrintHeader();
			bookList[idx].Display();
			return;
		}
	}
}

void Store::SellBook(const char* title) {
	for (int idx = 0 ; idx < sizeBookList ; idx++) {
		if (strcmp(bookList[idx].GetTitle(), title) == 0) {
			// add amount in cast register
			amount += bookList[idx].GetPrice();

			// remove book from list
			for(int i = idx + 1 ; i < sizeBookList ; i++)
				bookList[i - 1] = bookList[i];
			sizeBookList--;

			if (DEBUG)
				std::cout << "**Book sold...\n\n";

			ShrinkBookList();
			return;
		}
	}
}

void Store::Display() const {
	PrintHeader();
	for (int idx = 0 ; idx < sizeBookList ; idx++)
		bookList[idx].Display();

	std::cout << "\n\nTotal books: " << sizeBookList << "\n";
	PrintAmount();
}

void Store::DisplayByGenre(const Genre& genreType) const {
	if (DEBUG)
		std::cout << "**Searching Store based on Genre...\n\n";
	double total_cost = 0;
	int countBookGenre = 0;
	for (int idx = 0 ; idx < sizeBookList ; idx++) {
		if (bookList[idx].GetGenre() == genreType) {
			if (countBookGenre == 0)
				PrintHeader();
			bookList[idx].Display();
			countBookGenre++;
			total_cost += bookList[idx].GetPrice();
		}
	}
	std::cout << "\n\nTotal Books of this genre in Store: " << countBookGenre << "\n";
	std::cout << "Total cost of these books: " << total_cost << "\n\n";
}

void Store::PrintAmount() const {
	std::cout << "Current Amount in Store's Cash Register: "
			  << std::fixed << std::setprecision(2) << amount << "\n\n";
}

void Store::ChangeListCapacity(int newCapacity) {
	Book *newBookList = NULL;
	if (newCapacity > 0) {
		newBookList = new Book[newCapacity];
		for(int i = 0 ; i < sizeBookList ; i++) {
			newBookList[i] = bookList[i];
		}
	}

	DeleteBookList();

	bookList = newBookList;
	capacityBookList = newCapacity;
	if (DEBUG)
		std::cout << "\n**List Size changed to " << newCapacity << "\n\n";
}

void Store::DeleteBookList() {
	if (bookList != NULL) {
		if (DEBUG)
			std::cout << "**Booklist deleted...\n\n";
		delete [] bookList;
	}
}

void Store::PrintHeader() const {
	if (sizeBookList == 0)
		return;
	std::cout.width(30);
	std::cout << "Title" << "\t\t\t\t";
	std::cout.width(20);
	std::cout << "Author" << "\t\t\t";
	std::cout.width(8);
	std::cout << "Genre" << "\t\t";
	std::cout << "Price\n";
}
