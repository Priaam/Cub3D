/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylebee <yanislebee@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 17:08:11 by ylebee            #+#    #+#             */
/*   Updated: 2026/11/25 17:13:14 by ylebee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	mouse_move(void *param)
{
	t_data	*data;
	int		x;
	int		y;
	int		delta_x;

	data = (t_data *)param;
	if (!mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr, &x, &y))
		return (0);
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
	{
		mlx_mouse_move(data->mlx_ptr, data->win_ptr,
			WIDTH / 2, HEIGHT / 2);
		return (0);
	}
	delta_x = x - WIDTH / 2;
	if (delta_x != 0)
		rotate_camera(data, delta_x * 0.002);
	mlx_mouse_move(data->mlx_ptr, data->win_ptr,
		WIDTH / 2, HEIGHT / 2);
	return (0);
}
