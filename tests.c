#include "aiv_unit_test.h"
#include "tetris.h"

#define TETRAMINO_SETUP(width, height, x, y)     \
	tetramino_t tetramino;                       \
	tetris_map_t tetris_map;                     \
	tetris_map_init(&tetris_map, width, height); \
	tetramino_init_custom(&tetramino, x, y)

#define TETRAMINO_MOVE_DOWN(tetramino_pointer, map_pointer)                                        \
	{                                                                                              \
		int dead_cell;                                                                             \
		if (tetramino_check_status_down(tetramino_pointer, map_pointer, &dead_cell) == TETRAMINO_OK) \
		{                                                                                          \
			tetramino_move_down(tetramino_pointer);                                                \
		}                                                                                          \
		else                                                                                       \
		{                                                                                          \
			map_pointer->cell[dead_cell] = 1;													   \
		}                                                                                          \
	}

#define TETRAMINO_MOVE_RIGHT(tetramino_pointer, map_pointer)                            \
	{                                                                                   \
		if (tetramino_check_status_right(tetramino_pointer, map_pointer) == TETRAMINO_OK) \
		{                                                                               \
			tetramino_move_right(tetramino_pointer);                                    \
		}                                                                               \
	}

#define TETRAMINO_MOVE_LEFT(tetramino_pointer, map_pointer)                            \
	{                                                                                  \
		if (tetramino_check_status_left(tetramino_pointer, map_pointer) == TETRAMINO_OK) \
		{                                                                              \
			tetramino_move_left(tetramino_pointer);                                    \
		}                                                                              \
	}
#define TETRAMINO_COLOR_SETUP(tetramino_pointer)									\
	for (int i = 0; i < 4; i++)														\
	{																				\
		tetramino_pointer[i].r = 0;													\
		tetramino_pointer[i].g = 0;													\
		tetramino_pointer[i].b = 0;													\
	}

TEST(tetramino_init_custom)
{
	TETRAMINO_SETUP(1, 1, 5, 7);

	ASSERT_THAT(tetramino.x == 5);
	ASSERT_THAT(tetramino.y == 7)
}

TEST(spawn_cube)
{
	tetramino_t tetramini[4];
	TETRAMINO_COLOR_SETUP(tetramini)
	spawn_cube(tetramini, 0, 0);

	ASSERT_THAT(tetramini[0].x == 0);
	ASSERT_THAT(tetramini[0].y == 0);

	ASSERT_THAT(tetramini[1].x == 1);
	ASSERT_THAT(tetramini[1].y == 0);

	ASSERT_THAT(tetramini[2].x == 0);
	ASSERT_THAT(tetramini[2].y == 1);

	ASSERT_THAT(tetramini[3].x == 1);
	ASSERT_THAT(tetramini[3].y == 1);
}

TEST(spawn_line)
{
	tetramino_t tetramini[4];
	spawn_line(tetramini, 0, 0);

	ASSERT_THAT(tetramini[0].x == 0);
	ASSERT_THAT(tetramini[0].y == 0);

	ASSERT_THAT(tetramini[1].x == 1);
	ASSERT_THAT(tetramini[1].y == 0);

	ASSERT_THAT(tetramini[2].x == 2);
	ASSERT_THAT(tetramini[2].y == 0);

	ASSERT_THAT(tetramini[3].x == 3);
	ASSERT_THAT(tetramini[3].y == 0);
}

TEST(spawn_right_l)
{
	tetramino_t tetramini[4];
	spawn_right_l(tetramini, 3, 0);

	ASSERT_THAT(tetramini[0].x == 3);
	ASSERT_THAT(tetramini[0].y == 0);

	ASSERT_THAT(tetramini[1].x == 3);
	ASSERT_THAT(tetramini[1].y == 1);

	ASSERT_THAT(tetramini[2].x == 2);
	ASSERT_THAT(tetramini[2].y == 1);

	ASSERT_THAT(tetramini[3].x == 1);
	ASSERT_THAT(tetramini[3].y == 1);
}

TEST(spawn_left_l)
{
	tetramino_t tetramini[4];
	spawn_left_l(tetramini, 0, 0);

	ASSERT_THAT(tetramini[0].x == 0);
	ASSERT_THAT(tetramini[0].y == 0);

	ASSERT_THAT(tetramini[1].x == 0);
	ASSERT_THAT(tetramini[1].y == 1);

	ASSERT_THAT(tetramini[2].x == 1);
	ASSERT_THAT(tetramini[2].y == 1);

	ASSERT_THAT(tetramini[3].x == 2);
	ASSERT_THAT(tetramini[3].y == 1);
}

