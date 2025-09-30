/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:55:49 by lucpardo          #+#    #+#             */
/*   Updated: 2025/09/30 21:13:10 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

// to make display_moves_on_screen update the counter
static void	display_move_count(t_game *game)
{
	display_moves_on_screen(game);
}

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
void	move_player_bonus(t_game *game, int new_x, int new_y)
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
	display_move_count(game);
	update_player_position(game, old_x, old_y);
}
