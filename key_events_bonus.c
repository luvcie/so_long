/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 19:05:37 by lucpardo          #+#    #+#             */
/*   Updated: 2025/09/30 21:10:08 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

// norminette moment
int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	else if (keycode == KEY_W || keycode == KEY_UP || keycode == KEY_K)
		move_player_bonus(game, game->player.x, game->player.y - 1);
	else if (keycode == KEY_S || keycode == KEY_DOWN || keycode == KEY_J)
		move_player_bonus(game, game->player.x, game->player.y + 1);
	else if (keycode == KEY_A || keycode == KEY_LEFT || keycode == KEY_H)
		move_player_bonus(game, game->player.x - 1, game->player.y);
	else if (keycode == KEY_D || keycode == KEY_RIGHT || keycode == KEY_L)
		move_player_bonus(game, game->player.x + 1, game->player.y);
	return (0);
}
