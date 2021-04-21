/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhawick <lhawick@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 20:12:35 by lhawick           #+#    #+#             */
/*   Updated: 2021/04/13 20:12:35 by lhawick          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(t_game *game)
{
	t_list	*fst_sprite;

	fst_sprite = game->sprites;
	ray_cast(game);
	sort_sprites(&game, game->plr->x, game->plr->y);
	while (game->sprites)
	{
		draw_sprite(&game, game->sprites->content);
		game->sprites = game->sprites->next;
	}
	game->sprites = fst_sprite;
	mlx_do_sync(game->win->mlx);
	mlx_put_image_to_window(game->win->mlx, game->win->win, game->win->img,
		0, 0);
}
