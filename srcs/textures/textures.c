#include "Cub3d.h"

static int	load_texture(t_data *data, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(data->mlx_ptr, path,
			&texture->width, &texture->height);
	if (!texture->img)
		return (0);
	texture->pixels = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_len, &texture->endian);
	return (1);
}

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
	return (1);
}

void	free_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->textures[i].img)
			mlx_destroy_image(data->mlx_ptr, data->textures[i].img);
		i++;
	}
}
