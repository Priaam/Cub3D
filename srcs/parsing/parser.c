/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <pserre-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:55:10 by pserre-s          #+#    #+#             */
/*   Updated: 2026/06/01 19:04:57 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static int	is_map_part(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0' || line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			return (1);
		i++;
	}
	return (0);
}

int	fill_map_grid(int fd, t_map *map)
{
	int			i;
	int			map_started;
	int			line_count;
	char		*line;
	t_list		*map_list;
	t_list		*node;
	t_list		*tmp;

	i = 0;
	map_started = 0;
	line_count = 0;
	map_list = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (map_started == 1 && !is_map_part(line))
		{
			free(line);
			ft_lstclear(&map_list, &free);
			return (0);
		}
		if (map_started == 1 || is_map_part(line))
		{
			map_started = 1;
			node = ft_lstnew((char *)line);
			ft_lstadd_back(&map_list, node);
			line_count++;
		}
		else
			free(line);
		line = get_next_line(fd);
	}
	map->height = line_count;
	map->map_grid = malloc((line_count + 1) * sizeof(char *));
	if (!map->map_grid)
	{
		ft_lstclear(&map_list, &free);
		return (0);
	}
	node = map_list;
	while (node)
	{
		map->map_grid[i] = node->content;
		node = node->next;
		i++;
	}
	map->map_grid[i] = NULL;
	while (map_list)
	{
		tmp = map_list;
		map_list = map_list->next;
		free(tmp);
	}
	return (1);
}

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
	int     status;
	int		count_elements;

	count_elements = 0;
	line = get_next_line(fd);
	while (line)
	{
		status = 0;
		trimmed_line = ft_strtrim(line, " \t\n");
		if (trimmed_line && trimmed_line[0])
		{
			if (!ft_strncmp(trimmed_line, "NO ", 3))
				status = check_and_fill(map, NO, trimmed_line + 3);
			else if (!ft_strncmp(trimmed_line, "SO ", 3))
				status = check_and_fill(map, SO, trimmed_line + 3);
			else if (!ft_strncmp(trimmed_line, "WE ", 3))
				status = check_and_fill(map, WE, trimmed_line + 3);
			else if (!ft_strncmp(trimmed_line, "EA ", 3))
				status = check_and_fill(map, EA, trimmed_line + 3);
			else if (!ft_strncmp(trimmed_line, "F ", 2))
				status = check_and_fill(map, F, trimmed_line + 2);
			else if (!ft_strncmp(trimmed_line, "C ", 2))
				status = check_and_fill(map, C, trimmed_line + 2);
			if (status == 0)
				count_elements++;
			if (count_elements == 6)
			{
				free(line);
				free(trimmed_line);
				return (fill_map_grid(fd, map));
			}
			if (status == 1)
			{
				free(line);
				free(trimmed_line);
				line = get_next_line(fd);
				while (line)
				{
					free(line);
					line = get_next_line(fd);
				}
				return (0);
			}
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
		return (ft_putstr_fd("Error: fill map failed\n", 2), 0);
	}
	close(fd);
	return (1);
}
