#include "../minilibx/mlx.h"
#include "../include/so_long.h"



void	setup_graphics(t_game_state *game)
{
	int	texture_width;
	int	texture_height;

	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		cleanup_resources(game);
	game->win_ptr = mlx_new_window(game->mlx_ptr,
		game->board->width * PIXEL, game->board->height * PIXEL, "Game Engine");
	game->hero_img = mlx_xpm_file_to_image(game->mlx_ptr,
		TEXTURE_PLAYER, &texture_height, &texture_width);
	game->item_img = mlx_xpm_file_to_image(game->mlx_ptr,
		TEXTURE_COIN, &texture_height, &texture_width);
	game->door_img = mlx_xpm_file_to_image(game->mlx_ptr,
		TEXTURE_EXIT, &texture_height, &texture_width);
	game->barrier_img = mlx_xpm_file_to_image(game->mlx_ptr,
		TEXTURE_WALL, &texture_height, &texture_width);
	game->floor_img = mlx_xpm_file_to_image(game->mlx_ptr,
		TEXTURE_FLOOR, &texture_height, &texture_width);
	if (!game->win_ptr || !game->hero_img || !game->item_img
		|| !game->door_img || !game->barrier_img || !game->floor_img)
		cleanup_resources(game);
}

static void	render_tile(t_game_state *game, int x, int y)
{
	char cell = game->board->cells[y][x];

	// İlk olarak tüm karelerde zemin çiz
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->floor_img, x * PIXEL, y * PIXEL);

	if (cell == '1')
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->barrier_img, x * PIXEL, y * PIXEL);
	else if (cell == 'C')
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->item_img, x * PIXEL, y * PIXEL);
	else if (cell == 'E')
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->door_img, x * PIXEL, y * PIXEL);
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
		game->hero_pos.x * PIXEL, game->hero_pos.y * PIXEL);
	return (0);
}
