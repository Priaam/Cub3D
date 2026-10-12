/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylebee <ylebee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 01:07:12 by pserre-s          #+#    #+#             */
/*   Updated: 2026/10/12 17:07:48 by ylebee           ###   ########.fr       */
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
