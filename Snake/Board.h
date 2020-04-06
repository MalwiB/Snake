#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

typedef std::pair<int, int> Point;

const int speed = 180;
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const int P = 60;
// 900x600  ==  12x10
const int fieldsW = SCREEN_WIDTH/P;
const int fieldsH = SCREEN_HEIGHT/P;

class Snake;

class Board {
public:
	Point to_gain;
	Point speed_bonus;


	void initialize();
	void close();

	void set_black_background();

	void set_rectangle_black(SDL_Rect rectangle);

	void set_rectangle_yellow(SDL_Rect rectangle);

	void generate_to_gain(Snake* snake);
	void game_over();
};

