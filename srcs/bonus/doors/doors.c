/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylebee <ylebee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 18:45:00 by pserre-s          #+#    #+#             */
/*   Updated: 2026/10/12 17:05:19 by ylebee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

double	get_door_offset(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < 32)
	{
		if (data->doors[i].x == x && data->doors[i].y == y
			&& data->doors[i].state != 0)
			return (data->doors[i].offset);
		i++;
	}
	return (0.0);
}

#ifdef BONUS

static int	find_door_slot(t_data *data, int tx, int ty)
{
	int	i;
	int	slot;

	i = 0;
	slot = -1;
	while (i < 32)
	{
		if (data->doors[i].x == tx && data->doors[i].y == ty
			&& data->doors[i].state != 0)
			return (i);
		if (data->doors[i].state == 0 && slot == -1)
			slot = i;
		i++;
	}
	return (slot);
}

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

void	update_doors(t_data *data)
{
	int	i;

	i = 0;
	while (i < 32)
	{
		if (data->doors[i].state == 1)
		{
			data->doors[i].offset += 0.02; // Vitesse d'ouverture
			if (data->doors[i].offset >= 1.0)
			{
				data->doors[i].offset = 0.0;
				data->doors[i].state = 0;
				data->map.map_grid[data->doors[i].y][data->doors[i].x] = 'O';
			}
		}
		else if (data->doors[i].state == -1)
		{
			data->doors[i].offset -= 0.02; // Vitesse de fermeture
			if (data->doors[i].offset <= 0.0)
			{
				data->doors[i].offset = 0.0;
				data->doors[i].state = 0;
			}
		}
		i++;
	}
}

int	check_sliding_door(t_data *data, t_dda *dda, t_dda *ray, t_hit *hit)
{
	double	offset;
	double	dist;
	double	wall_x;

	offset = get_door_offset(data, dda->map_x, dda->map_y);
	if (hit->side == 0)
		dist = dda->side_dist_x - dda->delta_dist_x;
	else
		dist = dda->side_dist_y - dda->delta_dist_y;
	if (hit->side == 0)
		wall_x = data->player_y + dist * ray->ray_dir_y;
	else
		wall_x = data->player_x + dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	if (wall_x > offset)
	{
		hit->is_door = 1;
		return (1);
	}
	return (0);
}

#else

int	interact_door(t_data *data)
{
	(void)data;
	return (0);
}

void	update_doors(t_data *data)
{
	(void)data;
}

int	check_sliding_door(t_data *data, t_dda *dda, t_dda *ray, t_hit *hit)
{
	(void)data;
	(void)dda;
	(void)ray;
	(void)hit;
	(void)get_door_offset(data, dda->map_x, dda->map_y);
	return (0);
}
#endif