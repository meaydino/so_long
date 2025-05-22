// /* Utility functions */
// void			display_error(char *message);
// void			terminate_program(char *message, t_game_state *game, int flag);
// void			release_memory(void **memory_block);
// int				verify_file_extension(char *filename);

// /* File reading */
// char			*read_next_line(int fd);

// #endif

// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.c                                             :+:      :+:    :+:   */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../libft/libft.h"
// #include "../minilibx/mlx.h"
// #include "game_engine.h"
// #include <stdlib.h>

// t_game_state	*initialize_game(char *filename)
// {
// 	t_game_state	*game;
// 	int				file_lines;

// 	game = (t_game_state *)malloc(sizeof(t_game_state));
// 	if (!game)
// 		display_error("Error\nMemory allocation failed");
// 	game->board = (t_grid *)malloc(sizeof(t_grid));
// 	if (!game->board)
// 	{
// 		free(game);
// 		display_error("Error\nMemory allocation failed");
// 	}
// 	file_lines = calculate_file_lines(filename);
// 	game->board->cells = build_grid_from_file(filename, file_lines, game);
// 	if (!game->board->cells)
// 		terminate_program("Error\nFailed to create game board", game, 0);
// 	game->total_items = check_element_count(game->board->cells, 'C');
// 	if (game->total_items == 0)
// 		terminate_program("Error\nNo collectibles found", game, 1);
// 	return (game);
// }

// static void	setup_game_data(t_game_state *game)
// {
// 	game->items_left = game->total_items;
// 	game->path_validated = 1;
// 	game->board->width = ft_strlen(game->board->cells[0]);
// 	game->board->height = 0;
// 	while (game->board->cells[game->board->height])
// 		game->board->height++;
// 	locate_hero_position(game);
// 	game->moves_count = 0;
// }

// int	main(int argc, char **argv)
// {
// 	t_game_state	*game;

// 	if (argc != 2)
// 		display_error("Error\nInvalid argument count");
// 	if (!verify_file_extension(argv[1]))
// 		display_error("Error\nInvalid file extension");
// 	game = initialize_game(argv[1]);
// 	setup_game_data(game);
// 	create_visited_matrix(game, 0, 0);
// 	setup_graphics(game);
// 	mlx_key_hook(game->win_ptr, handle_key_input, game);
// 	mlx_hook(game->win_ptr, 17, 0, handle_window_close, game);
// 	mlx_loop_hook(game->mlx_ptr, render_frame, game);
// 	mlx_loop(game->mlx_ptr);
// 	return (0);
// }

// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   pathfinding.c                                      :+:      :+:    :+:   */
// /*                                                                            */
// /* ************************************************************************** */

// #include "game_engine.h"
// #include <stdlib.h>

// void	flood_fill_algorithm(int **visited, t_game_state *game, int x, int y)
// {
// 	if (game->board->cells[y][x] == 'C')
// 		game->items_left--;
// 	if (game->board->cells[y][x] == 'E')
// 		game->path_validated--;
// 	if (game->board->cells[y - 1][x] != '1' && visited[y - 1][x] == 0)
// 	{
// 		visited[y - 1][x] = 1;
// 		flood_fill_algorithm(visited, game, x, y - 1);
// 	}
// 	if (game->board->cells[y + 1][x] != '1' && visited[y + 1][x] == 0)
// 	{
// 		visited[y + 1][x] = 1;
// 		flood_fill_algorithm(visited, game, x, y + 1);
// 	}
// 	if (game->board->cells[y][x - 1] != '1' && visited[y][x - 1] == 0)
// 	{
// 		visited[y][x - 1] = 1;
// 		flood_fill_algorithm(visited, game, x - 1, y);
// 	}
// 	if (game->board->cells[y][x + 1] != '1' && visited[y][x + 1] == 0)
// 	{
// 		visited[y][x + 1] = 1;
// 		flood_fill_algorithm(visited, game, x + 1, y);
// 	}
// }

// static int	**allocate_visited_matrix(t_game_state *game)
// {
// 	int	**matrix;
// 	int	i;

// 	matrix = (int **)malloc(sizeof(int *) * (game->board->height + 1));
// 	if (!matrix)
// 		terminate_program("Memory allocation failed", game, 1);
// 	i = 0;
// 	while (i < game->board->height)
// 	{
// 		matrix[i] = (int *)malloc(sizeof(int) * (game->board->width + 1));
// 		if (!matrix[i])
// 		{
// 			release_memory((void **)matrix);
// 			terminate_program("Memory allocation failed", game, 1);
// 		}
// 		i++;
// 	}
// 	matrix[i] = NULL;
// 	return (matrix);
// }

