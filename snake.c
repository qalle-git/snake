#include "snake.h"
#include "paint.h"

#include <stdio.h>

void world_field(int world[Y_SIZE][X_SIZE], apple_t *apple, snake_t *snake)
{
	image_init(world, GRASS);

	add_rectangle(world, WALL, 0, 0, X_SIZE, Y_SIZE);

	add_point(world, APPLE, apple->x, apple->y);

	for (int tail = 0; tail < snake->length; tail++)
	{
		symbols_t symbol = tail == 0 ? SNAKE_HEAD : SNAKE_BODY;

		add_point(world, symbol, snake->x[tail], snake->y[tail]);
	}
}

void snake_init(snake_t *snake)
{
	snake->length = 2;

	int centerX = X_SIZE / 2;
	int centerY = Y_SIZE / 2;

	for (int tail = 0; tail < snake->length; tail++)
	{
		snake->x[tail] = centerX - tail;
		snake->y[tail] = centerY;
	}

	snake->dir = RIGHT;
}

void snake_turn(snake_t *snake)
{
	if (kbhit())
	{
		int input = getch();

		switch (input)
		{
			case UP_ARROW:
				snake->dir = UP;
				break;
			case DOWN_ARROW:
				snake->dir = DOWN;
				break;
			case RIGHT_ARROW:
				snake->dir = RIGHT;
				break;
			case LEFT_ARROW:
				snake->dir = LEFT;
				break;
		}
	}
}

void snake_move(snake_t *snake)
{
	// This is going to be the heads new position.
	point_t new_point = {0, 0};

	// Check which direction the snake is heading using a switch.
	switch (snake->dir)
	{
		case UP:
			new_point.y = -1;
			break;
		case DOWN:
			new_point.y = 1;
			break;
		case LEFT:
			new_point.x = -1;
			break;
		case RIGHT:
			new_point.x = 1;
			break;
		default:
			return; // No direction as we know of, return the program.
	}

	// Make the tails mimic the head.
	for (int tail = snake->length - 1; tail > 0; tail--)
	{
		snake->x[tail] = snake->x[tail - 1];
		snake->y[tail] = snake->y[tail - 1];
	}

	// Give the head the new position the snake was headed.
	snake->x[0] += new_point.x;
	snake->y[0] += new_point.y;
}

bool snake_hit_wall(snake_t *snake)
{
	const point_t head_position = { snake->x[0], snake->y[0] };

	if (head_position.x >= X_SIZE - 1 || head_position.x <= 0)
		return true;
	if (head_position.y >= Y_SIZE - 1 || head_position.y <= 0)
		return true;

	return false;
}

bool snake_hit_self(snake_t *snake)
{
	if (snake->length <= 2) {
		return false;
	}
	
	const point_t head_position = {snake->x[0], snake->y[0]};

	for (int tail = 1; tail < snake->length; tail++)
	{
		const point_t tail_position = {snake->x[tail], snake->y[tail]};

		if (head_position.x == tail_position.x && head_position.y == tail_position.y)
		{
			return true;
		}
	}

	return false;
}

void apple_new(apple_t *apple, snake_t *snake)
{
	bool found = false;

	point_t random_position;

	while (!found)
	{
		random_position.x = rand() % (X_SIZE - 2) + 1;
		random_position.y = rand() % (Y_SIZE - 2) + 1;

		for (int tail = 0; tail < snake->length; tail++)
		{
			const point_t tail_position = {snake->x[tail], snake->y[tail]};

			if (random_position.x == tail_position.x && random_position.y == tail_position.y)
			{
				continue;
			}

			found = true;

			break;
		}
	}

	apple->x = random_position.x;
	apple->y = random_position.y;
}

bool snake_eat_apple(apple_t *apple, snake_t *snake)
{
	const point_t head_position = {snake->x[0], snake->y[0]};

	if (head_position.x == apple->x && head_position.y == apple->y)
	{
		const point_t last_tail_position = {snake->x[snake->length - 1], snake->y[snake->length - 1]};

		snake->length++;

		snake->x[snake->length - 1] = last_tail_position.x;
		snake->y[snake->length - 1] = last_tail_position.y;

		apple_new(apple, snake);

		return true;
	}

	return false;
}
