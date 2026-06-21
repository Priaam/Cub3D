/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <pserre-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 16:55:12 by pserre-s          #+#    #+#             */
/*   Updated: 2026/06/21 17:56:40 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Cub3d.h>

static char	**copy_map(t_map *map)
{
	int		i;
	char	**copy;

	i = 0;
	copy = malloc((map->height + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	while (i < map->height)
	{
		copy[i] = ft_strdup(map->map_grid[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	free_map_copy(char **map_copy)
{
	int	i;

	i = 0;
	if (!map_copy)
		return ;
	while (map_copy[i])
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}

static int	check_flood_fill(char **map_copy, int x, int y, t_map *map)
{
	if (y < 0 || y >= map->height)
		return (0);
	if (x < 0 || x >= (int)ft_strlen(map_copy[y]))
		return (0);
	if (map_copy[y][x] == '1' || map_copy[y][x] == 'V')
		return (1);
	if (map_copy[y][x] == ' ' || map_copy[y][x] == '\0'
		|| map_copy[y][x] == '\n')
		return (0);
	map_copy[y][x] = 'V';
	if (!check_flood_fill(map_copy, x + 1, y, map)
		|| !check_flood_fill(map_copy, x - 1, y, map)
		|| !check_flood_fill(map_copy, x, y + 1, map)
		|| !check_flood_fill(map_copy, x, y - 1, map))
		return (0);
	return (1);
}

static int	find_player(char **map_copy, int *player_x, int *player_y)
{
	*player_y = 0;
	while (map_copy[*player_y])
	{
		*player_x = 0;
		while (map_copy[*player_y][*player_x])
		{
			if (map_copy[*player_y][*player_x] == 'N'
				|| map_copy[*player_y][*player_x] == 'S'
				|| map_copy[*player_y][*player_x] == 'E'
				|| map_copy[*player_y][*player_x] == 'W'
				|| map_copy[*player_y][*player_x] == 'P')
				return (1);
			(*player_x)++;
		}
		(*player_y)++;
	}
	return (0);
}

int	flood_fill(t_data *data)
{
	char	**map_copy;
	int		start_x;
	int		start_y;

	if (!find_player(data->map.map_grid, &start_x, &start_y))
		return (0);

	map_copy = copy_map(&data->map);
	if (!map_copy)
		return (0);

	if (!check_flood_fill(map_copy, start_x, start_y, &data->map))
	{
		free_map_copy(map_copy);
		return (0);
	}
	free_map_copy(map_copy);
	return (1);
}
