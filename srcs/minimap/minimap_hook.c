#include "Cub3d.h"

int	ft_exit(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	free_textures(data);
	if (data->img.img)
		mlx_destroy_image(data->mlx_ptr, data->img.img);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free_map_data(&data->map);
	exit(0);
	return (0);
}

int	key_press(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == KEY_W)
		data->key_w = 1;
	if (keycode == KEY_S)
		data->key_s = 1;
	if (keycode == KEY_A)
		data->key_a = 1;
	if (keycode == KEY_D)
		data->key_d = 1;
	if (keycode == KEY_LEFT)
		data->key_left = 1;
	if (keycode == KEY_RIGHT)
		data->key_right = 1;
	if (keycode == KEY_ESC)
		ft_exit(data);
	return (0);
}

int	key_release(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == KEY_W)
		data->key_w = 0;
	if (keycode == KEY_S)
		data->key_s = 0;
	if (keycode == KEY_A)
		data->key_a = 0;
	if (keycode == KEY_D)
		data->key_d = 0;
	if (keycode == KEY_LEFT)
		data->key_left = 0;
	if (keycode == KEY_RIGHT)
		data->key_right = 0;
	return (0);
}
