#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "fcntl.h"
# include "mlx.h"
# include "math.h"

# define TILE_SIZE 400
# define WIDTH 1920
# define HEIGHT 1080
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

typedef struct s_texture
{
	void	*img;
	char	*pixels;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef enum e_type
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	DATA_COUNT
}	t_type;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_map
{
	char	*data[DATA_COUNT];
	int		f_color;
	int		c_color;
	char	**map_grid;
	int		height;
	int		width;
}	t_map;

typedef struct s_data
{
	t_map		map;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_texture	textures[4];
	int			coef_minimap;
	int			coef_player;
	double		player_x;
	double		player_y;
	double		plane_x;
	double		plane_y;
	char		orientation;
	double		dir_x;
	double		dir_y;
	int			key_w;
	int			key_a;
	int			key_s;
	int			key_d;
	int			key_left;
	int			key_right;
}	t_data;

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
	double	perp_wall_dist;
	int		map_x;
	int		map_y;
	int		side;
	int		draw_start;
	int		draw_end;
}	t_hit;

typedef struct s_tex_column
{
	int		x;
	int		tex_x;
	int		draw_start;
	int		draw_end;
	double	step;
	double	tex_pos;
}	t_tex_column;

void	init_structs(t_data *data);
int		init_game(t_data *data);
int		init_textures(t_data *data);
void	free_textures(t_data *data);

int		check_extension(char *name, char *extension);
int		parse_map(char *map, t_data *data);
int		fill_map_data(int fd, t_map *map);
int		add_map_line(t_list **map_list, char *line);
int		check_and_fill(t_map *map, t_type type, char *value);
int		parse_data_status(t_map *map, char *line);
void	discard_remaining_lines(int fd);
int		check_xpm_header(char *path);
int		fill_map_grid(int fd, t_map *map);
int		collect_map_lines(int fd, t_list **map_list);
int		build_map_grid(t_map *map, t_list *map_list, int line_count);
int		is_valid_texture(t_map *map);
int		flood_fill(t_data *data);
int		find_map_player(char **map_copy, int *player_x, int *player_y);
void	free_map_data(t_map *map);

void	ft_put_pixel(t_img *img, int x, int y, int color);
int		find_biggest(char **map_grid);
void	ft_clear_image(t_data *data);

void	rotate_camera(t_data *data, double angle);
int		update_player(t_data *data);
int		is_walkable(t_data *data, double x, double y);

int		render(void *param);
void	render_3d(t_data *data);
void	draw_textured_wall(t_data *data, t_dda *ray, t_hit *hit, int x);
t_hit	dda(t_data *data, t_dda ray);
void	render_minimap(t_data *data);
void	draw_player_minimap(t_data *data);

int		key_press(int keycode, void *param);
int		key_release(int keycode, void *param);
int		ft_exit(void *param);

#endif