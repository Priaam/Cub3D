/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylebee <yanislebee@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 18:41:16 by ylebee            #+#    #+#             */
/*   Updated: 2026/10/14 18:43:30 by ylebee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

#ifdef BONUS

int	interact_door(t_data *data)
{
	int	tx;
	int	ty;
	int	slot;

	tx = (int)(data->player_x + data->dir_x * 1.5);
	ty = (int)(data->player_y + data->dir_y * 1.5);
	if (data->map.map_grid[ty][tx] != 'D' && data->map.map_grid[ty][tx] != 'O')
		return (0);
	slot = find_door_slot(data, tx, ty);
	if (slot == -1)
		return (0);
	data->doors[slot].x = tx;
	data->doors[slot].y = ty;
	if (data->map.map_grid[ty][tx] == 'D')
		data->doors[slot].state = 1;
	else
	{
		data->map.map_grid[ty][tx] = 'D';
		data->doors[slot].offset = 1.0;
		data->doors[slot].state = -1;
	}
	return (0);
}

void	update_doors(t_data *data, int i)
{
	while (i < 32)
	{
		if (data->doors[i].state == 1)
		{
			data->doors[i].offset += 0.02;
			if (data->doors[i].offset >= 1.0)
			{
				data->doors[i].offset = 0.0;
				data->doors[i].state = 0;
				data->map.map_grid[data->doors[i].y][data->doors[i].x] = 'O';
			}
		}
		else if (data->doors[i].state == -1)
		{
			data->doors[i].offset -= 0.02;
			if (data->doors[i].offset <= 0.0)
			{
				data->doors[i].offset = 0.0;
				data->doors[i].state = 0;
			}
		}
		i++;
	}
}

#else

int	interact_door(t_data *data)
{
	(void)data;
	return (0);
}

void	update_doors(t_data *data, int i)
{
	(void)data;
	(void)i;
}

#endif