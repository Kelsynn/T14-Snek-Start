#include "Goal.h"

Goal::Goal(std::mt19937 & rng, Board & brd, Snake & snake)
{
	Respawn(rng, brd, snake);
}

void Goal::Respawn(std::mt19937 & rng, Board & brd, Snake & snake)
{
	int snakeLength = snake.GetSnakeLength();
	bool isColliding = true;
	std::uniform_int_distribution<int> xDist(brd.GetBorderThickness(), brd.GetBoardWidth() - (2 *brd.GetBorderThickness()));
	std::uniform_int_distribution<int> yDist(brd.GetBorderThickness(), brd.GetBoardHeight() - (2 * brd.GetBorderThickness()));
	do
	{
		loc.x = xDist(rng);
		loc.y = yDist(rng);
		isColliding = snake.GoalCollisionCheck(loc) && !brd.IsInBounds(loc);
	} while (isColliding);
}

void Goal::Draw(Board & brd)
{
	brd.DrawCellInGamespace(loc, c);
}

Location Goal::GetLocation()
{
	return loc;
}
