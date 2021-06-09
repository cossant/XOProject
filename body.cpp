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

	gamesession* game = new gamesession();
	game->playrun();
}
