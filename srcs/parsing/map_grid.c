/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 20:04:24 by pserre-s          #+#    #+#             */
/*   Updated: 2026/10/11 18:30:07 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	get_max_width_arr(char **map_grid)
{
	int	i;
	int	biggest;
	int	len;

	i = 0;
	biggest = 0;
	while (map_grid[i])
	{
		len = ft_strlen(map_grid[i]);
		if (len > biggest)
			biggest = len;
		i++;
	}
	if (i > biggest)
		biggest = i;
	return (biggest);
}

int	add_map_line(t_list **map_list, char *line)
{
	t_list	*node;

	node = ft_lstnew(line);
	if (!node)
		return (0);
	ft_lstadd_back(map_list, node);
	return (1);
}

int	fill_map_grid(int fd, t_map *map, char *first_line)
{
	t_list	*map_list;
	int		line_count;

	map_list = NULL;
	line_count = collect_map_lines(fd, &map_list, first_line);
	if (line_count == 0)
		return (0);
	return (build_map_grid(map, map_list, line_count));
}
