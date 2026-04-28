/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_extension.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 13:20:14 by pserre-s          #+#    #+#             */
/*   Updated: 2026/04/24 14:25:11 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static char	*is_extension(char *map_name)
{
	char	*extension;

	extension = ft_strrchr(map_name, '.');
	if (!extension)
		return (NULL);
	return (extension);
}

int	is_cub_extension(char *map_name)
{
	char	*extension;

	extension = is_extension(map_name);
	if (!extension)
		return (0);
	if (!ft_strcmp(extension + 1, "cub") && (extension != map_name))
		return (1);
	return (0);
}
