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
	if ((*game)->plr)
		exit_with_error("you cant create more than one player");
	(*game)->plr = new_plr;
}

static void	move(t_plr *plr, char **map, float dx, float dy)
{
	if (map[(int)((plr->y + STEP * dy) / SCALE)][(int)((plr->x + STEP * dx)
		/ SCALE)] == '1')
		return ;
	plr->x += STEP * dx;
	plr->y += STEP * dy;
}

void	plr_move(int kc, t_game *game)
{
	if (kc == W)
		move(game->plr, game->map, cos(game->plr->dir), sin(game->plr->dir));
	if (kc == S)
		move(game->plr, game->map, -cos(game->plr->dir), -sin(game->plr->dir));
	if (kc == A)
		move(game->plr, game->map, sin(game->plr->dir), -cos(game->plr->dir));
	if (kc == D)
		move(game->plr, game->map, -sin(game->plr->dir), cos(game->plr->dir));
	if (kc == LEFT || kc == 65361)
		game->plr->dir -= (M_PI_2 / 9);
	if (kc == RIGHT || kc == 65363)
		game->plr->dir += (M_PI_2 / 9);
	render(game);
}
