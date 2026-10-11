/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   textures.c                                        :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/10/09 18:01:37 by username         #+#    #+#              */
/*   Updated: 2026/10/11 20:33:37 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static int	load_texture(t_data *data, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(data->mlx_ptr, path, &texture->width,
		&texture->height);
	if (!texture->img)
		return (0);
	texture->pixels = mlx_get_data_addr(texture->img, &texture->bpp,
		&texture->line_len, &texture->endian);
	return (1);
}

#ifdef BONUS

int	load_bonus_textures(t_data *data)
{
	if (data->map.data[DOOR])
	{
		if (!load_texture(data, &data->textures[DOOR], data->map.data[DOOR]))
			return (0);
	}
	return (1);
}
#else

int	load_bonus_textures(t_data *data)
{
	(void) data;
	return (1);
}
#endif

int	init_textures(t_data *data)
{
	if (!load_texture(data, &data->textures[NO], data->map.data[NO]))
		return (0);
	if (!load_texture(data, &data->textures[SO], data->map.data[SO]))
		return (0);
	if (!load_texture(data, &data->textures[WE], data->map.data[WE]))
		return (0);
	if (!load_texture(data, &data->textures[EA], data->map.data[EA]))
		return (0);
	if (!load_bonus_textures(data))
		return (0);
	return (1);
}

void	free_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (data->textures[i].img)
			mlx_destroy_image(data->mlx_ptr, data->textures[i].img);
		i++;
	}
}