// static void	initialize_matrix(int **matrix, t_game_state *game)
// {
// 	int	row;
// 	int	col;

// 	row = 0;
// 	while (row < game->board->height)
// 	{
// 		col = 0;
// 		while (col < game->board->width)
// 		{
// 			matrix[row][col] = 0;
// 			col++;
// 		}
// 		row++;
// 	}
// }

// void	create_visited_matrix(t_game_state *game, int start_x, int start_y)
// {
// 	int	**visited_grid;

// 	visited_grid = allocate_visited_matrix(game);
// 	initialize_matrix(visited_grid, game);
// 	flood_fill_algorithm(visited_grid, game, game->hero_pos.x, game->hero_pos.y);
// 	release_memory((void **)visited_grid);
// 	verify_accessibility(game);
// }

// void	verify_accessibility(t_game_state *game)
// {
// 	if (game->items_left != 0 && game->path_validated != 0)
// 		terminate_program("Error: Path validation failed!", game, 1);
// 	if (game->items_left != 0)
// 		terminate_program("Error: Some collectibles unreachable!", game, 1);
// 	if (game->path_validated != 0)
// 		terminate_program("Error: Exit is unreachable!", game, 1);
// }

// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   map_parser.c                                       :+:      :+:    :+:   */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../libft/libft.h"
// #include "game_engine.h"
// #include <fcntl.h>
// #include <stdlib.h>
// #include <unistd.h>

// int	calculate_file_lines(char *filename)
// {
// 	int		fd;
// 	int		bytes_read;
// 	char	character;
// 	int		line_count;

// 	line_count = 0;
// 	fd = open(filename, O_RDONLY);
// 	if (fd < 0)
// 		return (0);
// 	bytes_read = 1;
// 	while (bytes_read > 0)
// 	{
// 		bytes_read = read(fd, &character, 1);
// 		if (bytes_read <= 0)
// 			break ;
// 		if (character == '\n')
// 			line_count++;
// 	}
// 	close(fd);
// 	return (line_count);
// }

// static void	process_map_validation(char **grid_data, t_game_state *game)
// {
// 	if (check_newline_errors(grid_data))
// 	{
// 		release_memory((void **)grid_data);
// 		terminate_program("Error!", game, 0);
// 	}
// 	grid_data = remove_newlines(grid_data);
// 	if (validate_game_map_structure(grid_data) == 0)
// 	{
// 		release_memory((void **)grid_data);
// 		terminate_program("Error!\nInvalid map structure!", game, 0);
// 	}
// }

// char	**build_grid_from_file(char *filename, int lines, t_game_state *game)
// {
// 	char	**grid_data;
// 	char	*current_line;
// 	int		line_index;
// 	int		fd;

// 	fd = open(filename, O_RDONLY);
// 	if (fd < 0)
// 		return (NULL);
// 	grid_data = (char **)malloc(sizeof(char *) * (lines + 2));
// 	if (!grid_data)
// 		return (close(fd), NULL);
// 	line_index = 0;
// 	current_line = read_next_line(fd);
// 	while (current_line)
// 	{
// 		grid_data[line_index++] = current_line;
// 		current_line = read_next_line(fd);
// 	}
// 	grid_data[line_index] = NULL;
// 	close(fd);
// 	process_map_validation(grid_data, game);
// 	return (grid_data);
// }

// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   validation.c                                       :+:      :+:    :+:   */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../libft/libft.h"
// #include "game_engine.h"

// int	verify_file_extension(char *filename)
// {
// 	int	length;

// 	length = ft_strlen(filename);
// 	if (length < 4)
// 		return (0);
// 	if (filename[length - 1] != 'r')
// 		return (0);
// 	if (filename[length - 2] != 'e')
// 		return (0);
// 	if (filename[length - 3] != 'b')
// 		return (0);
// 	if (filename[length - 4] != '.')
// 		return (0);
// 	return (1);
// }

// int	check_element_count(char **grid, char element)
// {
// 	int	row;
// 	int	col;
// 	int	counter;

// 	row = 0;
// 	counter = 0;
// 	while (grid[row])
// 	{
// 		col = 0;
// 		while (grid[row][col])
// 		{
// 			if (grid[row][col] == element)
// 				counter++;
// 			col++;
// 		}
// 		row++;
// 	}
// 	return (counter);
// }

// int	check_newline_errors(char **grid)
// {
// 	int	row;
// 	int	col;

