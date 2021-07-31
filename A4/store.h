#include "book.h"
#define DEBUG 1

class Store {
private:
	double amount;
	Book *bookList;
	/* Ensure capacityBookList - sizeBookList <= 5 */
	int sizeBookList;
	int capacityBookList;

public:
	Store();
	~Store();
	bool SetAmount(const double _a);					// true if valid input
	void AddBook(const char* t, const char* a, Genre g, double p);
	void ExpandBookList();
	void ShrinkBookList();
	void SearchBookByAuthor(const char* author) const;
	void SearchBookByTitle(const char* title) const;
	void SellBook(const char* title);
	void Display() const;
	void DisplayByGenre(const Genre& genreType) const;
	void PrintAmount() const;

private:
	void ChangeListCapacity(int newCapacity);
	void DeleteBookList();
	void PrintHeader() const;

};
