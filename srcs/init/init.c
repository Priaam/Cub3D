/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 18:00:20 by pserre-s          #+#    #+#             */
/*   Updated: 2026/10/11 14:30:06 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static void	set_direction(t_data *data)
{
	if (data->orientation == 'N')
	{
		data->dir_y = -1.0;
		data->plane_x = 0.66;
	}
	else if (data->orientation == 'S')
	{
		data->dir_y = 1.0;
		data->plane_x = -0.66;
	}
	else if (data->orientation == 'E')
	{
		data->dir_x = 1.0;
		data->plane_y = 0.66;
	}
	else
	{
		data->dir_x = -1.0;
		data->plane_y = -0.66;
	}
}

int	init_game(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (0);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	data->img.img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->win_ptr || !data->img.img)
		return (0);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	if (!init_textures(data))
		return (0);
	set_direction(data);
	data->coef_minimap = TILE_SIZE / get_max_width_arr(data->map.map_grid);
	if (data->coef_minimap < 1)
		data->coef_minimap = 1;
	data->coef_player = data->coef_minimap / 2;
	return (1);
}
