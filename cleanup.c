/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:59:33 by lucpardo          #+#    #+#             */
/*   Updated: 2025/10/02 15:33:11 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

// frees all dynamically allocated memory for the map array:
// iterates through each row, frees the string, then frees array of pointers.
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

// DESTROYS all mlx images stored in X11 server memory and the window
// iterates through all 8 wall sprites to destroy each one. 
// mlx images are allocates on x11 server, not in the heap of the pgrogram.
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
			mlx_destroy_display(game->mlx);
			free(game->mlx);
	}
}

// main cleanup fn: it frees all allocated resources (map mem and mlx imgs)
// then exits cleanly. this is called when ESC is pressed and window X is click
// and also when player wins the game.
int	close_window(t_game *game)
{
	free_map(game);
	destroy_images(game);
	exit(0);
}
