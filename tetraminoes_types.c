#include "tetris.h"

void random_spawn_types(tetramino_t tetramini[], int *pivot, tetris_map_t *tetris_map)
{
	*pivot = 2;

	int max_value = 9;

	int half_map = tetris_map->width / 2;
	int spawn_y = -2;

	int random_choice = rand() % max_value;

	if (random_choice == 0 || random_choice == 1)
	{
		*pivot = 0;
		spawn_cube(tetramini, half_map - 1, spawn_y);
	}

	if (random_choice == 2 || random_choice == 3)
	{
		spawn_line(tetramini, half_map - 2, spawn_y + 1);
	}

	if (random_choice == 4)
	{
		spawn_right_l(tetramini, half_map + 1, spawn_y);
	}

	if (random_choice == 5)
	{
		spawn_left_l(tetramini, half_map - 1, spawn_y);
	}

	if (random_choice == 6)
	{
		spawn_right_z(tetramini, half_map + 1, spawn_y);
	}

	if (random_choice == 7)
	{
		spawn_left_z(tetramini, half_map - 1, spawn_y);
	}

	if (random_choice == 8 || random_choice == 9)
	{
		spawn_T(tetramini, half_map, spawn_y);
	}
}



void spawn_cube(tetramino_t tetramini[], int x, int y)
{
	int i;
	for (i = 0; i < 2; i++)
	{
		tetramino_init_custom(&tetramini[i], x + i, y);
		tetramini[i].r = 245;
		tetramini[i].g = 249;
		tetramini[i].b = 14;
	}
	y++;
	for (i = 0; i < 2; i++)
	{
		tetramino_init_custom(&tetramini[i + 2], x + i, y);
		tetramini[i + 2].r = 245;
		tetramini[i + 2].g = 249;
		tetramini[i + 2].b = 14;
	}
}

void spawn_line(tetramino_t tetramini[], int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		tetramino_init_custom(&tetramini[i], x + i, y);
		tetramini[i].r = 66;
		tetramini[i].g = 244;
		tetramini[i].b = 232;
	}
}

void spawn_T(tetramino_t tetramini[], int x, int y)
{
	tetramino_init_custom(&tetramini[0], x, y);
	tetramini[0].r = 181;
	tetramini[0].g = 15;
	tetramini[0].b = 193;
	y++;
	x--;
	for (int i = 0; i < 3; i++)
	{
		tetramino_init_custom(&tetramini[i + 1], x + i, y);
		tetramini[i + 1].r = 181;
		tetramini[i + 1].g = 15;
		tetramini[i + 1].b = 193;
	}
}

void spawn_left_z(tetramino_t tetramini[], int x, int y)
{
	int i;
	for (i = 0; i < 2; i++)
	{
		tetramino_init_custom(&tetramini[i], x + i, y);
		tetramini[i].r = 230;
		tetramini[i].g = 20;
		tetramini[i].b = 20;
	}
	y++;
	x++;
	for (i = 0; i < 2; i++)
	{
		tetramino_init_custom(&tetramini[i + 2], x + i, y);
		tetramini[i + 2].r = 230;
		tetramini[i + 2].g = 20;
		tetramini[i + 2].b = 20;
	}
}

void spawn_right_z(tetramino_t tetramini[], int x, int y)
{
	int i;
	for (i = 0; i < 2; i++)
	{
		tetramino_init_custom(&tetramini[i], x - i, y);
		tetramini[i].r = 21;
		tetramini[i].g = 214;
		tetramini[i].b = 21;
	}
	y++;
	x--;
	for (i = 0; i < 2; i++)
	{
		tetramino_init_custom(&tetramini[i + 2], x - i, y);
		tetramini[i + 2].r = 21;
		tetramini[i + 2].g = 214;
		tetramini[i + 2].b = 21;
	}
}

void spawn_left_l(tetramino_t tetramini[], int x, int y)
{
	int i = 0;
	tetramino_init_custom(&tetramini[0], x, y);
	tetramini[0].r = 25;
	tetramini[0].g = 17;
	tetramini[0].b = 249;
	y++;
	for (i = 0; i < 3; i++)
	{
		tetramino_init_custom(&tetramini[i + 1], x + i, y);
		tetramini[i + 1].r = 25;
		tetramini[i + 1].g = 17;
		tetramini[i + 1].b = 249;

	}
}

void spawn_right_l(tetramino_t tetramini[], int x, int y)
{
	int i;
	tetramino_init_custom(&tetramini[0], x, y);
	tetramini[0].r = 255;
	tetramini[0].g = 168;
	tetramini[0].b = 20;
	y++;
	for (i = 0; i < 3; i++)
	{
		tetramino_init_custom(&tetramini[i + 1], x - i, y);
		tetramini[i + 1].r = 255;
		tetramini[i + 1].g = 168;
		tetramini[i + 1].b = 20;
	}
}