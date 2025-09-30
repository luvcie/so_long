/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 21:32:11 by lucpardo          #+#    #+#             */
/*   Updated: 2025/09/30 21:37:10 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

// checks if filename ends with .ber extension by comparing last 4 characters
static int	check_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strncmp(filename + len - 4, ".ber", 4) != 0)
		return (0);
	return (1);
}

// verifies all rows have identical width to ensure rectangular map shape
static int	check_rectangular(t_game *game)
{
	int	y;
	int	len;

	y = 0;
	while (y < game->map_height)
	{
		len = ft_strlen(game->map[y]);
		if (len != game->map_width)
			return (0);
		y++;
	}
	return (1);
}

// checks if top, bottom, left, and right borders are all walls (1)
static int	check_walls(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->map_width)
	{
		if (game->map[0][x] != '1'
			|| game->map[game->map_height - 1][x] != '1')
			return (0);
		x++;
	}
	y = 0;
	while (y < game->map_height)
	{
		if (game->map[y][0] != '1'
			|| game->map[y][game->map_width - 1] != '1')
			return (0);
		y++;
	}
	return (1);
}

// counts players, exits, collectibles and validates only valid characters exist
static int	check_elements(t_game *game, int *counts)
{
	int	y;
	int	x;

	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (++x < game->map_width)
		{
			if (game->map[y][x] == 'P')
				counts[0]++;
			else if (game->map[y][x] == 'E')
				counts[1]++;
			else if (game->map[y][x] == 'C')
				counts[2]++;
			else if (game->map[y][x] != '0' && game->map[y][x] != '1')
				return (0);
		}
	}
	return (1);
}

// check if map has exactly 1 player, 1 exit, and at least 1 collectible
int	validate_map(char *filename, t_game *game)
{
	int	counts[3];

	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	if (!check_extension(filename) || !check_rectangular(game)
		|| !check_walls(game) || !check_elements(game, counts))
		return (0);
	if (counts[0] != 1 || counts[1] != 1 || counts[2] < 1)
		return (0);
	return (1);
}
