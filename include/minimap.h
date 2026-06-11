#ifndef MINIMAP_H
# define MINIMAP_H

#include <math.h>
#include <stdlib.h>

# define M_PI 3.14159265358979323846
#define TILE_SIZE 400

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_ESC 65307

typedef struct s_data t_data;

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
	double	perp_wall_dist;
	int		map_x;
	int		map_y;
	int		hit;
	int		side;
}	t_hit;


int		render(void *param);
int		find_biggest(char **map_grid);
void	ft_swap(char *a, char *b);
void	ft_put_pixel(t_img *img, int x, int y, int color);
int		ft_exit(void *param);
void	ft_render_and_display(t_data *data);
int		ft_handle_input(int keycode, void *data);
int 	key_press(int keycode, void *param);
int 	key_release(int keycode, void *param);
int 	loop(void *param);
t_hit	dda(t_data *data, t_dda dda_copy);

int	launch_minimap(t_data *data);

#endif