/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylebee <ylebee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 15:40:18 by ylebee            #+#    #+#             */
/*   Updated: 2026/06/01 17:00:46 by ylebee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	ft_swap(char *a, char *b)
{
	char temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
void	ft_put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

int	find_biggest(char **map_grid)
{
	int	i;
	int temp;
	int biggest;

	i = 0;
	temp = 0;
	biggest = 0;
	while (map_grid[i])
	{
		temp = ft_strlen(map_grid[i]);
		if (temp > biggest)
			biggest = temp;
		i++;
	}
	if (i > biggest)
		return (i);
	return (biggest);
}

char	*ft_strdup(char *str)
{
	char	*dup;
	size_t	i;

	if (!str)
		return (NULL);
	dup = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	i = 0;
	if (!dup)
		return (NULL);
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
