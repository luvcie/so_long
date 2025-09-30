/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:28:50 by lucpardo          #+#    #+#             */
/*   Updated: 2025/09/30 23:18:22 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1000
#endif

// reads BUFFER_SIZE bytes from fd into buffer, resets pos to 0
// returns nbr of bytes read or -1 for error or eof
static int	refill_buffer(int fd, char *buffer, int *pos)
{
	int	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	*pos = 0;
	return (bytes_read);
}

// returns next character from buffer, ?
// keeps pointer position
static int	read_char(int fd, char *buffer, int *pos, int *bytes_read)
{
	if (*pos >= *bytes_read)
	{
		*bytes_read = refill_buffer(fd, buffer, pos);
		if (*bytes_read <= 0)
			return (-1);
	}
	return (buffer[(*pos)++]);
}

// builds a line character by character until nl or eof
// static vars to maintain state between calls for same fd
// stops at nl, eof, or buffer limit, returns len of line
static int	build_line(int fd, char *line)
{
	static char	buffer[BUFFER_SIZE];
	static int	pos;
	static int	bytes_read;
	int			i;
	int			c;

	i = 0;
	while (1)
	{
		c = read_char(fd, buffer, &pos, &bytes_read);
		if (c == -1)
			break ;
		line[i] = c;
		if (line[i++] == '\n')
			break ;
		if (i >= BUFFER_SIZE - 1)
			break ;
	}
	line[i] = '\0';
	return (i);
}

// reads one line from fd including nl char if present
// returns NULL on error, eof, or invalid fd
// uses strdup to return dynamically allocated string
char	*get_next_line(int fd)
{
	char	line[BUFFER_SIZE];
	int		len;

	if (fd < 0)
		return (NULL);
	len = build_line(fd, line);
	if (len == 0)
		return (NULL);
	return (ft_strdup(line));
}
