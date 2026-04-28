/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:43:58 by pserre-s          #+#    #+#             */
/*   Updated: 2026/04/24 15:16:41 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "fcntl.h"
# include "mlx.h"
# include "math.h"

typedef struct s_map
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;

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
}	t_data;

// Init structs
void	init_structs(t_data *data);

// Parsing
int	is_cub_extension(char *map_name);
int	parse_map(char *map, t_data *data);

#endif