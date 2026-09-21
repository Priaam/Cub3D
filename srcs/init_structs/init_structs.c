/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylebee <ylebee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 14:41:14 by pserre-s          #+#    #+#             */
/*   Updated: 2026/09/21 15:00:38 by ylebee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	init_struct_parser(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
}

static void	init_north_south(t_data *data)
{
	if (data->orientaion == 'N')
	{
		data->dir_x = 0.0;
		data->dir_y = -1.0;
		data->plane_x = 1.0;
		data->plane_y = 0.0;
	}
	else if (data->orientaion == 'S')
	{
		data->dir_x = 0.0;
		data->dir_y = 1.0;
		data->plane_x = -1.0;
		data->plane_y = 0.0;
	}
}

static void	init_east_west(t_data *data)
{
	if (data->orientaion == 'E')
	{
		data->dir_x = 1.0;
		data->dir_y = 0.0;
		data->plane_x = 0.0;
		data->plane_y = 1.0;
	}
	else if (data->orientaion == 'W')
	{
		data->dir_x = -1.0;
		data->dir_y = 0.0;
		data->plane_x = 0.0;
		data->plane_y = -1.0;
	}
}

static void	init_keys(t_data *data)
{
	data->key_a = 0;
	data->key_w = 0;
	data->key_s = 0;
	data->key_d = 0;
	data->key_left = 0;
	data->key_right = 0;
}

void	ft_init_data_minimap(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	data->img.img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	init_north_south(data);
	init_east_west(data);
	init_keys(data);
}
