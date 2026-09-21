#include "Cub3d.h"

void	ft_put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = img->addr + y * img->line_len + x * (img->bpp / 8);
	*(unsigned int *)pixel = color;
}

void	ft_clear_image(t_data *data)
{
	ft_bzero(data->img.addr, HEIGHT * data->img.line_len);
}
