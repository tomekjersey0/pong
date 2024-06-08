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
		if (newPosBall.x >= player2.x && newPosBall.y + ball.height >= player2.y && newPosBall.y <= player2.y + player2.height) {
			return TRUE;
		}
	}
	// checking left player
	else {
		if (newPosBall.x <= player1.x + player1.width && newPosBall.y + ball.height >= player1.y && newPosBall.y <= player1.y + player1.height) {
			return TRUE;
		}
	}
	return FALSE;

}