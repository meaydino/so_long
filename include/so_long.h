/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meaydino <meaydino@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:00:00 by meaydino          #+#    #+#             */
/*   Updated: 2025/05/26 15:46:23 by meaydino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define PIXEL 96
# define BUFFER_SIZE 1

/* Key codes for movement */
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

/* Game elements */
# define EMPTY '0'
# define WALL '1'
# define COLLECTIBLE 'C'
# define PLAYER 'P'
# define EXIT 'E'

typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

typedef struct s_grid
{
	char	**cells;
	int		width;
	int		height;
}	t_grid;

typedef struct s_game_state
{
	t_position	hero_pos;
	int			items_left;
	int			moves_count;
	int			total_items;
	int			path_validated;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*hero_img;
	void		*item_img;
	void		*door_img;
	void		*barrier_img;
	void		*floor_img;
	t_grid		*board;
}	t_game_state;

/* ************************************************************************** */
/*                               MAIN FUNCTIONS                               */
/* ************************************************************************** */

/* main.c */
t_game_state	*initialize_game(char *filename);
int				main(int argc, char **argv);

/* ************************************************************************** */
/*                            PATHFINDING SYSTEM                             */
/* ************************************************************************** */

/* pathfinding.c */
void			flood_fill_algorithm(int **visited, t_game_state *game,
					int x, int y);
void			create_visited_matrix(t_game_state *game);
void			verify_accessibility(t_game_state *game);

/* ************************************************************************** */
/*                              MAP PROCESSING                                */
/* ************************************************************************** */

/* map_parser.c */
int				calculate_file_lines(char *filename);
char			**build_grid_from_file(char *filename, int lines,
					t_game_state *game);

/* ************************************************************************** */
/*                             VALIDATION SYSTEM                             */
/* ************************************************************************** */

/* validation.c */
int				verify_file_extension(char *filename);
int				check_element_count(char **grid, char element);
int				check_newline_errors(char **grid);
char			**remove_newlines(char **grid);
int				validate_game_map_structure(char **grid);

/* ************************************************************************** */
/*                             HELPER FUNCTIONS                              */
/* ************************************************************************** */

/* helper_functions.c */
void			locate_hero_position(t_game_state *game);
int				verify_wall_row(char *row);
int				validate_characters(char *line);

/* ************************************************************************** */
/*                             GRAPHICS SYSTEM                               */
/* ************************************************************************** */

/* graphics_engine.c */
void			setup_graphics(t_game_state *game);
void			draw_game_scene(t_game_state *game);
int				render_frame(t_game_state *game);

/* ************************************************************************** */
/*                              INPUT HANDLING                               */
/* ************************************************************************** */

/* input_handler.c */
int				handle_key_input(int keycode, t_game_state *game);
void			process_movement(t_game_state *game, int new_x, int new_y);
void			collect_item(t_game_state *game);
int				handle_window_close(t_game_state *game);

/* ************************************************************************** */
/*                            MEMORY MANAGEMENT                              */
/* ************************************************************************** */

/* cleanup.c */
void			cleanup_resources(t_game_state *game);
void			display_error(char *message);
void			terminate_program(char *message, t_game_state *game, int flag);
void			release_memory(void **memory_block);

/* ************************************************************************** */
/*                              FILE READING                                 */
/* ************************************************************************** */

/* get_next_line */
char	*get_next_line(int fd);


/* ************************************************************************** */
/*                             UTILITY MACROS                               */
/* ************************************************************************** */


# define TEXTURE_PLAYER "textures/player.xpm"
# define TEXTURE_COIN "textures/coin.xpm"
# define TEXTURE_EXIT "textures/exit.xpm"
# define TEXTURE_WALL "textures/wall.xpm"
# define TEXTURE_FLOOR "textures/bground.xpm"

/* ************************************************************************** */
/*                              ERROR MESSAGES                               */
/* ************************************************************************** */

# define ERR_ARGC "Error\nInvalid argument count"
# define ERR_FILE_EXT "Error\nInvalid file extension"
# define ERR_MALLOC "Error\nMemory allocation failed"
# define ERR_NO_COLLECTIBLES "Error\nNo collectibles found"
# define ERR_MAP_CREATE "Error\nFailed to create game board"
# define ERR_PLAYER_NOT_FOUND "Player not found"
# define ERR_PATH_VALIDATION "Error: Path validation failed!"
# define ERR_UNREACHABLE_ITEMS "Error: Some collectibles unreachable!"
# define ERR_UNREACHABLE_EXIT "Error: Exit is unreachable!"
# define ERR_INVALID_MAP "Error!\nInvalid map structure!"
# define ERR_TEXTURES "Error\nTextures not loaded!"

# define MSG_EXIT "Exit"
# define MSG_WINNER "Winner!"

#endif
