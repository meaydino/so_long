#include "../libft/libft.h"
#include "../include/so_long.h"



int	verify_file_extension(char *filename)
{
	int	length;
	int fd;

	length = ft_strlen(filename);
	if (filename[length - 1] != 'r' && filename[length - 2] != 'e'
		&& filename[length - 3] != 'b' && filename[length - 4] != '.'
		&& length > 4)
			return(0);
	else
	{
		fd = open(filename, O_RDONLY);
		if(fd == -1)
		{
			close(fd);
			return(0);
		}
	}
	return (1);
}

int	check_element_count(char **grid, char element)
{
	int	row;
	int	col;
	int	counter;

	row = 0;
	counter = 0;
	while (grid[row])
	{
		col = 0;
		while (grid[row][col])
		{
			if (grid[row][col] == element)
				counter++;
			col++;
		}
		row++;
	}
	return (counter);
}

int	check_newline_errors(char **grid)
{
	int	row;
	int	col;

	row = 0;
	while (grid[row])
	{
		col = 0;
		while (grid[row][col] && grid[row][col] != '\n')
			col++;
		if (grid[row][col] && grid[row + 1] && grid[row + 1][0] == '\n')
			return (1);
		row++;
	}
	return (0);
}

char	**remove_newlines(char **grid)
{
	int	row;
	int	col;

	row = 0;
	while (grid[row])
	{
		col = 0;
		while (grid[row][col] && grid[row][col] != '\n')
			col++;
		if (grid[row][col] == '\n')
			grid[row][col] = '\0';
		row++;
	}
	return (grid);
}

int	validate_game_map_structure(char **grid)
{
	unsigned int	row_width;
	int				row_index;

	row_index = 0;
	row_width = ft_strlen(grid[0]);
	if (!verify_wall_row(grid[0]))
		return (0);
	while (grid[row_index])
	{
		if (ft_strlen(grid[row_index]) != row_width)
			return (0);
		if (grid[row_index][0] != '1' || grid[row_index][row_width - 1] != '1')
			return (0);
		if (!validate_characters(grid[row_index]))
			return (0);
		row_index++;
	}
	if (check_element_count(grid, 'P') != 1 || check_element_count(grid, 'E') != 1)
		return (0);
	if (!verify_wall_row(grid[row_index - 1]))
		return (0);
	return (1);
}
