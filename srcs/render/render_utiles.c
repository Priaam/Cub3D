/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylebee <yanislebee@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 19:01:09 by ylebee            #+#    #+#             */
/*   Updated: 2026/10/14 19:03:35 by ylebee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	draw_background(t_data *data, int x, t_hit *hit)
{
	int	y;

	y = 0;
	while (y < hit->draw_start)
	{
		ft_put_pixel(&data->img, x, y, data->map.c_color);
		y++;
	}
	y = hit->draw_end + 1;
	while (y < HEIGHT)
	{
		ft_put_pixel(&data->img, x, y, data->map.f_color);
		y++;
	}
}

void	set_wall_limits(t_hit *hit)
{
	int	line_height;

	line_height = (int)(HEIGHT / hit->perp_wall_dist);
	hit->draw_start = HEIGHT / 2 - line_height / 2;
	hit->draw_end = HEIGHT / 2 + line_height / 2;
	if (hit->draw_start < 0)
		hit->draw_start = 0;
	if (hit->draw_end >= HEIGHT)
		hit->draw_end = HEIGHT - 1;
}
