#pragma once
#include "Header.h";
#include <iostream>;
#include <string>;
using namespace std;

gamesession::gamesession()
{
	cout << "������ ����� ���� � ��������-������. �� ������ ������ �� �������� - �.\n" <<
		"�� ������ ������ ������ � ����? (Y/N): ";
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
	cout << "���� � �������. ��� ���, �����.\n";
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
	cout << "�����, ��� ��� - ������� ���������� �������, � ������� ������ ���������� ���� \"�������\"\n"
		<< "�������, ��� ������� ������ ������� �������� ���� - A-1, � ����������� ������� ������� - �-1.\n";
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
	cout << "����� �������� ���� ���.\n"
		<< "������� \"Enter\" ��� �����������\n";
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