TEST(spawn_right_z)
{
	tetramino_t tetramini[4];
	spawn_right_z(tetramini, 2, 0);

	ASSERT_THAT(tetramini[0].x == 2);
	ASSERT_THAT(tetramini[0].y == 0);

	ASSERT_THAT(tetramini[1].x == 1);
	ASSERT_THAT(tetramini[1].y == 0);

	ASSERT_THAT(tetramini[2].x == 1);
	ASSERT_THAT(tetramini[2].y == 1);

	ASSERT_THAT(tetramini[3].x == 0);
	ASSERT_THAT(tetramini[3].y == 1);
}

TEST(spawn_left_z)
{
	tetramino_t tetramini[4];
	spawn_left_z(tetramini, 0, 0);

	ASSERT_THAT(tetramini[0].x == 0);
	ASSERT_THAT(tetramini[0].y == 0);

	ASSERT_THAT(tetramini[1].x == 1);
	ASSERT_THAT(tetramini[1].y == 0);

	ASSERT_THAT(tetramini[2].x == 1);
	ASSERT_THAT(tetramini[2].y == 1);

	ASSERT_THAT(tetramini[3].x == 2);
	ASSERT_THAT(tetramini[3].y == 1);
}

TEST(spawn_T)
{
	tetramino_t tetramini[4];
	spawn_T(tetramini, 0, 0);

	ASSERT_THAT(tetramini[0].x == 0);
	ASSERT_THAT(tetramini[0].y == 0);

	ASSERT_THAT(tetramini[1].x == -1);
	ASSERT_THAT(tetramini[1].y == 1);

	ASSERT_THAT(tetramini[2].x == 0);
	ASSERT_THAT(tetramini[2].y == 1);

	ASSERT_THAT(tetramini[3].x == 1);
	ASSERT_THAT(tetramini[3].y == 1);
}

TEST(move_all_down)
{
	tetramino_t tetramini[4];
	spawn_cube(tetramini, 0, -2);

	tetris_map_t map;
	tetris_map_init(&map, 2, 2);

	int res = tetramino_move_all_down(tetramini, &map);

	ASSERT_THAT(res == TETRAMINO_OK);

	ASSERT_THAT(tetramini[0].x == 0);
	ASSERT_THAT(tetramini[0].y == -1);

	ASSERT_THAT(tetramini[1].x == 1);
	ASSERT_THAT(tetramini[1].y == -1);

	ASSERT_THAT(tetramini[2].x == 0);
	ASSERT_THAT(tetramini[2].y == 0);

	ASSERT_THAT(tetramini[3].x == 1);
	ASSERT_THAT(tetramini[3].y == 0);
}

TEST(move_all_down_end_map)
{
	tetramino_t tetramini[4];
	spawn_cube(tetramini, 0, -2);

	tetris_map_t map;
	tetris_map_init(&map, 2, 1);

	int res = tetramino_move_all_down(tetramini, &map);
	res = tetramino_move_all_down(tetramini, &map);

	ASSERT_THAT(res == TETRAMINO_DEAD);
}

TEST(move_all_down_occupied_cell)
{
	tetramino_t tetramini[4];
	spawn_cube(tetramini, 0, -2);

	tetris_map_t map;
	tetris_map_init(&map, 2, 1);

	int res = tetramino_move_all_down(tetramini, &map);
	res = tetramino_move_all_down(tetramini, &map);

	tetramino_t tetramini2[4];
	spawn_cube(tetramini2, 0, -2);

	res = tetramino_move_all_down(tetramini2, &map);

	ASSERT_THAT(res == TETRAMINO_DEAD);
}

TEST(tetramino_move_down_check)
{
	TETRAMINO_SETUP(1, 1, 0, -1);
	int dead_cell;
	int res = tetramino_check_status_down(&tetramino, &tetris_map, &dead_cell);

	ASSERT_THAT(res == TETRAMINO_OK);
}

TEST(tetramino_move_down_check_red_light)
{
	TETRAMINO_SETUP(1, 1, 0, 0);
	int dead_cell;
	int res = tetramino_check_status_down(&tetramino, &tetris_map, &dead_cell);

	ASSERT_THAT(res == TETRAMINO_DEAD);
}

