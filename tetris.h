#include <string.h>
#include <stdlib.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>

#define TETRAMINO_OK 0
#define TETRAMINO_DEAD -1

#define ROTATION_CHECK_MOVE(pointer_to_tetraminoes,pointer_to_matrix_tetraminoes,index)		\
 if (pointer_to_tetraminoes[index].x == pointer_to_matrix_tetraminoes->x + 1)				\
	{																						\
	if (pointer_to_tetraminoes[index].y == pointer_to_matrix_tetraminoes->y - 1)			\
		{																					\
			pointer_to_tetraminoes[index].y += 2;											\
		}																					\
		else if (pointer_to_tetraminoes[index].y == pointer_to_matrix_tetraminoes->y + 1)	\
		{																					\
			pointer_to_tetraminoes[index].x -= 2;											\
		}																					\
		else if (pointer_to_tetraminoes[index].y == pointer_to_matrix_tetraminoes->y)		\
		{																					\
			pointer_to_tetraminoes[index].y += 1;											\
			pointer_to_tetraminoes[index].x -= 1;											\
		}																					\
	}																						\
 else if (pointer_to_tetraminoes[index].x == pointer_to_matrix_tetraminoes->x + 2 && pointer_to_tetraminoes[index].y == pointer_to_matrix_tetraminoes->y)	\
 {																							\
	pointer_to_tetraminoes[index].y += 2;													\
	pointer_to_tetraminoes[index].x -= 2;													\
 }																							\
 else if (pointer_to_tetraminoes[index].x == pointer_to_matrix_tetraminoes->x - 1)			\
 {																							\
	 if (pointer_to_tetraminoes[index].y == pointer_to_matrix_tetraminoes->y - 1)			\
	 {																						\
		 pointer_to_tetraminoes[index].x += 2;												\
	 }																						\
	 else if (pointer_to_tetraminoes[index].y == pointer_to_matrix_tetraminoes->y + 1)		\
	 {																						\
		 pointer_to_tetraminoes[index].y -= 2;												\
	 }																						\
	 else if (pointer_to_tetraminoes[index].y == pointer_to_matrix_tetraminoes->y)			\
	 {																						\
		 pointer_to_tetraminoes[index].y -= 1;												\
		 pointer_to_tetraminoes[index].x += 1;												\
	 }																						\
 }																							\
 else if (pointer_to_tetraminoes[index].x == pointer_to_matrix_tetraminoes->x - 2 && pointer_to_tetraminoes[index].y == pointer_to_matrix_tetraminoes->y)	\
 {																							\
	 pointer_to_tetraminoes[index].y -= 2;													\
	 pointer_to_tetraminoes[index].x += 2;													\
 }																							\
 else																						\
 {																							\
	 if (pointer_to_tetraminoes[index].y == pointer_to_matrix_tetraminoes->y - 1)			\
	 {																						\
		 pointer_to_tetraminoes[index].x += 1;												\
		 pointer_to_tetraminoes[index].y += 1;												\
	 }																						\
	 else if (pointer_to_tetraminoes[index].y == pointer_to_matrix_tetraminoes->y - 2)		\
	 {																						\
		 pointer_to_tetraminoes[index].x += 2;												\
		 pointer_to_tetraminoes[index].y += 2;												\
	 }																						\
	 else if (pointer_to_tetraminoes[index].y == pointer_to_matrix_tetraminoes->y + 1)		\
	 {																						\
		 pointer_to_tetraminoes[index].x -= 1;												\
		 pointer_to_tetraminoes[index].y -= 1;												\
	 }																						\
	 else if (pointer_to_tetraminoes[index].y == pointer_to_matrix_tetraminoes->y + 2)		\
	 {																						\
		 pointer_to_tetraminoes[index].x -= 2;												\
		 pointer_to_tetraminoes[index].y -= 2;												\
	 }																						\
 }

typedef struct tetramino
{
	int x;
	int y;
	int r;
	int g;
	int b;
}tetramino_t;


typedef struct tetris_map
{
	int width;
	int height;
	int *cell;
}tetris_map_t;

int tetramino_check_status_right(tetramino_t *tetramino, tetris_map_t *map);
int tetramino_move_right(tetramino_t *tetramino);
int tetramino_move_all_right(tetramino_t tetramini[], tetris_map_t *tetris_map);

int tetramino_check_status_left(tetramino_t *tetramino, tetris_map_t *map);
int tetramino_move_left(tetramino_t *tetramino);
int tetramino_move_all_left(tetramino_t tetramini[], tetris_map_t *tetris_map);

int tetramino_check_status_down(tetramino_t *tetramino, tetris_map_t *map, int *dead_cell);
int tetramino_move_down(tetramino_t *tetramino);
int tetramino_move_all_down(tetramino_t tetramini[4], tetris_map_t *tetris_map);

void rotate_tetraminoes_types(tetramino_t tetramini[], int pivot, tetris_map_t* tetris_map);

int check_for_full_lines(struct tetramino *tetramini, struct tetris_map *tetris_map, int *rows);
void remove_full_lines(tetris_map_t *tetris_map, int *out_rows, int rows_to_remove);
void order_rows(int *rows_to_order, int length_row);

void tetramino_init_custom(tetramino_t *tetramino, int x, int y);
void tetris_map_init(tetris_map_t *tetris_map, int width, int height);
void order_rows(int *rows_to_order, int length_row);

void tetramino_draw(tetramino_t *tetramino, SDL_Renderer *renderer, int size);
void tetraminoes_draw(tetramino_t tetramini[], SDL_Renderer *renderer, int size);
void tetris_map_draw(tetris_map_t *map, SDL_Renderer *renderer, int size);

void random_spawn_types(tetramino_t tetramini[], int *pivot, tetris_map_t *tetris_map);
void spawn_cube(tetramino_t tetramini[], int x, int y);
void spawn_line(tetramino_t tetramini[], int x, int y);
void spawn_T(tetramino_t tetramini[], int x, int y);
void spawn_left_z(tetramino_t tetramini[], int x, int y);
void spawn_right_z(tetramino_t tetramini[], int x, int y);
void spawn_left_l(tetramino_t tetramini[], int x, int y);
void spawn_right_l(tetramino_t tetramini[], int x, int y);