// 	row = 0;
// 	while (grid[row])
// 	{
// 		col = 0;
// 		while (grid[row][col] && grid[row][col] != '\n')
// 			col++;
// 		if (grid[row][col] && grid[row + 1] && grid[row + 1][0] == '\n')
// 			return (1);
// 		row++;
// 	}
// 	return (0);
// }

// char	**remove_newlines(char **grid)
// {
// 	int	row;
// 	int	col;

// 	row = 0;
// 	while (grid[row])
// 	{
// 		col = 0;
// 		while (grid[row][col] && grid[row][col] != '\n')
// 			col++;
// 		if (grid[row][col] == '\n')
// 			grid[row][col] = '\0';
// 		row++;
// 	}
// 	return (grid);
// }

// int	validate_game_map_structure(char **grid)
// {
// 	unsigned int	row_width;
// 	int				row_index;

// 	row_index = 0;
// 	row_width = ft_strlen(grid[0]);
// 	if (!verify_wall_row(grid[0]))
// 		return (0);
// 	while (grid[row_index])
// 	{
// 		if (ft_strlen(grid[row_index]) != row_width)
// 			return (0);
// 		if (grid[row_index][0] != '1' || grid[row_index][row_width - 1] != '1')
// 			return (0);
// 		if (!validate_characters(grid[row_index]))
// 			return (0);
// 		row_index++;
// 	}
// 	if (check_element_count(grid, 'P') != 1 || check_element_count(grid, 'E') != 1)
// 		return (0);
// 	if (!verify_wall_row(grid[row_index - 1]))
// 		return (0);
// 	return (1);
// }

// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   helper_functions.c                                 :+:      :+:    :+:   */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../libft/libft.h"
// #include "game_engine.h"

// void	locate_hero_position(t_game_state *game)
// {
// 	int	row;
// 	int	col;

// 	row = 0;
// 	while (game->board->cells[row])
// 	{
// 		col = 0;
// 		while (game->board->cells[row][col])
// 		{
// 			if (game->board->cells[row][col] == 'P')
// 			{
// 				game->hero_pos.x = col;
// 				game->hero_pos.y = row;
// 				return ;
// 			}
// 			col++;
// 		}
// 		row++;
// 	}
// 	terminate_program("Player not found\n", game, 1);
// }

// int	verify_wall_row(char *row)
// {
// 	int	index;

// 	index = 0;
// 	while (row[index] && row[index] != '\n')
// 	{
// 		if (row[index] != '1')
// 			return (0);
// 		index++;
// 	}
// 	return (1);
// }

// int	validate_characters(char *line)
// {
// 	int	index;

// 	index = 0;
// 	while (line[index])
// 	{
// 		if (line[index] != '1' && line[index] != '0' && line[index] != 'P' 
// 			&& line[index] != 'E' && line[index] != 'C')
// 			return (0);
// 		index++;
// 	}
// 	return (1);
// }

// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   graphics_engine.c                                  :+:      :+:    :+:   */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../minilibx/mlx.h"
// #include "game_engine.h"

// void	setup_graphics(t_game_state *game)
// {
// 	int	texture_width;
// 	int	texture_height;

// 	game->mlx_ptr = mlx_init();
// 	if (!game->mlx_ptr)
// 		cleanup_resources(game);
// 	game->win_ptr = mlx_new_window(game->mlx_ptr, 
// 		game->board->width * TILE_SIZE, game->board->height * TILE_SIZE, "Game Engine");
// 	game->hero_img = mlx_xpm_file_to_image(game->mlx_ptr, 
// 		"textures/player.xpm", &texture_height, &texture_width);
// 	game->item_img = mlx_xpm_file_to_image(game->mlx_ptr, 
// 		"textures/coin.xpm", &texture_height, &texture_width);
// 	game->door_img = mlx_xpm_file_to_image(game->mlx_ptr, 
// 		"textures/exit.xpm", &texture_height, &texture_width);
// 	game->barrier_img = mlx_xpm_file_to_image(game->mlx_ptr, 
// 		"textures/wall.xpm", &texture_height, &texture_width);
// 	game->floor_img = mlx_xpm_file_to_image(game->mlx_ptr, 
// 		"textures/bground.xpm", &texture_height, &texture_width);
// 	if (!game->win_ptr || !game->hero_img || !game->item_img 
// 		|| !game->door_img || !game->barrier_img || !game->floor_img)
// 		cleanup_resources(game);
// }

