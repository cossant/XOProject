#pragma once

enum class status {Cross, Zero, Blank};

const int FIELDLEN = 3;

class gamesession
{
public:
	// Should be setting the first move order and reset the field.
	gamesession();
	// Deleting previous info and putting new info and the board picture;
	void display();
	// Getting the player pick coordinates and checking if he wins. Returning true if he wins.
	bool player_turn();
private:
	status field[FIELDLEN*FIELDLEN];
	bool playerturn;
	// Randoming coordinates and checking if bot wins. Returning true in bot wins.
	bool bot_turn();
	// Returning true if it is a winning combination for <X/O> symbol.
	bool havewinfor(status oos);
	// Shows final screen for player, bot or draw.
	void summary(char condition);
	// Checks if it is draw condition, like not having any more spots.
	bool draw();
	// Counting blank spaces.
	int blanks();
};