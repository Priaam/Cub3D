/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylebee <yanislebee@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 18:03:13 by ylebee            #+#    #+#             */
/*   Updated: 2026/10/14 18:17:47 by ylebee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	player_move_coordinates(t_data *data, double *move_x, double *move_y)
{
	if (data->key_w)
	{
		*move_x += data->dir_x;
		*move_y += data->dir_y;
	}
	if (data->key_s)
	{
		*move_x -= data->dir_x;
		*move_y -= data->dir_y;
	}
	if (data->key_d)
	{
		*move_x -= data->dir_y;
		*move_y += data->dir_x;
	}
	if (data->key_a)
	{
		*move_x += data->dir_y;
		*move_y -= data->dir_x;
	}
}
