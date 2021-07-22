#include "diamond.h"

Diamond::Diamond(int _size, 			\
				 char _borderChar,		\
				 char _fillChar) 
{
	SetSizeInBounds(_size);
	SetBorder(_borderChar);
	SetFill(_fillChar);
}

int Diamond::GetSize() const {
	return size;
}

int Diamond::Perimeter() const {
	int perimeter = 4.0 * size;
	return perimeter;
}

double Diamond::Area() const {
	double area = 2.0 * size * size * (sqrt(3) / 4.0);
	return area;
}

void Diamond::Grow() {
	SetSizeInBounds(size + 1);
}

void Diamond::Shrink() {
	SetSizeInBounds(size - 1);
}

void Diamond::SetBorder(char newBorder) {
	if (33 <= newBorder && newBorder <= 126)
		borderChar = newBorder;
	else
		borderChar = DEFAULT_BORDER;
}

void Diamond::SetFill(char newFill) {
	if (33 <= newFill && newFill <= 126)
		fillChar = newFill;
	else
		fillChar = DEFAULT_FILL;
}

void Diamond::Draw() const {
	// print upper half of diamond
	PrintHalfDiamond(size, size - 1, -1);

	// print lower half of diamond
	PrintHalfDiamond(size - 1, 1, 1);
}

void Diamond::Summary() const{
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "Size of diamond's side = " << GetSize() << " units.\n"
			     "Perimeter of diamond = " << Perimeter() << " units.\n"
				 "Area of diamond = " << Area() << " units.\n"
			     "Diamond looks like:\n";
	Draw();
}

void Diamond::SetSizeInBounds(int _size) {
	size = (_size < MIN_SIZE)? MIN_SIZE : ((_size > MAX_SIZE)? MAX_SIZE: _size);
}

/******************************************************************************
 * 
 * numLines: 	number of lines in one half, lower half has one line less
 * numSpaces: 	number of spaces in first line of any half
 * deltaSpace: 	-1 for upper half as number of spaces decrease with more 
 * 					lines while +1 for lower half for the opposite reason
 * 
 ******************************************************************************/
void Diamond::PrintHalfDiamond(int numLines, 			\
							   int numSpaces, 			\
							   int deltaSpace) const {
	for(int line = 1; line <= numLines ; line++) {

		// print spaces
		for(int space = 1 ; space <= numSpaces; space++)
			std::cout << " ";

		// print charaters
		int numCharacters = size - numSpaces;
		for(int i = 1 ; i <= numCharacters ; i++) {
			if (i == numCharacters)
				std::cout << borderChar << "\n";
			else if (i == 1)
				std::cout << borderChar << " ";
			else
				std::cout << fillChar << " ";
		}

		numSpaces += deltaSpace;
	}
}
