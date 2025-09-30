/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:12:25 by lucpardo          #+#    #+#             */
/*   Updated: 2025/09/30 21:01:07 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

// validates movement by checking these 3 conditions: 
// 1. coords are ithin map boundaries
// 2. target position is not a wall (1), returns 1 if valid
// and returns 0 if invalid that way player can't noclip
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

// iterates through entire map to count remaining collectibles
// returns total of UNCOLLECTED items
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

// exit logic: if all collectibles were collected (0), win and exit
// if no then remind player to collect
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

// movement logic:
// validates movement, handles exit tries, updates map array by
// replacing old position with '0' and new position with 'P',
// increments move counter, prints when player collects and updates visuals
// Map array is both the current game state and the source to render from
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

// keyboard event handler that supports VIM keys, WASD, and arrows
// each movement call calculates new coors relative to current pos
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
