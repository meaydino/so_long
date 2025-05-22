#include "../ft_printf/ft_printf.h"
#include "../minilibx/mlx.h"
#include "so_long.h"
#include <stdlib.h>

void	cleanup_resources(t_game_state *game)
{
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->hero_img)
		mlx_destroy_image(game->mlx_ptr, game->hero_img);
	if (game->item_img)
		mlx_destroy_image(game->mlx_ptr, game->item_img);
	if (game->door_img)
		mlx_destroy_image(game->mlx_ptr, game->door_img);
	if (game->barrier_img)
		mlx_destroy_image(game->mlx_ptr, game->barrier_img);
	if (game->floor_img)
		mlx_destroy_image(game->mlx_ptr, game->floor_img);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	terminate_program("Exit", game, 1);
}

void	display_error(char *message)
{
	ft_printf("%s\n", message);
	exit(1);
}

void	terminate_program(char *message, t_game_state *game, int flag)
{
	if (flag == 1)
		release_memory((void **)game->board->cells);
	free(game->board);
	free(game);
	ft_printf("%s\n", message);
	exit(1);
}

void	release_memory(void **memory_block)
{
	int	index;

	index = -1;
	while (memory_block[++index])
		free(memory_block[index]);
	free(memory_block);
}