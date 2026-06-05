/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 14:41:14 by pserre-s          #+#    #+#             */
/*   Updated: 2026/06/05 15:12:58 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	init_struct_parser(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
}

void	ft_init_data_minimap(t_data *data)
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