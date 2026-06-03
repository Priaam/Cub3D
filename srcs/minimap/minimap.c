/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 16:10:30 by pserre-s          #+#    #+#             */
/*   Updated: 2026/06/03 16:12:10 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	ft_init_data(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	data->img.img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	data->angle = 4.0;
	data->dir_x = cos(data->angle);
	data->dir_y = sin(data->angle);
	data->key_a = 0;
	data->key_w = 0;
	data->key_s = 0;
	data->key_d = 0;
	data->key_left = 0;
	data->key_right = 0;
}

int	launch_minimap(t_data *data)
{
	int		x;
	int		y;
	double	p_x;
	double	p_y;

	p_x = -1;
	p_y = -1;
	y = 0;
	if (!data->map.map_grid)
		return (1);
	while (data->map.map_grid[y])
	{
		x = 0;
		while (data->map.map_grid[y][x])
		{
			if (data->map.map_grid[y][x] == 'P' || data->map.map_grid[y][x] == 'N' ||
				data->map.map_grid[y][x] == 'S' || data->map.map_grid[y][x] == 'E' ||
				data->map.map_grid[y][x] == 'W')
			{
				p_x = x + 0.5;
				p_y = y + 0.5;
				break ;
			}
			x++;
		}
		if (p_x != -1)
			break ;
		y++;
	}
	data->player_x = p_x;
	data->player_y = p_y;
	ft_init_data(data);
	data->coef_minimap = TILE_SIZE / find_biggest(data->map.map_grid);
	if (data->coef_minimap < 1)
		data->coef_minimap = 1;
	data->coef_player = data->coef_minimap / 2;
	ft_render_and_display(data);
	return (0);
}