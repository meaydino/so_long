#include "../libft/libft.h"
#include "../include/so_long.h"



void	locate_hero_position(t_game_state *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->board->cells[y])
	{
		x = 0;
		while (game->board->cells[y][x])
		{
			if (game->board->cells[y][x] == 'P')
			{
				game->hero_pos.x = x;
				game->hero_pos.y = y;
				return ;
			}
			x++;
		}
		y++;
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
