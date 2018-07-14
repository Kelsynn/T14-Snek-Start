#pragma once
#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics& gfx);
	int GetBoardHeight() const;
	int GetBoardWidth() const;
	bool IsInBounds(const Location& loc);
	void DrawCell(const Location& loc, Color c);
	void DrawCellInGamespace(const Location& loc, Color c);
	void DrawBorder();
	int GetBorderThickness() const;

private:
	Graphics& gfx;
	static constexpr int dimension = 15;
	static constexpr int width = 52;
	static constexpr int height = 38;
	static constexpr int borderThickness = 1;
	static constexpr int x_offset = 10;
	static constexpr int y_offset = 15;
	static constexpr Color borderColor = Colors::Blue;
};