/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include <random>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd( gfx ),
	snake(start_loc, rng),
	rng (std::random_device()()),
	goal (rng, brd, snake)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!GameIsOver)
	{
		if (wnd.kbd.KeyIsPressed(VK_UP))
		{
			if (!(delta_loc == Location { 0, 1 }))
			{
				delta_loc = { 0 , -1 };
			}
		}
		if (wnd.kbd.KeyIsPressed(VK_DOWN))
		{
			if (!(delta_loc == Location { 0, -1}))
			{
				delta_loc = { 0 , 1 };
			}
		}
		if (wnd.kbd.KeyIsPressed(VK_LEFT))
		{
			if (!(delta_loc == Location { 1, 0}))
			{
				delta_loc = { -1 , 0 };
			}
		}
		if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
			if (!(delta_loc == Location { -1, 0}))
			{
				delta_loc = { 1 , 0 };
			}
		}

		if (brd.IsInBounds(snake.NextHeadPath(delta_loc)))
		{
			bool isCollidingSelf = snake.SelfCollisionCheck(delta_loc);
			if (!isCollidingSelf)
			{
				SnakeMoveCounter++;
				if (SnakeMoveCounter >= SnakeMovePeriod)
				{
					SnakeMoveCounter = 0;
					if (snake.IsEatingGoal(goal.GetLocation(), delta_loc))
					{
						snake.Grow();
						goal.Respawn(rng, brd, snake);
					}
					snake.MoveBy(delta_loc);
				}
			} 
			else {
				GameIsOver = true;
			}
		}
		else
		{
			GameIsOver = true;
		}
	}
}

void Game::ComposeFrame()
{
	snake.Draw(brd);
	goal.Draw(brd);
	brd.DrawBorder();
	if (GameIsOver)
	{
		sprt.DrawGameOver(375, 275, gfx);
	}
}
