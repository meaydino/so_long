#include "../minilibx/mlx.h"
#include "so_long.h"


void	setup_graphics(t_game_state *game)
{
	int	texture_width;
	int	texture_height;

	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		cleanup_resources(game);
	game->win_ptr = mlx_new_window(game->mlx_ptr, 
		game->board->width * TILE_SIZE, game->board->height * TILE_SIZE, "Game Engine");
	game->hero_img = mlx_xpm_file_to_image(game->mlx_ptr, 
		"textures/player.xpm", &texture_height, &texture_width);
	game->item_img = mlx_xpm_file_to_image(game->mlx_ptr, 
		"textures/coin.xpm", &texture_height, &texture_width);
	game->door_img = mlx_xpm_file_to_image(game->mlx_ptr, 
		"textures/exit.xpm", &texture_height, &texture_width);
	game->barrier_img = mlx_xpm_file_to_image(game->mlx_ptr, 
		"textures/wall.xpm", &texture_height, &texture_width);
	game->floor_img = mlx_xpm_file_to_image(game->mlx_ptr, 
		"textures/bground.xpm", &texture_height, &texture_width);
	if (!game->win_ptr || !game->hero_img || !game->item_img 
		|| !game->door_img || !game->barrier_img || !game->floor_img)
		cleanup_resources(game);
}

static void	render_tile(t_game_state *game, int x, int y)
{
	if (game->board->cells[y][x] == '1')
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, 
			game->barrier_img, x * TILE_SIZE, y * TILE_SIZE);
	else
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, 
			game->floor_img, x * TILE_SIZE, y * TILE_SIZE);
	if (game->board->cells[y][x] == 'E')
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, 
			game->door_img, x * TILE_SIZE, y * TILE_SIZE);
	else if (game->board->cells[y][x] == 'C')
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, 
			game->item_img, x * TILE_SIZE, y * TILE_SIZE);
}

void	draw_game_scene(t_game_state *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game->board->height)
	{
		x = -1;
		while (++x < game->board->width)
			render_tile(game, x, y);
	}
}

int	render_frame(t_game_state *game)
{
	draw_game_scene(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->hero_img, 
		game->hero_pos.x * TILE_SIZE, game->hero_pos.y * TILE_SIZE);
	return (0);
}