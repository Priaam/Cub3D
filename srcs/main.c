/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylebee <ylebee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 01:31:33 by pserre-s          #+#    #+#             */
/*   Updated: 2026/10/12 17:12:13 by ylebee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (ft_putstr_fd("Usage: ./cub3d <map.cub>\n", 2), 1);
	init_structs(&data);
	if (!parse_map(argv[1], &data))
		return (free_map_data(&data.map), 1);
	if (!init_game(&data))
		return (free_game(&data), 1);
	mlx_mouse_hide(data.mlx_ptr, data.win_ptr);
	mlx_loop_hook(data.mlx_ptr, render, &data);
	mlx_hook(data.win_ptr, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win_ptr, 3, 1L << 1, key_release, &data);
	mlx_hook(data.win_ptr, 17, 0, ft_exit, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
