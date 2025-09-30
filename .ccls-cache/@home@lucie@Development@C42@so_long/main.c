/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:56:08 by lucpardo          #+#    #+#             */
/*   Updated: 2025/09/30 20:16:54 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

// welcome to my so_long :) 
// inits game state, resets counter to 0 and loads sprites
static void	init_game(t_game *game)
{
	game->player.moves = 0;
	load_sprites(game);
}

// connects MLX to X11 display server
static int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_printf("Error\nFailed to initialize MLX\n");
		return (0);
	}
	return (1);
}

// creates game window with these dimensions
// map_width * 64 pixels by map_height * 64 pixels
static int	create_window(t_game *game)
{
	game->win = mlx_new_window(game->mlx, game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE, "So Long");
	if (!game->win)
	{
		ft_printf("Error\nFailed to create window\n");
		return (0);
	}
	return (1);
}

// registers keyboard events for movement and exiting
static void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_key_hook(game->win, key_press, game);
}

// validates args, inits MLX, parses map 
// creates window, loads sprites, renders map, starts game loop
int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Error\nUsage: ./so_long map.ber\n");
		return (1);
	}
	if (!init_mlx(&game))
		return (1);
	parse_map(argv[1], &game);
	if (!create_window(&game))
		return (1);
	init_game(&game);
	render_map(&game);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}
