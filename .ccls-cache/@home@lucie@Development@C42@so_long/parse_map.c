/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:56:08 by lucpardo          #+#    #+#             */
/*   Updated: 2025/09/30 20:31:13 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

// the map is read twice, once to count and once to store, 4 gud mem allocation
// counts total lines in map file, opens it and counts newlines
// these newline characters are used to know map height before allocating
static int	count_lines(char *filename)
{
	int		fd;
	int		lines;
	char	buffer[1];

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	lines = 0;
	while (read(fd, buffer, 1) > 0)
	{
		if (buffer[0] == '\n')
			lines++;
	}
	close(fd);
	return (lines);
}

// allocates memory for the map awway based on map_height
// inits all pointers to NULL for safety
static void	init_map_memory(t_game *game)
{
	int	i;

	game->map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!game->map)
		exit(1);
	i = 0;
	while (i <= game->map_height)
	{
		game->map[i] = NULL;
		i++;
	}
}

// processes a line from map file, trims newline character with strtrim
// stores trimmed string in map[i] and sets map_width from first line
static void	process_line(t_game *game, char *line, int i, int fd)
{
	game->map[i] = ft_strtrim(line, "\n");
	if (!game->map[i])
	{
		free(line);
		close(fd);
		exit(1);
	}
	if (i == 0)
		game->map_width = ft_strlen(game->map[i]);
}

// reads entire map file, line by line using GNL
// processes each line and stores it in map array
static void	read_map_lines(char *filename, t_game *game)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit(1);
	i = 0;
	line = get_next_line(fd);
	while (line && i < game->map_height)
	{
		process_line(game, line, i, fd);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
}

// main parsing, counts lines to get height and allocates memory
// reads all map lines into array then finds player start position
void	parse_map(char *filename, t_game *game)
{
	game->map_height = count_lines(filename);
	if (game->map_height == 0)
		exit(1);
	init_map_memory(game);
	read_map_lines(filename, game);
	find_player(game);
}
