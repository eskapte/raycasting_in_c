/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhawick <lhawick@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 20:47:03 by lhawick           #+#    #+#             */
/*   Updated: 2021/04/13 20:47:03 by lhawick          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addr + (y * win->l_len + x * (win->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel(t_game **game, int x, int y, int i)
{
	char	*dst;

	dst = (*game)->txts[i].addr + (y * (*game)->txts[i].l_len
			+ x * ((*game)->txts[i].bpp / 8));
	return (*(unsigned int *)dst);
}

int	get_side(t_ray *ray)
{
	static int	side;

	if ((int)ray->x == ray->old_x && ray->old_y - (int)ray->y > 0)
		side = 0;
	else if ((int)ray->x == ray->old_x && ray->old_y - (int)ray->y < 0)
		side = 1;
	else if ((int)ray->y == ray->old_y && ray->old_x - (int)ray->x > 0)
		side = 2;
	else if ((int)ray->y == ray->old_y && ray->old_x - (int)ray->x < 0)
		side = 3;
	return (side);
}

static	int	draw_wall(t_game *game, int y, t_line *line, t_ray *ray)
{
	int	side;
	int	color;

	while (y < line->wall + line->sky && y < HEIGHT - 1)
	{
		side = get_side(ray);
		if (side < 2)
			color = get_pixel(&game, ray->hitx * SCALE - 1, SCALE * line->j++
					/ line->wall + 1, side);
		else
			color = get_pixel(&game, ray->hity * SCALE - 1, SCALE * line->j++
					/ line->wall + 1, side);
		pixel_put(game->win, line->x, y++, color);
	}
	return (y);
}

void	draw_line(t_game *game, float dst, int x, t_ray *ray)
{
	int		y;
	t_line	line;

	line.wall = HEIGHT / dst * SCALE;
	line.sky = HEIGHT / 2 - (line.wall / 2);
	line.j = 0;
	line.x = x;
	y = 0;
	if (line.sky < 0)
		line.j = fabs(line.sky);
	while (y < line.sky && y < HEIGHT - 1)
		pixel_put(game->win, x, y++, int_to_hex(0, 186, 255));
	y = draw_wall(game, y, &line, ray);
	while (y < HEIGHT - 1)
		pixel_put(game->win, x, y++, int_to_hex(255, 186, 100));
}
