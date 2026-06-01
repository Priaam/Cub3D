/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <pserre-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:43:28 by pserre-s          #+#    #+#             */
/*   Updated: 2026/06/01 19:06:01 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"
#include "stdio.h"

#include "stdio.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (ft_putstr_fd("Usage: ./cub3d <map.cub>\n", 2), 1);
	init_structs(&data);
	if (!parse_map(av[1], &data))
		return (1);
	int i;
	for (i=0; i < 6; i++)
	{
		printf("%s\n", data.map.data[i]);
	}
	printf("\n");
	int	j;
	for (j=0; j < data.map.height; j++)
	{
		printf("%s", data.map.map_grid[j]);
	}
}

