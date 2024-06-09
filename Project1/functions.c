#include "structs.h"
#include "constants.h"

int ciel(float number) {
	int floored = (int)number;
	if (floored == number)
		return number;
	else
		return floored + 1;
}

int touchingPlayer(struct ball ball, Vector2 newPosBall) {
	// if ball is travelling right, its velocity will be positive
	int ballDir = 1 ? (ball.velocity.x > 0) : 0;
	// checking right player
	if (ballDir) {
		if (newPosBall.x >= player2.x && newPosBall.x <= player2.x + player2.width && newPosBall.y + ball.height >= player2.y && newPosBall.y <= player2.y + player2.height) {
			return TRUE;
		}
	}
	// checking left player
	else {
		if (newPosBall.x <= player1.x + player1.width && newPosBall.x >= player1.x && newPosBall.y + ball.height >= player1.y && newPosBall.y <= player1.y + player1.height) {
			return TRUE;
		}
	}
	return FALSE;

}

int touchingBorder(struct ball ball, Vector2 newPosBall) {
	if (newPosBall.y + ball.height <= WINDOW_HEIGHT && newPosBall.y >= 0) 
		return FALSE;

	return TRUE;
	
}

int offTheScreen(struct ball ball, Vector2 newPosBall) {
	if (newPosBall.x >= 0 && newPosBall.x - ball.width <= WINDOW_WIDTH) 
		return FALSE;

	return TRUE;
}

struct text makeText(SDL_Renderer* renderer, TTF_Font* font, char* text, SDL_Color color, int x, int y) {
	SDL_Surface* temp = TTF_RenderText_Solid(font, text, color);
	SDL_Texture* textImage = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_Rect pos = { x, y, temp->w, temp->h };
	SDL_FreeSurface(temp);

	struct text _text = { textImage, pos };
	return _text;
}

struct text updateText(SDL_Renderer* renderer, TTF_Font* font, char* text, SDL_Color color, struct text self) {
	SDL_Surface* temp = TTF_RenderText_Solid(font, text, color);
	SDL_Texture* textImage = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);
	struct text _text = { textImage, self.pos };
	return _text;
}