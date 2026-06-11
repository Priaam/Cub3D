/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylebee <yanislebee@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 16:32:35 by pserre-s          #+#    #+#             */
/*   Updated: 2026/06/11 18:53:56 by ylebee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

// void draw_player(t_data *data)
// {
// 	int px;
// 	int py;
// 	int i;
// 	int j;
// 	int len;

// 	px = data->player_x * data->coef_minimap;
// 	py = data->player_y * data->coef_minimap;
// 	i = 0;
// 	while (i < data->coef_player)
// 	{
// 		j = 0;
// 		while (j < data->coef_player)
// 		{
// 			ft_put_pixel(&data->img,
// 				px + j - data->coef_player / 2,
// 				py + i - data->coef_player / 2,
// 				0xff2c2c);
// 			j++;
// 		}
// 		i++;
// 	}
// 	len = data->coef_minimap * 2;
// 	i = 0;
// 	while (i < len)
// 	{
// 		ft_put_pixel(&data->img,
// 			px + (int)(data->dir_x * i),
// 			py + (int)(data->dir_y * i),
// 			0x00FF00);
// 		i++;
// 	}
// }

// void draw_line(t_data *data, double x1, double y1, double x2, double y2, int color)
// {
//     double delta_x = x2 - x1;
//     double delta_y = y2 - y1;
//     int pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
    
//     delta_x /= pixels;
//     delta_y /= pixels;
    
//     double current_x = x1;
//     double current_y = y1;
    
//     while (pixels > 0)
//     {
//         if (current_x >= 0 && current_x < WIDTH && current_y >= 0 && current_y < HEIGHT)
//             ft_put_pixel(&data->img, (int)current_x, (int)current_y, color);
//         current_x += delta_x;
//         current_y += delta_y;
//         pixels--;
//     }
// }

// void	draw_square(t_data *data, int x, int y, int color)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < data->coef_minimap)
// 	{
// 		j = 0;
// 		while (j < data->coef_minimap)
// 		{
// 			ft_put_pixel(&data->img, x + j, y + i, color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// int render(void *param)
// {
// 	int     x;
// 	int     y;
// 	int     i;
// 	int     j;
// 	int     max_width;
// 	t_data  *data;

// 	data = (t_data *)param;
	
// 	max_width = find_biggest(data->map.map_grid);
	
// 	i = 0;
// 	y = 0;
// 	render_3d(data);
// 	while (data->map.map_grid[i] && y < HEIGHT)
// 	{
// 		j = 0;
// 		x = 0;
// 		while (j < max_width && x < WIDTH)
// 		{
// 			if (j < (int)ft_strlen(data->map.map_grid[i]) && data->map.map_grid[i][j] == '1')
// 				draw_square(data, x, y, 0xffffff);
// 			else if (j < (int)ft_strlen(data->map.map_grid[i]) && ft_strchr("0PNSEW", data->map.map_grid[i][j]))
// 				draw_square(data, x, y, 0x808080);
// 			else
// 				draw_square(data, x, y, 0x000000);
// 			j++;
// 			x += data->coef_minimap;
// 		}
// 		i++;
// 		y += data->coef_minimap;
// 	}
// 	draw_player(data);
// 	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
// 	return (0);
// }


int is_in_circle(int x, int y, int cx, int cy, int r)
{
	int dx = x - cx;
	int dy = y - cy;

	return (dx * dx + dy * dy <= r * r);
}

int is_on_circle_border(int x, int y, int cx, int cy, int r)
{
	int dx = x - cx;
	int dy = y - cy;

	int dist = dx * dx + dy * dy;

	return (dist <= r * r && dist >= (r - 2) * (r - 2));
}

int safe_get_tile(t_data *data, int x, int y)
{
	if (y < 0 || x < 0)
		return 0;

	if (!data->map.map_grid[y])
		return 0;

	if (y >= data->map.height)
		return 0;

	if (x >= (int)ft_strlen(data->map.map_grid[y]))
		return 0;

	return data->map.map_grid[y][x];
}

void render_minimap(t_data *data)
{
	int screen_x;
	int screen_y;
	int map_x;
	int map_y;

	int radius = 90;
	int tile = data->coef_minimap;
	int cx = radius;
	int cy = radius;

	if (tile <= 0)
		tile = 1;

	screen_y = 0;
	while (screen_y < radius * 2)
	{
		screen_x = 0;
		while (screen_x < radius * 2)
		{
			if (is_in_circle(screen_x, screen_y, cx, cy, radius))
			{
				map_x = (int)data->player_x + (screen_x - cx) / tile;
				map_y = (int)data->player_y + (screen_y - cy) / tile;

				if (safe_get_tile(data, map_x, map_y) == '1')
					ft_put_pixel(&data->img, screen_x, screen_y, 0xffffff);
				else if (safe_get_tile(data, map_x, map_y))
					ft_put_pixel(&data->img, screen_x, screen_y, 0x777777);
			}

			if (is_on_circle_border(screen_x, screen_y, cx, cy, radius))
				ft_put_pixel(&data->img, screen_x, screen_y, 0x00FFAA);

			screen_x++;
		}
		screen_y++;
	}
}

void draw_player_minimap(t_data *data)
{
	int cx = 90;
	int cy = 90;

	int size = 4;

	int i = -size;
	while (i <= size)
	{
		int j = -size;
		while (j <= size)
		{
			ft_put_pixel(&data->img, cx + j, cy + i, 0xff2c2c);
			j++;
		}
		i++;
	}
}

int render(void *param)
{
	t_data *data;

	data = (t_data *)param;
	render_3d(data);
	render_minimap(data);
	draw_player_minimap(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	return (0);
}

void ft_render_and_display(t_data *data)
{
	mlx_hook(data->win_ptr, 2, 1L<<0, (int (*)())(void *)key_press, data);
	mlx_hook(data->win_ptr, 3, 1L<<1, (int (*)())(void *)key_release, data);
	mlx_hook(data->win_ptr, 17, 0, (int (*)())(void *)ft_exit, data);
	mlx_loop_hook(data->mlx_ptr, (int (*)())(void *)loop, data);
	mlx_loop(data->mlx_ptr);
}