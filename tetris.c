#include "tetris.h"



void tetramino_init_custom(tetramino_t *tetramino, int x, int y)
{
	tetramino->x = x;
	tetramino->y = y;
	tetramino->r = 0;
	tetramino->g = 0;
	tetramino->b = 0;
}

int tetramino_move_all_down(tetramino_t tetramini[], tetris_map_t *tetris_map)
{
	int dead_cells[4];
	int i;
	// first check
	int can_move = 0;

	for (i = 0; i < 4; i++)
	{
		if (tetramino_check_status_down(&tetramini[i], tetris_map, &dead_cells[i]) == TETRAMINO_DEAD)
		{
			can_move = 1;
		}
	}

	if (can_move == 1)
	{
		for (int j = 0; j < 4; j++)
		{
			tetris_map->cell[dead_cells[j]] = 1;
		}
		return TETRAMINO_DEAD;
	}


	for (i = 0; i < 4; i++)
	{
		tetramino_move_down(&tetramini[i]);
	}

	return TETRAMINO_OK;
}



int tetramino_check_status_down(tetramino_t *tetramino, tetris_map_t *map, int *dead_cell)
{
	int current_index = map->width * tetramino->y + tetramino->x;
	int next_index = map->width * (tetramino->y + 1) + tetramino->x;

	*dead_cell = current_index;

	if (tetramino->y + 1 >= map->height)
	{
		return TETRAMINO_DEAD;
	}

	if (map->cell[next_index] == 1)
	{
		return TETRAMINO_DEAD;
	}

	return TETRAMINO_OK;

}

int tetramino_move_down(tetramino_t *tetramino)
{
	tetramino->y += 1;
	return TETRAMINO_OK;
}

int tetramino_check_status_right(tetramino_t *tetramino, tetris_map_t *map)
{
	int right_index = map->width * tetramino->y + (tetramino->x + 1);

	if (tetramino->x + 1 >= map->width)
	{
		return TETRAMINO_DEAD;
	}

	if (map->cell[right_index] == 1)
	{
		return TETRAMINO_DEAD;
	}

	return TETRAMINO_OK;

}

int tetramino_move_right(tetramino_t *tetramino)
{
	tetramino->x++;
	return TETRAMINO_OK;
}

int tetramino_move_all_right(tetramino_t tetramini[], tetris_map_t *tetris_map)
{

	int i;

	for (i = 0; i < 4; i++)
	{
		if (tetramino_check_status_right(&tetramini[i], tetris_map) == TETRAMINO_DEAD)
		{
			return TETRAMINO_DEAD;
		}
	}

	for (i = 0; i < 4; i++)
	{
		tetramino_move_right(&tetramini[i]);
	}

	return TETRAMINO_OK;
}

int tetramino_check_status_left(tetramino_t *tetramino, tetris_map_t *map)
{
	int left_index = map->width * tetramino->y + (tetramino->x - 1);

	if (tetramino->x <= 0)
	{
		return TETRAMINO_DEAD;
	}

	if (map->cell[left_index] == 1)
	{
		return TETRAMINO_DEAD;
	}

	return TETRAMINO_OK;
}

int tetramino_move_left(tetramino_t *tetramino)
{
	tetramino->x--;
	return TETRAMINO_OK;
}

int tetramino_move_all_left(tetramino_t tetramini[], tetris_map_t *tetris_map)
{

	int i;

	for (i = 0; i < 4; i++)
	{
		if (tetramino_check_status_left(&tetramini[i], tetris_map) == TETRAMINO_DEAD)
		{
			return TETRAMINO_DEAD;
		}
	}

	for (i = 0; i < 4; i++)
	{
		tetramino_move_left(&tetramini[i]);
	}

	return TETRAMINO_OK;
}

void rotate_tetraminoes_types(tetramino_t tetramini[], int pivot, tetris_map_t* tetris_map)
{
	//conceptual matrix for rotating tetramini
	tetramino_t *m_center = &tetramini[pivot];

	//current index of tetraminoes to check
	int index;

	//variables for backup the positions in case of non rotation
	int count_positions = 0;
	int backup_positions[8];


	if (pivot == 0)
	{
		return;
	}


	for (index = 0; index < 4; index++)
	{
		backup_positions[count_positions++] = tetramini[index].x;
		backup_positions[count_positions++] = tetramini[index].y;

		if (m_center == &tetramini[index])
		{
			continue;
		}
		//check rotation between tetramini and "matrix" in clockwise direction
		ROTATION_CHECK_MOVE(tetramini, m_center, index)

		//check for out of map 
		if (tetramini[index].x >= tetris_map->width || tetramini[index].x < 0)
		{
			break;
		}

		//check if current overlap
		int current_index = tetris_map->width * tetramini[index].y + tetramini[index].x;
		if (tetris_map->cell[current_index] == 1)
		{
			break;
		}
	}

	if (index == 4)
	{
		return;
	}

	count_positions = 0;
	for (int j = 0; j <= index; j++)
	{
		tetramini[j].x = backup_positions[count_positions++];
		tetramini[j].y = backup_positions[count_positions++];
	}
}

void tetris_map_init(tetris_map_t *tetris_map, int width, int height)
{
	int size = sizeof(int) * width * height;

	tetris_map->cell = malloc(size);
	memset(tetris_map->cell, 0, size);
	tetris_map->width = width;
	tetris_map->height = height;
}

int check_for_full_lines(tetramino_t *tetramini, tetris_map_t *tetris_map, int *out_rows)
{
	//total line to remove from out_rows
	int rows_to_remove = 0;
	for (int i = 0; i < 4; i++)
	{
		//current index of single tetramino (check tetramini)
		int current_index = tetris_map->width * tetramini[i].y + tetramini[i].x;
		//index of the row 
		int row = current_index / tetris_map->width;

		int line_full = 1;
		for (int x = 0; x < tetris_map->width; x++)
		{
			//current index of the row and column
			current_index = tetris_map->width * row + x;

			if (tetris_map->cell[current_index] == 1 && line_full)
			{
				continue;
			}
			line_full = 0;
		}

		if (line_full)
		{
			int finded = 0;
			for (int j = 0; j < rows_to_remove; j++)
			{
				//index of the tetraminoes when reach the ground or when the value of the current line is 1
				if (out_rows[j] == row)
				{
					finded = 1;
				}
			}

			if (!finded)
			{
				out_rows[rows_to_remove] = row;
				rows_to_remove++;
			}
		}
	}

	return rows_to_remove;
}

void remove_full_lines(tetris_map_t *tetris_map, int *out_rows, int rows_to_remove)
{
	order_rows(out_rows, rows_to_remove);
	for (int i = 0; i < rows_to_remove; i++)
	{
		size_t size = sizeof(int) * tetris_map->width * out_rows[i];
		SDL_memcpy(tetris_map->cell + tetris_map->width, tetris_map->cell, size);
	}
}

void order_rows(int *rows_to_order, int length_row)
{
	for (int i = 0; i < length_row; i++)
	{
		for (int j = 0; j < length_row; j++)
		{
			if (rows_to_order[j] > rows_to_order[i])
			{
				int tmp = rows_to_order[i];
				rows_to_order[i] = rows_to_order[j];
				rows_to_order[j] = tmp;
			}
		}
	}
}