/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucpardo <lucpardo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 21:40:39 by lucpardo          #+#    #+#             */
/*   Updated: 2025/10/02 18:43:19 by lucpardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

// validates element counts: exactly 1 P, 1 E, at least 1 C
void	validate_elements(t_game *game)
{
	int	counts[3];

	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	count_elements(game, counts);
	if (counts[0] != 1)
	{
		free_game_map(game);
		print_map_error("No doppelgangers allowed, only 1 player plz!");
	}
	if (counts[1] != 1)
	{
		free_game_map(game);
		print_map_error("Map must have exactly 1 exit!");
	}
	if (counts[2] < 1)
	{
		free_game_map(game);
		print_map_error(":((( Without anything to collect player is sad :(");
	}
}
