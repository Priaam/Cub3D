/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 14:24:45 by pserre-s          #+#    #+#             */
/*   Updated: 2026/10/11 19:29:19 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	free_map_data(t_map *map)
{
	int	i;

	i = 0;
	while (i < DATA_COUNT)
	{
		if (map->data[i])
			free(map->data[i]);
		i++;
	}
	ft_free_split(map->map_grid);
}

void	free_game(t_data *data)
{
	free_textures(data);
	if (data->img.img)
		mlx_destroy_image(data->mlx_ptr, data->img.img);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free_map_data(&data->map);
}

int	ft_exit(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	free_game(data);
	exit(0);
	return (0);
}