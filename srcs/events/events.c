/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylebee <ylebee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 01:07:12 by pserre-s          #+#    #+#             */
/*   Updated: 2026/10/12 16:02:41 by ylebee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	key_press(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == KEY_W)
		data->key_w = 1;
	if (keycode == KEY_S)
		data->key_s = 1;
	if (keycode == KEY_A)
		data->key_a = 1;
	if (keycode == KEY_D)
		data->key_d = 1;
	if (keycode == KEY_SPACE)
		interact_door(data);
	if (keycode == KEY_LEFT)
		data->key_left = 1;
	if (keycode == KEY_RIGHT)
		data->key_right = 1;
	if (keycode == KEY_ESC)
		ft_exit(data);
	return (0);
}

int	key_release(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == KEY_W)
		data->key_w = 0;
	if (keycode == KEY_S)
		data->key_s = 0;
	if (keycode == KEY_A)
		data->key_a = 0;
	if (keycode == KEY_D)
		data->key_d = 0;
	if (keycode == KEY_LEFT)
		data->key_left = 0;
	if (keycode == KEY_RIGHT)
		data->key_right = 0;
	return (0);
}

int	mouse_move(void *param)
{
	t_data	*data;
	int		x;
	int		y;
	int		delta_x;

	data = (t_data *)param;
	mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr, &x, &y);
	delta_x = x - (WIDTH / 2);
	if (delta_x == 0)
		return (0);
	rotate_camera(data, delta_x * 0.002);
	mlx_mouse_move(data->mlx_ptr, data->win_ptr,
		WIDTH / 2, HEIGHT / 2);
	return (0);
}