TEST(tetramino_move_down_check_multiple_block)
{
	TETRAMINO_SETUP(1, 1, 0, -1);
	tetramino.y = 0;

	int dead_cell;
	tetramino_check_status_down(&tetramino, &tetris_map, &dead_cell);
	tetris_map.cell[dead_cell] = 1;

	tetramino_t tetramino2;
	tetramino_init_custom(&tetramino2, 0, -1);

	int res = tetramino_check_status_down(&tetramino2, &tetris_map, &dead_cell);

	ASSERT_THAT(res == TETRAMINO_DEAD);
}

TEST(tetramino_move_down)
{
	TETRAMINO_SETUP(1, 1, 0, -1);
	tetramino_move_down(&tetramino);

	ASSERT_THAT(tetramino.y == 0);
}

TEST(tetramino_move_down_wrong_value)
{
	TETRAMINO_SETUP(1, 1, 0, -1);
	tetramino.y = 100;
	int dead_cell;
	if (tetramino_check_status_down(&tetramino, &tetris_map, &dead_cell) == TETRAMINO_OK)
	{
		tetramino_move_down(&tetramino);
	}

	ASSERT_THAT(tetramino.y == 100);
}

TEST(move_all_right)
{
	tetramino_t tetramini[4];
	spawn_cube(tetramini, 0, 0);

	tetris_map_t map;
	tetris_map_init(&map, 4, 4);

	ASSERT_THAT(tetramino_move_all_right(tetramini, &map) == TETRAMINO_OK);

	ASSERT_THAT(tetramini[0].x == 1);
	ASSERT_THAT(tetramini[0].y == 0);

	ASSERT_THAT(tetramini[1].x == 2);
	ASSERT_THAT(tetramini[1].y == 0);

	ASSERT_THAT(tetramini[2].x == 1);
	ASSERT_THAT(tetramini[2].y == 1);

	ASSERT_THAT(tetramini[3].x == 2);
	ASSERT_THAT(tetramini[3].y == 1);
}

TEST(move_all_right_border)
{
	tetramino_t tetramini[4];
	spawn_cube(tetramini, 0, 0);

	tetris_map_t map;
	tetris_map_init(&map, 3, 2);

	int res = tetramino_move_all_right(tetramini, &map);
	res = tetramino_move_all_right(tetramini, &map);

	ASSERT_THAT(res == TETRAMINO_DEAD);
}

TEST(tetramino_move_right_check)
{
	TETRAMINO_SETUP(2, 1, 0, -1);

	int res = tetramino_check_status_right(&tetramino, &tetris_map);

	ASSERT_THAT(res == TETRAMINO_OK);
}

TEST(tetramino_move_right_check_blocked)
{
	TETRAMINO_SETUP(1, 1, 0, -1);

	int res = tetramino_check_status_right(&tetramino, &tetris_map);

	ASSERT_THAT(res == TETRAMINO_DEAD);
}

TEST(tetramino_move_right_blocked)
{
	TETRAMINO_SETUP(1, 1, 0, -1);

	tetris_map_t *map = &tetris_map;
	TETRAMINO_MOVE_RIGHT(&tetramino, map);

	ASSERT_THAT(tetramino.x == 0);
}

TEST(tetramino_move_right)
{
	TETRAMINO_SETUP(2, 1, 0, 0);

	tetris_map_t *map = &tetris_map;
	TETRAMINO_MOVE_RIGHT(&tetramino, map);

	ASSERT_THAT(tetramino.x == 1);
}

TEST(tetramino_move_right_multiple)
{
	TETRAMINO_SETUP(2, 1, 0, 0);

	tetris_map_t *map = &tetris_map;
	TETRAMINO_MOVE_RIGHT(&tetramino, map);
	TETRAMINO_MOVE_RIGHT(&tetramino, map);

	ASSERT_THAT(tetramino.x == 1);
}

TEST(move_all_left)
{
	tetramino_t tetramini[4];
	spawn_cube(tetramini, 1, 0);

	tetris_map_t map;
	tetris_map_init(&map, 4, 4);


	ASSERT_THAT(tetramino_move_all_left(tetramini, &map) == TETRAMINO_OK);

	ASSERT_THAT(tetramini[0].x == 0);
	ASSERT_THAT(tetramini[0].y == 0);

	ASSERT_THAT(tetramini[1].x == 1);
	ASSERT_THAT(tetramini[1].y == 0);

	ASSERT_THAT(tetramini[2].x == 0);
	ASSERT_THAT(tetramini[2].y == 1);

	ASSERT_THAT(tetramini[3].x == 1);
	ASSERT_THAT(tetramini[3].y == 1);
}

