/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textured_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylebee <yanislebee@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 18:01:05 by pserre-s          #+#    #+#             */
/*   Updated: 2026/10/14 19:04:10 by ylebee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static int	get_texture_pixel(t_texture *texture, int x, int y)
{
	char	*pixel;

	pixel = texture->pixels + y * texture->line_len
		+ x * (texture->bpp / 8);
	return (*(unsigned int *)pixel);
}

static int	get_texture_y(t_texture *texture, double tex_pos)
{
	int	y;

	y = (int)tex_pos;
	if (y < 0)
		y = 0;
	if (y >= texture->height)
		y = texture->height - 1;
	return (y);
}

static void	draw_texture_column(t_data *data, t_texture *texture,
		t_tex_column *column)
{
	int	y;
	int	tex_y;

	y = column->draw_start;
	while (y <= column->draw_end)
	{
		tex_y = get_texture_y(texture, column->tex_pos);
		ft_put_pixel(&data->img, column->x, y,
			get_texture_pixel(texture, column->tex_x, tex_y));
		column->tex_pos += column->step;
		y++;
	}
}

static void	init_tex_column(t_tex_column *column, t_texture *texture,
		t_hit *hit, int x)
{
	int	wall_height;

	wall_height = (int)(HEIGHT / hit->perp_wall_dist);
	column->x = x;
	column->step = (double)texture->height / wall_height;
	column->tex_pos = 0;
}

void	draw_textured_wall(t_data *data, t_dda *ray, t_hit *hit, int x)
{
	t_texture		*texture;
	t_tex_column	column;
	int				wall_height;

	texture = &data->textures[texture_side(ray, hit)];
	init_tex_column(&column, texture, hit, x);
	column.tex_x = texture_x(data, ray, hit);
	wall_height = (int)(HEIGHT / hit->perp_wall_dist);
	column.draw_start = hit->draw_start;
	column.draw_end = hit->draw_end;
	column.tex_pos = (column.draw_start - HEIGHT / 2
			+ wall_height / 2) * column.step;
	draw_texture_column(data, texture, &column);
}
