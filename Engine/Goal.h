#pragma once
#include "Location.h"
#include "Board.h"
#include "Snake.h"
#include <random>

class Goal
{
public:
	Goal(std::mt19937& rng, Board& brd, Snake& snake);
	void Respawn(std::mt19937& rng, Board& brd, Snake& snake);
	void Draw(Board& brd);
	Location GetLocation();
private:
	Location loc;
	Color c = Colors::Red;
};