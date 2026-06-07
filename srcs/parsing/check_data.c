/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 16:10:32 by pserre-s          #+#    #+#             */
/*   Updated: 2026/06/07 17:41:52 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	is_valid_texture(t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	while (i < DATA_COUNT)
	{
		if (i == NO || i == SO || i == WE || i == EA)
		{
			if (!check_extension(data->map.data[i], ".xpm"))
				return (1);
			fd = open(data->map.data[i], O_RDONLY);
			if (fd < 0)
				return (1);
			close(fd);
		}
		// else if (i == F || data->map.data[i] == C);
		// {
			
		// }
		i++;
	}
	return (0);
}