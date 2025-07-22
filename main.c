/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:21:04 by lucpardo          #+#    #+#             */
/*   Updated: 2025/07/22 20:23:28 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		close_window(game);
	return (0);
}

void	fill_window(t_game *game, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < 600)
	{
		x = 0;
		while (x < 800)
		{
			mlx_pixel_put(game->mlx, game->win, x, y, color);
			x++;
		}
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("error\ndo this instead: ./so_long map.ber\n");
		return (1);
	}
	(void)argv;
	game.mlx = mlx_init();
	if (!game.mlx)
	{
		ft_printf("error\nmlx didn't init D:\n");
		return (1);
	}
	game.win = mlx_new_window(game.mlx, 800, 600, "So Long");
	if (!game.win)
	{
		ft_printf("error\nwindow wasn't created D:\n");
		return (1);
	}
	fill_window(&game, 0xFFD1DC);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_key_hook(game.win, key_press, &game);
	mlx_loop(game.mlx);
	return (0);
}
