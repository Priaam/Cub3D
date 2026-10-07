/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_data_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22  by pserre-s          #+#    #+#             */
/*   Updated: 2026/09/22  by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	check_xpm_header(char *path)
{
	int		fd;
	int		bytes_read;
	char	header[10];

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	bytes_read = read(fd, header, 9);
	header[9] = '\0';
	close(fd);
	if (bytes_read != 9 || ft_strcmp(header, "/* XPM */"))
		return (0);
	return (1);
}

int	parse_data_status(t_map *map, char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (check_and_fill(map, NO, line + 3));
	if (!ft_strncmp(line, "SO ", 3))
		return (check_and_fill(map, SO, line + 3));
	if (!ft_strncmp(line, "WE ", 3))
		return (check_and_fill(map, WE, line + 3));
	if (!ft_strncmp(line, "EA ", 3))
		return (check_and_fill(map, EA, line + 3));
	if (!ft_strncmp(line, "F ", 2))
		return (check_and_fill(map, F, line + 2));
	if (!ft_strncmp(line, "C ", 2))
		return (check_and_fill(map, C, line + 2));
	return (1);
}

void	discard_remaining_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}
