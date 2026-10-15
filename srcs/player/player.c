/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylebee <yanislebee@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 18:00:04 by pserre-s          #+#    #+#             */
/*   Updated: 2026/10/14 18:18:18 by ylebee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static int	is_wall(t_data *data, double x, double y)
{
	if (x < 0 || y < 0 || y >= data->map.height
		|| x >= data->map.width)
		return (1);
	return (data->map.map_grid[(int)y][(int)x] == '1'
				|| data->map.map_grid[(int)y][(int)x] == 'D');
}

int	is_walkable(t_data *data, double x, double y)
{
	return (!is_wall(data, x - 0.15, y - 0.15)
		&& !is_wall(data, x + 0.15, y - 0.15)
		&& !is_wall(data, x - 0.15, y + 0.15)
		&& !is_wall(data, x + 0.15, y + 0.15));
}

void	rotate_camera(t_data *data, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(angle)
		- data->dir_y * sin(angle);
	data->dir_y = old_dir_x * sin(angle)
		+ data->dir_y * cos(angle);
	old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(angle)
		- data->plane_y * sin(angle);
	data->plane_y = old_plane_x * sin(angle)
		+ data->plane_y * cos(angle);
}

static void	move_player(t_data *data, double *x, double *y)
{
	double	move_x;
	double	move_y;
	double	length;

	move_x = 0;
	move_y = 0;
	player_move_coordinates(data, &move_x, &move_y);
	length = sqrt(move_x * move_x + move_y * move_y);
	if (length > 0)
	{
		move_x = (move_x / length) * SPEED;
		move_y = (move_y / length) * SPEED;
	}
	*x += move_x;
	*y += move_y;
}

int	update_player(t_data *data)
{
	double	new_x;
	double	new_y;

	if (data->key_left)
		rotate_camera(data, -0.025);
	if (data->key_right)
		rotate_camera(data, 0.025);
	new_x = data->player_x;
	new_y = data->player_y;
	move_player(data, &new_x, &new_y);
	if (is_walkable(data, new_x, data->player_y))
		data->player_x = new_x;
	if (is_walkable(data, data->player_x, new_y))
		data->player_y = new_y;
	return (0);
}
