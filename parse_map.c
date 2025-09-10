/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:56:08 by lucpardo          #+#    #+#             */
/*   Updated: 2025/09/01 17:09:08 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

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

void	parse_map(char *filename, t_game *game)
{
	game->map_height = count_lines(filename);
	if (game->map_height == 0)
		exit(1);
	init_map_memory(game);
	read_map_lines(filename, game);
	find_player(game);
}
