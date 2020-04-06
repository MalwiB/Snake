#pragma once

#include <vector>

enum Direction {LEFT, RIGHT, UP, DOWN};

typedef std::pair<int, int> Point;

class Board;

class Snake {
public:
	std::vector<Point> sequence;

	Board* board;

	Direction recent_direction;

	// TODO
	int slow_bonus;
	int speed_bonus;


	Snake(Board* board);

	bool move(Direction direction);

	bool is_Snake(Point p);

	int size() { return sequence.size(); }

	Point operator[](int index) { return sequence[index]; }

};

