#pragma once

struct player {
	float x;
	float y;
	float width;
	float height;
	int ydir;
} player1, player2;

struct jab {
	float x;
	float y;
	float width;
	float height;
} jab;

typedef struct Vector2 {
	float x;
	float y;
} Vector2;

struct ball {
	float x;
	float y;
	float width;
	float height;
	Vector2 velocity;
	int touchingPlayer;
	float speed;
} ball;

struct score {
	int player1;
	int player2;
} score;