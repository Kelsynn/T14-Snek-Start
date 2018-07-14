#pragma once
#include "Location.h"
#include "Board.h"
#include <random>
class Snake
{
private:
	class Segment
	{
	public:
		void InitHead(Location& in_loc);
		void InitBody(std::mt19937 rng);
		void MoveBy(Location& delta_loc);
		void Follow(Segment& next);
		void Draw(Board& brd);
		Location GetLocation() const;
	private:
		static constexpr Color HEAD_COLOR = Colors::Yellow;
		static constexpr Color BODY_COLOR = Colors::Green;
		Location loc;
		Color c;
	};
public:
	Snake(Location& loc, std::mt19937& rng);
	void MoveBy(Location& delta_loc);
	void Grow();
	void Draw(Board& brd);
	Location NextHeadPath(Location& delta_loc) const;
	bool SelfCollisionCheck(Location& delta_loc);
	bool GoalCollisionCheck(Location& goal_loc);
	bool IsEatingGoal(Location& goal_loc, Location& delta_loc);

	int GetSnakeLength();
private:
	std::mt19937& rng;
	static constexpr int MAX_LENGTH = 100;
	Segment segments[MAX_LENGTH];
	int nSegments = 1;
};