/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylebee <yanislebee@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 18:30:31 by pserre-s          #+#    #+#             */
/*   Updated: 2026/10/14 18:55:10 by ylebee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

#ifdef BONUS

static int	is_bonus_door(char c)
{
	return (c == 'D');
}

#else

static int	is_bonus_door(char c)
{
	(void)c;
	return (0);
}

#endif

int	map_line_type(char *line)
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
			&& line[i] != '\n' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& !is_bonus_door(line[i]))
			return (0);
		i++;
	}
	return (2);
}
