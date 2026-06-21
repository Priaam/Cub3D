/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <pserre-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:55:10 by pserre-s          #+#    #+#             */
/*   Updated: 2026/06/21 17:38:42 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	parse_map(char *map, t_data *data)
{
	int	fd;

	if (!check_extension(map, ".cub"))
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
	if (!flood_fill(data))
		return (ft_putstr_fd("Error: the map is not closed\n", 2), 0);
	return (1);
}
