#include <iostream>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "Snake.h"
#include "Board.h"

bool QUIT_FLAG = false;


int main(int argc, char* args[]) {
	srand((unsigned int)time(0));

	Board board;
	board.initialize();
	board.set_black_background();

	Snake snake(&board);
	board.generate_to_gain(&snake);

	bool is_gained = false;
	
	SDL_Event e; // event handler
	while(!QUIT_FLAG) {
		if(SDL_PollEvent(&e) != 0) {
			if(e.type == SDL_QUIT)  // user exit
				QUIT_FLAG = true;
			else if(e.type == SDL_KEYDOWN) {  // key -> snake moves
				switch(e.key.keysym.sym) {
				case SDLK_UP:
					if(snake.recent_direction == DOWN)
						break;
					is_gained = snake.move(UP);
					break;
				case SDLK_DOWN:
					if(snake.recent_direction == UP)
						break;
					is_gained = snake.move(DOWN);
					break;
				case SDLK_LEFT:
					if(snake.recent_direction == RIGHT)
						break;
					is_gained = snake.move(LEFT);
					break;
				case SDLK_RIGHT:
					if(snake.recent_direction == LEFT)
						break;
					is_gained = snake.move(RIGHT);
					break;
				default:
					break;
				}
			}
			if(!is_gained)
				SDL_Delay(150);
		}
		else {  // snake moves further in previously choosen direction
			is_gained = snake.move(snake.recent_direction);
			if(!is_gained)
				SDL_Delay(150);
		}
	}

	board.close();

	return 0;
}
