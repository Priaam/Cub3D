/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 20:04:24 by pserre-s          #+#    #+#             */
/*   Updated: 2026/09/12 16:57:44 by pserre-s         ###   ########.fr       */
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

static int	find_biggest_lst(t_list *map_list)
{
	int		max_len;
	int		len;
	char	*str;
	t_list	*node;

	max_len = 0;
	node = map_list;
	while (node)
	{
		str = (char *)node->content;
		len = ft_strlen(str);
		if (len > 0 && str[len - 1] == '\n')
			len--;
		if (len > max_len)
			max_len = len;
		node = node->next;
	}
	return (max_len);
}

static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	fill_map_grid(int fd, t_map *map)
{
	int			i;
	int			x;
	int			map_started;
	int			map_ended;
	int			line_count;
	char		*line;
	char		*str;
	t_list		*map_list;
	t_list		*node;
	t_list		*tmp;

	i = 0;
	map_started = 0;
	map_ended = 0;
	line_count = 0;
	map_list = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (is_empty_line(line))
		{
			if (map_started == 1)
				map_ended = 1;
			free(line);
		}
		else
		{
			if (map_ended == 1 || !is_map_part(line))
			{
				free(line);
				ft_lstclear(&map_list, &free);
				return (0);
			}
			map_started = 1;
			node = ft_lstnew((char *)line);
			ft_lstadd_back(&map_list, node);
			line_count++;
		}
		line = get_next_line(fd);
	}
	map->map_grid = malloc((line_count + 1) * sizeof(char *));
	if (!map->map_grid)
	{
		ft_lstclear(&map_list, &free);
		return (0);
	}
	map->width = find_biggest_lst(map_list);
	i = 0;
	node = map_list;
	while (node)
	{
		map->map_grid[i] = malloc((map->width + 1) * sizeof(char));
		if (!map->map_grid[i])
		{
			while (i > 0)
				free(map->map_grid[--i]);
			free(map->map_grid);
			ft_lstclear(&map_list, &free);
			return (0);
		}
		x = 0;
		str = (char *)node->content;
		while (x < map->width)
		{
			if (str && *str && *str != '\n')
			{
				map->map_grid[i][x] = *str;
				str++;
			}
			else
				map->map_grid[i][x] = ' ';
			x++;
		}
		map->map_grid[i][x] = '\0';
		free(node->content);
		node = node->next;
		i++;
	}
	map->map_grid[i] = NULL;
	map->height = line_count;
	while (map_list)
	{
		tmp = map_list;
		map_list = map_list->next;
		free(tmp);
	}
	return (1);
}
