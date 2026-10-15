/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylebee <yanislebee@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 18:56:32 by ylebee            #+#    #+#             */
/*   Updated: 2026/10/14 19:00:42 by ylebee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	init_delta_dist(t_dda *dda)
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

void	init_side_dist(t_data *data, t_dda *dda)
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

t_dda	init_dda(t_data *data, t_dda ray)
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
