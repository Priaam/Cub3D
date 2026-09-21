#include "Cub3d.h"

static void	draw_background(t_data *data, int x, t_hit *hit)
{
	int	y;

	y = 0;
	while (y < hit->draw_start)
	{
		ft_put_pixel(&data->img, x, y, data->map.c_color);
		y++;
	}
	y = hit->draw_end + 1;
	while (y < HEIGHT)
	{
		ft_put_pixel(&data->img, x, y, data->map.f_color);
		y++;
	}
}

static void	set_wall_limits(t_hit *hit)
{
	int	line_height;

	line_height = (int)(HEIGHT / hit->perp_wall_dist);
	hit->draw_start = HEIGHT / 2 - line_height / 2;
	hit->draw_end = HEIGHT / 2 + line_height / 2;
	if (hit->draw_start < 0)
		hit->draw_start = 0;
	if (hit->draw_end >= HEIGHT)
		hit->draw_end = HEIGHT - 1;
}

static void	render_column(t_data *data, int x)
{
	t_dda	ray;
	t_hit	hit;
	double	camera_x;

	camera_x = 2.0 * x / (double)WIDTH - 1.0;
	ray.ray_dir_x = data->dir_x + data->plane_x * camera_x;
	ray.ray_dir_y = data->dir_y + data->plane_y * camera_x;
	hit = dda(data, ray);
	set_wall_limits(&hit);
	draw_background(data, x, &hit);
	draw_textured_wall(data, &ray, &hit, x);
}

void	render_3d(t_data *data)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		render_column(data, x);
		x++;
	}
}

int	render(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	update_player(data);
	ft_clear_image(data);
	render_3d(data);
	render_minimap(data);
	draw_player_minimap(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.img, 0, 0);
	return (0);
}
