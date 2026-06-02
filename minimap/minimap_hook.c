/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylebee <ylebee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 16:57:46 by ylebee            #+#    #+#             */
/*   Updated: 2026/06/02 17:10:58 by ylebee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "minimap.h"

 int ft_exit(void *param)
{
	t_mlx *data = (t_mlx *)param;

	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(0);
	return (0);
}

int key_press(int keycode, void *param)
{
	t_mlx *data = (t_mlx *)param;

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
	t_mlx *data = (t_mlx *)param;

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

void ft_clear_image(t_mlx *data)
{
    ft_memset(
        data->img.addr,
        0,
        HEIGHT * data->img.line_len
    );
}

int loop(void *param)
{
	t_mlx *data = (t_mlx *)param;
	double speed = 0.005;
	double new_x;
	double new_y;

	if (data->key_left)
		data->angle -= 0.005;
	if (data->key_right)
		data->angle += 0.005;
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
	if (data->map_grid[(int)new_y][(int)new_x] != '1')
	{
		data->player_x = new_x;
		data->player_y = new_y;
	}
	ft_clear_image(data);
	render(data);

	return (0);
}