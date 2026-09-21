#include "Cub3d.h"

static void	set_direction(t_data *data)
{
	if (data->orientation == 'N')
	{
		data->dir_y = -1.0;
		data->plane_x = 0.66;
	}
	else if (data->orientation == 'S')
	{
		data->dir_y = 1.0;
		data->plane_x = -0.66;
	}
	else if (data->orientation == 'E')
	{
		data->dir_x = 1.0;
		data->plane_y = 0.66;
	}
	else
	{
		data->dir_x = -1.0;
		data->plane_y = -0.66;
	}
}

static int	find_player(t_data *data)
{
	int	x;
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (ft_strchr("NSEW", data->map.map_grid[y][x]))
			{
				data->orientation = data->map.map_grid[y][x];
				data->player_x = x + 0.5;
				data->player_y = y + 0.5;
				data->map.map_grid[y][x] = '0';
				count++;
			}
			x++;
		}
		y++;
	}
	return (count == 1);
}

int	init_game(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (0);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	data->img.img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->win_ptr || !data->img.img)
		return (0);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	if (!find_player(data) || !init_textures(data))
		return (0);
	set_direction(data);
	data->coef_minimap = TILE_SIZE / find_biggest(data->map.map_grid);
	if (data->coef_minimap < 1)
		data->coef_minimap = 1;
	data->coef_player = data->coef_minimap / 2;
	return (1);
}
