/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 20:14:38 by pserre-s          #+#    #+#             */
/*   Updated: 2026/10/09 18:08:27 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	check_and_fill(t_map *map, t_type type, char *value)
{
	if (map->data[type] != NULL)
		return (1);
	map->data[type] = ft_strtrim(value, " \t\n");
	if (!map->data[type])
		return (1);
	return (0);
}

static int	parse_data_line(t_map *map, char *line, int *count_elements)
{
	char	*trimmed_line;
	int		status;

	status = 0;
	trimmed_line = ft_strtrim(line, " \t\n");
	if (trimmed_line && trimmed_line[0])
	{
		status = parse_data_status(map, trimmed_line);
		if (!status)
			(*count_elements)++;
	}
	free(trimmed_line);
	return (status);
}

static int	read_map_data(int fd, t_map *map)
{
	char	*line;
	int		status;
	int		count_elements;

	count_elements = 0;
	line = get_next_line(fd);
	while (line)
	{
		status = parse_data_line(map, line, &count_elements);
		if (count_elements == 6)
		{
			free(line);
			if (!is_valid_texture(map))
				return (discard_remaining_lines(fd), 0);
			return (fill_map_grid(fd, map));
		}
		if (status == 1)
			return (free(line), discard_remaining_lines(fd), 0);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	fill_map_data(int fd, t_map *map)
{
	return (read_map_data(fd, map));
}

void	free_map_data(t_map *map)
{
	int	i;

	i = 0;
	while (i <= 5)
	{
		if (map->data[i])
			free(map->data[i]);
		i++;
	}
	ft_free_split(map->map_grid);
}