TEST(move_all_left_border)
{
	tetramino_t tetramini[4];
	spawn_cube(tetramini, 1, 0);

	tetris_map_t map;
	tetris_map_init(&map, 3, 2);

	int res = tetramino_move_all_right(tetramini, &map);
	res = tetramino_move_all_right(tetramini, &map);

	ASSERT_THAT(res == TETRAMINO_DEAD);
}

TEST(tetramino_move_left_check)
{
	TETRAMINO_SETUP(2, 1, 1, -1);

	int res = tetramino_check_status_left(&tetramino, &tetris_map);

	ASSERT_THAT(res == TETRAMINO_OK);
}

TEST(tetramino_move_left_check_blocked)
{
	TETRAMINO_SETUP(1, 1, 0, -1);

	int res = tetramino_check_status_left(&tetramino, &tetris_map);

	ASSERT_THAT(res == TETRAMINO_DEAD);
}

TEST(tetramino_move_left_blocked)
{
	TETRAMINO_SETUP(1, 1, 0, -1);

	tetris_map_t *map = &tetris_map;
	TETRAMINO_MOVE_LEFT(&tetramino, map);

	ASSERT_THAT(tetramino.x == 0);
}

TEST(tetramino_move_left)
{
	TETRAMINO_SETUP(2, 1, 1, -1);

	tetris_map_t *map = &tetris_map;
	TETRAMINO_MOVE_LEFT(&tetramino, map);

	ASSERT_THAT(tetramino.x == 0);
}

TEST(tetramino_move_left_multiple)
{
	TETRAMINO_SETUP(2, 1, 1, -1);

	tetris_map_t *map = &tetris_map;
	TETRAMINO_MOVE_LEFT(&tetramino, map);
	TETRAMINO_MOVE_LEFT(&tetramino, map);

	ASSERT_THAT(tetramino.x == 0);
}

TEST(tetramino_busy_cell)
{
	TETRAMINO_SETUP(1, 1, 0, -1);

	tetris_map_t *map_pointer = &tetris_map;

	TETRAMINO_MOVE_DOWN(&tetramino, map_pointer);
	TETRAMINO_MOVE_DOWN(&tetramino, map_pointer);

	tetramino_t tetramino2;
	tetramino_init_custom(&tetramino2, 0, -1);

	TETRAMINO_MOVE_DOWN(&tetramino, map_pointer);
	TETRAMINO_MOVE_DOWN(&tetramino, map_pointer);

	ASSERT_THAT(tetramino2.y == -1);
}

TEST(tetramino_fill_two_blocks)
{
	TETRAMINO_SETUP(1, 2, 0, -1);

	tetris_map_t *map_pointer = &tetris_map;

	TETRAMINO_MOVE_DOWN(&tetramino, map_pointer);
	TETRAMINO_MOVE_DOWN(&tetramino, map_pointer);
	TETRAMINO_MOVE_DOWN(&tetramino, map_pointer);

	ASSERT_THAT(tetramino.y == 1);

	tetramino_t tetramino2;
	tetramino_init_custom(&tetramino2, 0, -1);

	TETRAMINO_MOVE_DOWN(&tetramino2, map_pointer);
	TETRAMINO_MOVE_DOWN(&tetramino2, map_pointer);
	TETRAMINO_MOVE_DOWN(&tetramino2, map_pointer);

	ASSERT_THAT(tetramino2.y == 0);
}

TEST(tetramino_map_init)
{
	tetris_map_t tetris_map;
	tetris_map_init(&tetris_map, 1, 1);

	ASSERT_THAT(tetris_map.cell[0] == 0);
}

