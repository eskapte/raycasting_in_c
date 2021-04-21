/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhawick <lhawick@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 20:32:16 by lhawick           #+#    #+#             */
/*   Updated: 2021/04/13 20:32:16 by lhawick          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*create_plr(int x, int y, float dir, t_game **game)
{
	t_plr	*new_plr;

	new_plr = callocl(1, sizeof(t_plr));
	new_plr->x = (float)x * SCALE;
	new_plr->y = (float)y * SCALE;
	new_plr->dir = dir;
	(*game)->plr = new_plr;
}

void	plr_move(int kc, t_game *game)
{
	if (kc == W)
	{
		game->plr->y += STEP * sin(game->plr->dir);
		game->plr->x += STEP * cos(game->plr->dir);
	}
	if (kc == S)
	{
		game->plr->y -= STEP * sin(game->plr->dir);
		game->plr->x -= STEP * cos(game->plr->dir);
	}
	if (kc == A)
	{
		game->plr->x += STEP * sin(game->plr->dir);
		game->plr->y -= STEP * cos(game->plr->dir);
	}
	if (kc == D)
	{
		game->plr->x -= STEP * sin(game->plr->dir);
		game->plr->y += STEP * cos(game->plr->dir);
	}
	if (kc == LEFT || kc == 65361)
		game->plr->dir -= (M_PI_2 / 9);
	if (kc == RIGHT || kc == 65363)
		game->plr->dir += (M_PI_2 / 9);
	render(game);
}
