/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 18:00:56 by pserre-s          #+#    #+#             */
/*   Updated: 2026/10/09 18:00:58 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static void	init_delta_dist(t_dda *dda)
{
	if (dda->ray_dir_x == 0)
		dda->delta_dist_x = 1e30;
	else
		dda->delta_dist_x = fabs(1.0 / dda->ray_dir_x);
	if (dda->ray_dir_y == 0)
		dda->delta_dist_y = 1e30;
	else
		dda->delta_dist_y = fabs(1.0 / dda->ray_dir_y);
}

static void	init_side_dist(t_data *data, t_dda *dda)
{
	if (dda->ray_dir_x < 0)
		dda->side_dist_x = (data->player_x - dda->map_x)
			* dda->delta_dist_x;
	else
		dda->side_dist_x = (dda->map_x + 1.0 - data->player_x)
			* dda->delta_dist_x;
	if (dda->ray_dir_y < 0)
		dda->side_dist_y = (data->player_y - dda->map_y)
			* dda->delta_dist_y;
	else
		dda->side_dist_y = (dda->map_y + 1.0 - data->player_y)
			* dda->delta_dist_y;
}

static t_dda	init_dda(t_data *data, t_dda ray)
{
	t_dda	dda;

	dda = ray;
	dda.map_x = (int)data->player_x;
	dda.map_y = (int)data->player_y;
	dda.step_x = 1;
	dda.step_y = 1;
	if (dda.ray_dir_x < 0)
		dda.step_x = -1;
	if (dda.ray_dir_y < 0)
		dda.step_y = -1;
	init_delta_dist(&dda);
	init_side_dist(data, &dda);
	return (dda);
}

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
	while (inside_map(data, dda_data.map_x, dda_data.map_y))
	{
		dda_step(&dda_data, &hit);
		if (inside_map(data, dda_data.map_x, dda_data.map_y)
			&& data->map.map_grid[dda_data.map_y][dda_data.map_x] == '1')
			break ;
	}
	hit.map_x = dda_data.map_x;
	hit.map_y = dda_data.map_y;
	set_wall_distance(&dda_data, &hit);
	return (hit);
}
