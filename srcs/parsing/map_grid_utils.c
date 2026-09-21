/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22  by pserre-s          #+#    #+#             */
/*   Updated: 2026/09/22  by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static int	map_line_type(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
		i++;
	if (!line[i])
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' '
			&& line[i] != '\n' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (2);
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

int	collect_map_lines(int fd, t_list **map_list)
{
	int		map_ended;
	char	*line;

	map_ended = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (map_line_type(line) == 1)
		{
			if (*map_list)
				map_ended = 1;
			free(line);
		}
		else if (map_ended || map_line_type(line) == 0)
			return (free(line), ft_lstclear(map_list, &free), 0);
		else
		{
			if (!add_map_line(map_list, line))
				return (free(line), ft_lstclear(map_list, &free), 0);
		}
		line = get_next_line(fd);
	}
	return (ft_lstsize(*map_list));
}

static void	fill_map_row(char *dest, char *src, int width)
{
	int	x;

	x = 0;
	while (x < width)
	{
		if (src && *src && *src != '\n')
			dest[x] = *src++;
		else
			dest[x] = ' ';
		x++;
	}
	dest[x] = '\0';
}

int	build_map_grid(t_map *map, t_list *map_list, int line_count)
{
	int		i;
	t_list	*node;

	map->map_grid = ft_calloc(line_count + 1, sizeof(char *));
	if (!map->map_grid)
		return (ft_lstclear(&map_list, &free), 0);
	map->width = find_biggest_lst(map_list);
	i = 0;
	node = map_list;
	while (node)
	{
		map->map_grid[i] = malloc((map->width + 1) * sizeof(char));
		if (!map->map_grid[i])
		{
			ft_free_split(map->map_grid);
			ft_lstclear(&map_list, &free);
			return (0);
		}
		fill_map_row(map->map_grid[i++], node->content, map->width);
		node = node->next;
	}
	map->height = line_count;
	ft_lstclear(&map_list, &free);
	return (1);
}
