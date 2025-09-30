/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_moves_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:49:41 by lucpardo          #+#    #+#             */
/*   Updated: 2025/09/30 19:54:28 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

// draws charcoal color pixels in a 100x30 pixels rectangle to clear old text
static void	clear_text_area(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < 30)
	{
		x = 0;
		while (x < 100)
		{
			mlx_pixel_put(game->mlx, game->win, x, y, 0x2F2F2F);
			x++;
		}
		y++;
	}
}

// converts int move count to a string, displays it on screen at coords 10,20
void	display_moves_on_screen(t_game *game)
{
	char	*moves_str;
	char	*display_text;

	clear_text_area(game);
	moves_str = ft_itoa(game->player.moves);
	display_text = ft_strjoin("Moves: ", moves_str);
	mlx_string_put(game->mlx, game->win, 10, 20, 12096877, display_text);
	free(moves_str);
	free(display_text);
}
