/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:43:28 by pserre-s          #+#    #+#             */
/*   Updated: 2026/09/12 14:07:55 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

#include "stdio.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (ft_putstr_fd("Usage: ./cub3d <map.cub>\n", 2), 1);
	init_struct_parser(&data);
	if (!parse_map(av[1], &data))
		return (1);
	int i;
	for (i=0; i < 6; i++)
	{
		printf("%s\n", data.map.data[i]);
	}
	printf("\n");
	for (i=0; i < data.map.height; i++)
	{
		printf("%s\n", data.map.map_grid[i]);
	}
	printf("\n\nf=%x | c=%x\n", data.map.f_color, data.map.c_color);
	printf("\n\nheight = %d | width = %d\n", data.map.height, data.map.width);
	launch_minimap(&data);
}

