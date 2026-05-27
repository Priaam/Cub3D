/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:55:10 by pserre-s          #+#    #+#             */
/*   Updated: 2026/05/27 16:45:56 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static int check_and_fill(t_map *map, t_type type, char *value)
{
	if (map->data[type] != NULL)
		return (1);
	map->data[type] = ft_strtrim(value, " \t\n");
	if (!map->data[type])
        return (1);
	return (0);
}

int	fill_map_data(int fd, t_map *map)
{
	char	*line;
	char	*trimmed_line;

	line = get_next_line(fd);
	while (line)
	{
		trimmed_line = ft_strtrim(line, " \t\n");
		if (trimmed_line && trimmed_line[0])
		{
			if (!ft_strncmp(trimmed_line, "NO ", 3))
                check_and_fill(map, NO, trimmed_line + 3);
            else if (!ft_strncmp(trimmed_line, "SO ", 3))
                check_and_fill(map, SO, trimmed_line + 3);
            else if (!ft_strncmp(trimmed_line, "WE ", 3))
                check_and_fill(map, WE, trimmed_line + 3);
            else if (!ft_strncmp(trimmed_line, "EA ", 3))
                check_and_fill(map, EA, trimmed_line + 3);
            else if (!ft_strncmp(trimmed_line, "F ", 2))
                check_and_fill(map, F, trimmed_line + 2);
            else if (!ft_strncmp(trimmed_line, "C ", 2))
                check_and_fill(map, C, trimmed_line + 2);
		}
		free(line);
		free(trimmed_line);
		line = get_next_line(fd);
	}
	return (1);
}

int	parse_map(char *map, t_data *data)
{
	int	fd;

	if (!is_cub_extension(map))
		return (ft_putstr_fd("Error: invalid extension\n", 2), 0);
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error: failed to open the map\n", 2), 0);
	if (!fill_map_data(fd, &data->map))
	{
		close(fd);
		return (ft_putstr_fd("Error: fill map failed", 2), 0);
	}
	close(fd);
	return (1);
}
