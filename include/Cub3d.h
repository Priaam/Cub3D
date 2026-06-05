/* include/Cub3d.h */
#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "fcntl.h"
# include "mlx.h"
# include "math.h"

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
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
}   t_img;

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
	struct s_map	map;
	void			*mlx_ptr;
	void			*win_ptr;
	t_img   		img;
	int				coef_minimap;
	int				coef_player;
    double  		player_x;
    double  		player_y;
    double  		angle;
	double 			dir_x;
	double			dir_y;
	int				key_w;
	int				key_a;
	int				key_s;
	int				key_d;
	int				key_left;
	int				key_right;
}	t_data;

// Init structs
void	init_struct_parser(t_data *data);
void	ft_init_data_minimap(t_data *data);

// Parsing
int		is_cub_extension(char *map_name);
int		parse_map(char *map, t_data *data);
int		fill_map_data(int fd, t_map *map);
int		fill_map_grid(int fd, t_map *map);

# include "minimap.h"

#endif