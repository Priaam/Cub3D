/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:55:10 by pserre-s          #+#    #+#             */
/*   Updated: 2026/04/28 15:33:40 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static int	check_textures(char *line, t_map *map)
{
	if (!ft_strncmp(line, "NO ", 3) && !map->no)
		map->no = ft_strdup(line + 3);
	else if ()
	if (!ft_strncmp(line, "SO ", 3) && !map->so)
		map->so = ft_strdup(line + 3);
	if (!ft_strncmp(line, "WE ", 3) && !map->we)
		map->we = ft_strdup(line + 3);
	if (!ft_strncmp(line, "EA ", 3) && !map->ea)
		map->ea = ft_strdup(line + 3);
	
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
			
		}
		free(line);
		line = get_next_line(fd);
	}
}

int	parse_map(char *map, t_data *data)
{
	int	fd;

	if (!is_cub_extension(map))
		return (ft_putstr_fd("Error: invalid extension\n", 2), 0);
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (ft_putchar_fd("Error: failed to open the map\n", 2), 0);
	if (!fill_map_data(fd, &data->map))
		return (ft_putstr_fd("Error: fill map failed", 2), 0);
	return (1);
}
