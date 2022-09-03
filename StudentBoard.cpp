#include "Board.hpp"
#include "BoardValues.hpp"

#include <algorithm>
#include <iostream>
#include<string>
#include<iomanip>

using namespace std;


/*****************************************************************
constructor constructs the board of size height x width
*****************************************************************/
Board::Board()
{
	grid = new int[HEIGHT * WIDTH];
	for (int i = 0; i < HEIGHT * WIDTH; ++i)
		grid[i] = 0;
}
//copy constructor
/*****************************************************************
 copy constructor
*****************************************************************/
Board::Board(const Board& other)
{
	this->grid = new int[HEIGHT * WIDTH];
	for (int i = 0; i < HEIGHT * WIDTH; ++i)
		this->grid[i] = other.grid[i];
	this->visible = other.visible;
}


/*****************************************************************
operator overloaded
*****************************************************************/
Board& Board::operator=(const Board& other)
{
	Board temp;
	for (int i = 0; i < HEIGHT * WIDTH; ++i)
		temp.grid[i] = other.grid[i];
	temp.visible = other.visible;
	return temp;
}

/*****************************************************************
deconstructor
*****************************************************************/
Board::~Board()
{
	delete[] grid;
}

//setter to set visible
void Board::setVisible(bool v)
{
	visible = v;
}


/*****************************************************************
index operator overloaded(Provided by the instructor)
@param index
@return the grid
*****************************************************************/
int& Board::Internal::operator[](int index)
{
	if (index >= WIDTH)
	{
		throw std::out_of_range(std::to_string(index) + " is greater value than or equal to grid width of " + std::to_string(WIDTH));
	}
	return _grid[index];
}

Board::Internal Board::operator[](int index)
{
	if (index >= HEIGHT)
	{
		throw std::out_of_range(std::to_string(index) + " is greater value than or equal to grid height of " + std::to_string(HEIGHT));
	}
	return Board::Internal(grid + (index * WIDTH));
}


/*****************************************************************
//output operator overloaded
@param ostream and board
@return os
*****************************************************************/
std::ostream& operator<<(std::ostream& os, Board& b)
{
//it will print the player board
	if (b.visible == true)
	{
		cout << "-----------Player-----------\n";
		cout << "  " << setw(5);
		for (int i = 0; i < WIDTH; ++i)
			cout << i << setw(5);
		cout << endl;
		for (int i = 0; i < HEIGHT; ++i)
		{
			cout << i << setw(5);
			for (int j = 0; j < WIDTH; ++j)
			{
				cout << b[i][j] << setw(5);
			}
			cout << endl;
		}
		return os;
	}
	//it will print the computers board
	else
	{
		cout << "------------PC-------------\n";
		cout << "  " << setw(5);
		for (int i = 0; i < WIDTH; ++i)
			cout << i << setw(5);
		cout << endl;
		for (int i = 0; i < HEIGHT; ++i)
		{
			cout << i << setw(5);
			for (int j = 0; j < WIDTH; ++j)
			{
				if (b[i][j] != 'C'&& b[i][j] != 'D'&& b[i][j] != 'P'&& b[i][j] != 'B'&& b[i][j] != 'S')
				{
					cout << b[i][j] << setw(5);
				}
				else
					cout << "0" << setw(5);
			}
			cout << endl;
		}
		return os;
	}
}


/*****************************************************************
 /it will count scores
 @return the count of the board
*****************************************************************/
int Board::count() const
{
	Board temp = *this;
	int count = 17;
	if (visible == true) {
		for (int i = 0; i < HEIGHT; ++i)
		{
			for (int j = 0; j < WIDTH; ++j)
				if (temp[i][j] == 'o')
					count--;
		}
	}
	else {
		for (int i = 0; i < HEIGHT; ++i)
		{
			for (int j = 0; j < WIDTH; ++j)
				if (temp[i][j] == 'x')
					count--;
		}
	}
	return count;
}


/*****************************************************************
output operator overloaded to count score of the boards
@param board and copy
@return true or false based on count
*****************************************************************/
bool Board::operator<(const Board& other)
{
	if (this->count() < other.count())
		return true;
	return false;
}
