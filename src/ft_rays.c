/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhawick <lhawick@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 20:15:42 by lhawick           #+#    #+#             */
/*   Updated: 2021/04/13 20:15:42 by lhawick          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	cast(t_game *game, t_ray *ray, float dir)
{
	ray->x = game->plr->x;
	ray->y = game->plr->y;
	ray->delta_x = cos(dir) / 5;
	ray->delta_y = sin(dir) / 5;
	while (game->map[(int)(ray->y / SCALE)][(int)(ray->x / SCALE)] != '1')
	{
		ray->old_x = (int)ray->x;
		ray->old_y = (int)ray->y;
		ray->x += ray->delta_x;
		ray->y += ray->delta_y;
	}
	ray->hitx = (int)(ray->x / SCALE) - ray->x / SCALE;
	ray->hity = (int)(ray->y / SCALE) - ray->y / SCALE;
}

void	ray_cast(t_game *game)
{
	t_ray	ray;
	float	start;
	float	end;
	int		x;

	ray.dir = game->plr->dir;
	start = ray.dir - (M_PI_2 / 3);
	end = ray.dir + (M_PI_2 / 3);
	x = 0;
	while (start <= end)
	{
		cast(game, &ray, start);
		draw_line(game, get_d(game->plr->x, game->plr->y, ray.x, ray.y)
			* cos(ray.dir - start), x++, &ray);
		start += (M_PI_2 / 1.5) / WIDTH;
	}
}