#include <iostream>
#include <cmath>
#include <iomanip>

#define DEFAULT_BORDER '#'
#define DEFAULT_FILL '*'
#define MAX_SIZE 39
#define MIN_SIZE 1

class Diamond {

private:
	int size; 										// length of side 1 <= size <= 39
	char borderChar;
	char fillChar;

public:
	Diamond(int _size, 								\
			char _borderChar=DEFAULT_BORDER, 		\
			char _fillChar=DEFAULT_FILL);

	int GetSize() const;
	int Perimeter() const; 							// perimeter of diamond
	double Area() const; 							// area of diamond
	void Grow(); 									// increase size by 1
	void Shrink(); 									// decrease size by 1 
	void SetBorder(char newBorder);					// setting up borderChar
	void SetFill(char newFill);						// setting up fillChar
	void Draw() const; 								// draw diamond on screen
	void Summary() const;							// a summary of diamond class
private:
	void SetSizeInBounds(int _size);				// set size within limits of 1 to 39
	void PrintHalfDiamond(int numLines, 			\
						  int numSpaces, 			\
						  int deltaSpace) const;
};
