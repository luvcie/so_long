/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:34:29 by lucpardo          #+#    #+#             */
/*   Updated: 2025/10/02 15:49:57 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

// creates a copy of the map to mark visited tiles during flood fill
static char	**copy_map(t_game *game)
{
	char	**map_copy;
	int		i;

	map_copy = malloc(sizeof(char *) * (game->map_height + 1));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < game->map_height)
	{
		map_copy[i] = ft_strdup(game->map[i]);
		if (!map_copy[i])
		{
			while (--i >= 0)
				free(map_copy[i]);
			free(map_copy);
			return (NULL);
		}
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

// frees the temporary map copy used during validation
static void	free_map_copy(char **map_copy, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}

// recursively marks all reachable tiles from position (x,y) by replacing
// walkable characters with 'V' (visited). stops at walls and map boundaries
static void	flood_fill(char **map, int x, int y, t_game *game)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'V')
		return ;
	map[y][x] = 'V';
	flood_fill(map, x + 1, y, game);
	flood_fill(map, x - 1, y, game);
	flood_fill(map, x, y + 1, game);
	flood_fill(map, x, y - 1, game);
}

// checks if all collectibles and exit were reached during flood fill
// by verifying no 'C' or 'E' characters remain in the flooded map
static int	check_all_reachable(char **map, t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (map[y][x] == 'C' || map[y][x] == 'E')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

// checks that the player can reach all collectibles and exit using flood fill.
// creates temporary map copy, floods from player position, checks if all
// C's and E are visited. if path is invalid it prints error
void	validate_path(t_game *game)
{
	char	**map_copy;

	map_copy = copy_map(game);
	if (!map_copy)
		print_map_error("Memory allocation failed");
	flood_fill(map_copy, game->player.x, game->player.y, game);
	if (!check_all_reachable(map_copy, game))
	{
		free_map_copy(map_copy, game->map_height);
		free_game_map(game);
		print_map_error("Invalid path: not all vinyls can be collected :(");
	}
	free_map_copy(map_copy, game->map_height);
}
