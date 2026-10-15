/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylebee <yanislebee@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 18:01:25 by pserre-s          #+#    #+#             */
/*   Updated: 2026/10/14 19:01:41 by ylebee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static void	render_column(t_data *data, int x)
{
	t_dda	ray;
	t_hit	hit;
	double	camera_x;

	camera_x = 2.0 * x / (double)WIDTH - 1.0;
	ray.ray_dir_x = data->dir_x + data->plane_x * camera_x;
	ray.ray_dir_y = data->dir_y + data->plane_y * camera_x;
	hit = dda(data, ray);
	set_wall_limits(&hit);
	draw_background(data, x, &hit);
	draw_textured_wall(data, &ray, &hit, x);
}

void	render_3d(t_data *data)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		render_column(data, x);
		x++;
	}
}

#ifdef BONUS

static void	render_bonus_features(t_data *data)
{
	int	i;

	i = 0;
	render_minimap(data);
	draw_player_minimap(data);
	update_doors(data, i);
	mouse_move(data);
}

#else

static void	render_bonus_features(t_data *data)
{
	(void)data;
}

#endif

int	render(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	update_player(data);
	render_3d(data);
	render_bonus_features(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.img, 0, 0);
	render_weapon(data);
	return (0);
}
