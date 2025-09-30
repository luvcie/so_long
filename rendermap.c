/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendermap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:21:12 by lucpardo          #+#    #+#             */
/*   Updated: 2025/09/30 20:50:17 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

// calculates which wall sprite to use depending on tile coords
// using this formula to get the sprites in random places
static int	get_wall_variant(int x, int y)
{
	return ((x * 7 + y * 13) % 8);
}

// renders a single tile at position (x,y), draws floor first
// then draws appropiate sprite on top depending on character
// uses get_wall_variant to choose wall sprites
// coords are mult by TILE_SIZE(64) to convert from grid to pixels
static void	render_tile(t_game *game, int x, int y)
{
	int	wall_idx;

	mlx_put_image_to_window(game->mlx, game->win, game->floor.ptr,
		x * TILE_SIZE, y * TILE_SIZE);
	if (game->map[y][x] == '1')
	{
		wall_idx = get_wall_variant(x, y);
		mlx_put_image_to_window(game->mlx, game->win,
			game->wall[wall_idx].ptr, x * TILE_SIZE, y * TILE_SIZE);
	}
	else if (game->map[y][x] == 'P')
		mlx_put_image_to_window(game->mlx, game->win, game->player_img.ptr,
			x * TILE_SIZE, y * TILE_SIZE);
	else if (game->map[y][x] == 'C')
		mlx_put_image_to_window(game->mlx, game->win, game->collectible.ptr,
			x * TILE_SIZE, y * TILE_SIZE);
	else if (game->map[y][x] == 'E')
		mlx_put_image_to_window(game->mlx, game->win, game->exit.ptr,
			x * TILE_SIZE, y * TILE_SIZE);
}

// iterates through entire map array and renders each tile
void	render_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			render_tile(game, x, y);
			x++;
		}
		y++;
	}
}

// only redraws the two tiles affected by player movement
// old position and new position instead of redraw entire map like b4
void	update_player_position(t_game *game, int old_x, int old_y)
{
	render_tile(game, old_x, old_y);
	render_tile(game, game->player.x, game->player.y);
}
