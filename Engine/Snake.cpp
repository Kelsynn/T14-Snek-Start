#include "Snake.h"
void Snake::Segment::InitHead(Location& in_loc)
{
	loc = in_loc;
	c = HEAD_COLOR;
}

void Snake::Segment::InitBody(std::mt19937 rng)
{
	std::uniform_int_distribution<int> gDist(50, 220);
	loc = Location{ 1, 1 };
	c = Color {char(0),unsigned char(gDist(rng)),unsigned char(0)};
}

void Snake::Segment::MoveBy(Location & delta_loc)
{
	loc.Add(delta_loc);
}

void Snake::Segment::Follow(Segment & next)
{
	loc = next.loc;
}

void Snake::Segment::Draw(Board & brd)
{
	brd.DrawCellInGamespace(loc, c);
}

Location Snake::Segment::GetLocation() const
{
	return loc;
}

Snake::Snake(Location & loc, std::mt19937& in_rng)
	:
	rng (in_rng)
{
	segments[0].InitHead(loc);
	
}

void Snake::MoveBy(Location & delta_loc)
{
	for (int i = nSegments - 1; i > 0; i--)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

void Snake::Grow()
{
	if (nSegments < MAX_LENGTH)
	{
		segments[nSegments].InitBody(rng);
		nSegments++;
	}
}

void Snake::Draw(Board & brd)
{
	for (int i = 0; i < nSegments; i++)
	{
		segments[i].Draw(brd);
	}
}

Location Snake::NextHeadPath(Location& delta_loc) const
{
	Location head = segments[0].GetLocation();
	head.Add(delta_loc);
	return head;
}

bool Snake::SelfCollisionCheck(Location& delta_loc)
{
	Location next_loc = NextHeadPath(delta_loc);
	bool isColliding = false;
	for (int i = 0; i < nSegments - 1; i++)
	{
		if (!isColliding)
		{
			if (segments[i].GetLocation() == next_loc)
			{
				isColliding = true;
			}
		}
	}
	return isColliding;
}

bool Snake::GoalCollisionCheck(Location & goal_loc)
{
	bool isColliding = false;
	for (int i = 0; i < nSegments; i++)
	{
		if (!isColliding)
		{
			if (segments[i].GetLocation() == goal_loc)
			{
				isColliding = true;
			}
		}
	}
	return isColliding;
}

bool Snake::IsEatingGoal(Location& goal_loc, Location& delta_loc)
{
	return NextHeadPath(delta_loc) == goal_loc;
}

int Snake::GetSnakeLength()
{
	return nSegments;
}
