#include <iostream>
#include <cstring>
#include "book.h"
#include "store.h"
using namespace std;

#define MAX_TITLE_LEN 20
#define MAX_AUTHOR_LEN 30

void GetBookAmount(double& amount) {
	cin >> amount;
	if (amount > 0)
		return;
	cout << "Must enter a positive price.  Please re-enter: ";
	GetBookAmount(amount);
}

void GetCashAmount(Store &store) {
	// get cash amount
	cout << "Enter starting amount of money in the store's cash register: ";
	double amount; cin >> amount;
	while(not store.SetAmount(amount)) cin >> amount;
}

void GetCharUpperCase(char& ch) {
	cin >> ch;
	if (ch >= 97)
		ch -= 32;
}

void GetTitleInput(char title[]) {
	cout << "Enter book title: ";
	cin.ignore();
	cin.getline(title, MAX_TITLE_LEN);
}

void GetAuthorInput(char author[]) {
	cout << "Enter author title: ";
	cin.getline(author, MAX_AUTHOR_LEN);
}

void PrintMenu() {
	cout << "Below is the menu:-\n";
	cout << "\n-------------------------------------------------\n";
	cout << "A:   Add a book to inventory\n"
			"F:   Find a book from inventory\n"
			"S:   Sell a book\n"
			"D:   Display the inventory list\n"
			"G:   Genre summary\n"
			"M:   Show this Menu\n"
			"X:   eXit the program\n";
	cout << "-------------------------------------------------\n\n";
	cout << "press the corresponding character: ";
}

void GetBookGenreType(Genre& genre) {
	char ch;
	GetCharUpperCase(ch);

	if (ch == 'F')
		genre = FICTION;
	else if (ch == 'M')
		genre = MYSTERY;
	else if (ch == 'S')
		genre = SCIFI;
	else if (ch == 'C')
		genre = COMPUTER;
	else {
		cout << "Invalid genre entry.  Please re-enter: ";
		GetBookGenreType(genre);
	}
}

void GetBookDetailsAndAdd(Store& store) {
	char title[MAX_TITLE_LEN + 1];
	GetTitleInput(title);

	char author[MAX_AUTHOR_LEN + 1];
	GetAuthorInput(author);

	Genre genre;
	cout << "Enter genre: ";
	GetBookGenreType(genre);

	double bookAmount;
	cout << "Enter Book Price: ";
	GetBookAmount(bookAmount);

	store.AddBook(title, author, genre, bookAmount);
}

void SearchBook(Store& store) {
	cout << "Press 'A' to search by Author\n"
			"Press 'T' to search by Title\n";
	char choice; 
	GetCharUpperCase(choice);

	if (choice == 'A') {
		cin.ignore();
		char author[MAX_AUTHOR_LEN + 1];
		GetAuthorInput(author);
		store.SearchBookByAuthor(author);
	}
	else if (choice == 'T') {
		char title[MAX_TITLE_LEN + 1];
		GetTitleInput(title);
		store.SearchBookByTitle(title);
	}
	else {
		cout << "Invalid character. Try again...\n\n";
		SearchBook(store);
	}
}

void SellBook(Store& store) {
	char title[MAX_TITLE_LEN + 1];
	GetTitleInput(title);
	store.SellBook(title);
}

void DisplayListByGenre(Store& store) {
	Genre genre;
	cout << "Enter genre: ";
	GetBookGenreType(genre);
	store.DisplayByGenre(genre);
}

void MenuDrivenCode(Store& store) {
	PrintMenu();
	char choice;
	GetCharUpperCase(choice);

	if (choice == 'A')
		GetBookDetailsAndAdd(store);
	else if(choice == 'F')
		SearchBook(store);
	else if(choice == 'S')
		SellBook(store);
	else if(choice == 'D')
		store.Display();
	else if(choice == 'G') {
		DisplayListByGenre(store);
	}
	else if(choice == 'M') {
		MenuDrivenCode(store);
		return;
	}
	else if(choice == 'X') {
		store.PrintAmount();
		return;
	}

	MenuDrivenCode(store);
}

void drive() {
	Store store;
	GetCashAmount(store);
	MenuDrivenCode(store);
}

void test1() {
	Store store;
	store.SetAmount(232.455);
	store.Display();
	store.AddBook("1", "a", FICTION, 12.4);
	store.AddBook("2", "b", COMPUTER, 12.44);
	store.AddBook("3", "a", FICTION, 5512.45);
	store.AddBook("4", "a", FICTION, 712.45);
	store.AddBook("5", "b", FICTION, 162.4);
	store.Display();
	store.AddBook("6", "c", SCIFI, 122.44);
	store.AddBook("7", "b", FICTION, 132.4);
	store.AddBook("8", "a", FICTION, 112.4);
	store.AddBook("9", "b", COMPUTER, 122.4);
	store.AddBook("10", "c", MYSTERY, 12.4);
	store.Display();
	store.SearchBookByAuthor("a");
	store.SearchBookByAuthor("vg");
	store.SearchBookByTitle("a");
	store.SearchBookByTitle("7");
	store.DisplayByGenre(FICTION);
	store.PrintAmount();
	store.SellBook("2");
	store.SellBook("3");
	store.SellBook("4");
	store.PrintAmount();
	store.SellBook("2");
	store.PrintAmount();
	store.SellBook("1");
	store.SellBook("10");
	store.SellBook("8");
	store.Display();
	store.SearchBookByAuthor("a");
	store.SearchBookByAuthor("vg");
	store.SearchBookByTitle("a");
	store.SearchBookByTitle("7");
	store.DisplayByGenre(FICTION);
	store.PrintAmount();
}

int main() {
	test1();
}
