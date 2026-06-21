/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 16:10:32 by pserre-s          #+#    #+#             */
/*   Updated: 2026/06/11 18:13:06 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static int	convert_color(char *color)
{
	char	*ptr;
	int		hexa_color;
	int		r;
	int		g;
	int		b;
	
	ptr = color;
	r = ft_atoi(ptr);
	ptr = ft_strchr(ptr, ',');
	if (ptr)
		ptr++;
	g = ft_atoi(ptr);
	ptr = ft_strchr(ptr, ',');
	if (ptr)
		ptr++;
	b = ft_atoi(ptr);
	hexa_color = (r << 16) | (g << 8) | b;
	return (hexa_color);
}

int	is_valid_texture(t_map *map)
{
	int	i;
	int	fd;

	i = 0;
	while (i < DATA_COUNT)
	{
		if (i == NO || i == SO || i == WE || i == EA)
		{
			if (!check_extension(map->data[i], ".xpm"))
				return (0);
			fd = open(map->data[i], O_RDONLY);
			if (fd < 0)
				return (close(fd), 0);
			close(fd);
		}
		if (i == F)
			map->f_color = convert_color(map->data[i]);
		if (i == C)
			map->c_color = convert_color(map->data[i]);
		i++;
	}
	return (1);
}