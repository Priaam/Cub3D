/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* minimap.c                                          :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: ylebee <ylebee@student.42.fr>              +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/05/28 17:23:28 by ylebee            #+#    #+#             */
/* Updated: 2026/05/28 19:55:00 by ylebee           ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "minimap.h"

void	ft_init_data(t_mlx *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
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

int	main(void)
{
	t_mlx	data;
	int	x;
	int	y;
	double p_x;
	double p_y;

	x = 0;
	y = 0;
	p_x = -1;
	p_y = -1;
	data.map_grid = malloc(sizeof(char *) * 20);
	if (!data.map_grid)
		return (1);
	data.map_grid[0] = ft_strdup("111111111111111111");
	data.map_grid[1] = ft_strdup("100000000000000001");
	data.map_grid[2] = ft_strdup("100000000000000001");
	data.map_grid[3] = ft_strdup("100000000000000001");
	data.map_grid[4] = ft_strdup("100000000000000001");
	data.map_grid[5] = ft_strdup("100000001100000001");
	data.map_grid[6] = ft_strdup("100000000000000001");
	data.map_grid[7] = ft_strdup("100000000000000001");
	data.map_grid[8] = ft_strdup("100001100000000001");
	data.map_grid[9] = ft_strdup("100000000000000001");
	data.map_grid[10] = ft_strdup("100000000000000001");
	data.map_grid[11] = ft_strdup("100000000000000001");
	data.map_grid[12] = ft_strdup("100000000000000001");
	data.map_grid[13] = ft_strdup("100000000000000001");
	data.map_grid[14] = ft_strdup("1000000000P0000001");
	data.map_grid[15] = ft_strdup("100000000000000001");
	data.map_grid[16] = ft_strdup("100000000000000001");
	data.map_grid[17] = ft_strdup("100000000000000001");
	data.map_grid[18] = ft_strdup("111111111111111111");
	data.map_grid[19] = NULL;
	while (data.map_grid[y])
	{
		x = 0;
		while (data.map_grid[y][x])
		{
			if (data.map_grid[y][x] == 'P')
			{
				p_x = x;
				p_y = y;
				break ;
			}
			x++;
		}
		if (p_x != -1)
			break ;
		y++;
	}
	data.player_x = p_x;
	data.player_y = p_y;
	ft_init_data(&data);
	data.coef_minimap = TILE_SIZE / find_biggest(data.map_grid);
	if (data.coef_minimap < 1)
		data.coef_minimap = 1;
	data.coef_player = data.coef_minimap / 2;
	ft_render_and_display(&data);
	free(data.map_grid);
	return (0);
}
