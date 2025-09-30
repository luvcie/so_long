/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:37:08 by lucpardo          #+#    #+#             */
/*   Updated: 2025/09/30 20:41:25 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <so_long.h>

// loads all 8 wall sprite variants into the wall array :)
// that way the game can look cute !!! 
static void	load_wall_sprites(t_game *game)
{
	int	width;
	int	height;

	game->wall[0].ptr = mlx_xpm_file_to_image(game->mlx,
			"sprites/wall1.xpm", &width, &height);
	game->wall[1].ptr = mlx_xpm_file_to_image(game->mlx,
			"sprites/wall2.xpm", &width, &height);
	game->wall[2].ptr = mlx_xpm_file_to_image(game->mlx,
			"sprites/wall3.xpm", &width, &height);
	game->wall[3].ptr = mlx_xpm_file_to_image(game->mlx,
			"sprites/wall4.xpm", &width, &height);
	game->wall[4].ptr = mlx_xpm_file_to_image(game->mlx,
			"sprites/wall5.xpm", &width, &height);
	game->wall[5].ptr = mlx_xpm_file_to_image(game->mlx,
			"sprites/wall6.xpm", &width, &height);
	game->wall[6].ptr = mlx_xpm_file_to_image(game->mlx,
			"sprites/wall7.xpm", &width, &height);
	game->wall[7].ptr = mlx_xpm_file_to_image(game->mlx,
			"sprites/wall8.xpm", &width, &height);
}

static void	load_game_sprites(t_game *game)
{
	int	width;
	int	height;

	game->floor.ptr = mlx_xpm_file_to_image(game->mlx,
			"sprites/floor.xpm", &width, &height);
	game->player_img.ptr = mlx_xpm_file_to_image(game->mlx,
			"sprites/player.xpm", &width, &height);
	game->collectible.ptr = mlx_xpm_file_to_image(game->mlx,
			"sprites/orb.xpm", &width, &height);
	game->exit.ptr = mlx_xpm_file_to_image(game->mlx,
			"sprites/exit.xpm", &width, &height);
}

// verifies that all sprites loaded succesfully by checking 
// if pointers are not NULLL
static int	check_sprites_loaded(t_game *game)
{
	int	i;

	if (!game->floor.ptr || !game->player_img.ptr
		|| !game->collectible.ptr || !game->exit.ptr)
		return (0);
	i = 0;
	while (i < 8)
	{
		if (!game->wall[i].ptr)
			return (0);
		i++;
	}
	return (1);
}

static void	print_error_exit(void)
{
	ft_printf("Error\nFailed to load sprites\n");
	exit(1);
}

void	load_sprites(t_game *game)
{
	load_game_sprites(game);
	load_wall_sprites(game);
	if (!check_sprites_loaded(game))
		print_error_exit();
}
