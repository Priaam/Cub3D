/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylebee <yanislebee@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 18:45:00 by pserre-s          #+#    #+#             */
/*   Updated: 2026/10/14 18:51:09 by ylebee           ###   ########.fr       */
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

int	find_door_slot(t_data *data, int tx, int ty)
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