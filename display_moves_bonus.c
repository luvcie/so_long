/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_moves_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:49:41 by lucpardo          #+#    #+#             */
/*   Updated: 2025/09/30 18:49:54 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display_moves_on_screen(t_game *game)
{
	char	*moves_str;
	char	*display_text;

	moves_str = ft_itoa(game->player.moves);
	display_text = ft_strjoin("Moves: ", moves_str);
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, display_text);
	free(moves_str);
	free(display_text);
}
