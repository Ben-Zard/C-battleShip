/*******************************************************************
In this pro,ject I create a battleship game that would take a human
 position and play against a computer at random. It will switch between
 players until someone has won. This code is in C++ and includes a
 player on the local system.
 https://code-projects.org/battleship-game-in-c-with-source-code-2/
 I used the following site to understand more of the game logic that
 was needed. This included making the board and trying to avoid any
 C code style. This helped me to understand the use of constructors and
 deconstructors as well as overload methods to improve the game logic.
 I also used this site to understand the way to plot and check coordinate
 values.

@author Ben Zardus
@version CIS 343 Winter 2022
*****************************************************************/
#include "Board.hpp"
#include "Direction.hpp"
#include "Game.hpp"
#include "Ship.hpp"
#include <iostream>
#include <random>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <ctime>

using namespace std;

/*****************************************************************
The constructor will create the ship's vector and add ships to it.
 specify the ships and their values
*****************************************************************/
Game::Game()
{
	// vector<Ship> ships;
	Ship carrier(5, "Carrier", 'C');
	Ship Battle_Ship(4, "Battle Ship", 'B');
	Ship Destroyer(3, "Destroyer", 'D');
	Ship Submarine(3, "Submarine", 'S');
	Ship Petrol_Boat(2, "Petrol Boat", 'P');

	ships.push_back(carrier);
	ships.push_back(Battle_Ship);
	ships.push_back(Destroyer);
	ships.push_back(Submarine);
	ships.push_back(Petrol_Boat);

	player.setVisible(true);
}



/*****************************************************************
Begin Game let's user and then computer setup boards then calls run()
*****************************************************************/
void Game::beginGame()
{
	int turn = 0; // 0 mean human--1 mean pc
	for (int i = 0; i < 5; ++i)
		cout << ships[i] << endl;

	placeShips();
	placeShipsPC();

	run();
}


/*****************************************************************
Handle the human placing ships.
*****************************************************************/
void Game::placeShips()
{
	// it will place the ships of user

	int currentShip = 0;

	while (currentShip < ships.size())
	{
		bool placed = false;
		while (!placed)
		{
			int x = 0, y = 0;
			cout << "input Coordinates\n";
			cin >> x >> y;
			cout << endl;
			int dir;
			cout << "Horizontal/Verticle 0,1\n";
			cin >> dir;
			Direction d;
			if (dir == 0)
				d = HORIZONTAL;
			else
				d = VERTICAL;

			Ship ship(0, "", 't');
			if (currentShip == 0)
				ship = ships[currentShip];
			if (currentShip == 1)
				ship = ships[currentShip];
			if (currentShip == 2)
				ship = ships[currentShip];
			if (currentShip == 3)
				ship = ships[currentShip];
			if (currentShip == 4)
				ship = ships[currentShip];
			placed = place(x, y, d, ship, player);
			// placed = validPlace(x, y, d, ship);
			if (!placed)
				cout << "input Valid coordinates";
		}
		currentShip++;
	}
}

// static int currShip = 0;

/*****************************************************************
handles the PC placement and is random
*****************************************************************/
void Game::placeShipsPC()
{
	// it will place ships of computer
	srand(time(NULL));
	int currentShip = 0;
	while (currentShip < ships.size())
	{
		bool placed = false;
		while (!placed)
		{
			int x = rand() % 9, y = rand() % 9;
			int dir = rand() % 2;

			Direction d;
			if (dir == 0)
				d = HORIZONTAL;
			else
				d = VERTICAL;

			Ship ship(0, "", 't');
			if (currentShip == 0)
				ship = ships[currentShip];
			if (currentShip == 1)
				ship = ships[currentShip];
			if (currentShip == 2)
				ship = ships[currentShip];
			if (currentShip == 3)
				ship = ships[currentShip];
			if (currentShip == 4)
				ship = ships[currentShip];
			placed = place(x, y, d, ship, computer);
			// placed = validPlace(x, y, d, ship);
		}
		currentShip++;
	}
}



/*****************************************************************
Helper method that checks if it is safe to put a ship
at a particular spot with a particular direction.
@param The coordinates of X and Y and the Ship value and Board value
@return true or false based on placement parameters
*****************************************************************/
bool Game::place(const int &x, const int &y, Direction d, const Ship &s, Board &b)
{
	bool valid = false;
	// to place horizontal ships
	if (d == HORIZONTAL)
	{
		if (y + s.getSpaces() < WIDTH)
		{
			for (int i = 0; i < s.getSpaces(); ++i)
			{
				if (b[x][i + y] == 0)
					valid = true;
				else
					return false;
			}
			if (valid == true)
			{
				for (int i = 0; i < s.getSpaces(); ++i)
				{
					b[x][i + y] = s.getChr();
				}
				return true;
			}
		}
	}

	// to place verticle ships
	else
	{
		if (x + s.getSpaces() < HEIGHT)
		{
			for (int i = 0; i < s.getSpaces(); ++i)
			{
				if (b[i + x][y] == 0)
					valid = true;
				else
					return false;
			}
			if (valid == true)
			{
				for (int i = 0; i < s.getSpaces(); ++i)
				{
					b[i + x][y] = s.getChr();
				}
				return true;
			}
		}
	}
}


/*****************************************************************
Call human turn/computer turn until someone wins.
@return true or false based on turn count
*****************************************************************/
void Game::run()
{
	bool win = false;
	// it will print the boards and plays game until someone wins the game
	while (!win)
	{
		system("clear");
		cout << player << endl;
		cout << computer << endl;
		cout << "Score p/c=\t" << player.count() << "/" << computer.count() << endl;
		humanTurn();
		computerTurn();

		if (player.count() == 0 || computer.count() == 0)
			win = true;
	}
	if (player.count() < computer.count())
		cout << "Computer Wins\n";
	else
		cout << "Player Wins\n";
}
/*****************************************************************
if true humans will continue to pick a turn
@return true or false based on human choice
*****************************************************************/
void Game::humanTurn()
{
	while (true)
	{
		cout << "Attack Coordinates\n";
		int x, y;
		cin >> x >> y;
		cout << endl;
		if (x < HEIGHT && y < WIDTH)
		{
			if(computer[x][y]==0)
			{
				computer[x][y] = '_';
				break;
			}
			if (computer[x][y] == 'C' || computer[x][y] == 'S' || computer[x][y] == 'D' || computer[x][y] == 'P' || computer[x][y] == 'B')
			{
				computer[x][y] = 'x';
				break;
			}
			else if (computer[x][y] == '_' || computer[x][y] == 'x')
			{
				cout << "input correct coordinates\n";
			}
		}
		else
		{
			cout << "input correct coordinates\n";
		}
	}
}
void Game::computerTurn()
{
	while (true)
	{
		int x = rand() % 10, y = rand() % 10;
		if (x < HEIGHT && y < WIDTH)
		{
			if(player[x][y]==0)
			{
				player[x][y] = '_';
				break;
			}
			if (player[x][y] == 67 || player[x][y] == 66 || player[x][y] == 68 || player[x][y] == 83 || player[x][y] == 80)
			{
				player[x][y] = 'o';
				break;
			}
			else if (player[x][y] == '_' || player[x][y] == 'o')
			{
				cout << "input correct coordinates\n";
			}
		}
		else
		{
			cout << "input correct coordinates\n";
		}
	}
}


/*****************************************************************
Create a game instance and start. The main method to execute game logic
@param all methods
@return false once game is done
*****************************************************************/
int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	Game g;
	g.beginGame();

	return 0;
}
