/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   laser.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylebee <ylebee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 14:29:37 by ylebee            #+#    #+#             */
/*   Updated: 2026/11/23 14:27:47 by ylebee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	render_laser(t_data *data)
{
	int	frame;
	int	radius;

	frame = data->weapon.laser_frame;
	if (!frame)
		return ;
	if (frame <= 8)
		laser_beam(data, frame);
	else
	{
		radius = (int)(30.0 / (data->weapon.laser_distance + 0.5));
		if (radius < 3)
			radius = 3;
		if (radius > 35)
			radius = 35;
		draw_disk(data, WIDTH / 2, HEIGHT / 2, radius);
	}
	data->weapon.laser_frame++;
	if (data->weapon.laser_frame > LASER_FRAMES)
		data->weapon.laser_frame = 0;
}
