#pragma once
#include "structs.h"

int ciel(float number);

int touchingPlayer(struct ball ball, Vector2 newPosBall);
int touchingBorder(struct ball ball, Vector2 newPosBall);
int offTheScreen(struct ball ball, Vector2 newPosBall);