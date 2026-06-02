/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 17:20:22 by ylebee            #+#    #+#             */
/*   Updated: 2026/06/02 20:21:22 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H
#include "../../libs/minilibx-linux/mlx.h"
//#include "../../libs/Libft/include/libft.h"
#include <math.h>
#include <stdlib.h>

# define M_PI 3.14159265358979323846
#define WIDTH 1920
#define HEIGHT 1080
#define TILE_SIZE 500

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_ESC 65307

typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
}   t_img;

typedef struct s_mlx
{
    void    *mlx;
    void    *win;
    t_img   img;
    char    **map_grid;
	int		coef_minimap;
	int		coef_player;
    double  player_x;
    double  player_y;
    double  angle;
	double 	dir_x;
	double	dir_y;
	int		key_w;
	int		key_a;
	int		key_s;
	int		key_d;
	int		key_left;
	int		key_right;
}   t_mlx;

typedef struct s_dda
{
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
}	t_dda;

typedef struct s_hit
{
	double	delta_dist_x;
	double	delta_dist_y;
	int		map_x;
	int		map_y;
	int		hit;
	int		side;
}	t_hit;


int	render(void *param);
int	find_biggest(char **map_grid);
void	ft_swap(char *a, char *b);
void	ft_put_pixel(t_img *img, int x, int y, int color);
int	ft_strlen(char *str);
int	ft_exit(void *param);
void ft_render_and_display(t_mlx *data);
int	ft_handle_input(int keycode, void *data);
char	*ft_strdup(char *str);
int key_press(int keycode, void *param);
int key_release(int keycode, void *param);
int loop(void *param);
int ft_exit(void *param);
t_hit dda(t_mlx *data, t_dda dda_copy);
#endif