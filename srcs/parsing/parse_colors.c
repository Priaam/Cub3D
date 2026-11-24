/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylebee <ylebee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 16:10:32 by pserre-s          #+#    #+#             */
/*   Updated: 2026/11/24 17:00:11 by ylebee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static int	parse_rgb_component(char *component)
{
	int	i;
	int	value;
	int	has_digit;

	i = 0;
	value = 0;
	has_digit = 0;
	while (component[i] == ' ')
		i++;
	while (ft_isdigit(component[i]))
	{
		has_digit = 1;
		if (value > 25 || (value == 25 && component[i] - '0' > 5))
			return (-1);
		value = value * 10 + component[i] - '0';
		i++;
	}
	while (component[i] == ' ')
		i++;
	if (!has_digit || component[i])
		return (-1);
	return (value);
}

static int	rgb_to_int(char **rgb_color)
{
	int	r;
	int	g;
	int	b;

	r = parse_rgb_component(rgb_color[0]);
	g = parse_rgb_component(rgb_color[1]);
	b = parse_rgb_component(rgb_color[2]);
	if (r == -1 || g == -1 || b == -1)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

static int	convert_color(char *color)
{
	char	**rgb_color;
	int		result;

	if (!color || !is_rgb_format(color))
		return (-1);
	rgb_color = ft_split(color, ',');
	if (!rgb_color)
		return (-1);
	if (ft_tabsize(rgb_color) != 3)
		return (ft_free_split(rgb_color), -1);
	result = rgb_to_int(rgb_color);
	ft_free_split(rgb_color);
	return (result);
}

static int	parse_and_validate_entry(t_map *map, int i)
{
	if (i == NO || i == SO || i == WE || i == EA)
	{
		if (!check_extension(map->data[i], ".xpm"))
			return (0);
		if (!check_xpm_header(map->data[i]))
			return (0);
	}
	if (i == F)
		map->f_color = convert_color(map->data[i]);
	if (i == C)
		map->c_color = convert_color(map->data[i]);
	if ((i == F && map->f_color == -1)
		|| (i == C && map->c_color == -1))
		return (0);
	return (1);
}

int	is_valid_texture(t_map *map)
{
	int	i;

	i = 0;
	while (i < DATA_COUNT)
	{
		if (!parse_and_validate_entry(map, i))
			return (0);
		i++;
	}
	return (1);
}
