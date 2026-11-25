/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylebee <ylebee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:55:10 by pserre-s          #+#    #+#             */
/*   Updated: 2026/11/23 15:04:34 by ylebee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	parse_map(char *map, t_data *data)
{
	int	fd;

	if (!check_extension(map, ".cub"))
		return (ft_putstr_fd("Error\nInvalid extension\n", 2), 0);
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nFailed to open the map\n", 2), 0);
	if (!fill_map_data(fd, &data->map))
	{
		close(fd);
		return (ft_putstr_fd("Error\nFill map failed\n", 2), 0);
	}
	close(fd);
	if (!flood_fill(data))
		return (ft_putstr_fd("Error\nThe map is not closed\n", 2), 0);
	return (1);
}
