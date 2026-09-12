/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 16:10:32 by pserre-s          #+#    #+#             */
/*   Updated: 2026/09/11 16:37:32 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static int	is_rgb_format(char *color)
{
	int	i;
	int	comma;
	
	i = 0;
	comma = 0;
	while(color[i])
	{
		if (color[i] == ',')
			comma++;
		if (!ft_isdigit(color[i]) && color[i] != ' ' && color[i] != ',')
			return (0);
		i++;
	}
	if (comma != 2)
		return (0);
	return (1);
}

static int	convert_color(char *color)
{
	char **rgb_color;
	int	r;
	int	g;
	int	b;

	if (!is_rgb_format(color))
		return (-1);
		
	rgb_color = ft_split(color, ',');
	
	if (ft_tabsize(rgb_color) != 3)
		return (ft_free_split(rgb_color), -1);

	r = ft_atoi(rgb_color[0]);
	g = ft_atoi(rgb_color[1]);
	b = ft_atoi(rgb_color[2]);

	ft_free_split(rgb_color);
	
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
		
	return ((r << 16) | (g << 8) | b);
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
				return (0);
			close(fd);
		}
		if (i == F)
		{
			map->f_color = convert_color(map->data[i]);
			if (map->f_color == -1)
				return (0);
		}
		if (i == C)
		{
			map->c_color = convert_color(map->data[i]);
			if (map->c_color == -1)
				return (0);
		}
		i++;
	}
	return (1);
}