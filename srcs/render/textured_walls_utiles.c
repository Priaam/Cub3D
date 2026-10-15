/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textured_walls_utiles.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylebee <yanislebee@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 19:04:22 by ylebee            #+#    #+#             */
/*   Updated: 2026/10/14 19:05:50 by ylebee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	texture_side(t_dda *ray, t_hit *hit)
{
	if (hit->is_door)
		return (DOOR);
	if (hit->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (WE);
		return (EA);
	}
	if (ray->ray_dir_y > 0)
		return (SO);
	return (NO);
}

int	texture_x(t_data *data, t_dda *ray, t_hit *hit)
{
	double	wall_x;
	int		x;
	int		side;

	side = texture_side(ray, hit);
	if (hit->side == 0)
		wall_x = data->player_y
			+ hit->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = data->player_x
			+ hit->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	if (hit->is_door)
		wall_x -= get_door_offset(data, hit->map_x, hit->map_y);
	x = (int)(wall_x * data->textures[side].width);
	if (hit->side == 0 && ray->ray_dir_x > 0)
		x = data->textures[side].width - x - 1;
	if (hit->side == 1 && ray->ray_dir_y < 0)
		x = data->textures[side].width - x - 1;
	return (x);
}
