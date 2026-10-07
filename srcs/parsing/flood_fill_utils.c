/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22  by pserre-s          #+#    #+#             */
/*   Updated: 2026/09/22  by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	find_map_player(char **map_copy, int *player_x, int *player_y)
{
	int	player_number;
	int	x;
	int	y;

	y = 0;
	player_number = 0;
	while (map_copy[y])
	{
		x = -1;
		while (map_copy[y][++x])
		{
			if (map_copy[y][x] == 'N' || map_copy[y][x] == 'S'
				|| map_copy[y][x] == 'E' || map_copy[y][x] == 'W')
			{
				*player_y = y;
				*player_x = x;
				player_number++;
			}
		}
		y++;
	}
	return (player_number == 1);
}
