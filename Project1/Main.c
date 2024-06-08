#include <stdio.h>
#include <SDL.h>
#include "functions.h"
#include "structs.h"
#include "constants.h"

int game_is_running;
int last_frame_time = 0;
int KEYS[322];
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int w = 0;
int s = 0;
int up = 0;
int down = 0;
int wAlreadyPressed = 0;
int sAlreadyPressed = 0;
int upAlreadyPressed = 0;
int downAlreadyPressed = 0;

int initialise_window(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error, could not initialise SDL.\n");
		return FALSE;
	}

	window = SDL_CreateWindow(
		NULL, 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		WINDOW_WIDTH, 
		WINDOW_HEIGHT, 
		SDL_WINDOW_BORDERLESS
	);

	if (!window) {
		fprintf(stderr, "Error, could not create SDL Window.\n");
		return FALSE;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer) {
		fprintf(stderr, "Error, could not create SDl Renderer.\n");
		return FALSE;
	}

	return TRUE;
}

void setup() {
	for (int i = 0; i < sizeof(KEYS) / sizeof(KEYS[0]); i++) {
		KEYS[i] = FALSE;
	}

	player1.width = WINDOW_WIDTH / 120.0;
	player1.height = WINDOW_HEIGHT / 10.0;
	player1.x = WINDOW_WIDTH / 8.0;
	player1.y = WINDOW_HEIGHT / 2.0 - player1.height;
	player1.ydir = 0;

	player2.width = WINDOW_WIDTH / 120.0;
	player2.height = WINDOW_HEIGHT / 10.0;
	player2.x = WINDOW_WIDTH / 8.0 * 7;
	player2.y = WINDOW_HEIGHT / 2.0 - player2.height;
	player2.ydir = 0;

	jab.width = WINDOW_WIDTH / 400.0;
	jab.height = WINDOW_HEIGHT / 70.0;
	jab.x = WINDOW_WIDTH / 2.0 - jab.width/2;
	jab.y = 0;

	ball.width = WINDOW_WIDTH / 100;
	ball.height = ball.width;
	ball.x = WINDOW_WIDTH / 2.0 - ball.width/2;
	ball.y = WINDOW_HEIGHT / 2.0;
	ball.velocity.x = 1;
	ball.velocity.y = 0;
	ball.touchingPlayer = FALSE;

}

void process_input() {
	SDL_Event event;
	SDL_PollEvent(&event);



	switch (event.type)
	{
		case SDL_QUIT:
			game_is_running = FALSE;
			break;


		case SDL_KEYDOWN:
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				game_is_running = FALSE;
				break;
			}
			if (event.key.keysym.sym == SDLK_w) {
				w = 1;
				break;
			}
			if (event.key.keysym.sym == SDLK_s) {
				s = 1;
				break;
			}
			if (event.key.keysym.sym == SDLK_UP) {
				up = 1;
				break;
			}
			if (event.key.keysym.sym == SDLK_DOWN) {
				down = 1;
				break;
			}
			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_w) {
				w = 0;
				break;
			}
			if (event.key.keysym.sym == SDLK_s) {
				s = 0;
				break;
			}
			if (event.key.keysym.sym == SDLK_UP) {
				up = 0;
				break;
			}
			if (event.key.keysym.sym == SDLK_DOWN) {
				down = 0;
				break;
			}
			break;
		
	}


}

void update() {


	float deltaTime = (SDL_GetTicks() - last_frame_time) / 1000.0;

	last_frame_time = SDL_GetTicks();

	// speed is measured in pixels per second

	int playerSpeed = WINDOW_HEIGHT;
	int ballSpeed = WINDOW_WIDTH / 3;

	// player 1
		if (w && !sAlreadyPressed) {
			player1.ydir = -1;
			wAlreadyPressed = 1;
		}
		if (s && !wAlreadyPressed) {
			player1.ydir = 1;
			sAlreadyPressed = 1;
		}

		if (!w)
			wAlreadyPressed = 0;
		if (!s)
			sAlreadyPressed = 0;
		if (!w && !s)
			player1.ydir = 0;

	//player 2
		if (up && !downAlreadyPressed) {
			player2.ydir = -1;
			upAlreadyPressed = 1;
		}
		if (down && !upAlreadyPressed) {
			player2.ydir = 1;
			downAlreadyPressed = 1;
		}

		if (!up)
			upAlreadyPressed = 0;
		if (!down)
			downAlreadyPressed = 0;
		if (!up && !down)
			player2.ydir = 0;

	float newPos = player1.y + (player1.ydir * playerSpeed * deltaTime);
	if (newPos >= 0 && newPos <= WINDOW_HEIGHT - player1.height)
		player1.y = newPos;

	newPos = player2.y + (player2.ydir * playerSpeed * deltaTime);
	if (newPos >= 0 && newPos <= WINDOW_HEIGHT - player2.height)
		player2.y = newPos;


	// ball logic
	// normal movement
	Vector2 newPosBall;
	newPosBall.x = ball.x + ball.velocity.x * ballSpeed * deltaTime;
	newPosBall.y = ball.y + ball.velocity.y * ballSpeed * deltaTime;

	if (newPosBall.x >= player1.x && newPosBall.x <= player2.x) {
		ball.x = newPosBall.x;
	}
	// check if touching player
	else if (touchingPlayer(ball, newPosBall)) {
		ball.velocity.x *= -1;
		newPosBall.x = ball.x + ball.velocity.x * ballSpeed * deltaTime;
		ball.x = newPosBall.x;
	}
	

}

void render() {

	// background color
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// draw shi
	SDL_Rect player1_rect = {
		ciel(player1.x),
		ciel(player1.y),
		ciel(player1.width),
		ciel(player1.height)
	};

	SDL_Rect player2_rect = {
		ciel(player2.x),
		ciel(player2.y),
		ciel(player2.width),
		ciel(player2.height)
	};

	SDL_Rect jab_rect = {
		ciel(jab.x),
		ciel(jab.y),
		ciel(jab.width),
		ciel(jab.height)
	};

	SDL_Rect ball_rect = {
		ciel(ball.x),
		ciel(ball.y),
		ciel(ball.width),
		ciel(ball.height)
	};


	// render players
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &player1_rect);
	SDL_RenderFillRect(renderer, &player2_rect);

	// draw jagged lines in the middle
	while (jab_rect.y < WINDOW_HEIGHT) {
		SDL_RenderFillRect(renderer, &jab_rect);
		jab_rect.y += WINDOW_HEIGHT / 30.0;
	}

	// render ball
	SDL_RenderFillRect(renderer, &ball_rect);

	// display it to the screen
	SDL_RenderPresent(renderer);
}

void destroy_window() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
int main(int argc, char* args[]) {
	game_is_running = initialise_window();

	setup();

	while (game_is_running) {
		process_input();
		update();
		render();
	}

	destroy_window();

	return 0;
}


