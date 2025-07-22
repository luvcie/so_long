#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <stdlib.h>

# define TILE_SIZE 64

typedef struct s_img
{
	void	*ptr;
	int		width;
	int		height;
}			t_img;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		map_width;
	int		map_height;

	t_img	floor;
	t_img	wall;
	t_img	player;
}			t_game;

load_sprites(t_game *game);
parse_map(char *map_file, t_game *game);
render_map(t_game *game);

#endif
