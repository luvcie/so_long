/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:12:25 by lucpardo          #+#    #+#             */
/*   Updated: 2025/09/30 18:55:03 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

static int	is_valid_move(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= game->map_width)
		return (0);
	if (new_y < 0 || new_y >= game->map_height)
		return (0);
	if (game->map[new_y][new_x] == '1')
		return (0);
	return (1);
}

static int	count_collectibles(t_game *game)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'C')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	handle_exit(t_game *game, int new_x, int new_y)
{
	if (count_collectibles(game) == 0)
	{
		game->map[game->player.y][game->player.x] = '0';
		game->player.x = new_x;
		game->player.y = new_y;
		game->player.moves++;
		ft_printf("You found the exit! Total moves: %d\n",
			game->player.moves);
		close_window(game);
	}
	else
	{
		ft_printf("You need to collect all orbs first! (%d remaining)\n",
			count_collectibles(game));
	}
}

static void	move_player(t_game *game, int new_x, int new_y)
{
	int	old_x;
	int	old_y;

	if (!is_valid_move(game, new_x, new_y))
		return ;
	if (game->map[new_y][new_x] == 'E')
	{
		handle_exit(game, new_x, new_y);
		return ;
	}
	old_x = game->player.x;
	old_y = game->player.y;
	game->map[game->player.y][game->player.x] = '0';
	game->player.x = new_x;
	game->player.y = new_y;
	game->player.moves++;
	if (game->map[new_y][new_x] == 'C')
		ft_printf("Collected an orb!\n");
	game->map[new_y][new_x] = 'P';
	ft_printf("Moves: %d\n", game->player.moves);
	update_player_position(game, old_x, old_y);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	else if (keycode == KEY_W || keycode == KEY_UP || keycode == KEY_K)
		move_player(game, game->player.x, game->player.y - 1);
	else if (keycode == KEY_S || keycode == KEY_DOWN || keycode == KEY_J)
		move_player(game, game->player.x, game->player.y + 1);
	else if (keycode == KEY_A || keycode == KEY_LEFT || keycode == KEY_H)
		move_player(game, game->player.x - 1, game->player.y);
	else if (keycode == KEY_D || keycode == KEY_RIGHT || keycode == KEY_L)
		move_player(game, game->player.x + 1, game->player.y);
	return (0);
}
