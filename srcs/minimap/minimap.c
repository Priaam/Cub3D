/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 01:07:37 by pserre-s          #+#    #+#             */
/*   Updated: 2026/09/22 01:07:38 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	find_biggest(char **map_grid)
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
