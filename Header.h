#pragma once

//enum class status {Cross, Zero, Blank};

const int FIELDLEN = 3;

class gamesession
{
public:
	// Should be setting the first move order and reset the field.
	gamesession();
	void playrun();
	

protected:
	enum class status { Cross, Zero, Blank };
	enum class gamepart {PLAYERWON, BOTWON, DRAW, RUNNING};
	status field[FIELDLEN * FIELDLEN];
	gamepart gameresponse;
	bool playerturn;
	// Deleting previous info and putting new info and the board picture;
	void display();
	// Getting the player pick coordinates and checking if he wins. Returning true if he wins.
	bool player_turn();
	// Randoming coordinates and checking if bot wins. Returning true in bot wins.
	bool bot_turn();
	// Returning true if it is a winning combination for <X/O> symbol.
	bool havewinfor(status oos);
	// Shows final screen for player, bot or draw.
	void summary(gamepart condition);
	// Checks if it is draw condition, like not having any more spots.
	bool draw();
	// Counting blank spaces.
	int blanks();
};