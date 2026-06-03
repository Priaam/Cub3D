/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 15:40:18 by ylebee            #+#    #+#             */
/*   Updated: 2026/06/03 16:14:50 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	ft_put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

int	find_biggest(char **map_grid)
{
	int	i;
	int temp;
	int biggest;

	i = 0;
	temp = 0;
	biggest = 0;
	while (map_grid[i])
	{
		temp = ft_strlen(map_grid[i]);
		if (temp > biggest)
			biggest = temp;
		i++;
	}
	if (i > biggest)
		return (i);
	return (biggest);
}

