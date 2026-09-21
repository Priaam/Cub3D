#include "Cub3d.h"

static int	is_in_circle(int x, int y, int radius)
{
	int	dx;
	int	dy;

	dx = x - radius;
	dy = y - radius;
	return (dx * dx + dy * dy <= radius * radius);
}

static char	safe_get_tile(t_data *data, int x, int y)
{
	if (x < 0 || y < 0)
		return (' ');
	if (x >= data->map.width || y >= data->map.height)
		return (' ');
	return (data->map.map_grid[y][x]);
}

static void	draw_minimap_pixel(t_data *data, int x, int y, int radius)
{
	int		map_x;
	int		map_y;
	char	tile;

	map_x = (int)data->player_x
		+ (x - radius) / data->coef_minimap;
	map_y = (int)data->player_y
		+ (y - radius) / data->coef_minimap;
	tile = safe_get_tile(data, map_x, map_y);
	if (tile == '1')
		ft_put_pixel(&data->img, x, y, 0xffffff);
	else if (tile != ' ')
		ft_put_pixel(&data->img, x, y, 0x777777);
}

void	render_minimap(t_data *data)
{
	int	x;
	int	y;
	int	radius;

	radius = 90;
	y = 0;
	while (y < radius * 2)
	{
		x = 0;
		while (x < radius * 2)
		{
			if (is_in_circle(x, y, radius))
				draw_minimap_pixel(data, x, y, radius);
			x++;
		}
		y++;
	}
}

void	draw_player_minimap(t_data *data)
{
	int	i;
	int	j;

	i = -4;
	while (i <= 4)
	{
		j = -4;
		while (j <= 4)
		{
			ft_put_pixel(&data->img, 90 + j, 90 + i, 0xff2c2c);
			j++;
		}
		i++;
	}
}
