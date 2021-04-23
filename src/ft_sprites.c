/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhawick <lhawick@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 22:06:24 by lhawick           #+#    #+#             */
/*   Updated: 2021/04/15 22:06:24 by lhawick          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_sprite(t_list **sprites, int x, int y)
{
	t_sprt	*sprite;

	sprite = callocl(1, sizeof(t_sprt));
	sprite->x = (float)x * SCALE + (SCALE / 2);
	sprite->y = (float)y * SCALE + (SCALE / 2);
	ft_lstadd_back(sprites, ft_lstnew(sprite));
}

void	sort_sprites(t_game **game, float px, float py)
{
	t_list	*sprites;
	t_list	*start;
	t_sprt	*tmp;
	t_sprt	*cur;
	t_sprt	*next;

	sprites = (*game)->sprites;
	start = sprites;
	while (start && start->next)
	{
		while (sprites->next)
		{
			cur = sprites->content;
			next = sprites->next->content;
			if (get_d(px, py, cur->x, cur->y) < get_d(px, py, next->x, next->y))
			{
				tmp = cur;
				sprites->content = sprites->next->content;
				sprites->next->content = tmp;
			}
			sprites = sprites->next;
		}
		start = start->next;
		sprites = start;
	}
}

static	void	draw(t_game *game, t_sprt *sprt, float s_dst, t_txts *txts)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	j = 0;
	while (j++ < sprt->height)
	{
		if (sprt->v_offset + j < 0 || sprt->v_offset + j > game->h)
			continue ;
		while (i++ < sprt->width)
		{
			if (sprt->h_offset + i < 0 || sprt->h_offset + i > game->w
				|| s_dst > game->d_rays[(int)sprt->h_offset + i])
				continue ;
			color = get_pixel(&game, i * txts[4].width / sprt->width,
					j * txts[4].height / sprt->height, 4);
			pixel_put(game->win, sprt->h_offset + i, sprt->v_offset + j, color);
		}
		i = 0;
	}
}

void	draw_sprite(t_game **game, t_sprt *sprt)
{
	float	s_dir;
	float	s_dst;

	s_dir = atan2(sprt->y - (*game)->plr->y, sprt->x - (*game)->plr->x);
	while (s_dir - (*game)->plr->dir > M_PI)
		s_dir -= 2 * M_PI;
	while (s_dir - (*game)->plr->dir < -M_PI)
		s_dir += 2 * M_PI;
	s_dst = get_d((*game)->plr->x, (*game)->plr->y, sprt->x, sprt->y);
	sprt->width = (*game)->txts[4].width / s_dst * SCALE;
	sprt->height = (*game)->txts[4].height / s_dst * SCALE;
	sprt->h_offset = (s_dir - (*game)->plr->dir) * ((*game)->w) / (M_PI_2 / 1.5)
		+ ((*game)->w / 2) - sprt->width / 2;
	sprt->v_offset = (*game)->h / 2;
	draw(*game, sprt, s_dst, (*game)->txts);
}
