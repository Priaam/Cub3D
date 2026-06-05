/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylebee <yanislebee@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 16:32:35 by pserre-s          #+#    #+#             */
/*   Updated: 2026/06/05 18:20:18 by ylebee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void draw_player(t_data *data)
{
	int px;
	int py;
	int i;
	int j;
	int len;

	px = data->player_x * data->coef_minimap;
	py = data->player_y * data->coef_minimap;
	i = 0;
	while (i < data->coef_player)
	{
		j = 0;
		while (j < data->coef_player)
		{
			ft_put_pixel(&data->img,
				px + j - data->coef_player / 2,
				py + i - data->coef_player / 2,
				0xff2c2c);
			j++;
		}
		i++;
	}
	len = data->coef_minimap * 2;
	i = 0;
	while (i < len)
	{
		ft_put_pixel(&data->img,
			px + (int)(data->dir_x * i),
			py + (int)(data->dir_y * i),
			0x00FF00);
		i++;
	}
}

void draw_line(t_data *data, double x1, double y1, double x2, double y2, int color)
{
    double delta_x = x2 - x1;
    double delta_y = y2 - y1;
    int pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
    
    delta_x /= pixels;
    delta_y /= pixels;
    
    double current_x = x1;
    double current_y = y1;
    
    while (pixels > 0)
    {
        if (current_x >= 0 && current_x < WIDTH && current_y >= 0 && current_y < HEIGHT)
            ft_put_pixel(&data->img, (int)current_x, (int)current_y, color);
        current_x += delta_x;
        current_y += delta_y;
        pixels--;
    }
}

void draw_rays_on_minimap(t_data *data)
{
    int     x;
    t_dda   ray;
    t_hit   hit;
    double  camera_x;
    double  wall_dist;
    double player_pixel_x = data->player_x * data->coef_minimap;
    double player_pixel_y = data->player_y * data->coef_minimap;
    x = 0;
    while (x < WIDTH)
    {
        camera_x = 2 * x / (double)WIDTH - 1;
        ray.ray_dir_x = data->dir_x + data->plane_x * camera_x;
        ray.ray_dir_y = data->dir_y + data->plane_y * camera_x;
        hit = dda(data, ray);
        if (hit.side == 0)
            wall_dist = (hit.map_x - data->player_x + (1 - (ray.ray_dir_x < 0 ? -1 : 1)) / 2) / ray.ray_dir_x;
        else
            wall_dist = (hit.map_y - data->player_y + (1 - (ray.ray_dir_y < 0 ? -1 : 1)) / 2) / ray.ray_dir_y;
        double impact_x = data->player_x + ray.ray_dir_x * wall_dist;
        double impact_y = data->player_y + ray.ray_dir_y * wall_dist;
        double impact_pixel_x = impact_x * data->coef_minimap;
        double impact_pixel_y = impact_y * data->coef_minimap;
        draw_line(data, player_pixel_x, player_pixel_y, impact_pixel_x, impact_pixel_y, 0xFFFF00);
        x++;
    }
}

void	draw_square(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->coef_minimap)
	{
		j = 0;
		while (j < data->coef_minimap)
		{
			ft_put_pixel(&data->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

int render(void *param)
{
	int     x;
	int     y;
	int     i;
	int     j;
	int     max_width;
	t_data  *data;

	data = (t_data *)param;
	
	max_width = find_biggest(data->map.map_grid);
	
	i = 0;
	y = 0;
	while (data->map.map_grid[i] && y < HEIGHT)
	{
		j = 0;
		x = 0;
		while (j < max_width && x < WIDTH)
		{
			if (j < (int)ft_strlen(data->map.map_grid[i]) && data->map.map_grid[i][j] == '1')
				draw_square(data, x, y, 0xffffff);
			else if (j < (int)ft_strlen(data->map.map_grid[i]) && ft_strchr("0PNSEW", data->map.map_grid[i][j]))
				draw_square(data, x, y, 0x808080);
			else
				draw_square(data, x, y, 0x000000);
			j++;
			x += data->coef_minimap;
		}
		i++;
		y += data->coef_minimap;
	}
	draw_player(data);
	draw_rays_on_minimap(data);
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