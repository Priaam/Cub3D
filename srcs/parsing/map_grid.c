/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 20:04:24 by pserre-s          #+#    #+#             */
/*   Updated: 2026/09/22 01:40:37 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	add_map_line(t_list **map_list, char *line)
{
	t_list	*node;

	node = ft_lstnew(line);
	if (!node)
		return (0);
	ft_lstadd_back(map_list, node);
	return (1);
}

int	fill_map_grid(int fd, t_map *map)
{
	t_list	*map_list;
	int		line_count;

	map_list = NULL;
	line_count = collect_map_lines(fd, &map_list);
	if (line_count == 0)
		return (0);
	return (build_map_grid(map, map_list, line_count));
}