TEST(rotate_cube)
{
	tetramino_t tetramini[4];
	int pivot = 0;
	spawn_cube(tetramini, 0, 0);

	tetris_map_t map;
	tetris_map_init(&map, 4, 4);

	rotate_tetraminoes_types(tetramini, pivot, &map);

	ASSERT_THAT(tetramini[0].x == 0);
	ASSERT_THAT(tetramini[0].y == 0);

	ASSERT_THAT(tetramini[1].x == 1);
	ASSERT_THAT(tetramini[1].y == 0);

	ASSERT_THAT(tetramini[2].x == 0);
	ASSERT_THAT(tetramini[2].y == 1);

	ASSERT_THAT(tetramini[3].x == 1);
	ASSERT_THAT(tetramini[3].y == 1);

	rotate_tetraminoes_types(tetramini, pivot, &map);

	ASSERT_THAT(tetramini[0].x == 0);
	ASSERT_THAT(tetramini[0].y == 0);

	ASSERT_THAT(tetramini[1].x == 1);
	ASSERT_THAT(tetramini[1].y == 0);

	ASSERT_THAT(tetramini[2].x == 0);
	ASSERT_THAT(tetramini[2].y == 1);

	ASSERT_THAT(tetramini[3].x == 1);
	ASSERT_THAT(tetramini[3].y == 1);
}

TEST(rotate_T)
{
	tetramino_t tetramini[4];
	int pivot = 2;
	spawn_T(tetramini, 1, 0);

	tetris_map_t map;
	tetris_map_init(&map, 4, 4);

	rotate_tetraminoes_types(tetramini, pivot, &map);
	printf("%d", tetramini[0].x);
	printf("%d", tetramini[1].x);
	printf("%d", tetramini[2].x);
	printf("%d", tetramini[3].x);


	ASSERT_THAT(tetramini[0].x == 2);
	ASSERT_THAT(tetramini[0].y == 1);

	ASSERT_THAT(tetramini[1].x == 1);
	ASSERT_THAT(tetramini[1].y == 0);

	ASSERT_THAT(tetramini[2].x == 1);
	ASSERT_THAT(tetramini[2].y == 1);

	ASSERT_THAT(tetramini[3].x == 1);
	ASSERT_THAT(tetramini[3].y == 2);
}

TEST(rotate_T_red_light)
{
	tetramino_t tetramini[4];
	int pivot = 2;
	spawn_T(tetramini, 1, 0);

	tetris_map_t map;
	tetris_map_init(&map, 4, 4);
	map.cell[9] = 1;

	rotate_tetraminoes_types(tetramini, pivot, &map);

	ASSERT_THAT(tetramini[0].x == 1);
	ASSERT_THAT(tetramini[0].y == 0);

	ASSERT_THAT(tetramini[1].x == 0);
	ASSERT_THAT(tetramini[1].y == 1);

	ASSERT_THAT(tetramini[2].x == 1);
	ASSERT_THAT(tetramini[2].y == 1);

	ASSERT_THAT(tetramini[3].x == 2);
	ASSERT_THAT(tetramini[3].y == 1);
}

TEST(rotate_line)
{
	tetramino_t tetramini[4];
	int pivot = 2;
	spawn_line(tetramini, 0, 2);

	tetris_map_t map;
	tetris_map_init(&map, 4, 4);

	rotate_tetraminoes_types(tetramini, pivot, &map);

	ASSERT_THAT(tetramini[0].x == 2);
	ASSERT_THAT(tetramini[0].y == 0);

	ASSERT_THAT(tetramini[1].x == 2);
	ASSERT_THAT(tetramini[1].y == 1);

	ASSERT_THAT(tetramini[2].x == 2);
	ASSERT_THAT(tetramini[2].y == 2);

	ASSERT_THAT(tetramini[3].x == 2);
	ASSERT_THAT(tetramini[3].y == 3);
}

TEST(rotate_line_red_light)
{
	tetramino_t tetramini[4];
	int pivot = 2;
	spawn_line(tetramini, 0, 1);

	tetris_map_t map;
	tetris_map_init(&map, 4, 4);
	map.cell[2] = 1;

	rotate_tetraminoes_types(tetramini, pivot, &map);

	ASSERT_THAT(tetramini[0].x == 0);
	ASSERT_THAT(tetramini[0].y == 1);

	ASSERT_THAT(tetramini[1].x == 1);
	ASSERT_THAT(tetramini[1].y == 1);

	ASSERT_THAT(tetramini[2].x == 2);
	ASSERT_THAT(tetramini[2].y == 1);

	ASSERT_THAT(tetramini[3].x == 3);
	ASSERT_THAT(tetramini[3].y == 1);
}

