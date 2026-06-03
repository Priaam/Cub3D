/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 17:33:21 by ylebee            #+#    #+#             */
/*   Updated: 2026/06/03 15:42:32 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

t_dda   init_dda(t_data *data, t_dda dda_copy) 
{
    t_dda   dda;
 
    dda = dda_copy;
    dda.map_x = (int)data->player_x;
    dda.map_y = (int)data->player_y;
    if (dda.ray_dir_x < 0)
        dda.step_x = -1;
    else
        dda.step_x = 1;
    if (dda.ray_dir_y < 0)
        dda.step_y = -1;
    else
        dda.step_y = 1;
    dda.delta_dist_x = fabs(1 / data->dir_x);
    dda.delta_dist_y = fabs(1 / data->dir_y);
    if (data->dir_x < 0)
        dda.side_dist_x = (data->player_x - dda.map_x) * dda.delta_dist_x;
    else
        dda.side_dist_x = (dda.map_x + 1 - data->player_x) * dda.delta_dist_x;
    if (data->dir_y < 0)
        dda.side_dist_y = (data->player_y - dda.map_y) * dda.delta_dist_y;
    else
        dda.side_dist_y = (dda.map_y + 1 - data->player_y) * dda.delta_dist_y;
    return (dda);
}

t_hit dda(t_data *data, t_dda dda_copy)
{
    t_dda   dda;
    t_hit     hit;
    int     side;

    dda = init_dda(data, dda_copy);
    hit.hit = 0;
    while (hit.hit == 0)
    {
        if (dda.side_dist_x < dda.side_dist_y)
        {
            dda.side_dist_x += dda.delta_dist_x;
            dda.map_x += dda.step_x;
            side = 0;
        }
        else
        {
            dda.side_dist_y += dda.delta_dist_y;
            dda.map_y += dda.step_y;
            side = 1;
        }
        if (data->map.map_grid[dda.map_y][dda.map_x] == '1')
            hit.hit = 1;
    }
    hit.delta_dist_x = dda.delta_dist_x;
    hit.delta_dist_x = dda.delta_dist_y;
    hit.map_x = dda.map_x;
    hit.map_y = dda.map_y;
    hit.side = side;
    return (hit);
}