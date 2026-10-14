/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylebee <yanislebee@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 18:00:56 by pserre-s          #+#    #+#             */
/*   Updated: 2026/10/14 18:57:33 by ylebee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static int	inside_map(t_data *data, int x, int y)
{
	return (x >= 0 && y >= 0 && x < data->map.width
		&& y < data->map.height);
}

static void	dda_step(t_dda *dda, t_hit *hit)
{
	if (dda->side_dist_x < dda->side_dist_y)
	{
		dda->side_dist_x += dda->delta_dist_x;
		dda->map_x += dda->step_x;
		hit->side = 0;
	}
	else
	{
		dda->side_dist_y += dda->delta_dist_y;
		dda->map_y += dda->step_y;
		hit->side = 1;
	}
}

static void	set_wall_distance(t_dda *dda, t_hit *hit)
{
	if (hit->side == 0)
		hit->perp_wall_dist = dda->side_dist_x - dda->delta_dist_x;
	else
		hit->perp_wall_dist = dda->side_dist_y - dda->delta_dist_y;
}

t_hit	dda(t_data *data, t_dda ray)
{
	t_dda	dda_data;
	t_hit	hit;

	dda_data = init_dda(data, ray);
	hit.side = 0;
	hit.is_door = 0;
	while (inside_map(data, dda_data.map_x, dda_data.map_y))
	{
		dda_step(&dda_data, &hit);
		if (!inside_map(data, dda_data.map_x, dda_data.map_y))
			break ;
		if (data->map.map_grid[dda_data.map_y][dda_data.map_x] == '1')
			break ;
		if (data->map.map_grid[dda_data.map_y][dda_data.map_x] == 'D')
		{
			if (check_sliding_door(data, &dda_data, &ray, &hit))
				break ;
		}
	}
	hit.map_x = dda_data.map_x;
	hit.map_y = dda_data.map_y;
	set_wall_distance(&dda_data, &hit);
	return (hit);
}
