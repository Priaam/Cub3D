/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 20:04:24 by pserre-s          #+#    #+#             */
/*   Updated: 2026/09/12 13:25:41 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static int	is_map_part(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' 
			&& line[i] != ' ' && line[i] != '\n'
			&& line[i] != 'N' && line[i] != 'S' 
			&& line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
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
	map->height = line_count;
	map->width = ft_strlen(map->map_grid[0]);
	while (map_list)
	{
		tmp = map_list;
		map_list = map_list->next;
		free(tmp);
	}
	return (1);
}
