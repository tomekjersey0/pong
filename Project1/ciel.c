int ciel(float number) {
	int floored = (int)number;
	if (floored == number)
		return number;
	else
		return floored + 1;
}