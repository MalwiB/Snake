#include "Snake.h"
#include "Board.h"


Snake::Snake(Board* board) {
	this->board = board;

	Point starting_point(13,4);
	SDL_Rect starting_square = {starting_point.first*P, starting_point.second*P, P, P};
	sequence.push_back(starting_point);
	board->set_rectangle_yellow(starting_square);

	recent_direction = LEFT;
}

bool Snake::is_Snake(Point p) {
	for(std::vector<Point>::iterator it = sequence.begin(); it < sequence.end(); it++) {
		if(((*it).first == p.first) && ((*it).second == p.second))
			return true;
	}
	return false;
}

bool Snake::move(Direction direction) {

	Point previous_start_point = sequence.front();
	Point previous_last_point = sequence.back();
	std::vector <Point>::iterator snake_start_ptr = sequence.begin();
	Point new_start_point;

	bool gained_FLAG = false;

	//  when snake moves one step further ->
	//  new starting sequence element is getting yellow, previous last element - black
	switch(direction) {
	case UP:
		// starting rect coordinates : (x, y)
		// new starting rect coordinates: (x, y-1)
		new_start_point.first = previous_start_point.first;
		new_start_point.second = previous_start_point.second - 1;
		if(is_Snake(new_start_point) || (new_start_point.second == -1))
			board->game_over();
		if(previous_start_point.first == board->to_gain.first && previous_start_point.second == board->to_gain.second+1) {	// if gained...
			sequence.insert(snake_start_ptr, board->to_gain);
			board->generate_to_gain(this);
			gained_FLAG = true;
		}
		else {
			sequence.insert(snake_start_ptr, new_start_point);
			sequence.pop_back();
		}
		break;
	case DOWN:
		//(x, y+1)
		new_start_point.first = previous_start_point.first;
		new_start_point.second = previous_start_point.second + 1;
		if(is_Snake(new_start_point) || (new_start_point.second == fieldsH))
			board->game_over();
		if(previous_start_point.first == board->to_gain.first && previous_start_point.second == board->to_gain.second-1) {
			sequence.insert(snake_start_ptr, board->to_gain);
			board->generate_to_gain(this);
			gained_FLAG = true;
		}
		else {
			sequence.insert(snake_start_ptr, new_start_point);
			sequence.pop_back();
		}
		break;
	case LEFT:
		//(x-1, y)
		new_start_point.first = previous_start_point.first - 1;
		new_start_point.second = previous_start_point.second;
		if(is_Snake(new_start_point) || (new_start_point.first == -1))
			board->game_over();
		if(previous_start_point.first == board->to_gain.first+1 && previous_start_point.second == board->to_gain.second) {
			sequence.insert(snake_start_ptr, board->to_gain);
			board->generate_to_gain(this);
			gained_FLAG = true;
		}
		else {
			sequence.insert(snake_start_ptr, new_start_point);
			sequence.pop_back();
		}
		break;
	case RIGHT:
		//(x+1, y)
		new_start_point.first = previous_start_point.first + 1;
		new_start_point.second = previous_start_point.second;
		if(is_Snake(new_start_point) || (new_start_point.first == fieldsW))
			board->game_over();
		if(previous_start_point.first == board->to_gain.first-1 && previous_start_point.second == board->to_gain.second) {
			sequence.insert(snake_start_ptr, board->to_gain);
			board->generate_to_gain(this);
			gained_FLAG = true;
		}
		else {
			sequence.insert(snake_start_ptr, new_start_point);
			sequence.pop_back();
		}
		break;
	default:
		break;
	}

	if(!gained_FLAG ) {
		SDL_Rect light_up_start = {sequence.front().first *P, sequence.front().second*P, P, P};
		SDL_Rect hide_last = {previous_last_point.first*P, previous_last_point.second*P, P, P};

		board->set_rectangle_yellow(light_up_start);
		board->set_rectangle_black(hide_last);
	}

	recent_direction = direction;

	return gained_FLAG;
}