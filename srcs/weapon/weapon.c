/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylebee <yanislebee@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:55:58 by ylebee            #+#    #+#             */
/*   Updated: 2026/10/14 17:52:14 by ylebee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	init_weapon(t_data *data)
{
	data->weapon.img = mlx_xpm_file_to_image(data->mlx_ptr,
			"./textures/arme_256_propree.xpm", &data->weapon.width,
			&data->weapon.height);
	if (!data->weapon.img)
		return (1);
	return (0);
}

static void	draw_weapon_row(t_data *data, char *addr, int stride, int y)
{
	int				x;
	int				pos_x;
	int				pos_y;
	unsigned int	color;

	x = 0;
	while (x < data->weapon.width * WEAPON_SCALE)
	{
		color = *(unsigned int *)(addr + (y / WEAPON_SCALE)
				* stride + (x / WEAPON_SCALE) * 4);
		pos_x = (WIDTH - data->weapon.width * WEAPON_SCALE) / 2 + x;
		pos_y = HEIGHT - data->weapon.height * WEAPON_SCALE + y;
		if (!(color & 0xFF000000) && pos_x >= 0 && pos_x < WIDTH
			&& pos_y >= 0 && pos_y < HEIGHT)
			ft_put_pixel(&data->img, pos_x, pos_y, color);
		x++;
	}
}

void	render_weapon(t_data *data)
{
	int		bpp;
	int		stride;
	int		endian;
	int		y;
	char	*addr;

	if (!data->weapon.img)
		return ;
	addr = mlx_get_data_addr(data->weapon.img, &bpp, &stride, &endian);
	if (!addr || bpp != 32)
		return ;
	y = 0;
	while (y < data->weapon.height * WEAPON_SCALE)
	{
		draw_weapon_row(data, addr, stride, y);
		y++;
	}
}
