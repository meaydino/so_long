#include "../libft/libft.h"
#include "../minilibx/mlx.h"
#include "../include/so_long.h"
#include <stdlib.h>

t_game_state	*initialize_game(char *filename)
{
	t_game_state	*game;
	int				file_lines;

	game = (t_game_state *)malloc(sizeof(t_game_state));
	if (!game)
		display_error(ERR_MALLOC);
	game->board = (t_grid *)malloc(sizeof(t_grid));
	if (!game->board)
		terminate_program(ERR_MALLOC, game, 0);
	file_lines = calculate_file_lines(filename);
	if(file_lines == 0)
		terminate_program("incorrected lines", game, 0);
	game->board->cells = build_grid_from_file(filename, file_lines, game);
	if (!game->board->cells)
		terminate_program(ERR_MAP_CREATE, game, 0);
	game->total_items = check_element_count(game->board->cells, 'C');
	if (game->total_items == 0)
		terminate_program(ERR_NO_COLLECTIBLES, game, 1);
	return (game);
}

static void	setup_game_data(t_game_state *game)
{
	game->items_left = game->total_items;
	game->path_validated = 1;
	game->board->width = ft_strlen(game->board->cells[0]);
	game->board->height = 0;
	while (game->board->cells[game->board->height])
		game->board->height++;
	locate_hero_position(game);
	game->moves_count = 0;
}

int	main(int argc, char **argv)
{
	t_game_state	*game;

	if (argc != 2)
		display_error(ERR_ARGC);
	if (!verify_file_extension(argv[1]))
		display_error(ERR_FILE_EXT);
	game = initialize_game(argv[1]);
	setup_game_data(game);
	create_visited_matrix(game);
	setup_graphics(game);
	render_frame(game);
	mlx_key_hook(game->win_ptr, handle_key_input, game);
	mlx_hook(game->win_ptr, 17, 0, handle_window_close, game);
	mlx_loop(game->mlx_ptr);
	return (0);
}
