#pragma once
#include "Header.h";
#include <iostream>;
#include <string>;
using namespace std;

gamesession::gamesession()
{
	cout << "Начата новая игра в крестики-нолики. Вы будете играть за крестики - Х.\n" <<
		"Вы хотите ходить первым в игре? (Y/N): ";
	char responce;
	cin >> responce;
	//cin.ignore();
	playerturn = (responce == 'Y');

	for (int i = 0; i < FIELDLEN * FIELDLEN; i++)
	{
		field[i] = status::Blank;
	}
}


void gamesession::display()
{
	system("cls");
	cout << "Игра в разгаре. Ваш ход, игрок.\n";
	for (int i = 0; i < FIELDLEN * FIELDLEN; i++)
	{
		switch (field[i])
		{
		case status::Zero:
			cout << "O ";
			break;
		case status::Cross:
			cout << "X ";
			break;
		default:
			cout << "_ ";
			break;
		}
		if ((i + 1) % 3 == 0)
			cout << '\n';
	}
}


bool gamesession::player_turn()
{
	cout << "Игрок, ваш ход - введите координаты позиции, в которую хотите разместить свой \"крестик\"\n"
		<< "Считаем, что позиция левого нижнего верхнего угла - A-1, а центральная верхняя позиция - Б-1.\n";
	string responce;
	cin >> responce;
	cin.ignore();
	int xcord, ycord;

	if (responce.substr(0, responce.find('-')) == "A")
		xcord = 0;
	else if (responce.substr(0, responce.find('-')) == "B")
		xcord = 1;
	else
		xcord = 2;
	responce.replace(0, responce.find('-') + 1, "");
	// Debug measure.
	cout << "Testing msg: responce sec cord left )" << responce << "(\n";

	// As '1' = 49. To normalize the ycord.
	ycord = int(char(responce[0])) - 49;
	
	field[ycord * 3 + xcord] = status::Cross;

	return havewinfor(status::Cross);
}


bool gamesession::bot_turn()
{

	// Getting random position.
	int randmod = (rand() % blanks());
	int spaceswas;
	spaceswas = 0;
	int chosen = 0;
	while (spaceswas != randmod)
	{
		if (field[chosen] == status::Blank)
			spaceswas++;
		chosen++;
	}

	// Printing O.
	field[chosen] = status::Zero;
	cout << "Робот выполнил свой ход.\n"
		<< "Нажмите \"Enter\" для продолжения\n";
	string garbage;
	cin.ignore();
	getline(cin, garbage);
	
	return havewinfor(status::Zero);
}

int gamesession::blanks()
{
	int count;
	count = 0;
	for (int i = 0; i < FIELDLEN * FIELDLEN; i++)
		if (field[i] == status::Blank)
			count++;
	return count;
}


bool gamesession::havewinfor(status obj)
{
	bool trynow[8];
	int xcord, ycord, xmod, ymod;
	// Checking all positions.
	for (int i = 0; i < 9; i++)
	{
		// Resetting possible directions to null.
		for (int j = 0; j < 8; j++)
			trynow[j] = false;

		// Representng linear adress as a pair of coordinates. 
		xcord = i % 3;
		ycord = i / 3;

		// Interpreting position as combination of possible directions.
		switch (i)
		{
		case 0:
			trynow[2] = true; // Right.
			trynow[3] = true; // DownRight.
			trynow[4] = true; // Down.
			break;
		case 1:
			trynow[4] = true; // Down.
			break;
		case 2:
			trynow[5] = true; // Downleft.
			trynow[4] = true; // Down.
			break;
		case 3:
			trynow[2] = true; // Right.
			break;
		case 4:
			// All combinations through this direction will be covered from the other positions.
			break;
		case 5:
			// All combinations through this direction will be covered from the other positions.
			break;
		case 6:
			trynow[2] = true; // Right.
			break;
		case 7:
			// All combinations through this direction will be covered from the other positions.
			break;
		case 8:
			// All combinations through this direction will be covered from the other positions.
			break;
		default:
			cout << "Exception: Went though undefined position.\n";
			break;
		}

		// Go through all chosen directions.
		for (int j = 0; j < 8; j++)
		{
			if (trynow[j])
			{
				// Interpretating current active direction as modifiers combination.
				switch (j)
				{
				case 2: // Right.
					xmod = 1;
					ymod = 0;
					break;
				case 3: // DownRight.
					xmod = 1;
					ymod = 1;
					break;
				case 4: // Down.
					xmod = 0;
					ymod = 1;
					break;
				case 5: // Downleft.
					xmod =-1;
					ymod = 1;
					break;
				// Others directions shouldnt be used during normal expluatation.
				default: 
					cout << "Exception : Trying to check uncnown direction.\n";
					break;
				}

				int curx, cury;
				bool brokenwin = false;
				// Go through the three positions in the chosen direction.
				for (int k = 0; k < 3; k++)
				{
					curx = xcord + k * xmod;
					cury = ycord + k * ymod;
					////////////////////////////////////////////////////////// Should I add an array indexes check here? ////////////////////////////////////////////////
					// Checking having necessary symbol in the actual memory array usint it's coordinates.
					if (field[curx + cury * 3] != obj)
						brokenwin = true;
					if (!brokenwin)
						return true;
				}
			}
		}
	}
}