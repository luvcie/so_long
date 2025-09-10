/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendermap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:21:12 by lucpardo          #+#    #+#             */
/*   Updated: 2025/09/01 16:40:29 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

static int	get_wall_variant(int x, int y)
{
	return ((x * 7 + y * 13) % 8);
}

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

void	update_player_position(t_game *game, int old_x, int old_y)
{
	render_tile(game, old_x, old_y);
	render_tile(game, game->player.x, game->player.y);
}
