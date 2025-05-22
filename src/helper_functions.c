#include "../libft/libft.h"
#include "so_long.h"


void	locate_hero_position(t_game_state *game)
{
	int	row;
	int	col;

	row = 0;
	while (game->board->cells[row])
	{
		col = 0;
		while (game->board->cells[row][col])
		{
			if (game->board->cells[row][col] == 'P')
			{
				game->hero_pos.x = col;
				game->hero_pos.y = row;
				return ;
			}
			col++;
		}
		row++;
	}
	terminate_program("Player not found\n", game, 1);
}

int	verify_wall_row(char *row)
{
	int	index;

	index = 0;
	while (row[index] && row[index] != '\n')
	{
		if (row[index] != '1')
			return (0);
		index++;
	}
	return (1);
}

int	validate_characters(char *line)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (line[index] != '1' && line[index] != '0' && line[index] != 'P' 
			&& line[index] != 'E' && line[index] != 'C')
			return (0);
		index++;
	}
	return (1);
}