#include "Board.h"

Board::Board(Graphics & gfx)
	:
	gfx( gfx )
{
}

int Board::GetBoardHeight() const
{
	return height;
}

int Board::GetBoardWidth() const
{
	return width;
}

bool Board::IsInBounds(const Location& loc)
{
	return !(loc.x < borderThickness ||
		loc.x + (borderThickness * 2) > width ||
		loc.y < borderThickness ||
		loc.y + (borderThickness * 2) > height);
}

void Board::DrawCell(const Location& loc, Color c)
{
	gfx.DrawRectDim((loc.x * dimension) + x_offset, (loc.y * dimension) + y_offset, dimension, dimension, c);
}

void Board::DrawCellInGamespace(const Location & loc, Color c)
{
	int borderOffsetX = loc.x;
	int borderOffsetY = loc.y;
	gfx.DrawRectDim((borderOffsetX * dimension) + x_offset + 1, (borderOffsetY * dimension) + y_offset + 1, dimension - 2 , dimension - 2, c);
}

void Board::DrawBorder()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Location drawing_loc = { x, y };
			if (y == 0 || y == height-1 || x == 0 || x == width-1)
			{
				DrawCell(drawing_loc, borderColor);
			}
		}
	}
}

int Board::GetBorderThickness() const
{
	return borderThickness;
}
