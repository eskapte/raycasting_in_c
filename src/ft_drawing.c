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

static void	pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addr + (y * win->l_len + x * (win->bpp / 8));
	*(unsigned int *)dst = color;
}

static	int	get_pixel(t_game **game, int x, int y, int i)
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

void	draw_line(t_game *game, float dst, int x, t_ray *ray)
{
	int		y;
	float	line;
	float	sky;
	int		j;
	int		color;
	int		side;

	line = HEIGHT / dst * SCALE;
	sky = HEIGHT / 2 - (line / 2);
	y = 0;
	j = 0;
	if (sky < 0)
		j = fabs(sky);
	while (y < sky && y < HEIGHT - 1)
		mlx_pixel_put(game->win->mlx, game->win->win, x, y++,
			int_to_hex(0, 186, 255));
	while (y < line + sky && y < HEIGHT - 1)
	{
		side = get_side(ray);
		if (side < 2)
			color = get_pixel(&game, ray->hitx * SCALE, j * SCALE / line, side);
		else
			color = get_pixel(&game, ray->hity * SCALE, j * SCALE / line, side);
		mlx_pixel_put(game->win->mlx, game->win->win, x, y++, color);
		j++;
	}
	while (y < HEIGHT - 1)
		mlx_pixel_put(game->win->mlx, game->win->win, x, y++,
			int_to_hex(255, 186, 100));
}
