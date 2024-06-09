#pragma once
#include "structs.h"

int ciel(float number);

int touchingPlayer(struct ball ball, Vector2 newPosBall);
int touchingBorder(struct ball ball, Vector2 newPosBall);
int offTheScreen(struct ball ball, Vector2 newPosBall);
struct text makeText(SDL_Renderer* renderer, TTF_Font* font, char* text, SDL_Color color, int x, int y);
struct text updateText(SDL_Renderer* renderer, TTF_Font* font, char* text, SDL_Color color, struct text self);