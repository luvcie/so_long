/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 21:32:11 by lucpardo          #+#    #+#             */
/*   Updated: 2025/09/30 21:40:16 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

// prints error message and exits with status 1 when map validation fails
void	print_map_error(char *message)
{
	ft_printf("Error\n%s\n", message);
	exit(1);
}

// validates extension, prints specific error if invalid
void	validate_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		print_map_error("Invalid file name");
	if (ft_strncmp(filename + len - 4, ".ber", 4) != 0)
		print_map_error("File must have .ber extension");
}

// validates rectangular shape, prints error if rows have different lengths
void	validate_rectangular(t_game *game)
{
	int	y;
	int	len;

	y = 0;
	while (y < game->map_height)
	{
		len = ft_strlen(game->map[y]);
		if (len != game->map_width)
			print_map_error("Map must be rectangular");
		y++;
	}
}

// validates walls surround entire map perimeter
void	validate_walls(t_game *game)
{
	int	x;
	int	y;

	x = -1;
	while (++x < game->map_width)
		if (game->map[0][x] != '1'
			|| game->map[game->map_height - 1][x] != '1')
			print_map_error("Map must be surrounded by walls");
	y = -1;
	while (++y < game->map_height)
		if (game->map[y][0] != '1'
			|| game->map[y][game->map_width - 1] != '1')
			print_map_error("Map must be surrounded by walls");
}

// helper function to count element types in map
void	count_elements(t_game *game, int *counts)
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
				print_map_error("Invalid character in map");
		}
	}
}
