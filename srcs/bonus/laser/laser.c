/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   laser.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylebee <yanislebee@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 14:29:37 by ylebee            #+#    #+#             */
/*   Updated: 2026/10/15 15:09:29 by ylebee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"


static double	get_laser_distance(t_data *data)
{
	t_dda	ray;
	t_hit	hit;

	ft_bzero(&ray, sizeof(t_dda));
	ray.ray_dir_x = data->dir_x;
	ray.ray_dir_y = data->dir_y;
	hit = dda(data, ray);
	return (hit.perp_wall_dist);
}

int	laser_click(int button, int x, int y, void *param)
{
	t_data	*data;

	(void)x;
	(void)y;
	data = (t_data *)param;
	if (button == 1 && data->weapon.laser_frame == 0)
	{
		data->weapon.laser_distance = get_laser_distance(data);
		data->weapon.laser_frame = 1;
	}
	return (0);
}

static void	draw_disk(t_data *data, int x, int y, int radius)
{
	int	dx;
	int	dy;

	dy = -radius;
	while (dy <= radius)
	{
		dx = -radius;
		while (dx <= radius)
		{
			if (dx * dx + dy * dy <= radius * radius)
				ft_put_pixel(&data->img, x + dx, y + dy, 0x00FFFFFF);
			dx++;
		}
		dy++;
	}
}

// static void	laser_beam(t_data *data, int frame)
// {
// 	int	i;
// 	int	x;
// 	int	y;
// 	int	steps;

// 	steps = (HEIGHT / 2) * frame / 8;
// 	i = 0;
// 	while (i <= steps)
// 	{
// 		x = (WIDTH - data->weapon.width * WEAPON_SCALE) / 2
// 			+ 102 * WEAPON_SCALE - (i * 2 / 3);
// 		y = HEIGHT - data->weapon.height * WEAPON_SCALE
// 			+ 130 * WEAPON_SCALE - i;
// 		draw_disk(data, x, y, 2);
// 		i += 2;
// 	}
// }

static void	laser_point(t_data *data, int *x, int *y, int i)
{
	int	start_y;

	start_y = HEIGHT - data->weapon.height * WEAPON_SCALE
		+ 94 * WEAPON_SCALE;
	*x = WIDTH / 2;
	*y = start_y + (HEIGHT / 2 - start_y) * i / 100;
}

static void	laser_beam(t_data *data, int frame)
{
	int	i;
	int	x;
	int	y;
	int	steps;

	steps = 100 * frame / 8;
	i = 0;
	while (i <= steps)
	{
		laser_point(data, &x, &y, i);
		draw_disk(data, x, y, 2);
		i += 2;
	}
}

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
