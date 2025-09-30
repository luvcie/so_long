/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:32:17 by lucpardo          #+#    #+#             */
/*   Updated: 2025/09/30 19:08:22 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# define TILE_SIZE 64

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_H 104
# define KEY_J 106
# define KEY_K 107
# define KEY_L 108
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

typedef struct s_img
{
	void	*ptr;
	int		width;
	int		height;
}			t_img;

typedef struct s_player
{
	int		x;
	int		y;
	int		moves;
}			t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	int			map_width;
	int			map_height;
	t_player	player;
	t_img		floor;
	t_img		wall[8];
	t_img		player_img;
	t_img		collectible;
	t_img		exit;
}				t_game;

void	display_moves_on_screen(t_game *game);
void	load_sprites(t_game *game);
void	parse_map(char *map_file, t_game *game);
void	update_player_position(t_game *game, int old_x, int old_y);
void	render_map(t_game *game);
void	find_player(t_game *game);
void	move_player_bonus(t_game *game, int new_x, int new_y);
int		close_window(t_game *game);
int		key_press(int keycode, t_game *game);
char	*get_next_line(int fd);

#endif