TEST(remove_full_line)
{
	tetris_map_t map;
	tetris_map_init(&map, 4, 2);

	map.cell[4] = 1;
	map.cell[5] = 1;
	map.cell[6] = 1;
	map.cell[7] = 1;

	int rows[4];
	rows[0] = 1;

	remove_full_lines(&map, rows, 1);

	ASSERT_THAT(map.cell[4] == 0);
	ASSERT_THAT(map.cell[5] == 0);
	ASSERT_THAT(map.cell[6] == 0);
	ASSERT_THAT(map.cell[7] == 0);
}

TEST(remove_multiple_lines)
{
	tetris_map_t map;
	tetris_map_init(&map, 4, 4);

	map.cell[4] = 1;
	map.cell[5] = 1;
	map.cell[6] = 1;
	map.cell[7] = 1;

	map.cell[8] = 1;
	map.cell[9] = 1;
	map.cell[10] = 1;
	map.cell[11] = 1;

	map.cell[12] = 1;
	map.cell[13] = 1;
	map.cell[14] = 1;
	map.cell[15] = 1;

	int rows[4];
	rows[0] = 1;
	rows[1] = 2;
	rows[2] = 3;

	remove_full_lines(&map, rows, 3);

	ASSERT_THAT(map.cell[4] == 0);
	ASSERT_THAT(map.cell[5] == 0);
	ASSERT_THAT(map.cell[6] == 0);
	ASSERT_THAT(map.cell[7] == 0);

	ASSERT_THAT(map.cell[8] == 0);
	ASSERT_THAT(map.cell[9] == 0);
	ASSERT_THAT(map.cell[10] == 0);
	ASSERT_THAT(map.cell[11] == 0);

	ASSERT_THAT(map.cell[12] == 0);
	ASSERT_THAT(map.cell[13] == 0);
	ASSERT_THAT(map.cell[14] == 0);
	ASSERT_THAT(map.cell[15] == 0);
}

TEST(check_for_full_lines)
{
	tetramino_t tetramini[4];
	spawn_cube(tetramini, 0, 0);

	tetris_map_t map;
	tetris_map_init(&map, 2, 2);

	map.cell[0] = 1;
	map.cell[1] = 1;
	map.cell[2] = 1;
	map.cell[3] = 1;

	int rows[4];
	int ret = check_for_full_lines(tetramini, &map, rows);

	ASSERT_THAT(ret == 2);
	ASSERT_THAT(rows[0] == 0);
	ASSERT_THAT(rows[1] == 1);
}








int main(int argc, char **argv)
{
	RUN_TEST(tetramino_init_custom);
	RUN_TEST(tetramino_map_init);
	RUN_TEST(spawn_cube);
	RUN_TEST(spawn_left_l);
	RUN_TEST(spawn_left_z);
	RUN_TEST(spawn_right_l);
	RUN_TEST(spawn_right_z);
	RUN_TEST(spawn_line);
	RUN_TEST(spawn_T);

	RUN_TEST(tetramino_move_down_check);
	RUN_TEST(tetramino_move_down_check_red_light);
	RUN_TEST(tetramino_move_down_check_multiple_block);

	RUN_TEST(tetramino_move_down);
	RUN_TEST(tetramino_move_down_wrong_value);

	RUN_TEST(tetramino_busy_cell);
	RUN_TEST(tetramino_fill_two_blocks);

	RUN_TEST(move_all_right);
	RUN_TEST(move_all_right_border);
	RUN_TEST(tetramino_move_right_check);
	RUN_TEST(tetramino_move_right_check_blocked);
	RUN_TEST(tetramino_move_right);
	RUN_TEST(tetramino_move_right_blocked);
	RUN_TEST(tetramino_move_right_multiple);

	RUN_TEST(move_all_left);
	RUN_TEST(move_all_left_border);
	RUN_TEST(tetramino_move_left_check);
	RUN_TEST(tetramino_move_left_check_blocked);
	RUN_TEST(tetramino_move_left);
	RUN_TEST(tetramino_move_left_blocked);
	RUN_TEST(tetramino_move_left_multiple);

	RUN_TEST(move_all_down);
	RUN_TEST(move_all_down_end_map);
	RUN_TEST(move_all_down_occupied_cell);

	RUN_TEST(rotate_cube);
	RUN_TEST(rotate_T);
	RUN_TEST(rotate_T_red_light);
	RUN_TEST(rotate_line);
	RUN_TEST(rotate_line_red_light);

	RUN_TEST(remove_full_line);
	RUN_TEST(remove_multiple_lines);
	RUN_TEST(check_for_full_lines);

	PRINT_TEST_RESULTS();
	return 0;
}