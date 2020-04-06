#include "Board.h"
#include "Snake.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* screen_surface = NULL;
SDL_Surface* current_screen_surface = NULL;


void Board::initialize() {
	if(SDL_Init( SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}

	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		std::cerr << "Linear texture filtering error." << std::endl;
		exit(EXIT_FAILURE);
	}

	window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(window == NULL) {
		std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
		
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL) {
		std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void Board::close() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	SDL_FreeSurface(current_screen_surface);

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


void Board::generate_to_gain(Snake* snake) {
	int x, y;
	do {
		x = rand()%fieldsW;
		y = rand()%fieldsH;
		to_gain.first = x;
		to_gain.second = y; 
		std::cout << "generate: " << x << ", " << y << "." << std::endl;
	} while((*snake).is_Snake(to_gain));

	SDL_Rect zlapJeWszystkie = {x*P, y*P, P, P};
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0x00, 0xFF );
	SDL_RenderFillRect( renderer, &zlapJeWszystkie);
	SDL_RenderPresent(renderer);
}

void Board::set_rectangle_black(SDL_Rect rectangle) {
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderFillRect( renderer, &rectangle );
	SDL_RenderPresent( renderer );
}

void Board::set_rectangle_yellow(SDL_Rect rectangle) {
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0x00, 0xFF );
	SDL_RenderFillRect( renderer, &rectangle );
	SDL_RenderPresent( renderer );
}

void Board::set_black_background() {
	SDL_RenderClear( renderer );
	
	//black background
	SDL_Rect background = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderFillRect( renderer, &background );
	SDL_RenderPresent( renderer );
}

void Board::game_over() {
			screen_surface = SDL_GetWindowSurface(window);
			current_screen_surface = SDL_LoadBMP("game_over.bmp");
			if(current_screen_surface == NULL) {
				printf("Unable to open .bmp file.");
				exit(EXIT_FAILURE);
			}
			SDL_BlitSurface(current_screen_surface, NULL, screen_surface , NULL);
			SDL_UpdateWindowSurface(window);
			SDL_Delay(2000);
			exit(EXIT_SUCCESS);

			// TODO: try again!
}