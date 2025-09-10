/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:59:33 by lucpardo          #+#    #+#             */
/*   Updated: 2025/09/01 16:59:49 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

static void	free_map(t_game *game)
{
	int	i;

	if (game->map)
	{
		i = 0;
		while (i < game->map_height)
		{
			if (game->map[i])
				free(game->map[i]);
			i++;
		}
		free(game->map);
	}
}

static void	destroy_images(t_game *game)
{
	int	i;

	if (game->mlx)
	{
		if (game->floor.ptr)
			mlx_destroy_image(game->mlx, game->floor.ptr);
		if (game->player_img.ptr)
			mlx_destroy_image(game->mlx, game->player_img.ptr);
		if (game->collectible.ptr)
			mlx_destroy_image(game->mlx, game->collectible.ptr);
		if (game->exit.ptr)
			mlx_destroy_image(game->mlx, game->exit.ptr);
		i = 0;
		while (i < 8)
		{
			if (game->wall[i].ptr)
				mlx_destroy_image(game->mlx, game->wall[i].ptr);
			i++;
		}
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
	}
}

int	close_window(t_game *game)
{
	free_map(game);
	destroy_images(game);
	exit(0);
}
