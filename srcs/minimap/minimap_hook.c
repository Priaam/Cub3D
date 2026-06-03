/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 16:57:46 by ylebee            #+#    #+#             */
/*   Updated: 2026/06/03 16:11:54 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "Cub3d.h"

 int ft_exit(void *param)
{
	t_data *data = (t_data *)param;

	if (data->img.img)
		mlx_destroy_image(data->mlx_ptr, data->img.img);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	exit(0);
	return (0);
}

int key_press(int keycode, void *param)
{
	t_data *data = (t_data *)param;

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

int key_release(int keycode, void *param)
{
	t_data *data = (t_data *)param;

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

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

void ft_clear_image(t_data *data)
{
    ft_memset(
        data->img.addr,
        0,
        HEIGHT * data->img.line_len
    );
}

int loop(void *param)
{
	t_data	*data;
	double	speed;
	double	new_x;
	double	new_y;

	data = (t_data *)param;
	speed = 0.05;
	
	if (data->key_left)
		data->angle -= 0.05;
	if (data->key_right)
		data->angle += 0.05;
	if (data->angle < 0)
		data->angle += 2 * M_PI;
	if (data->angle > 2 * M_PI)
		data->angle -= 2 * M_PI;
	
	data->dir_x = cos(data->angle);
	data->dir_y = sin(data->angle);
	
	new_x = data->player_x;
	new_y = data->player_y;

	if (data->key_w)
	{
		new_x += data->dir_x * speed;
		new_y += data->dir_y * speed;
	}
	if (data->key_s)
	{
		new_x -= data->dir_x * speed;
		new_y -= data->dir_y * speed;
	}
	if (data->key_d)
	{
		new_x += -data->dir_y * speed;
		new_y +=  data->dir_x * speed;
	}
	if (data->key_a)
	{
		new_x -= -data->dir_y * speed;
		new_y -=  data->dir_x * speed;
	}
	if (new_y >= 0 && new_x >= 0)
	{

		if (data->map.map_grid[(int)new_y] != NULL)
		{
			if ((int)new_x < (int)ft_strlen(data->map.map_grid[(int)new_y]))
			{
				if (data->map.map_grid[(int)new_y][(int)new_x] != '1')
				{
					data->player_x = new_x;
					data->player_y = new_y;
				}
			}
		}
	}
	ft_clear_image(data);
	render(data);

	return (0);
}