// static void	render_tile(t_game_state *game, int x, int y)
// {
// 	if (game->board->cells[y][x] == '1')
// 		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, 
// 			game->barrier_img, x * TILE_SIZE, y * TILE_SIZE);
// 	else
// 		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, 
// 			game->floor_img, x * TILE_SIZE, y * TILE_SIZE);
// 	if (game->board->cells[y][x] == 'E')
// 		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, 
// 			game->door_img, x * TILE_SIZE, y * TILE_SIZE);
// 	else if (game->board->cells[y][x] == 'C')
// 		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, 
// 			game->item_img, x * TILE_SIZE, y * TILE_SIZE);
// }

// void	draw_game_scene(t_game_state *game)
// {
// 	int	x;
// 	int	y;

// 	y = -1;
// 	while (++y < game->board->height)
// 	{
// 		x = -1;
// 		while (++x < game->board->width)
// 			render_tile(game, x, y);
// 	}
// }

// int	render_frame(t_game_state *game)
// {
// 	draw_game_scene(game);
// 	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->hero_img, 
// 		game->hero_pos.x * TILE_SIZE, game->hero_pos.y * TILE_SIZE);
// 	return (0);
// }

// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   input_handler.c                                    :+:      :+:    :+:   */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../ft_printf/ft_printf.h"
// #include "game_engine.h"

// static void	execute_move(t_game_state *game, int direction)
// {
// 	int	new_x;
// 	int	new_y;

// 	new_x = game->hero_pos.x;
// 	new_y = game->hero_pos.y;
// 	if (direction == 1)
// 		new_y--;
// 	else if (direction == 2)
// 		new_x--;
// 	else if (direction == 3)
// 		new_y++;
// 	else if (direction == 4)
// 		new_x++;
// 	if (game->board->cells[new_y][new_x] != '1')
// 		process_movement(game, new_x, new_y);
// }

// int	handle_key_input(int keycode, t_game_state *game)
// {
// 	if (keycode == 65307)
// 		cleanup_resources(game);
// 	else if (keycode == 119)
// 		execute_move(game, 1);
// 	else if (keycode == 97)
// 		execute_move(game, 2);
// 	else if (keycode == 115)
// 		execute_move(game, 3);
// 	else if (keycode == 100)
// 		execute_move(game, 4);
// 	else
// 		return (0);
// 	return (0);
// }

// void	process_movement(t_game_state *game, int new_x, int new_y)
// {
// 	game->hero_pos.x = new_x;
// 	game->hero_pos.y = new_y;
// 	game->moves_count++;
// 	ft_printf("Move: %d\n", game->moves_count);
// 	if (game->board->cells[new_y][new_x] == 'C')
// 		collect_item(game);
// 	if (game->board->cells[new_y][new_x] == 'E' && game->total_items == 0)
// 		cleanup_resources(game);
// }

// void	collect_item(t_game_state *game)
// {
// 	game->total_items--;
// 	game->board->cells[game->hero_pos.y][game->hero_pos.x] = '0';
// }

// int	handle_window_close(t_game_state *game)
// {
// 	cleanup_resources(game);
// 	return (0);
// }

// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   cleanup.c                                          :+:      :+:    :+:   */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../ft_printf/ft_printf.h"
// #include "../minilibx/mlx.h"
// #include "game_engine.h"
// #include <stdlib.h>

// void	cleanup_resources(t_game_state *game)
// {
// 	if (game->win_ptr)
// 		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
// 	if (game->hero_img)
// 		mlx_destroy_image(game->mlx_ptr, game->hero_img);
// 	if (game->item_img)
// 		mlx_destroy_image(game->mlx_ptr, game->item_img);
// 	if (game->door_img)
// 		mlx_destroy_image(game->mlx_ptr, game->door_img);
// 	if (game->barrier_img)
// 		mlx_destroy_image(game->mlx_ptr, game->barrier_img);
// 	if (game->floor_img)
// 		mlx_destroy_image(game->mlx_ptr, game->floor_img);
// 	if (game->mlx_ptr)
// 	{
// 		mlx_destroy_display(game->mlx_ptr);
// 		free(game->mlx_ptr);
// 	}
// 	terminate_program("Exit", game, 1);
// }

// void	display_error(char *message)
// {
// 	ft_printf("%s\n", message);
// 	exit(1);
// }

// void	terminate_program(char *message, t_game_state *game, int flag)
// {
// 	if (flag == 1)
// 		release_memory((void **)game->board->cells);
// 	free(game->board);
// 	free(game);
// 	ft_printf("%s\n", message);
// 	exit(1);
// }

// void	release_memory(void **memory_block)
// {
// 	int	index;

// 	index = -1;
// 	while (memory_block[++index])
// 		free(memory_block[index]);
// 	free(memory_block);
// }