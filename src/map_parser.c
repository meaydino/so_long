#include "../libft/libft.h"
#include "../include/so_long.h"


#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	calculate_file_lines(char *filename)
{
	int		fd;
	int		bytes_read;
	char	character;
	int		line_count;

	line_count = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, &character, 1);
		if (bytes_read <= 0)
			break ;
		if (character == '\n')
			line_count++;
	}
	close(fd);
	return (line_count);
}

static void	process_map_validation(char **grid_data, t_game_state *game)
{
	if (check_newline_errors(grid_data))
	{
		release_memory((void **)grid_data);
		terminate_program("Error!", game, 0);
	}
	grid_data = remove_newlines(grid_data);
	if (validate_game_map_structure(grid_data) == 0)
	{
		release_memory((void **)grid_data);
		terminate_program("Error!\nInvalid map structure!", game, 0);
	}
}

char	**build_grid_from_file(char *filename, int lines, t_game_state *game)
{
	char	**grid_data;
	char	*current_line;
	int		line_index;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	grid_data = (char **)malloc(sizeof(char *) * (lines + 2));
	if (!grid_data)
		return (close(fd), NULL);
	line_index = 0;
	current_line = get_next_line(fd);
	while (current_line)
	{
		grid_data[line_index++] = current_line;
		current_line = get_next_line(fd);
	}
	grid_data[line_index] = NULL;
	close(fd);
	process_map_validation(grid_data, game);
	return (grid_data);
}
