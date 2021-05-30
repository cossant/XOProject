#include <iostream>;
#include <random>;
#include <ctime>;
#include <string>;
#include "Header.h";

using namespace std;

int main()
{
	setlocale(LC_CTYPE, "Russian");
	srand(time(NULL));

	gamesession test;
	test.player_turn();
	test.player_turn();
	bool so = test.player_turn();
	if (so)
		cout << "win";
	else
		cout << "winn't";
}
