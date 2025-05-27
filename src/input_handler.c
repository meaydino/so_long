#include "../ft_printf/ft_printf.h"
#include "../include/so_long.h"



static void	execute_move(t_game_state *game, int direction)
{
	int	new_x;
	int	new_y;

	new_x = game->hero_pos.x;
	new_y = game->hero_pos.y;
	if (direction == 1)
		new_y--;
	else if (direction == 2)
		new_x--;
	else if (direction == 3)
		new_y++;
	else if (direction == 4)
		new_x++;
	if (game->board->cells[new_y][new_x] != '1')
		process_movement(game, new_x, new_y);
}

int	handle_key_input(int keycode, t_game_state *game)
{
	if (keycode == KEY_ESC)
		cleanup_resources(game);
	else if (keycode == KEY_W)
		execute_move(game, 1);
	else if (keycode == KEY_A)
		execute_move(game, 2);
	else if (keycode == KEY_S)
		execute_move(game, 3);
	else if (keycode == KEY_D)
		execute_move(game, 4);
	else
		return (0);
	render_frame(game);
	return (0);
}

void	process_movement(t_game_state *game, int new_x, int new_y)
{
	game->hero_pos.x = new_x;
	game->hero_pos.y = new_y;
	game->moves_count++;
	ft_printf("Move: %d\n", game->moves_count);
	if (game->board->cells[new_y][new_x] == 'C')
		collect_item(game);
	if (game->board->cells[new_y][new_x] == 'E' && game->total_items == 0)
		cleanup_resources(game);
}

void	collect_item(t_game_state *game)
{
	game->total_items--;
	game->board->cells[game->hero_pos.y][game->hero_pos.x] = '0';
}

int	handle_window_close(t_game_state *game)
{
	cleanup_resources(game);
	return (0);
}
