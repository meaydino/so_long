#include "so_long.h"

#include <stdlib.h>

void	flood_fill_algorithm(int **visited, t_game_state *game, int x, int y)
{
	if (game->board->cells[y][x] == 'C')
		game->items_left--;
	if (game->board->cells[y][x] == 'E')
		game->path_validated--;
	if (game->board->cells[y - 1][x] != '1' && visited[y - 1][x] == 0)
	{
		visited[y - 1][x] = 1;
		flood_fill_algorithm(visited, game, x, y - 1);
	}
	if (game->board->cells[y + 1][x] != '1' && visited[y + 1][x] == 0)
	{
		visited[y + 1][x] = 1;
		flood_fill_algorithm(visited, game, x, y + 1);
	}
	if (game->board->cells[y][x - 1] != '1' && visited[y][x - 1] == 0)
	{
		visited[y][x - 1] = 1;
		flood_fill_algorithm(visited, game, x - 1, y);
	}
	if (game->board->cells[y][x + 1] != '1' && visited[y][x + 1] == 0)
	{
		visited[y][x + 1] = 1;
		flood_fill_algorithm(visited, game, x + 1, y);
	}
}

static int	**allocate_visited_matrix(t_game_state *game)
{
	int	**matrix;
	int	i;

	matrix = (int **)malloc(sizeof(int *) * (game->board->height + 1));
	if (!matrix)
		terminate_program("Memory allocation failed", game, 1);
	i = 0;
	while (i < game->board->height)
	{
		matrix[i] = (int *)malloc(sizeof(int) * (game->board->width + 1));
		if (!matrix[i])
		{
			release_memory((void **)matrix);
			terminate_program("Memory allocation failed", game, 1);
		}
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}

static void	initialize_matrix(int **matrix, t_game_state *game)
{
	int	row;
	int	col;

	row = 0;
	while (row < game->board->height)
	{
		col = 0;
		while (col < game->board->width)
		{
			matrix[row][col] = 0;
			col++;
		}
		row++;
	}
}

void	create_visited_matrix(t_game_state *game, int start_x, int start_y)
{
	int	**visited_grid;

	visited_grid = allocate_visited_matrix(game);
	initialize_matrix(visited_grid, game);
	flood_fill_algorithm(visited_grid, game, game->hero_pos.x, game->hero_pos.y);
	release_memory((void **)visited_grid);
	verify_accessibility(game);
}

void	verify_accessibility(t_game_state *game)
{
	if (game->items_left != 0 && game->path_validated != 0)
		terminate_program("Error: Path validation failed!", game, 1);
	if (game->items_left != 0)
		terminate_program("Error: Some collectibles unreachable!", game, 1);
	if (game->path_validated != 0)
		terminate_program("Error: Exit is unreachable!", game, 1);
}