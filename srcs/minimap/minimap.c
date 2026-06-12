/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 16:10:30 by pserre-s          #+#    #+#             */
/*   Updated: 2026/06/12 15:47:23 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	launch_minimap(t_data *data)
{
	int		x;
	int		y;
	double	p_x;
	double	p_y;

	p_x = -1;
	p_y = -1;
	y = 0;
	if (!data->map.map_grid)
		return (1);
	while (data->map.map_grid[y])
	{
		x = 0;
		while (data->map.map_grid[y][x])
		{
			if (data->map.map_grid[y][x] == 'P' || data->map.map_grid[y][x] == 'N' ||
				data->map.map_grid[y][x] == 'S' || data->map.map_grid[y][x] == 'E' ||
				data->map.map_grid[y][x] == 'W')
			{
				data->orientaion = data->map.map_grid[y][x];
				p_x = x + 0.5;
				p_y = y + 0.5;
				break ;
			}
			x++;
		}
		if (p_x != -1)
			break ;
		y++;
	}
	data->player_x = p_x;
	data->player_y = p_y;
	ft_init_data_minimap(data);
	data->coef_minimap = TILE_SIZE / find_biggest(data->map.map_grid);
	if (data->coef_minimap < 1)
		data->coef_minimap = 1;
	data->coef_player = data->coef_minimap / 2;
	
	ft_render_and_display(data);
	return (0);
}