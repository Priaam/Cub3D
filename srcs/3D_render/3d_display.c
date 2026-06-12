#include "Cub3d.h"
#include "minimap.h"
#include <sys/wait.h>
#include <unistd.h>

#define NB_PROC 4

static void	render_range(t_data *data, int x_start, int x_end)
{
	int		x;
	double	camera_x;
	t_dda	ray;
	t_hit	hit;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		y;

	x = x_start;
	while (x < x_end)
	{
		camera_x = 2.0 * x / (double)WIDTH - 1.0;
		ray.ray_dir_x = data->dir_x + data->plane_x * camera_x;
		ray.ray_dir_y = data->dir_y + data->plane_y * camera_x;
		hit = dda(data, ray);
		line_height = (int)(HEIGHT / hit.perp_wall_dist);
		draw_start = HEIGHT / 2 - line_height / 2;
		draw_end = HEIGHT / 2 + line_height / 2;
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;
		y = 0;
		while (y < draw_start)
			ft_put_pixel(&data->img, x, y++, data->map.c_color);
		while (y <= draw_end)
		{
			if (hit.side == 0)
				ft_put_pixel(&data->img, x, y++, 0x00FF00);
			else
				ft_put_pixel(&data->img, x, y++, 0x007700);
		}
		while (y < HEIGHT)
			ft_put_pixel(&data->img, x, y++, data->map.f_color);
		x++;
	}
}

void	render_3d(t_data *data)
{
	pid_t	pid;
	int		i;
	int		start;
	int		end;
	int		step;

	step = WIDTH / NB_PROC;
	i = 0;

	while (i < NB_PROC)
	{
		start = i * step;
		if (i == NB_PROC - 1)
			end = WIDTH;
		else
			end = start + step;
		pid = fork();
		if (pid == 0)
		{
			render_range(data, start, end);
			exit(0);
		}
		i++;
	}
	while (wait(NULL) > 0);
}